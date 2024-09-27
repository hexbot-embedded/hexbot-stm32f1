#include "usart.h"

uint8_t USART2_RX_BUF[USART2_REC_LEN];//接收缓冲,最大USART_REC_LEN个字节.
uint16_t USART2_RX_STA=0;//接收状态标记//bit15：接收完成标志，bit14：接收到0x0d，bit13~0：接收到的有效字节数目
uint8_t USART2_NewData;//当前串口中断接收的1个字节数据的缓存

void  HAL_UART_RxCpltCallback(UART_HandleTypeDef  *huart)//串口中断回调函数
{
	if(huart ==&huart2)//判断中断来源（串口2：USB转串口）
    {
       if((USART2_RX_STA&0x8000)==0){//接收未完成
           if(USART2_RX_STA&0x4000){//接收到了0x0d
               if(USART2_NewData!=0x0a)USART2_RX_STA=0;//接收错误,重新开始
               else USART2_RX_STA|=0x8000;   //接收完成了
           }else{ //还没收到0X0D
               if(USART2_NewData==0x0d)USART2_RX_STA|=0x4000;
               else{
                  USART2_RX_BUF[USART2_RX_STA&0X3FFF]=USART2_NewData; //将收到的数据放入数组
                  USART2_RX_STA++;  //数据长度计数加1
                  if(USART2_RX_STA>(USART2_REC_LEN-1))USART2_RX_STA=0;//接收数据错误,重新开始接收
               }
           }
       }
       HAL_UART_Receive_IT(&huart2,(uint8_t *)&USART2_NewData,1); //再开启接收中断
    }
}
