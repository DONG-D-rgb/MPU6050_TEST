#include "main.h"
#include "MPU6050.h"   
#include "stm32f4xx_hal_i2c.h"  
#include "stm32f4xx_hal.h"
#include "stdio.h"
#include "stdint.h"



extern I2C_HandleTypeDef hi2c1;

uint8_t Single_WriteI2C(uint8_t REG_ADD, uint8_t data)
{
	 return HAL_I2C_Mem_Write(&hi2c1,SlaveAddress,REG_ADD,I2C_MEMADD_SIZE_8BIT,&data,1,100);
}
	
uint8_t Single_ReadI2C(uint8_t REG_Address)
{
	uint8_t REG_data = 0xFF;
	HAL_StatusTypeDef status;
	status = HAL_I2C_Mem_Read(&hi2c1,SlaveAddress+1,REG_Address,I2C_MEMADD_SIZE_8BIT,&REG_data,1,100);
	
	if( HAL_OK ==status)
	{
		printf ("读取成功\r\n");
		return REG_data;
	}
	else 
	{
		printf("读取错误\r\n");
		return 0xFF;
	}
}



void Init_MPU (void)
{
	Single_WriteI2C(MPU_60X0_PWR_MGMT_1_REG_ADDR, MPU_60X0_RESET_REG_VALU);   
    HAL_Delay (50);
    Single_WriteI2C(MPU_60X0_PWR_MGMT_1_REG_ADDR, MPU_60X0_PWR_MGMT_1_REG_VALU);  
    Single_WriteI2C(MPU_60X0_USER_CTRL_REG_ADDR, MPU_60X0_USER_CTRL_REG_VALU);  
    Single_WriteI2C(MPU_60X0_SMPLRT_DIV_REG_ADDR, MPU_60X0_SMPLRT_DIV_REG_VALU);  
    Single_WriteI2C(MPU_60X0_CONFIG_REG_ADDR, MPU_60X0_CONFIG_REG_VALU);  
    Single_WriteI2C(MPU_60X0_GYRO_CONFIG_REG_ADDR, MPU_60X0_GYRO_CONFIG_REG_VALU);  
    Single_WriteI2C(MPU_60X0_ACCEL_CONFIG_REG_ADDR, MPU_60X0_ACCEL_CONFIG_REG_VALU);  
    Single_WriteI2C(MPU_60X0_FIFO_EN_REG_ADDR, MPU_60X0_FIFO_EN_REG_VALU);  
}



uint16_t GetData(uint8_t REG_Address)  
{  
    uint8_t H,L;  
    H=Single_ReadI2C(REG_Address);  
    L=Single_ReadI2C(REG_Address+1);  
    return (int16_t)(H<<8)+L;   //合成数据  
}  



void data_Out(void)
{
			int16_t acc_x,acc_y,acc_z,gy_x,gy_y,gy_z;
			printf("获取数据\r\n");
			acc_x= GetData(ACCEL_XOUT_H);
			acc_y= GetData(ACCEL_YOUT_H);
			acc_z= GetData(ACCEL_ZOUT_H);
			gy_x= GetData(GYRO_XOUT_H);
			gy_y= GetData(GYRO_YOUT_H);
			gy_z= GetData(GYRO_ZOUT_H);

			printf("ACC: \r\nX=%d\r\nY=%d\r\nZ=%d \r\n",acc_x,acc_y,acc_z);
			printf("GYRO: \r\nX=%d\r\nY=%d\r\nZ=%d\r\n",gy_x,gy_y,gy_z);
}

void TEST_printID(void)
{
		  printf("readID\r\n");
			uint8_t iic_ID = Single_ReadI2C(0x75);
			HAL_Delay (500);
			HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_10);
			printf("MPU6050 ID = 0x%02X\r\n",iic_ID);
			printf("获取数据\r\n");
}















