#include "image.h"
#include "common.h"
#include "HW_GPIO.h"
#include "math.h"
#define H 309         
#define V 240


GPIO_InitTypeDef pta_init;//OV场信号接口初始化：PTA5-V
GPIO_InitTypeDef ptb_init;//OV行信号接口初始化：PTB3-H
GPIO_InitTypeDef pte_init;//OV PCLK信号接口初始化：PTE6-PCLK
GPIO_InitTypeDef ptd_init;//OV数据口初始化：PTD0~PTD7
GPIO_InitTypeDef ptc_init;//按键
GPIO_InitTypeDef gpio_init_struct;
DMA_InitTypeDef dma_init_struct;
UART_InitTypeDef uart4_init_struct,uart1_init_struct;

int image_get,v_counter,vs_counter,sd;
extern int time_jian;
extern int16 ss;
uint8 date[80][H]={0},aa[80][H]={0},bb[80][H]={0},a=0,b=0,h=0,figl=0;
uint32 xx,y,c;
int32 Z;
void send_image()    //发送图像
{
static int i=0,j=0;
     
    LPLD_UART_PutChar(UART4,0);  //上位机通信协议
    LPLD_UART_PutChar(UART4,255);
    LPLD_UART_PutChar(UART4,1);
    LPLD_UART_PutChar(UART4,0);
        
    for(i=0;i<=79;i++)   
    {
        for(j=0;j<=H-1;j++)   
        {
                 LPLD_UART_PutChar(UART4,date[i][j]);
        }
    }
    LPLD_GPIO_ClearIntFlag(PORTA);
    enable_irq(PORTA_IRQn);
   
    image_get = 0;
    EnableInterrupts;
}

int chuli_image(int n , int p ,int k)
{ 
   static long i=0,j=0;  
//   uint32 i,j, x, y, a, b;
   double IA = 0;
   int A;
//   LPLD_UART_PutChar(UART4,0);  //上位机通信协议
//   LPLD_UART_PutChar(UART4,255);
//   LPLD_UART_PutChar(UART4,1);
//   LPLD_UART_PutChar(UART4,0);
   
//   for(i=0;i<=79;i++)   
//   {
//        for(j=0;j<=H-1;j++)   
//        {
//             if(date[i][j]>0xef)
//             {
//		aa[i][j]=0xff;
//             }
//             else
//             {
//                aa[i][j]=0x00;
//             }
//             LPLD_UART_PutChar(UART4,aa[i][j]);
//        }
//    }
//	
//      // for(i=0;i<=79;i++)   
//      // {
//        // for(j=0;j<=H-1;j++)   
//        // {
//                  // if(aa[i][j]==1 && aa[i][j+1]==1 && aa[i][j+2]==1 && i<79)
//                  // {
//                          // aa[i][j]=1;
//                          // aa[i][j+1]=1;
//                          // aa[i][j+2]=1;
//                          // i += 2;
//                  // }
//                  // else 
//                  // {
//                          // aa[i][j]=0;
//                  // }
//	   
//         // }
//      // }
//	
//    for(i=1;i<78;i++)   
//    {
//        for(j=0;j<H-2;j++)   
//        {
//
//            if(aa[i][j] == 0xff && aa[i-1][j] == 0 && aa[i][j+1] == 0xff &&
//               aa[i-1][j+1] == 0 && aa[i][j+2] == 0xff && aa[i-1][j+2] == 0 &&
//               aa[i+1][j] == 0xff)
//            { 
//                    a = j;
//                    break;
//            }
//	}
//    }
//   
//    for(i=1;i<78;i++)   
//    {
//      for(j=0;j<H-2;j++)   
//      {        
//        if(aa[i][j] == 0xff && aa[i+1][j] == 0 && aa[i-1][j] == 0xff &&
//           aa[i][j+1] == 0xff && aa[i+1][j+1] == 0 && aa[i-1][j+1] == 0xff &&
//           aa[i][j+2] == 0xff && aa[i+1][j+2] == 0 && aa[i-1][j+2] == 0xff
//          )
//        {
//                 b = j; 
//                 //break;
//        }
//
//      }
//     }
//	
//    x = (b - a)/2 + a;//图像的中间行
//    a = 0;
//    b = 0;
//    
//    if(x != 0)//确定列
//    {  
//     
//      for(i=1;i<78;i++)   
//      {
//        for(j=0;j<H-2;j++)   
//        {
//            if(aa[i][j] == 0xff && aa[i+1][j] == 0xff && aa[i+2][j] == 0xff &&
//                  aa[i-1][j] == 0)
//            {
//               a = i;
//               break;
//            }
//             
//        }
//      }
//      for(i=1;i<78;i++)   
//      {
//         for(j=0;j<H-2;j++)   
//         {
//             if(aa[i][j] == 0xff && aa[i+1][j] == 0 && aa[i-1][j] == 0xff &&
//                    aa[i-2][j] == 0xff)
//             {
//                   b = i;
//                   //break;
//             }   
//         }
//      }
//     }
//	
//      y = (b - a) / 2 + a; //中间列
//      a = 0;
//      b = 0;
//	
//      if(x != 0 && y != 0)//转换成角度 和返回值
//      {
//         IA=((double)x-151)/(80-(double)y);
//         x=0;y=0;
//         IA = atan(IA)*180.0/3.14;// 角度转换公式 自己理解
//         if(IA<(-35)){IA=-35;}
//         if(IA>(35)){IA=35;}
//         return (int)IA;
//      }
  for(i=0;i<=79;i++)   
    {
        for(j=0;j<=H-1;j++)   
        {
             if(date[i][j]>n)
             {aa[i][j]=0xff;}
             else{aa[i][j]=0x00;}
//                    LPLD_UART_PutChar(UART4,aa[i][j]);
        }
    }
       for(i=1;i<78;i++)
       {
         for(j=1;j<H-2;j++)
         {
           if(aa[i][j]==0xff)
           {
             for(a=0;a<3;a++)
              {
                for(b=0;b<3;b++)
                  {
                    if(aa[i+a-1][j+b-1]==0xff)
                      {
                        c++;
                      }
                  }
              }
            bb[i][j] = c;
               c=0;
            }
         
         }
       }
       for(i=0;i<79;i++)
       {
         for(j=0;j<H-1;j++)
         {
           if(p<bb[i][j])
           {
             bb[i][j]=0xff;
           }
           else
           {
             bb[i][j]=0x00;
           }
//        LPLD_UART_PutChar(UART4,bb[i][j]);
         }
       }
       for(i=0;i<79;i++)
       {
         for(j=0;j<H-1;j++)
         {
           if(bb[i][j]==0xff)
           {
             c++;
             xx += i;
             y += j;
           }
         }
        }
     h=0;
     
     if(c!=0)
     {
      xx=(xx/c);
      y=y/c+52;
     }
       if(xx!= 0 && y != 0)//转换成角度 和返回值
      {
         IA=((double)y-154)/(80-(double)xx);
         IA = atan(IA)*180.0/3.14;}
     for(i=0;i<79;i++)
       {
         for(j=0;j<H-1;j++)
         {
       aa[i][j]=0x00;
       bb[i][j]=0x00;
         }
         }    
      LPLD_GPIO_ClearIntFlag(PORTA);
        enable_irq(PORTA_IRQn);
      EnableInterrupts;
      A=4500;
        if(c==0)
       {IA=-70;
       A=2500;
       Z=A;
       return (int)IA;
       } 
       if(xx>k)
       {
       A=0;
       Z=A;
        
       }
       Z=A;
   
        if(IA!=0)//转换成角度 和返回值
      {
//         IA=((double)y-154)/(80-(double)xx);
//         IA = atan(IA)*180.0/3.14;// 角度转换公式 自己理解
//         if(figl==1)
//         {IA=Z;}
//        else if(xx>30)
//         {figl=1;
//           if(-50<IA&&IA<50)
//         {if(IA<0){Z=50;}
//         else{Z=-50;}  
//         }
//         IA=Z;
//         }
//         else if(2<xx&&xx<30)
//         {figl=0;}
         
         xx=0;
         y=0;
         c=0;
         if(IA<(-50)){IA=-50;}
         if(IA>(50)){IA=50;}
         image_get = 0;
         return (int)IA;
      }

   
  return (int)IA;
}

void uart_init(void)    //串口初始化
{
  uart4_init_struct.UART_Uartx = UART4; //使用UART4
  uart4_init_struct.UART_BaudRate =9600; //设置波特率
  uart4_init_struct.UART_RxPin = PTC15;  //接收引脚为PTC15
  uart4_init_struct.UART_TxPin = PTC14;  //发送引脚为PTC14
  //初始化UART 
  LPLD_UART_Init(uart4_init_struct);
}
void uart1_init(void)    //串口初始化
{
  uart1_init_struct.UART_Uartx = UART1; //使用UART4
  uart1_init_struct.UART_BaudRate =9600; //设置波特率
  //初始化UART 
  LPLD_UART_Init(uart1_init_struct);
}
void gpio_init() 
{ 
  //OV数据口初始化：PTD0~PTD7
  ptd_init.GPIO_PTx = PTD;
  ptd_init.GPIO_Dir = DIR_INPUT;
  ptd_init.GPIO_Pins = GPIO_Pin0_7;
  ptd_init.GPIO_PinControl = IRQC_DIS | INPUT_PULL_DIS;
  LPLD_GPIO_Init(ptd_init);
  
  //OV行信号接口初始化：PTB3-H
  ptb_init.GPIO_PTx = PTB;
  ptb_init.GPIO_Dir = DIR_INPUT;
  ptb_init.GPIO_Pins = GPIO_Pin3;
  ptb_init.GPIO_PinControl = IRQC_RI|INPUT_PULL_DOWN;   //行上升沿
  ptb_init.GPIO_Isr = portb_isr;
  LPLD_GPIO_Init(ptb_init); 
  
  //OV场信号接口初始化：PTA5-V
  pta_init.GPIO_PTx = PTA;
  pta_init.GPIO_Dir = DIR_INPUT;
  pta_init.GPIO_Pins = GPIO_Pin5;
  pta_init.GPIO_PinControl = IRQC_RI|INPUT_PULL_DOWN;    //场上升沿
  pta_init.GPIO_Isr = porta_isr;
  LPLD_GPIO_Init(pta_init); 
  
  //OV PCLK信号接口初始化：PTE6-PCLK
  pte_init.GPIO_PTx = PTE;
  pte_init.GPIO_Pins = GPIO_Pin6;
  pte_init.GPIO_Dir = DIR_INPUT;
  pte_init.GPIO_PinControl = IRQC_DMARI | INPUT_PULL_DIS;   //像素上升沿出发
  LPLD_GPIO_Init(pte_init); 
  
  gpio_init_struct.GPIO_PTx = PTE;
  gpio_init_struct.GPIO_Pins = GPIO_Pin11|GPIO_Pin10;
  gpio_init_struct.GPIO_Dir = DIR_OUTPUT;
  gpio_init_struct.GPIO_Output = OUTPUT_H;
  gpio_init_struct.GPIO_PinControl = IRQC_DIS;
  LPLD_GPIO_Init(gpio_init_struct);
  
  gpio_init_struct.GPIO_PTx = PTA;
  gpio_init_struct.GPIO_Pins = GPIO_Pin28;
  gpio_init_struct.GPIO_Dir = DIR_OUTPUT;
  gpio_init_struct.GPIO_Output = OUTPUT_H;
  gpio_init_struct.GPIO_PinControl = IRQC_DIS;
  LPLD_GPIO_Init(gpio_init_struct);
  
  gpio_init_struct.GPIO_PTx = PTC;
  gpio_init_struct.GPIO_Pins = GPIO_Pin5|GPIO_Pin6|GPIO_Pin7|GPIO_Pin8;
  gpio_init_struct.GPIO_Dir = DIR_INPUT;
  gpio_init_struct.GPIO_PinControl = INPUT_PULL_UP;
  LPLD_GPIO_Init(gpio_init_struct);
  
  gpio_init_struct.GPIO_PTx = PTA;
  gpio_init_struct.GPIO_Pins = GPIO_Pin6;
  gpio_init_struct.GPIO_Dir = DIR_OUTPUT;
  gpio_init_struct.GPIO_Output = OUTPUT_H;
  gpio_init_struct.GPIO_PinControl = IRQC_DIS;
  LPLD_GPIO_Init(gpio_init_struct);
}

void dma_init()      //dma初始化
{
  //DMA参数配置
  dma_init_struct.DMA_CHx = DMA_CH0;    //CH0通道
  dma_init_struct.DMA_Req = PORTE_DMAREQ;       //PORTE为请求源
  dma_init_struct.DMA_MajorLoopCnt = H; //主循环计数值：行采集点数，宽度
  dma_init_struct.DMA_MinorByteCnt = 1; //次循环字节计数：每次读入1字节
  dma_init_struct.DMA_SourceAddr = (uint32)&PTD->PDIR;        //源地址：PTD0~7
  dma_init_struct.DMA_DestAddr = (uint32)date;      //目的地址：存放图像的数组
  dma_init_struct.DMA_DestAddrOffset = 1;       //目的地址偏移：每次读入增加1
  dma_init_struct.DMA_AutoDisableReq = TRUE;    //自动禁用请求
  //初始化DMA
  LPLD_DMA_Init(dma_init_struct);
}

void ftm_init()
{
    FTM_InitTypeDef ftm1_init_struct;
    ftm1_init_struct.FTM_Ftmx = FTM1;
    ftm1_init_struct.FTM_Mode = FTM_MODE_PWM;
    ftm1_init_struct.FTM_PwmFreq = 100;
    LPLD_FTM_Init(ftm1_init_struct);
    
    LPLD_FTM_PWM_Enable(FTM1, FTM_Ch0, 0, PTA8, ALIGN_LEFT);
    LPLD_FTM_PWM_Enable(FTM1, FTM_Ch1, 0, PTA9, ALIGN_LEFT);
    
    
    FTM_InitTypeDef ftm2_init_struct_QD;
    ftm2_init_struct_QD.FTM_Ftmx = FTM2;
    ftm2_init_struct_QD.FTM_Mode = FTM_MODE_QD;
    LPLD_FTM_Init(ftm2_init_struct_QD);
    LPLD_FTM_QD_Enable(FTM2, PTA10, PTA11);


}

void pit_init()
{
    PIT_InitTypeDef PIT0_Init_struct;
    PIT0_Init_struct.PIT_Pitx = PIT0;
    PIT0_Init_struct.PIT_PeriodMs = 50;
    PIT0_Init_struct.PIT_PeriodS = 0;
    PIT0_Init_struct.PIT_PeriodUs = 0;
    PIT0_Init_struct.PIT_Isr = pit_isr0;
    LPLD_PIT_Init(PIT0_Init_struct);
    LPLD_PIT_EnableIrq(PIT0_Init_struct);   //50ms
}

/*转向舵机控制函数
 angle：角度 从左到又 -35度到35度*/
//int qidong(int n)
//{ static long i=0,j=0;
//   int pp;
//  for(i=0;i<=79;i++)   
//    {
//        for(j=0;j<=H-1;j++)   
//        {
//             if(date[i][j]>n)
//             {pp++;}
//          
//        }
//    }
//  if(pp>=1)
//  {pp=1;}
//   return (int)pp;  
//}
void MotorActuator(int angle)
{
  uint32 val;
  switch(angle)
  {
      case 0:val=1600;break;//1600中点//1800右偏极限//1400左偏极限
      case 1:val=1604;break;
      case 2:val=1608;break;
      case 3:val=1612;break;
      case 4:val=1616;break;
      case 5:val=1620;break;
      case 6:val=1624;break;
      case 7:val=1628;break;
      case 8:val=1632;break;
      case 9:val=1636;break;
      case 10:val=1640;break;
      case 11:val=1644;break;
      case 12:val=1648;break;
      case 13:val=1652;break;
      case 14:val=1656;break;
      case 15:val=1660;break;
      case 16:val=1664;break;
      case 17:val=1668;break;
      case 18:val=1672;break;
      case 19:val=1676;break;
      case 20:val=1680;break;
      case 21:val=1684;break;
      case 22:val=1688;break;
      case 23:val=1692;break;
      case 24:val=1696;break;
      case 25:val=1700;break;
      case 26:val=1704;break;
      case 27:val=1708;break;
      case 28:val=1712;break;
      case 29:val=1716;break;
      case 30:val=1720;break;
      case 31:val=1724;break;
      case 32:val=1728;break;
      case 33:val=1732;break;
      case 34:val=1736;break;
      case 35:val=1740;break;
      case 36:val=1744;break;
      case 37:val=1748;break;
      case 38:val=1752;break;
      case 39:val=1756;break;
      case 40:val=1760;break;
      case 41:val=1764;break;
      case 42:val=1768;break;
      case 43:val=1772;break;
      case 44:val=1776;break;
      case 45:val=1780;break;
      case 46:val=1784;break;
      case 47:val=1788;break;
      case 48:val=1792;break;
      case 49:val=1796;break;
      case 50:val=1800;break;
      case 70:val=1950;break;
       case 80:val=1600;break;
      case -70:val=1250;break;
      case -50:val=1400;break;
      case -49:val=1404;break;
      case -48:val=1408;break;
      case -47:val=1412;break;
      case -46:val=1416;break;
      case -45:val=1420;break;
      case -44:val=1424;break;
      case -43:val=1428;break;
      case -42:val=1432;break;
      case -41:val=1436;break;
      case -40:val=1440;break;
      case -39:val=1444;break;
      case -38:val=1448;break;
      case -37:val=1452;break;
      case -36:val=1456;break;
      case -35:val=1460;break;
      case -34:val=1464;break;
      case -33:val=1468;break;
      case -32:val=1472;break;
      case -31:val=1476;break;
      case -30:val=1480;break;
      case -29:val=1484;break;
      case -28:val=1488;break;
      case -27:val=1492;break;
      case -26:val=1496;break;
      case -25:val=1500;break;
      case -24:val=1504;break;
      case -23:val=1508;break;
      case -22:val=1512;break;
      case -21:val=1516;break;
      case -20:val=1520;break;
      case -19:val=1524;break;
      case -18:val=1528;break;
      case -17:val=1532;break;
      case -16:val=1536;break;
      case -15:val=1540;break;
      case -14:val=1544;break;
      case -13:val=1548;break;
      case -12:val=1552;break;
      case -11:val=1556;break;
      case -10:val=1560;break;
      case -9:val=1564;break;
      case -8:val=1568;break;
      case -7:val=1572;break;
      case -6:val=1576;break;
      case -5:val=1580;break;
      case -4:val=1584;break;
      case -3:val=1588;break;
      case -2:val=1592;break;
      case -1:val=1596;break;
      default:break;
  }
 
  
  LPLD_FTM_PWM_ChangeDuty(FTM1, FTM_Ch0, val);
 }

int jiaodu(int sudu)
 {
 int16 jd=40;
  switch(sudu)
  {   case 0:jd=49;break;
      case 1:jd=48;break;//1600中点//1800右偏极限//1400左偏极限
      case 2:jd=47;break;
      case 3:jd=46;break;
      case 4:jd=45;break;
      case 5:jd=44;break;//1600中点//1800右偏极限//1400左偏极限
      case 6:jd=43;break;
      case 7:jd=42;break;
      case 8:jd=41;break;
      case 9:jd=40;break;//1600中点//1800右偏极限//1400左偏极限
      case 10:jd=30;break;
      case 11:jd=20;break;
      case 12:jd=21;break;
      case 13:jd=22;break;//1600中点//1800右偏极限//1400左偏极限
      case 14:jd=23;break;
      case 15:jd=24;break;
      case 16:jd=24;break;
      case 17:jd=25;break;
      case 18:jd=23;break;
      case 19:jd=22;break;
      case 20:jd=21;break;
      case 21:jd=20;break;
      case 22:jd=19;break;
      case 23:jd=18;break;
      case 24:jd=17;break;
      case 25:jd=17;break;
      case 26:jd=16;break;
  default:jd=15;break;
  }  
   
  return (int)jd;
 }
void Motor(uint8 move, uint32 val)    
{
  if(move == 0)
  {
    LPLD_GPIO_Output_b(PTE, 10, 1);
    LPLD_GPIO_Output_b(PTE, 11, 0);
  }
  else if(move == 1)
  {
    LPLD_GPIO_Output_b(PTE, 10, 0);
    LPLD_GPIO_Output_b(PTE, 11, 1);
  }
    
    LPLD_FTM_PWM_ChangeDuty(FTM1, FTM_Ch1, val);
}

void porta_isr()     //场中断函数
{ 

  vs_counter++;
  if(vs_counter>=2)
  { 
    vs_counter=0;
  if(LPLD_GPIO_IsPinxExt(PORTA, GPIO_Pin5))
  {
    //检测到场开始信号，加载目的地址
    LPLD_DMA_LoadDstAddr(DMA_CH0, date);
    //清行中断标志，防止进入无效行中断
    LPLD_GPIO_ClearIntFlag(PORTB);
    enable_irq(PORTB_IRQn);    //开行中断
  }
  }
}

void portb_isr()     //行中断函数
{
  if(LPLD_GPIO_IsPinxExt(PORTB, GPIO_Pin3))
  { //检测到行开始信号，使能DMA   
  if(v_counter<V)
   { 
     v_counter++; 
     if(v_counter%3==0)           // 80行
      LPLD_DMA_EnableReq(DMA_CH0);  
     
   }
   
   else{                 //行数采集已满，关闭中断
      //关GPIO中断 
      // disable_irq(PORTA_IRQn);      //场中段    //发送图像到上位机时该行必须注释掉
        disable_irq(PORTB_IRQn);       //行中断
        image_get = 1;//可以显示图像
        v_counter=0;
     }
    }
}

void delayS(uint16 n)       // 约为0.1s
{
  uint16 i, j;
  while(n--)
  {
    
      for(j = 0; j < 1000; ++j)
        for(i=0; i < 12500; i++)
        {
          asm("nop");
        }
  }
}
