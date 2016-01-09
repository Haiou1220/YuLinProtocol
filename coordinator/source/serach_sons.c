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

/* �������ְ� */
 void send_hand_cmd(const uchar_8 rate, const uchar_8 linked_port )
 {
 	/*
	 * �����ʱ��������Ϊ�ҷ��ֲ��������ݷ���̫�죬��������
	 * ��ʾ������(����ȷʵ�յ���)
	 */
 	delay_for_debug(); 
 	print_stream(sizeof(hand_cmd),rate,linked_port,hand_cmd);	//�������ְ�
//	
 }


 void link_son(const uchar_8 rate,const uchar_8 linked_port)
 {
 	uchar_8 i = 0;

  	for( i=0;i<FREQUENCY_LINKED;i++ ){

		send_hand_cmd(rate,linked_port);	//�������ְ�

		timeout_cnt = 0;
		while( timeout_cnt < 5 ){
			 		
			if( outside_data_coming( linked_port ) ){

				for( i=0;i<MESSAGE_LENGTH;i++){				
					serial_buffer[i] = serial_read_byte(rate,linked_port);

					byte_time_out_cnt = 0;
				//	while( (!outside_data_coming(linked_port)) && (i < MESSAGE_LENGTH - 1) );  //�ȴ���һbyte����
				
					while( (byte_time_out_cnt < 1) && (!outside_data_coming(linked_port)) && (i < MESSAGE_LENGTH - 1) );  //�ȴ���һbyte����
				}

				if( (serial_buffer[0]==hand_ack[0]) && (serial_buffer[1] ==hand_ack[1]) ){
				
					// ��������Ҫɾ��
					print_stream(sizeof("���ֳɹ�"),rate,linked_port,"���ֳɹ�");

					goto out;
				}	
			}			
		}
	}  
	out: return;	
 }	


 void serach_sons( const uchar_8 rate )
 {
 	uchar_8 number_port = 0;

	// ������number_port��Ҫ��1��ʼ
 	for( number_port=0;number_port<SONS_AMOUNT;number_port++){

		switch(number_port){

			//port 0Ϊ�븸�ڵ����·
			case 0:	print_stream(sizeof("��ʱ���Ҹ���:"),rate,0,"��ʱ���Ҹ���:");link_son(rate,number_port); break; 
			case 1:	print_stream(sizeof("���Ҷ���1:"),rate,0,"���Ҷ���1:");link_son(rate,number_port); break; 
		  	case 2: print_stream(sizeof("���Ҷ���2:"),rate,0,"���Ҷ���2:");link_son(rate,number_port); break;
			case 3: break;
			default : break;
		}
		//����ʱ�������������ʾ��������
			delay_for_debug();
	}		
 }



