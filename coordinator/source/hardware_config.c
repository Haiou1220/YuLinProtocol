/****************************************************************************************
 *	Ӳ������ģ��
 *
 */

 /* REGX52.H������ڵ�һ��include */
 #include <REGX52.H>			
 #include "..\\include\\config.h" 
 #include "..\\include\\hardware_config.h"
 #include "..\\include\\serial.h" 
 #include "..\\include\\environment.h"
 #include "..\\include\\req_son_data.h" 
 #include "..\\include\\rcv_father_cmd.h" 
 #include "..\\include\\serach_sons.h" 

 uint_16 debug_cnt = 0;

/* ϵͳ�δ� */
 uint_16  sys_tick = 0;

/* ϵͳ������ʱ���� */
/* void sys_launch_delay(void)
 {
	unsigned char 	i,
					j;

	for( i=0; i<200; i++ )
		for( j=0; j<210; j++ )
		;
	return;
 }*/

/* �ӵ��Լ� */
/* void power_on_self_test(void)
 {
 	//ROUTER_RCVI_PIN_1 = 0;
//	ROUTER_SEND_PIN_1 = 1;
	/* do something	*/
/*	return;
 } */

/*
 * ��ʱ������
 */
 void timer_config(void)
 {
	 TMOD=0x12;					//T0��ʽ2,T1��ʽ1

	 T2MOD |= 0x00;				//��ʱ��2����ģʽ�Ĵ��� ����ͷ�ļ���û����� sfr T2MOD  = 0xC9;
	 T2CON  = 0x30; 			//��ʱ��2���ƼĴ���
	 SCON   = 0x50;  			//�����жϹ���ģʽ1
	 RCAP2H = 0xff; 			//��ʱ��2�Զ�װ�صĳ�ֵ
	 RCAP2L = 0xdc;

	 /*
	  *		���´����ǶԶ�ʱ��0�����ã���ʱ��0�������������ڵĲ����ʣ�
	  * �������������þ��൱��Ҫ��TH0 = (256 - 192)������һ������ʵ
	  * ������ѡ����ֵ������ֵΪ96������
	  */

	 TR0=0;
 	 TF0=0;
     TH0=(256-192);				/* ʧ֮���壬����ǧ��*/
     TL0=TH0;


	 TH1 = 0xFC;  				//T1��ʱ��11.0592M ��ʱ1ms
     TL1 = 0x66;;
	 TH2 = 0xff;	 			//��ʱ��2����9600�����ʳ�ֵ
	 TL2 = 0xdc;

	 ES  = 1;	 				//�򿪴����ж�
	 ET1 = 1; 					//��ʱ��1����
   	 ET0 = 1; 					//��ʱ��0����
	 TR0 = 1; 					//��ʱ��0��
	 TR1 = 1; 					//��ʱ��1��
	 TR2 = 1; 					//��ʱ��2��

     ET0=1;

	 /* �趨��ʱ��0Ϊ������ȼ������ֵ�ı佫����ϵͳ�������ȶ� */
	 IP = 0x02;	  				
     EA=1;
 }	 



/* Ӳ����ʼ�� */
 void hardware_init(void)
 {
	GPIO_1(0) = 0;
	GPIO_1(1) = 1;
	GPIO_1(2) = 1;
	GPIO_1(3) = 1;
	GPIO_1(4) = 1;
	GPIO_1(5) = 1;
	GPIO_1(6) = 1;
	GPIO_1(7) = 1;
	/* ��ʱ������ */
	timer_config();

	return;
 }

 void timer_0_IRQ(void) interrupt 1 using 0 
 {
 	return;	
 }

 bit aaa = 0;
  void timer_1_IRQ(void) interrupt 3   
 {
 	TH1 = 0xFC;
    TL1 = 0x66;	
	

	//����Ӧ�øĻ���
	//byte_time_out_cnt ++;
	//timeout_cnt ++;

 	sys_tick ++;
	/* ϵͳ�δ��ʱ1ms  */
	if( sys_tick >= 999 ){
		sys_tick = 0;

		byte_time_out_cnt ++;
		timeout_cnt ++;

		debug_cnt ++;
		aaa = ~aaa;	
 		GPIO_0(1) = aaa; 
	}		   
	return;	
 } 

/* Ӳ���������� */
 void hardware_launch(void)
 {
    //power_on_self_test();
 	hardware_init();

	return;
 } 

 /* ��ģ����Թ��ܺ��� */
/* void test_hardware_moudle(void)
 {
	//test_pin_6 = 0;
 	//test_pin_7 = 0;
 	/* do somthing */
 //	return;
 //}*/

