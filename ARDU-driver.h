
#ifndef __ARDU_H__
#define __ARDU_H__

#pragma systemFile

#ifndef __COMMON_H__
	#include "common.h"
#endif

//*******************************************************************************
// REGISTER LOCATIONS AND COMMANDS for the Arduino Sensor
//*******************************************************************************
#define ARDU_I2C_ADDR   		0x0A  /*!< I2C address used by the ARDU */
#define ARDU_CMD_REG    		0x30  /*!< Register used for issuing commands */
#define ARDU_PING           0x1E  /*!< Register used for checking if arduino is connected */
#define ARDU_SLEEP          0x09  /*!< Register used put to sleep*/

#define US1 0
#define US2 1
#define US3 2
#define US4 3

// R = Reverse
// S = Stop
// F = Forward

#define ARDU_US             26
#define ARDU_US1            0x1A
#define ARDU_US2            0x1B
#define ARDU_US3            0x1C
#define ARDU_US4            0x1D

#define ARDU_SERVO1_R       0x50  /*!< Referse Reg for servo*/
#define ARDU_SERVO1_S       0x51  /*!< Stop Reg for servo*/
#define ARDU_SERVO1_F       0x52  /*!< Forward Reg for servo*/

#define ARDU_SERVO2_R       0x55  /*!< Referse Reg for servo*/
#define ARDU_SERVO2_S       0x56  /*!< Stop Reg for servo*/
#define ARDU_SERVO2_F       0x57  /*!< Forward Reg for servo*/

#define ARDU_SERVO3_R       0x5A  /*!< Referse Reg for servo*/
#define ARDU_SERVO3_S       0x5B  /*!< Stop Reg for servo*/
#define ARDU_SERVO3_F       0x5C  /*!< Forward Reg for servo*/

#define ARDU_SERVO4_R       0x60  /*!< Referse Reg for servo*/
#define ARDU_SERVO4_S       0x61  /*!< Stop Reg for servo*/
#define ARDU_SERVO4_F       0x62  /*!< Forward Reg for servo*/

tByteArray ARDU_I2CRequest;       /*!< Array to hold I2C command data */
tByteArray ARDU_I2CReply;         /*!< Array to hold I2C reply data */
ubyte oneByte2;

//*******************************************************************************
// PUBLIC Arduino functions
//*******************************************************************************
bool ARDUinit(tSensors link);		                            /*!< Set up arduino sensor type */
//bool ARDUset_servo(tSensors link,int servo, int dir);          /*!< Set servo speed*/

bool ARDUwakeUp(tSensors link);
bool ARDUsleep(tSensors link);
//*******************************************************************************
// INTERNAL USE ONLY - Arduino functions - used by the above
//*******************************************************************************
bool _arduino_cmd(tSensors link, ubyte cmd);                      /*!< Send a command to the arduino */
bool _arduino_write(tSensors link, ubyte regToWrite, ubyte data);  /*!< Write to a arduino Register */
bool _arduino_read(tSensors link, ubyte regToRead, ubyte &retval); /*!< Read one ubyte from a arduino Register */
bool _arduino_read(tSensors link, ubyte regToRead, int numBytes, tByteArray &pDatag);  /*!< Read data from a arduino Register */

//*******************************************************************************
// FUNCTION DEFINITIONS
//*******************************************************************************

bool _arduino_cmd(tSensors link, ubyte cmd) {
  ARDU_I2CRequest[0] = 3;             // Message size
  ARDU_I2CRequest[1] = ARDU_I2C_ADDR;   // I2C Address
  ARDU_I2CRequest[2] = ARDU_CMD_REG;    // Register used for issuing commands
  ARDU_I2CRequest[3] = cmd;           // Command to be executed

  return writeI2C(link, ARDU_I2CRequest, 0);
}


/**
 * This function writes data to a register in the ARDU sensor over I2C.
 *
 * Note: this is an internal function and should not be caARDUed directly.
 * @param link the sensor port number
 * @param regToWrite the register to write to
 * @param data the value to write to the register
 * @return true if no error occured, false if it did
 */

bool _arduino_write(tSensors link, ubyte regToWrite, ubyte data) {

  memset(ARDU_I2CRequest, 0, sizeof(tByteArray));
	ARDU_I2CRequest[0] = 3;             // Message size
  ARDU_I2CRequest[1] = ARDU_I2C_ADDR;   // I2C Address
  ARDU_I2CRequest[2] = regToWrite;    // Register address to set
  ARDU_I2CRequest[3] = data;          // value to place in register address

  if (!writeI2C(link, ARDU_I2CRequest, 0))
		return false;
	return true;
}


/**
 * This function reads one ubyte from a register in the ARDU sensor over I2C.
 *
 * Note: this is an internal function and should not be caARDUed directly.
 * @param link the sensor port number
 * @param regToRead the register to read from
 * @param retval the ubyte in which to store the reply
 * @return true if no error occured, false if it did
 */
bool _arduino_read(tSensors link, ubyte regToRead, ubyte &retval) {
	memset(ARDU_I2CRequest, 0, sizeof(ARDU_I2CRequest));
	ARDU_I2CRequest[0] =  2;
	ARDU_I2CRequest[1] =  ARDU_I2C_ADDR;
	ARDU_I2CRequest[2] =  regToRead;

  if (!writeI2C(link, ARDU_I2CRequest, 1))
    return false;

  if (!readI2C(link, ARDU_I2CReply, 1))
    return false;

  retval = (int)ARDU_I2CReply[0];
  return true;
}


/**
 * This function reads multiple bytes from a register in the ARDU sensor over I2C.
 *
 * Note: this is an internal function and should not be caARDUed directly.
 * @param link the sensor port number
 * @param regToRead the register to read from
 * @param numBytes the number of bytes to read
 * @param pDatag tByteArray to store reply
 * @return true if no error occured, false if it did
 */
bool _arduino_read(tSensors link, ubyte regToRead, int numBytes, tByteArray &pDatag) {
	memset(ARDU_I2CRequest, 0, sizeof(tByteArray));
	memset(pDatag, 0, sizeof(tByteArray));

	ARDU_I2CRequest[0] =  2;
	ARDU_I2CRequest[1] =  ARDU_I2C_ADDR;
	ARDU_I2CRequest[2] =  regToRead;


  if (!writeI2C(link, ARDU_I2CRequest, numBytes))
    return false;

  if (!readI2C(link, ARDU_I2CReply, numBytes))
    return false;

  // copy the result into the array to be returned.
  memcpy(pDatag, ARDU_I2CReply, sizeof(tByteArray));
  return true;
}

bool ARDUinit(tSensors link) {
	nI2CBytesReady[link] = 0;
	SensorType[link] = sensorI2CCustom;
	if (!ARDUwakeUp(link))
	  return false;
	return true;
}

bool ARDUwakeUp(tSensors link){
  if (!_arduino_read(link,ARDU_PING,oneByte2))
	  return false;

	writeDebugStreamLine("RET:%i",oneByte2);

	if(oneByte2==0)
	  return false;


  return true;
}

bool ARDUsleep(tSensors link){
  if (!_arduino_read(link,ARDU_SLEEP,oneByte2))
	  return false;
  return true;
}

bool ARDUset_servo(tSensors link,int servo, int dir){

  int RegToWrite;

  switch(servo){
    case 1:
      RegToWrite=ARDU_SERVO1_S;
      break;
    case 2:
      RegToWrite=ARDU_SERVO2_S;
      break;
    case 3:
      RegToWrite=ARDU_SERVO3_S;
      break;
    case 4:
      RegToWrite=ARDU_SERVO4_S;
      break;
    default:
      return false;
  }

  if(dir<-1 || dir>1){
    return false;
  }
  RegToWrite+=dir;
  nI2CBytesReady[link] = 0;
	SensorType[link] = sensorI2CCustom;
	if (!_arduino_read(link,RegToWrite,oneByte2))
	  return false;
	return true;
}

#define GARRA_H_ABRE  1
#define GARRA_H_FECHA -1
#define GARRA_H_PARA  0

sub GARRA_H(tSensors link, int dir){
  ARDUset_servo(link,3,dir*-1);
  ARDUset_servo(link,4,dir);
}


#define GARRA_V_SOBE  1
#define GARRA_V_DESCE -1
#define GARRA_V_PARA  0

sub GARRA_V(tSensors link, int dir){
  ARDUset_servo(link,1,dir*-1);
  ARDUset_servo(link,2,dir);
}

int ReadUS(tSensors link, int Sensor)
{
  memset(ARDU_I2CRequest, 0, sizeof(tByteArray));

  ARDU_I2CRequest[0] = 2;               // Number of bytes in I2C command
  ARDU_I2CRequest[1] = ARDU_I2C_ADDR;   // I2C address of compass sensor
  ARDU_I2CRequest[2] = ARDU_US + Sensor;         // Set write address to sensor mode register

  if (!writeI2C(link, ARDU_I2CRequest, 2)){
    ClearSounds();
    PlaySound(soundException);
    return -1;
  }

  if (!readI2C(link, ARDU_I2CReply, 2)){
    ClearSounds();
    PlaySound(soundException);
    return -1;
  }

  //writeDebugStreamLine("------");
  //writeDebugStreamLine("A:%i | B:%i | C:%i | D:%i | E:%i" ,ARDU_I2CReply[0],ARDU_I2CReply[1],ARDU_I2CReply[2],ARDU_I2CReply[3],ARDU_I2CReply[4]);
  // Result is made up of two bytes.  Reassemble for final heading.
  return ARDU_I2CReply[0];
}



bool ReadAllUS(tSensors link,tByteArray &Return)
{
  memset(ARDU_I2CRequest, 0, sizeof(tByteArray));

  ARDU_I2CRequest[0] = 2;               // Number of bytes in I2C command
  ARDU_I2CRequest[1] = ARDU_I2C_ADDR;   // I2C address of arduino sensor
  ARDU_I2CRequest[2] = ARDU_US;         // Set write address to sensor mode register

  if (!writeI2C(link, ARDU_I2CRequest, 3)){
    ClearSounds();
    PlaySound(soundException);
    return false;
  }

  if (!readI2C(link, ARDU_I2CReply, 3)){
    ClearSounds();
    PlaySound(soundException);
    return false;
  }

  writeDebugStreamLine("A:%i | B:%i | C:%i" ,ARDU_I2CReply[0],ARDU_I2CReply[1],ARDU_I2CReply[2]);

  // Result is made up of two bytes.  Reassemble for final heading.
  memcpy(Return, ARDU_I2CReply, sizeof(tByteArray));
  return true;
}

bool ReadAllUS_short(tSensors link,tByteArray &Return)
{
  memset(ARDU_I2CRequest, 0, sizeof(tByteArray));

  ARDU_I2CRequest[0] = 2;               // Number of bytes in I2C command
  ARDU_I2CRequest[1] = ARDU_I2C_ADDR;   // I2C address of arduino sensor
  ARDU_I2CRequest[2] = 0x1F;         // Set write address to sensor mode register

  if (!writeI2C(link, ARDU_I2CRequest, 3)){
    ClearSounds();
    PlaySound(soundException);
    return false;
  }

  if (!readI2C(link, ARDU_I2CReply, 3)){
    ClearSounds();
    PlaySound(soundException);
    return false;
  }


  // Result is made up of two bytes.  Reassemble for final heading.
  memcpy(Return, ARDU_I2CReply, sizeof(tByteArray));

  writeDebugStreamLine("A:%i | B:%i | C:%i" ,ARDU_I2CReply[0],ARDU_I2CReply[1],ARDU_I2CReply[2]);

  return true;
}

bool PingUS(tSensors link){

  nI2CBytesReady[link] = 0;
	if (!_arduino_read(link,0x1E,oneByte2)){
    ClearSounds();
    PlaySound(soundException);
	  return false;
	}

	return true;
}

int ReadTouch(tSensors link)
{
  memset(ARDU_I2CRequest, 0, sizeof(tByteArray));

  ARDU_I2CRequest[0] = 2;               // Number of bytes in I2C command
  ARDU_I2CRequest[1] = ARDU_I2C_ADDR;   // I2C address of compass sensor
  ARDU_I2CRequest[2] = 0x70;            // Set write address to sensor mode register

  if (!writeI2C(link, ARDU_I2CRequest, 1)){
    ClearSounds();
    PlaySound(soundException);
    return -1;
  }

  if (!readI2C(link, ARDU_I2CReply, 1)){
    ClearSounds();
    PlaySound(soundException);
    return -1;
  }

  //writeDebugStreamLine("------");
  //writeDebugStreamLine("TOUCH = %i" ,ARDU_I2CReply[0]);
  // Result is made up of two bytes.  Reassemble for final heading.
  return ARDU_I2CReply[0];
}

#endif // __ARDU_H__
