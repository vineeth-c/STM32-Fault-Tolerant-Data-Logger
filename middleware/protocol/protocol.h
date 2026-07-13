#ifndef PROTOCOL_H
#define PROTOCOL_H
#include <stddef.h>
#include <stdint.h>
#include "status.h"
#include "project_config.h"
#define PROTOCOL_SOF0 0xA5u
#define PROTOCOL_SOF1 0x5Au
#define PROTOCOL_VERSION 1u
typedef enum { MSG_PING=1,MSG_GET_DEVICE_INFO=2,MSG_GET_HEALTH=3,MSG_GET_DIAGNOSTICS=4,MSG_TAKE_SAMPLE=5,MSG_GET_LATEST_SAMPLE=6,MSG_READ_LOG=7,MSG_ERASE_LOG=8,MSG_GET_CRASH_RECORD=9,MSG_CLEAR_CRASH_RECORD=10,MSG_REBOOT=11,MSG_ENTER_BOOTLOADER=12,MSG_BEGIN_FIRMWARE_UPDATE=13,MSG_WRITE_FIRMWARE_CHUNK=14,MSG_FINALIZE_FIRMWARE_UPDATE=15,MSG_GET_UPDATE_STATUS=16 } protocol_message_t;
typedef struct {uint8_t version,type,flags,sequence;uint16_t length;uint8_t payload[PROTOCOL_MAX_PAYLOAD];} protocol_frame_t;
typedef enum {PARSER_SOF0,PARSER_SOF1,PARSER_HEADER,PARSER_PAYLOAD,PARSER_CRC} parser_state_t;
typedef struct {parser_state_t state;uint8_t scratch[6u+PROTOCOL_MAX_PAYLOAD+4u];size_t index,needed;uint32_t crc_failures,resets;} protocol_parser_t;
void protocol_parser_init(protocol_parser_t*);
status_t protocol_parser_feed(protocol_parser_t*,uint8_t,protocol_frame_t*,int*);
status_t protocol_encode(const protocol_frame_t*,uint8_t*,size_t,size_t*);
#endif
