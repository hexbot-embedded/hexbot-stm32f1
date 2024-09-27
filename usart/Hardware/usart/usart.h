#ifndef INC_USART_H_
#define INC_USART_H_

#include "stm32f1xx_hal.h" //HAL���ļ�����
#include <string.h>//�����ַ�������Ŀ�

extern UART_HandleTypeDef huart2;//����USART2��HAL��ṹ��

#define USART2_REC_LEN  200//����USART1�������ֽ���

extern uint8_t  USART2_RX_BUF[USART2_REC_LEN];//���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з�
extern uint16_t USART2_RX_STA;//����״̬���
extern uint8_t USART2_NewData;//��ǰ�����жϽ��յ�1���ֽ����ݵĻ���

void  HAL_UART_RxCpltCallback(UART_HandleTypeDef  *huart);//�����жϻص���������

#endif /* INC_USART_H_ */
