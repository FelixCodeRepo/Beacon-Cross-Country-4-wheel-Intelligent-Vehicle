/*************************************************************
             7620����ͷ��������
            ��������
����ͷ   
          ���ݿ�    d0--d7
          ���ж�    b3
          ���ж�    a5 
          pclk      e6
����    ������256000
         rx      c15 
         tx      c14
*///////////////////////////////////////////////
#include "common.h"
#include "image.h"
#include "HW_GPIO.h"
#include "HW_FTM.h"
#include "HW_PIT.h"
#include "math.h"
extern int image_get,Z;    //ͼ��ɼ���ɱ�־
extern int IA;
int16 encoder = 0,tt=0;
//void tinzhi()
//{Motor(1, 0);}
//void houtui()
//{ MotorActuator(-70);
//          Motor(1, 0);
//         delayS(1);
//         Motor(0,3500);
//         delayS(2);
//         Motor(1, 0);
//        delayS(1);
//         MotorActuator(70);
//         Motor(1,3500);
//         delayS(1);}
//void qianjin()
//{Motor(1,3500);}
void main (void)
{   
    int16 tingzhi=1,qidong=0,n=0,sudu=4000;
    gpio_init();        //��ʼ��
    uart1_init();
    dma_init();
    ftm_init();
    pit_init();
    DisableInterrupts;
    enable_irq(PORTB_IRQn);    //��
    enable_irq(PORTA_IRQn);    //��
    EnableInterrupts;
    while(1)
    {
      if(image_get==1) 
      {  
        
        int8 qianzhan=jiaodu(-encoder);     
       if(LPLD_GPIO_Input_b(PTA, 6) == 1)
       { 
         if(-chuli_image(0xef,2,qianzhan)!=70)
        { 
          LPLD_GPIO_Output_b(PTA, 28, 0);               //����
         qidong=1;
        }
        else
        {
          LPLD_GPIO_Output_b(PTA, 28, 1);
        }
        MotorActuator(-chuli_image(0xef,2,qianzhan));
        sudu=Z;
//        if (qidong==1)
//        {
//        Motor(1,n);
//        qidong=0;}
//        else if(fig==1)
//         {Motor(1, 0);}
//        else if(encoder>=0&&nn==1)
//        {Motor(1,n);
//        delayS(1);
//        fig=0;
//        nn=0;
//         }
//        else if(encoder<0||fig==0)
//        { Motor(1, n);
//       fig=0;
//       qidong=1;
//        }
//        else if(encoder==0&&fig==0)
//    {
//      MotorActuator(-70);
//          Motor(1, 0);
//        delayS(1);
//         Motor(0,n);
//         delayS(1);
//         fig=0;
//         nn=1;
//         Motor(1, 0);
//        delayS(1);
//        }
//         LPLD_UART_PutChar(UART1,0xff);
//           if(sudu==0){
//         
//         if(n<10)
//         {
//           int8 acs[2] = {0};
//           if(encoder < 0)
//             encoder = -encoder;
//           acs[0] = (encoder>>8 & 0xff);
//           acs[1] = (encoder &0xff);
//           LPLD_UART_PutChar(UART1,acs[1]);
//         n++;}       }
        if(encoder==0&&tingzhi==0&&tt>3)
        {MotorActuator(-70);
          Motor(1, 0);
         delayS(1);
         Motor(0,2500);
         delayS(1);
         Motor(1, 0);
        delayS(1);
         MotorActuator(70);
         Motor(1,2500);
         delayS(1);
        tingzhi=0;
        }
//        else if(-chuli_image(0xef,2,qianzhan)== 70 && encoder!=0 && tingzhi==0 )
//        {
//          Motor(1,sudu-1500);
//          tingzhi=0;
//          tt++;
//        }
        else if(tingzhi==0||qidong==1||encoder!=0)
        {Motor(1,sudu);
        tingzhi=0;
        tt++;
       }
        else if(tingzhi==1)
        {Motor(1, 0);}
     
         
       }
       else{MotorActuator(-chuli_image(0xef,2,qianzhan));
//       if(-chuli_image(0xef,2,jiaodu(-encoder))==50){
//         
//         if(n<10)
//         {
//           int8 acs[2] = {0};
//           if(encoder < 0)
//             encoder = -encoder;
//           
//           acs[0] = (encoder>>8 & 0xff);
//           acs[1] = (encoder &0xff);
////           LPLD_UART_PutChar(UART4,acs[0]);
//           LPLD_UART_PutChar(UART4,acs[1]);
//         n++;}
//         
//       }
       }
      }
      
      if(tt == 10)
        tt = 10;
}
}
void pit_isr0()
{ 
  encoder = (int16)LPLD_FTM_GetCounter(FTM2);
  //���㹫ʽ
  encoder *= 0.025132;    //������һ���̶���0.025132mm
  encoder /= 5;    //50ms
  LPLD_FTM_ClearCounter(FTM2);
}
