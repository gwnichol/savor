#include<savor/sd.h>
#include<savor/spi.h>

uint8_t sd_r1;
uint32_t sd_data;

volatile uint8_t * sd_port;
uint8_t sd_cs_mask;

// PRIVATE: Send the arguments of a command
static void inline sendCommand(SD_CMD command, uint32_t args, uint8_t crc){

}

void SD_Initialize(volatile uint8_t * ddr, volatile uint8_t * port, uint8_t mask){
    // Configure SD
    *ddr = *ddr | mask;
    sd_port = port;


}

void SD_SendFullCommand(SD_CMD command, uint32_t args, uint8_t crc, uint8_t ret_length){
    *sd_port = *sd_port & ~sd_cs_mask;

    if(command & ACMD_FLAG){
        SD_SendCommand(APP_CMD);
    }

    SPI_Tranceive((command & ~ACMD_FLAG) | 0x40);

    SPI_Tranceive(args >> 24);
    SPI_Tranceive(args >> 16);
    SPI_Tranceive(args >> 8);
    SPI_Tranceive(args);
    
    SPI_Tranceive(crc);

    sd_r1 = SPI_Receive();

    sd_data = 0;
    for(int i = 1; i < ret_length; i++){
        sd_data = sd_data << 8;
        sd_data |= SPI_Receive();
    }

    // Throw away one last response for the CRC check (CRC verification not supported)
    SPI_Receive();

    *sd_port = *sd_port | sd_cs_mask;
}

// Send a set count of dummy bytes so the SD knows clock period
void SD_SendDummy(char dummy_count){
    *sd_port = *sd_port | sd_cs_mask;

    for(int i = 0; i < dummy_count; i++){
        SPI_Tranceive(0xFF);
    }
}


