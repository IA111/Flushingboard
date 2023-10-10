#ifndef __I2C_H__
#define __I2C_H__

unsigned char I2C_ReceiveAck(void);
void I2C_SendAck(unsigned char AckBit);
unsigned char I2C_ReceiveByte(void);
void I2C_SendByte(unsigned char Byte);
void I2C_Stop(void);
void I2C_Start(void);	
#endif