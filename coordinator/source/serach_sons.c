/*********************************************************************************
 *
 * �ⲿ��code�Ǳ���������·�� ���������ӵĽڵ�����ӽڵ�
 * ����ԭ�����ӽڵ�Ͽ�����kill it
 *
 */
 #include <REGX52.H>
 #include "..\\include\\config.h" 
 #include "..\\include\\hardware_config.h"
 #include "..\\include\\serial.h" 
 #include "..\\include\\environment.h"

 #define FREQUENCY_LINKED 3	//ÿһ������һ���������Ӵ���
 
 
 extern void delay_for_debug(void);

 uint_16 byte_time_out_cnt = 0;

 void send_hand_cmd( const uchar_8 linked_port )
 {
 	/*
	 * �����ʱ��������Ϊ�ҷ��ֲ��������ݷ���̫�죬��������
	 * ��ʾ������(����ȷʵ�յ���)
	 */
 	delay_for_debug(); 
 	print_stream(sizeof(hand_cmd),1,linked_port,hand_cmd);	//�������ְ�
//	
 }


 void link_son(const uchar_8 rate,const uchar_8 linked_port)
 {
 	uchar_8 i = 0;

 	for( i=0;i<FREQUENCY_LINKED;i++ ){
		send_hand_cmd(linked_port);

		timeout_cnt = 0;
		while( timeout_cnt < 50 ){

			if( outside_data_coming() ){

				for( i=0;i<9;i++){				
					serial_buffer[i] = serial_read_byte(rate,0);
		  	//		print_stream(sizeof("�յ�"),0,"�յ�");

					byte_time_out_cnt = 0;
					while( (byte_time_out_cnt < BYTE_TIME_OUT) && (!outside_data_coming()) && (i < MESSAGE_LENGTH - 1) );  //�ȴ���һbyte����
				}
			}			
		}	
	}	
 }	


 void serach_sons( void )
 {
 	uchar_8 number_port = 0;

 	for( number_port=1;number_port<SONS_AMOUNT;number_port++){

		switch(number_port){
			//port 0Ϊ�븸�ڵ����·
			case 1: break; 
		  	case 2: break;
			case 3: break;
			default : break;
		}
	}		
 }



