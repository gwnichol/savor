#ifndef SD_H
#define SD_H

// Define the SD SPI Mode Commands that are available to use

#include <avr/io.h>

#define ACMD_FLAG 0x80
#define ACMD(NUM) NUM | ACMD_FLAG

#define GO_IDLE_STATE           CMD0
#define SEND_OP_COND            CMD1
#define SWITCH_FUNC             CMD6
#define SEND_IF_COND            CMD8
#define SEND_CSD                CMD9
#define SEND_CID                CMD10
#define STOP_TRANSMISSION       CMD12
#define SEND_STATUS             CMD13
#define SET_BLOCKLEN            CMD16
#define READ_SINGLE_BLOCK       CMD17
#define READ_MULTIPLE_BLOCK     CMD18
#define WRITE_BLOCK             CMD24
#define WRITE_MULTIPLE_BLOCK    CMD25
#define PROGRAM_CSD             CMD27
#define SET_WRITE_PROT          CMD28
#define CLR_WRITE_PROT          CMD29
#define SEND_WRITE_PROT         CMD30
#define ERASE_WR_BLK_START_ADDR CMD32
#define ERASE_WR_BLK_END_ADDR   CMD33
#define ERASE                   CMD38
#define LOCK_UNLOCK             CMD42
#define APP_CMD                 CMD55
#define GEN_CMD                 CMD56
#define READ_OCR                CMD58
#define CRC_ON_OFF              CMD59

#define SD_STATUS               ACMD13
#define SEND_NUM_WR_BLOCKS      ACMD22
#define SEND_WR_ERASE_COUNT     ACMD23
#define SD_SEND_OP_COND         ACMD41
#define SET_CLR_CARD_DETECT     ACMD42
#define SEND_SCR                ACMD51

typedef enum{
    CMD0  = 0, // GO_IDLE_STATE
    CMD1  = 1, // SEND_OP_COND [32] Reserved, [30] HCS, [29:0] Reserved
    CMD6  = 6, // SWITCH_FUNC, Section 4.2.10
    CMD8  = 8, // SEND_IF_COND, [31:12] Reserved, [11:8] Supply Voltage, [7:0] Check pattern    
    CMD9  = 9, // SEND_CSD, Ask send card-specific data
    CMD10 = 10, // SEND_CID, Ask send card identification
    CMD12 = 12, // STOP_TRANSMISSION, Forces card to stop transmission in MBR op
    CMD13 = 13, // SEND_STATUS, Ask send status reg
    CMD16 = 16, // SET_BLOCKLEN, [31:0] Block length
    CMD17 = 17, // READ_SINGLE_BLOCK, [31:0] Data address
    CMD18 = 18, // READ_MULTIPLE_BLOCK, [31:0] Data address
    CMD24 = 24, // WRITE_BLOCK, [31:0] Data address
    CMD25 = 25, // WRITE_MULTIPLE_BLOCK, [31:0] Data address
    CMD27 = 27, // PROGRAM_CSD, Programing the programmable bits of CSD
    CMD28 = 28, // SET_WRITE_PROT, [31:0] Data address
    CMD29 = 29, // CLR_WRITE_PROT, [31:0] Data address
    CMD30 = 30, // SEND_WRITE_PROT, [31:0] Data address
    CMD32 = 32, // ERASE_WR_BLK_START_ADDR, [31:0] Data address
    CMD33 = 33, // ERASE_WR_BLK_END_ADDR, [31:0] Data address
    CMD38 = 38, // ERASE, [31:0] Data address
    CMD42 = 42, // LOCK_UNLOCK, [31:0] Reserved
    CMD55 = 55, // APP_CMD
    CMD56 = 56, // GEN_CMD, [0] RD/WR
    CMD58 = 58, // READ_OCR, Read the OCR register
    CMD59 = 59, // CRC_ON_OFF, [0] CRC option

    ACMD13 = ACMD(13), // SD_STATUS, Send the SD Status from Table 4-44
    ACMD22 = ACMD(22), // SEND_NUM_WR_BLOCKS, Send the number of blocks written without error
    ACMD23 = ACMD(23), // SEND_WR_ERASE_COUNT, Send the number of blocks erased without error
    ACMD41 = ACMD(41), // SD_SEND_OP_COND, [30] HCS
    ACMD42 = ACMD(42), // SET_CLR_CARD_DETECT, [0] set_cd
    ACMD51 = ACMD(51), // SEND_SCR, Read the SD Config Register
} SD_CMD;

#define R1 0
#define R2 1


// R1 Response Bits
#define R1_IN_IDLE_STATE        0
#define R1_ERASE_RESET          1
#define R1_ILLEGAL_COMMAND      2
#define R1_COM_CRC_ERROR        3
#define R1_ERASE_SEQUENCE_ERROR 4
#define R1_ADDRESS_ERROR        5
#define R1_PARAMETER_ERROR      6

// R2 Response Bits
#define R2_CARD_LOCKED          0
#define R2_WP_ERASE_SKIP        1
#define R2_ERROR                2
#define R2_CC_ERROR             3
#define R2_CARD_ECC_FAILED      4
#define R2_WP_VIOLATION         5
#define R2_ERASE_PARAM          6
#define R2_OUT_OF_RANGE         7

// Repsonce types and their length
#define SD_R1 1
#define SD_R2 2
#define SD_R3 5
#define SD_R7 5

// Command Specific Bits or Shifts
#define CMD8_VHS 8
#define CMD8_CHECK 0
#define CMD8_CHECK_BITS 0xA5

extern uint8_t sd_r1;
extern uint32_t sd_data;

extern volatile uint8_t * sd_port;
extern uint8_t sd_cs_mask;


void SD_Initialize(volatile uint8_t * ddr, volatile uint8_t * port, uint8_t mask);

// Default CRC is Calculated ahead of time
#define SD_SendCommand(command) ({\
    switch(command){\
        case GO_IDLE_STATE:\
            SD_SendFullCommand(GO_IDLE_STATE, 0x00000000, 0x95, SD_R1); \
            break;\
        case SEND_IF_COND:\
            SD_SendFullCommand(SEND_IF_COND, (0x1 << CMD8_VHS) | (CMD8_CHECK_BITS << CMD8_CHECK), 0x81, SD_R7); \
            break;\
        case APP_CMD:\
            SD_SendFullCommand(APP_CMD, 0x00000000, 0xF1, SD_R1); \
            break;\
        default:\
            SD_SendFullCommand(command, sd_data, 0x00, SD_R1);\
            break;\
    }\
})

void SD_SendFullCommand(SD_CMD command, uint32_t args, uint8_t crc, uint8_t ret_length);
void SD_SendDummy(char dummy_count);


#endif
