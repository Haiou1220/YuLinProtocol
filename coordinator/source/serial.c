/******************************************************************************************
 *  
 *	��������ģ��
 *
 *	[ע]:����δ֪ԭ����ϵͳ����֮���͵ĵ�һ�����ݻᷢ������
 *       ��˽������Ա�ڷ���ϵͳ������ÿһ����Ҫʹ�õ�ģ�⴮��Ӧ��
 *  	 �ȷ���һ���޹ؽ�Ҫ�����ݣ���
 *  	 ��֤�������ݷ�����ȷ��
 */

 #include <REGX52.H>
 #include <intrins.h>
 #include "..\\include\\config.h"

 
/* ���������ʶ�ʱ��ʹ�������� */
 #define BAUD_TIMER_START(enable) TR0 = ##enable

 #define BAUD_4800 1
 #define BAUD_9600 2

 uchar_8 idata hand_cmd_buffer[9] = {0};
 uchar_8 idata hand_ack_buffer[9] = {0};

/* �ȴ�һ��byte���ݴ������ */
 #define WAIT_BYTE_OVER do{				 	 	\
 						while(!TF0);  	      	 \
     					TF0 = 0;		       	  \
												   \
					}while(0)


 #define TIMER_ENABLE() 	{				  	\
 								TL0=TH0;	     \
								TR0=1;		      \
								TF0=0;		       \
							}//ʹ��T/C
 #define TIMER_DISABLE() 	{				 	\
 								TR0=0;		     \
								TF0=0;		      \
											       \
							}//��ֹT/C   


 void set_baud_rate(uchar_8 rate)
 {
 	switch(rate){
		case 1: TH0 = (256-192);TL0 = TH0;break; 	//4800bps
		case 2: TH0 = (256-92) ;TL0 = TH0;break; 	//9600bps
		default:TH0 = (256-192);TL0 = TH0;break;
	}
	return;
 }

/* ϵͳ���봫��ģʽ */    
 void into_serial_pattern(void)
 {
 	 ES  = 0;	            		/*�򿪴����ж�*/
	 ET0 = 1;				 		/*��ʱ��0����*/
	 TR0 = 1; 		   		   		/*��ʱ��0��*/
	 ET1 = 0;   		   		    /*��ʱ��1��ֹ*///��ʱ�ȴ� for debug
	 TR1 = 0; 		   		     	/*��ʱ��1�ر�*///��ʱ�ȴ� for debug
	 TR2 = 0; 						/*��ʱ��2�ر�*/
 }



/* ϵͳ�˳�����ģʽ */    
 void exit_serial_pattern(void)
 {
 	 ES  = 1;	            		/*�򿪴����ж�*/
	 ET0 = 1;				 		/*��ʱ��0����*/
	 TR0 = 1; 		   		   		/*��ʱ��0��*/
	 ET1 = 1;   		   		    /*��ʱ��1��ֹ*/
	 TR1 = 1; 		   		     	/*��ʱ��1�ر�*/
	 TR2 = 1; 						/*��ʱ��2�ر�*/
 }

  

/* ����0����һ���ַ� */ 
 void serial_0_write_byte(const uchar_8 rate,uchar_8 input)  
 {  
    uchar_8 i=8;
 
 	TXD_0=0;

	set_baud_rate(rate);		//���ò�����
 	into_serial_pattern();		//���봮��ģʽ

 	TIMER_ENABLE();
 	WAIT_BYTE_OVER;
 
 	while(i--)
 	{
 		if( input&1 ){
			TXD_0=1;
 		}else{
			TXD_0=0;
 		}

 		WAIT_BYTE_OVER;

 		input>>=1;
 	}
 
 	TXD_0=1;	 //���ͽ���
 
 	WAIT_BYTE_OVER;
 	TIMER_DISABLE();

	exit_serial_pattern();		//�˳�����ģʽ
 }

 /* ����1����һ���ַ� */ 
 void serial_1_write_byte(const uchar_8 rate,uchar_8 input)  
 {  
    uchar_8 i=8;
 
 	TXD_1=0;

	set_baud_rate(rate);		//���ò�����
 	into_serial_pattern();		//���봮��ģʽ

 	TIMER_ENABLE();
 	WAIT_BYTE_OVER;
 
 	while(i--)
 	{
 		if( input&1 ){
			TXD_1=1;
 		}else{
			TXD_1=0;
 		}

 		WAIT_BYTE_OVER;

 		input>>=1;
 	}
 
 	TXD_1=1;	 //���ͽ���
 
 	WAIT_BYTE_OVER;
 	TIMER_DISABLE();

	exit_serial_pattern();		//�˳�����ģʽ
 }




/* ���ڷ���byte����  */
 void serial_write_byte(const uchar_8 rate,const uchar_8 serial_number,uchar_8 input)
 {

 /*
  * doc:
  *	"serial_number" is the number of serial,and "input" is the
  * will be sent date ,only byte, accross serial��
  */

  	switch( serial_number ){
  		case 0:	 serial_0_write_byte(rate,input);break;	   //����0����
		case 1:	 serial_1_write_byte(rate,input);break;	   //����1����

		default: break;
  	}

 }

/* RXD_0����һ���ַ� */  
 uchar_8 serial_0_read_byte(const uchar_8 rate)  
 {  
    uchar_8 i;
 	uchar_8 read_byte=0;

	set_baud_rate(rate);		//���ò����� 
	into_serial_pattern();		//���봮��ģʽ

   	TIMER_ENABLE();
   	WAIT_BYTE_OVER;

	/*
	 * ��δ���ִ��ʱ����ϵ��ú����ķѵ�ʱ���ܹ���Լռһ��byte����ʱ���һ�룬
	 * ��������ʹ�õ�ƽ����������ÿһ��byte���м�
	 */
	 /* There are some codes deleted recently ,all of which are the function of _nop_().  */ 
	_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();


   	for(i=0;i<8;i++){
     	if(RXD_0){
 	  		read_byte |= (1<<i);
		}
 
     	WAIT_BYTE_OVER;
   	}
 
    WAIT_BYTE_OVER; //�ȴ�����λ
    TIMER_DISABLE();
 

	exit_serial_pattern();		//�˳�����ģʽ
 	return read_byte; 
}

/* RXD_1����һ���ַ� */  
 uchar_8 serial_1_read_byte(const uchar_8 rate)  
 {  
    uchar_8 i;
 	uchar_8 read_byte=0;

	set_baud_rate(rate);		//���ò�����
	into_serial_pattern();		//���봮��ģʽ

   	TIMER_ENABLE();
   	WAIT_BYTE_OVER;

	/*
	 * ��δ���ִ��ʱ����ϵ��ú����ķѵ�ʱ���ܹ���Լռһ��byte����ʱ���һ�룬
	 * ��������ʹ�õ�ƽ����������ÿһ��byte���м�
	 */
	 /* There are some codes deleted recently ,all of which are the function of _nop_().  */ 


   	for(i=0;i<8;i++){
     	if(RXD_1){
 	  		read_byte |= (1<<i);
		}
 
     	WAIT_BYTE_OVER;
   	}
 
    WAIT_BYTE_OVER; //�ȴ�����λ
    TIMER_DISABLE();
 

	exit_serial_pattern();		//�˳�����ģʽ
 	return read_byte; 
}

/* ���ڽ���byte���� */
 uchar_8 serial_read_byte(const uchar_8 rate,const uchar_8 serial_number)
 {
 /*
  * doc:
  *	"serial_number" is the number of serial,and "input" is the
  * will be sent date ,only byte, accross serial��
  */

  switch( serial_number ){
  	case 0:	 return serial_0_read_byte(rate);	   //����0����
	case 1:	 return serial_1_read_byte(rate);	   //����1����

	default: return 0;
  }
	 
 }


/* ��������� */ 
 void print_stream(const uchar_8 data_size,const uchar_8 rate,const uchar_8 serial_number, uchar_8 * pstream)
 {
 	/**
	 **	������2015.12.31 23:36:57�����Ͽ����ˣ���ȥ����̡�
	 **/

	/*
	 * ���������ڷ��͹��콫�������ݽ��ճ������Բ�����ֱ��ʹ�ñ�����
	 */
	 uchar_8 i =0;
	 for( i=0;i<data_size;i++ ){
	 	serial_write_byte(rate,serial_number, *(pstream+i) );
	 }
	 /*
	 * ��δ��벻��������Ϊ�����ӡ��pstream��ʼ���ڴ�δ��������������
 	while(pstream && *pstream){
 		serial_write_byte(serial_number, *pstream++ );
 	}*/
 }



 /* �ⲿ���������� */
 uchar_8 outside_data_coming(void)
 {
 	return (RXD_0 == 0);
 }  