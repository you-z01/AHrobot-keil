/**
 * @Author: z
 * @Date: 2024-11-15 
 * @LastEditTime: 2024-11-19 
 * @Description: IIC��������
 * @FilePath: \AHrobot\Peripheral_Driver\iic.c
 */
#include "iic.h"

/****************************************************************************************
 * @description: IIC��ʼ��
 * @return {*}
 ****************************************************************************************/
void IIC_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(IIC_SCL_PORT_RCC | IIC_SDA_PORT_RCC, ENABLE);

	GPIO_InitStructure.GPIO_Pin = IIC_SCL_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(IIC_SCL_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = IIC_SDA_PIN;
	GPIO_Init(IIC_SDA_PORT, &GPIO_InitStructure);

	IIC_SCL = 1;
	IIC_SDA = 1;
}

/****************************************************************************************
 * @description: SDA�������
 * @return {*}
 ****************************************************************************************/
void SDA_OUT(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = IIC_SDA_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(IIC_SDA_PORT, &GPIO_InitStructure);
}

/****************************************************************************************
 * @description: SDA��������
 * @return {*}
 ****************************************************************************************/
void SDA_IN(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = IIC_SDA_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_Init(IIC_SDA_PORT, &GPIO_InitStructure);
}

/****************************************************************************************
 * @description: ����IIC��ʼ�ź�
 * @return {*}
 ****************************************************************************************/
void IIC_Start(void)
{
	SDA_OUT(); // sda�����
	IIC_SDA = 1;
	IIC_SCL = 1;
	delay_us(5);
	IIC_SDA = 0; // START:when CLK is high,DATA change form high to low
	delay_us(6);
	IIC_SCL = 0; // ǯסI2C���ߣ�׼�����ͻ��������
}

/****************************************************************************************
 * @description: ����IICֹͣ�ź�
 * @return {*}
 ****************************************************************************************/
void IIC_Stop(void)
{
	SDA_OUT(); // sda�����
	IIC_SCL = 0;
	IIC_SDA = 0; // STOP:when CLK is high DATA change form low to high
	IIC_SCL = 1;
	delay_us(6);
	IIC_SDA = 1; // ����I2C���߽����ź�
	delay_us(6);
}

/****************************************************************************************
 * @description: �ȴ�Ӧ���źŵ���
 * @return {u8} 1-����Ӧ��ʧ��	0-����Ӧ��ɹ�
 ****************************************************************************************/
u8 IIC_Wait_Ack(void)
{
	u8 tempTime = 0;

	IIC_SDA = 1;
	delay_us(1);
	SDA_IN(); // SDA����Ϊ����
	IIC_SCL = 1;
	delay_us(1);
	while (READ_SDA)
	{
		tempTime++;
		if (tempTime > 250)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL = 0; // ʱ�����0
	return 0;
}

/****************************************************************************************
 * @description: ����ACKӦ��
 * @return {*}
 ****************************************************************************************/
void IIC_Ack(void)
{
	IIC_SCL = 0;
	SDA_OUT();
	IIC_SDA = 0;
	delay_us(2);
	IIC_SCL = 1;
	delay_us(5);
	IIC_SCL = 0;
}

/****************************************************************************************
 * @description: ����NACK��Ӧ��
 * @return {*}
 ****************************************************************************************/
void IIC_NAck(void)
{
	IIC_SCL = 0;
	SDA_OUT();
	IIC_SDA = 1;
	delay_us(2);
	IIC_SCL = 1;
	delay_us(5);
	IIC_SCL = 0;
}

/****************************************************************************************
 * @description: IIC����һ���ֽ�
 * @param {u8} txd ���͵��ֽ�
 * @return {*}
 ****************************************************************************************/
void IIC_Send_Byte(u8 txd)
{
	u8 t;
	SDA_OUT();
	IIC_SCL = 0; // ����ʱ�ӿ�ʼ���ݴ���
	for (t = 0; t < 8; t++)
	{
		if ((txd & 0x80) > 0) // 0x80  1000 0000
			IIC_SDA = 1;
		else
			IIC_SDA = 0;
		txd <<= 1;
		delay_us(2); // ��TEA5767��������ʱ���Ǳ����
		IIC_SCL = 1;
		delay_us(2);
		IIC_SCL = 0;
		delay_us(2);
	}
}

/****************************************************************************************
 * @description: IIC��һ���ֽ�
 * @param {u8} ack =1ʱ������ACK��=0������nACK
 * @return {u8} receive Ӧ����Ӧ��
 ****************************************************************************************/
u8 IIC_Read_Byte(u8 ack)
{
	u8 i, receive = 0;
	SDA_IN(); // SDA����Ϊ����
	for (i = 0; i < 8; i++)
	{
		IIC_SCL = 0;
		delay_us(2);
		IIC_SCL = 1;
		receive <<= 1;
		if (READ_SDA)
			receive++;
		delay_us(1);
	}
	if (!ack)
		IIC_NAck(); // ����nACK
	else
		IIC_Ack(); // ����ACK
	return receive;
}