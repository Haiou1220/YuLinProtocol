 #define MCU8051 

 #ifdef MCU8051	 
 /*
  *	������ζ�������8051��Ƭ��Ӳ����ض���
  */

    #ifndef  uchar_8
 		#define uchar_8  unsigned char
	#endif
	#ifndef  uint_16
 		#define uint_16  unsigned int
	#endif

	#define GPIO_0(pin)  P0_##pin
	#define GPIO_1(pin)  P1_##pin

 #endif/* 8051������� */


 /**		
  **		Ԭ����ˮ��ǧ�
  **		����ʮ���С�
  **		�����ޱ��
  **		ֻ���绹�硣
  **				-- 2016/01/04 01:16
  **/


 #ifndef __CONFIG_H__
 #define __CONFIG_H__
 	
	 #define BAUD_4800 1
 	 #define BAUD_9600 2

	/*  ����0����  */
	#define RXD_0 GPIO_1(0) 					//�������ݵ�����
  	#define TXD_0 GPIO_1(1) 					//�������ݵ�����

	/*  ����1����  */
	#define RXD_1 GPIO_1(2) 					//�������ݵ�����
  	#define TXD_1 GPIO_1(3) 					//�������ݵ�����

	/*  ����2����  */
	#define RXD_2 GPIO_1(4) 					//�������ݵ�����
  	#define TXD_2 GPIO_1(5) 					//�������ݵ�����

	#define FATHER_PORT 0						//���Ӹ��ڵ�˿�
	#define SON_PORT(son)  son					//���ӵ�һ�����Ӷ˿�
	#define PORT(port)	port 					//�˿ں�

  //#define TASK_WAIT 1 			//����ȴ�
  //#define TASK_OVER 0			//������ִ��

  	#define SON_CONNECTED 1		//�ӽڵ�����״̬
  	#define SON_DISCONNECTED 0	//�ӽڵ�Ͽ�״̬
	#define FATHER_CONNECTED 1	//�ӽڵ�Ͽ�״̬
	#define FATHER_DISCONNECTED 0	//�ӽڵ�Ͽ�״̬

	#define SONS_AMOUNT   2		//���������ӽڵ��������

	#define SYS_BAUD	BAUD_4800		

 #endif //__CONFIG_H__