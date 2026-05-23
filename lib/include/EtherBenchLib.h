/**
 * @file    EtherBenchLib.h
 * @author  l.heywang <leonard.heywang@proton.me>
 * @brief   Define the serial protocol used for the EtherBench serial library.
 *          It aim to extend the abilities of the GUI by serializing metadata
 *          around a payload.
 *          On the GUI, you then be able to sort the printed messages depending
 *          on the different metadata.
 * @version 0.1
 * @date    2026-05-23
 *
 * @copyright Copyright (c) 2026
 *
 */
#ifndef _ETHERBENCH_LIB_H_
#define _ETHERBENCH_LIB_H_

/*****************************************************************************/
/*                                  CONFIG                                   */
/*****************************************************************************/
/*
 * Uncomment to use the extended format, which span over 256 bytes rather
 * than 64.
 * This enable to add more data, and more metadata over the link. If you're
 * using USB-CDC, make sure to be able to handle the split, as a packet is
 * limited to 64 bytes.
 *
 * This flag can also be added before including the file, or as a compiler flag:
 * -DETHERBENCH_LIB_EXTENDED_FRAME
 */
// #define ETHERBENCH_LIB_EXTENDED_FRAME

/*****************************************************************************/
/*                                  INCLUDES                                 */
/*****************************************************************************/
#ifdef __cplusplus
#include <cstdint>
#include <string>
#else
#include <stdint.h>
#include <string.h>
#endif /* __cplusplus */

/*****************************************************************************/
/*                                  DEFINES                                  */
/*****************************************************************************/
#ifdef ETHERBENCH_LIB_EXTENDED_FRAME
#pragma message "[EtherBenchLib] : Using the extended frame format"
#define ETHERBENCH_LIB_BUFFER_MAX_SIZE 256
#define ETHERBENCH_LIB_PAYLOAD_MAX_SIZE 234
#define ETHERBENCH_LIB_MARKER 0xEB1B
#else
#define ETHERBENCH_LIB_BUFFER_MAX_SIZE 64
#define ETHERBENCH_LIB_PAYLOAD_MAX_SIZE 52
#define ETHERBENCH_LIB_MARKER 0xEBED
#endif /* ETHERBENCH_LIB_EXTENDED_FRAME */

/*****************************************************************************/
/*                                    ENUMS                                  */
/*****************************************************************************/

typedef enum {
  // Default value
  ETHERBENCH_SOURCE_NONE = 0x00, ///< Default source of logs

  // Buses
  ETHERBENCH_SOURCE_USART0 = 0x02, ///< This message came from USART 0
  ETHERBENCH_SOURCE_USART1 = 0x03, ///< This message came from USART 1
  ETHERBENCH_SOURCE_USART2 = 0x04, ///< This message came from USART 2
  ETHERBENCH_SOURCE_SPI0 = 0x05,   ///< This message came from SPI 0
  ETHERBENCH_SOURCE_SPI1 = 0x06,   ///< This message came from SPI 1
  ETHERBENCH_SOURCE_SPI2 = 0x07,   ///< This message came from SPI 2
  ETHERBENCH_SOURCE_I2C0 = 0x08,   ///< This message came from I2C 0
  ETHERBENCH_SOURCE_I2C1 = 0x09,   ///< This message came from I2C 1
  ETHERBENCH_SOURCE_I2C2 = 0x0A,   ///< This message came from I2C 2
  ETHERBENCH_SOURCE_CAN0 = 0x0B,   ///< This message came from CAN 0

  // Chips, is there's multiple on the DUT
  ETHERBENCH_SOURCE_MCU1 = 0x10, ///< This message came from MCU 0
  ETHERBENCH_SOURCE_MCU2 = 0x11, ///< This message came from MCU 1
  ETHERBENCH_SOURCE_MCU3 = 0x12, ///< This message came from MCU 2
  ETHERBENCH_SOURCE_FPGA = 0x13, ///< This message came from FPGA
  ETHERBENCH_SOURCE_MPU = 0x14,  ///< This message came from MPU

  // Sensors, from any types they could
  ETHERBENCH_SOURCE_SENSOR0 = 0x20,  ///< This message came from SENSOR 0
  ETHERBENCH_SOURCE_SENSOR1 = 0x21,  ///< This message came from SENSOR 1
  ETHERBENCH_SOURCE_SENSOR2 = 0x22,  ///< This message came from SENSOR 2
  ETHERBENCH_SOURCE_SENSOR3 = 0x23,  ///< This message came from SENSOR 3
  ETHERBENCH_SOURCE_SENSOR4 = 0x24,  ///< This message came from SENSOR 4
  ETHERBENCH_SOURCE_SENSOR5 = 0x25,  ///< This message came from SENSOR 5
  ETHERBENCH_SOURCE_SENSOR6 = 0x26,  ///< This message came from SENSOR 6
  ETHERBENCH_SOURCE_SENSOR7 = 0x27,  ///< This message came from SENSOR 7
  ETHERBENCH_SOURCE_SENSOR8 = 0x28,  ///< This message came from SENSOR 8
  ETHERBENCH_SOURCE_SENSOR9 = 0x29,  ///< This message came from SENSOR 9
  ETHERBENCH_SOURCE_SENSOR10 = 0x2A, ///< This message came from SENSOR 10
  ETHERBENCH_SOURCE_SENSOR11 = 0x2B, ///< This message came from SENSOR 11
  ETHERBENCH_SOURCE_SENSOR12 = 0x2C, ///< This message came from SENSOR 12
  ETHERBENCH_SOURCE_SENSOR13 = 0x2D, ///< This message came from SENSOR 13
  ETHERBENCH_SOURCE_SENSOR14 = 0x2E, ///< This message came from SENSOR 14
  ETHERBENCH_SOURCE_SENSOR15 = 0x2F, ///< This message came from SENSOR 15

  ETHERBENCH_SOURCE_CUSTOM0 = 0xF0,  ///< This message came from CUSTOM 0
  ETHERBENCH_SOURCE_CUSTOM1 = 0xF1,  ///< This message came from CUSTOM 1
  ETHERBENCH_SOURCE_CUSTOM2 = 0xF2,  ///< This message came from CUSTOM 2
  ETHERBENCH_SOURCE_CUSTOM3 = 0xF3,  ///< This message came from CUSTOM 3
  ETHERBENCH_SOURCE_CUSTOM4 = 0xF4,  ///< This message came from CUSTOM 4
  ETHERBENCH_SOURCE_CUSTOM5 = 0xF5,  ///< This message came from CUSTOM 5
  ETHERBENCH_SOURCE_CUSTOM6 = 0xF6,  ///< This message came from CUSTOM 6
  ETHERBENCH_SOURCE_CUSTOM7 = 0xF7,  ///< This message came from CUSTOM 7
  ETHERBENCH_SOURCE_CUSTOM8 = 0xF8,  ///< This message came from CUSTOM 8
  ETHERBENCH_SOURCE_CUSTOM9 = 0xF9,  ///< This message came from CUSTOM 9
  ETHERBENCH_SOURCE_CUSTOM10 = 0xFA, ///< This message came from CUSTOM 10
  ETHERBENCH_SOURCE_CUSTOM_DEF =
      0xFF, ///< This message configure a custom source.

} EtherBenchLib_Source;

typedef enum {
  ETHERBENCH_FIELD_SOURCE = 0x10,    ///< Modify the source bytes
  ETHERBENCH_FIELD_PAYLOAD = 0x20,   ///< Modify the payload bytes
  ETHERBENCH_FIELD_TIMESTAMP = 0x30, ///< Modify the timestamps bytes

#ifdef ETHERBENCH_LIB_EXTENDED_FRAME
  ETHERBENCH_FIELD_TYPE = 0x40, ///< Modify the type bytes
  ETHERBENCH_FIELD_ID = 0x50,   ///< Modify the id bytes

#endif /* ETHERBENCH_LIB_EXTENDED_FRAME */

} EtherBenchLib_Field;

#ifdef ETHERBENCH_LIB_EXTENDED_FRAME
typedef enum {
  // Default
  ETHERBENCH_TYPE_NONE = 0x00, ///< Unknown type

  // Basic types
  ETHERBENCH_TYPE_STR = 0x01, ///< Shown as a string
  ETHERBENCH_TYPE_INT = 0x02, ///< Shown as integer (1/2/4/8 first bytes only).
  ETHERBENCH_TYPE_FLOAT = 0x03, ///< Shown as a float (4 bytes)
  ETHERBENCH_TYPE_LOG = 0x10,   ///< Shown as a log.

  // Complex types
  ETHERBENCH_TYPE_CUSTOM0 = 0xF0,    ///< Shown as a custom type, slot 0
  ETHERBENCH_TYPE_CUSTOM1 = 0xF1,    ///< Shown as a custom type, slot 1
  ETHERBENCH_TYPE_CUSTOM2 = 0xF2,    ///< Shown as a custom type, slot 2
  ETHERBENCH_TYPE_CUSTOM3 = 0xF3,    ///< Shown as a custom type, slot 3
  ETHERBENCH_TYPE_CUSTOM4 = 0xF4,    ///< Shown as a custom type, slot 4
  ETHERBENCH_TYPE_CUSTOM5 = 0xF5,    ///< Shown as a custom type, slot 5
  ETHERBENCH_TYPE_CUSTOM6 = 0xF6,    ///< Shown as a custom type, slot 6
  ETHERBENCH_TYPE_CUSTOM7 = 0xF7,    ///< Shown as a custom type, slot 7
  ETHERBENCH_TYPE_CUSTOM8 = 0xF8,    ///< Shown as a custom type, slot 8
  ETHERBENCH_TYPE_CUSTOM9 = 0xF9,    ///< Shown as a custom type, slot 9
  ETHERBENCH_TYPE_CUSTOM10 = 0xFA,   ///< Shown as a custom type, slot 10
  ETHERBENCH_TYPE_CUSTOM_DEF = 0xFF, ///< Define a type on the receiver GUI.

} EtherBenchLib_DataType;
#endif /* ETHERBENCH_LIB_EXTENDED_FRAME */

/*****************************************************************************/
/*                                    STRUCT                                 */
/*****************************************************************************/

typedef struct EtherBenchLib_Message __attribute__((packed)) {

  // Common header and initial metadata
  uint16_t header; ///< Constant header to mark start of message
  uint16_t size;   ///< Mark the size of the message. Over 16 bit for support of
                   ///< even larger size
  uint8_t source;  ///< Source byte

  // Payload
  uint8_t payload[ETHERBENCH_LIB_PAYLOAD_MAX_SIZE]; ///< Message payload, user
                                                    ///< defined

// Timestamp
#ifndef ETHERBENCH_LIB_EXTENDED_FRAME
  uint32_t timestamp; ///< Timestamp over 32 bits in STANDARD mode
#else
  uint64_t timestamp; ///< Timestamp over 64 bits in EXTENDED mode
#endif /* ETHERBENCH_LIB_EXTENDED_FRAME */

// Additionnal metadata
#ifdef ETHERBENCH_LIB_EXTENDED_FRAME
  uint16_t buffer_id; ///< A buffer ID, to further sort the message from the
                      ///< same source
  uint8_t type;       ///< Mark the data type, for the GUI to sort them
#endif                /* ETHERBENCH_LIB_EXTENDED_FRAME */

// Checksum byte
#ifndef ETHERBENCH_LIB_EXTENDED_FRAME
  uint8_t checksum; ///< Xored the whole message until here to ensure the
                    ///< message has been correctly transfered
#else
  uint32_t checksum;  ///< CRC32 of the message. This is more reliable than a
                      ///< classical XOR.
#endif /* ETHERBENCH_LIB_EXTENDED_FRAME */

  // Final marker
  uint8_t footer[2]; ///< End marker. Constant to 0xEB0A, to remain compatible
                     ///< with standard terminals (0x0A is '\n')
};

#endif /* _ETHERBENCH_LIB_H_ */

/*****************************************************************************/
/*                                    FUNCTIONS                               */
/*****************************************************************************/