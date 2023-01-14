#include "common.h"
#include "HW_GPIO.h"
#include "HW_FTM.h"
#include "HW_PIT.h"


void porta_isr();       //���ж�
void portb_isr();       //���ж�
void pit_isr0();        //PIT0�Д�


void gpio_init();       //io�ڳ�ʼ��
void dma_init();        //dma��ʼ��
void send_image();      //ͼ����
void delayS(uint16 n);   //��ʱ����
void uart_init();       //���ڳ�ʼ��
int chuli_image(int n , int p ,int k);     //����ͼ��
void Motor(uint8 move, uint32 val);
void MotorActuator(int angle);
void ftm_init(void);       //ftm��ʼ��
void pit_init(void);       //pit��ʼ��
int jiaodu(int sudu);
void uart1_init();       //���ڳ�ʼ��
