#ifndef __MPU6050_H
#define __MPU6050_H


#include "stdint.h"
#define	SMPLRT_DIV		0x19	//???????????????????0x07(125Hz)
#define	CONFIG			0x1A	//?????????????????0x06(5Hz)
#define	GYRO_CONFIG		0x1B	//???????????????¦¶?????????0x18(?????2000deg/s)
#define	ACCEL_CONFIG	0x1C	//??????????????¦¶???????????????????0x01(?????2G??5Hz)
#define	ACCEL_XOUT_H	0x3B
#define	ACCEL_XOUT_L	0x3C
#define	ACCEL_YOUT_H	0x3D
#define	ACCEL_YOUT_L	0x3E
#define	ACCEL_ZOUT_H	0x3F
#define	ACCEL_ZOUT_L	0x40
#define	TEMP_OUT_H		0x41
#define	TEMP_OUT_L		0x42
#define	GYRO_XOUT_H		0x43
#define	GYRO_XOUT_L		0x44	
#define	GYRO_YOUT_H		0x45
#define	GYRO_YOUT_L		0x46
#define	GYRO_ZOUT_H		0x47
#define	GYRO_ZOUT_L		0x48
#define	PWR_MGMT_1		0x6B		//????????????????0x00(????????)
#define	WHO_AM_I			0x75	//IIC????????(??????0x68?????)
#define	SlaveAddress	0xD0		//IIC§Õ???????????????+1????

#define MPU_60X0_PWR_MGMT_1_REG_ADDR        0x6B  
#define MPU_60X0_USER_CTRL_REG_ADDR         0x6A  
#define MPU_60X0_SMPLRT_DIV_REG_ADDR        0x19  
#define MPU_60X0_CONFIG_REG_ADDR            0x1A  
#define MPU_60X0_GYRO_CONFIG_REG_ADDR       0x1B  
#define MPU_60X0_ACCEL_CONFIG_REG_ADDR      0x1C  
#define MPU_60X0_FIFO_EN_REG_ADDR           0x23  
  
#define MPU_60X0_RESET_REG_VALU             0x80  
#define MPU_60X0_PWR_MGMT_1_REG_VALU        0x09    // Disable temperature sensor, PLL with X axis gyroscope reference  
#define MPU_60X0_USER_CTRL_REG_VALU         0x45    // Enable FIFO. Reset FIFO and signal paths for all sensors  
#define MPU_60X0_SMPLRT_DIV_REG_VALU        0x00    // DLPF_CFG is 0x01, so Gyroscope Output Rate = 1kHz, divided by 1, still 1kHz  
#define MPU_60X0_CONFIG_REG_VALU            0x03    // 184Hz 2.0ms 188Hz 1.9ms 1kHz. So there will be 6x2 bytes new data in FIFO every 1ms  
#define MPU_60X0_GYRO_CONFIG_REG_VALU       0x08    // Gyroscope works at 500dps. If selftest is needed, REMEMBER to put this to 250dps  
#define MPU_60X0_ACCEL_CONFIG_REG_VALU      0x08    // Accelerometer works at 4g range. If selftest is needed, REMEMBER to put this to 8g range  
#define MPU_60X0_FIFO_EN_REG_VALU           0x78    // Only enable accel and gyro  

uint8_t Single_WriteI2C(uint8_t REG_ADD, uint8_t data);
uint8_t Single_ReadI2C(uint8_t REG_Address);
void Init_MPU (void);
uint16_t GetData(uint8_t REG_Address)  ;
void TEST_printID(void);
void data_Out(void);




#endif
