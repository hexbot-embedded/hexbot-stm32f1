#include "usart.h"

uint8_t USART2_RX_BUF[USART2_REC_LEN];//���ջ���,���USART_REC_LEN���ֽ�.
uint16_t USART2_RX_STA=0;//����״̬���//bit15��������ɱ�־��bit14�����յ�0x0d��bit13~0�����յ�����Ч�ֽ���Ŀ
uint8_t USART2_NewData;//��ǰ�����жϽ��յ�1���ֽ����ݵĻ���

void  HAL_UART_RxCpltCallback(UART_HandleTypeDef  *huart)//�����жϻص�����
{
	if(huart ==&huart2)//�ж��ж���Դ������2��USBת���ڣ�
    {
       if((USART2_RX_STA&0x8000)==0){//����δ���
           if(USART2_RX_STA&0x4000){//���յ���0x0d
               if(USART2_NewData!=0x0a)USART2_RX_STA=0;//���մ���,���¿�ʼ
               else USART2_RX_STA|=0x8000;   //���������
           }else{ //��û�յ�0X0D
               if(USART2_NewData==0x0d)USART2_RX_STA|=0x4000;
               else{
                  USART2_RX_BUF[USART2_RX_STA&0X3FFF]=USART2_NewData; //���յ������ݷ�������
                  USART2_RX_STA++;  //���ݳ��ȼ�����1
                  if(USART2_RX_STA>(USART2_REC_LEN-1))USART2_RX_STA=0;//�������ݴ���,���¿�ʼ����
               }
           }
       }
       HAL_UART_Receive_IT(&huart2,(uint8_t *)&USART2_NewData,1); //�ٿ��������ж�
    }
}
