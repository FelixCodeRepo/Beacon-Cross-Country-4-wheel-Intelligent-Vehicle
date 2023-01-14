#include "common.h"
#include "HW_GPIO.h"
#include "HW_FTM.h"
#include "HW_PIT.h"


void porta_isr();       //场中断
void portb_isr();       //行中断
void pit_isr0();        //PIT0中斷


void gpio_init();       //io口初始化
void dma_init();        //dma初始化
void send_image();      //图像发送
void delayS(uint16 n);   //延时函数
void uart_init();       //串口初始化
int chuli_image(int n , int p ,int k);     //处理图像
void Motor(uint8 move, uint32 val);
void MotorActuator(int angle);
void ftm_init(void);       //ftm初始化
void pit_init(void);       //pit初始化
int jiaodu(int sudu);
void uart1_init();       //串口初始化
