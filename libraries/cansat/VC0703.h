/**
 * @file       VC0703.h
 * @author     Dongwon Lee
 * @license    This project is released under the MIT License (MIT)
 * @copyright  Copyright (c) 2018 Dongwon Lee
 * @date       Feb 2018
 * @brief      This is a library for the Cansat JPEG Camera (VC0703 chipset)
 *             This code is modified from Adafruit VC0706 library
 */
 /***************************************************
   This is a library for the Adafruit TTL JPEG Camera (VC0706 chipset)

   Pick one up today in the adafruit shop!
   ------> http://www.adafruit.com/products/397

   These displays use Serial to communicate, 2 pins are required to interface

   Adafruit invests time and resources providing this open source code,
   please support Adafruit and open-source hardware by purchasing
   products from Adafruit!

   Written by Limor Fried/Ladyada for Adafruit Industries.
   BSD license, all text above must be included in any redistribution
  ****************************************************/

 #ifndef VC0703_h
 #define VC0703_h

#include "Arduino.h"


#define VC0703_GEN_VERSION 0x11
#define VC0703_SET_SERIAL_NUMBER 0x21
#define VC0703_SET_PORT 0x24
#define VC0703_RESET  0x26

#define VC0703_READ_DATA 0x30
#define VC0703_WRITE_DATA 0x31
#define VC0703_READ_FBUF 0x32
#define VC0703_GET_FBUF_LEN 0x34
#define VC0703_FBUF_CTRL 0x36
#define VC0703_COMM_MOTION_CTRL 0x37
#define VC0703_COMM_MOTION_STATUS 0x38
#define VC0703_COMM_MOTION_DETECTED 0x39
#define VC0703_MIRROR_CTRL 0x3A
#define VC0703_MIRROR_STATUS 0x3B
#define VC0703_COLOR_CTRL 0x3C
#define VC0703_COLOR_STATUS 0x3D
#define VC0703_POWER_SAVE_CTRL 0x3E
#define VC0703_POWER_SAVE_STATUS 0x3F

#define VC0703_AE_CTRL 0x40
#define VC0703_AE_STATUS 0x41
#define VC0703_MOTION_CTRL 0x42
#define VC0703_MOTION_STATUS 0x43
#define VC0703_TVOUT_CTRL 0x44
#define VC0703_OSD_ADD_CHAR 0x45

#define VC0703_DOWNSIZE_CTRL 0x54
#define VC0703_DOWNSIZE_STATUS 0x55

#define VC0703_GET_FLASH_SIZE 0x60
#define VC0703_ERASE_FLASH_SECTOR 0x61
#define VC0703_ERASE_FLASH_ALL 0x62

#define VC0703_READ_LOGO 0x70
#define VC0703_SET_BIZTMAP 0x71
#define VC0703_BATCH_WRITE 0x80





#define VC0703_STOPCURRENTFRAME 0x0
#define VC0703_STOPNEXTFRAME 0x1
#define VC0703_RESUMEFRAME 0x3
#define VC0703_STEPFRAME 0x2

#define VC0703_640x480 0x00
#define VC0703_320x240 0x11
#define VC0703_160x120 0x22

#define VC0703_MOTIONCONTROL 0x0
#define VC0703_UARTMOTION 0x01
#define VC0703_ACTIVATEMOTION 0x01

#define VC0703_SET_ZOOM 0x52
#define VC0703_GET_ZOOM 0x53

#define CAMERABUFFSIZ 128
#define CAMERADELAY 10


class VC0703 {
 public:

  VC0703(HardwareSerial *ser); // Constructor when using HardwareSerial
  boolean begin(uint16_t baud = 38400);
  boolean reset(void);
  boolean TVon(void);
  boolean TVoff(void);
  boolean takePicture(void);
  uint8_t *readPicture(uint8_t n);
  boolean resumeVideo(void);
  uint32_t frameLength(void);
  char *getVersion(void);
  uint8_t available();
  uint8_t getDownsize(void);
  boolean setDownsize(uint8_t);
  uint8_t getImageSize();
  boolean setImageSize(uint8_t);
  boolean getMotionDetect();
  uint8_t getMotionStatus(uint8_t);
  boolean motionDetected();
  boolean setMotionDetect(boolean f);
  boolean setMotionStatus(uint8_t x, uint8_t d1, uint8_t d2);
  boolean cameraFrameBuffCtrl(uint8_t command);
  uint8_t getCompression();
  boolean setCompression(uint8_t c);

  boolean getPTZ(uint16_t &w, uint16_t &h, uint16_t &wz, uint16_t &hz, uint16_t &pan, uint16_t &tilt);
  boolean setPTZ(uint16_t wz, uint16_t hz, uint16_t pan, uint16_t tilt);

  void OSD(uint8_t x, uint8_t y, char *s); // isnt supported by the chip :(

char* setBaud9600();
char* setBaud19200();
char* setBaud38400();
char* setBaud57600();
char* setBaud115200();

 private:
  uint8_t  serialNum;
  uint8_t  camerabuff[CAMERABUFFSIZ+1];
  uint8_t  bufferLen;
  uint16_t frameptr;

  HardwareSerial *hwSerial;

  void common_init(void);
  boolean runCommand(uint8_t cmd, uint8_t args[], uint8_t argn, uint8_t resp, boolean flushflag = true);
  void sendCommand(uint8_t cmd, uint8_t args[], uint8_t argn);
  uint8_t readResponse(uint8_t numbytes, uint8_t timeout);
  boolean verifyResponse(uint8_t command);
  void printBuff(void);
};

#endif
