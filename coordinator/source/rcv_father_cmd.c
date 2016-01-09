/***********************************************************************************
 *	
 * ������code�ǽ������Ը��ڵ�����������Ӧ���ݻ�����������ڵ�
 * ��δ�����task1
 *
 */
 #include <REGX52.H>
 #include "..\\include\\config.h" 
 #include "..\\include\\hardware_config.h"
 #include "..\\include\\serial.h" 
 #include "..\\include\\environment.h"


 void send_delay(const uchar_8 delay_time )
 {
 	uchar_8 i,
			j;

	for( i=0;i<delay_time;i++ ){
		for( j=0;j<20;j++ ){
			;
		}
	}	
 }

 /* �򸸽ڵ㷢�����ݶ����������� */
 void send_queue_to_father(const uchar_8 rate)
 {
 	 if( !queue_estimate_empty() ){

		while( !queue_estimate_empty() ){

	  		queue_read(); 		//���������ݶ���������
	 		if( data_processed.dirty == 0 ){	
				print_stream(sizeof(data_processed.cmd),rate,FATHER_PORT,data_processed.cmd);			 
	  			data_processed.dirty = 1;		//��������������
			}

			send_delay(20);
	  }
	 }else{
			print_stream(sizeof("queue emptied"),rate,FATHER_PORT,"queue emptied");	
	 }
 	  
	  
 }

/* �Ӹ��ڵ�������� */
 void rcv_father_data(const uchar_8 rate)
 {
 	uchar_8 i = 0;
			
 	if( outside_data_coming( FATHER_PORT ) ){

		for( i=0;i<MESSAGE_LENGTH;i++){				
			serial_buffer[i] = serial_read_byte(rate,FATHER_PORT);

		//	while( (!outside_data_coming( FATHER_PORT )) && (i < MESSAGE_LENGTH - 1) );  //�ȴ���һbyte����
		  	
			timeout_cnt = 0;	//	��ʱ������
			while( (timeout_cnt < WAIT_DATA_TIMEOUT) && (!outside_data_coming(FATHER_PORT)) && (i < MESSAGE_LENGTH - 1) );  //�ȴ���һbyte����
		 }

		 // print_stream(sizeof(serial_buffer),rate,FATHER_PORT,serial_buffer);	 
		if( (serial_buffer[0] == hand_cmd[0]) && (serial_buffer[1] == hand_cmd[1])){
			//���ְ�����
			print_stream(sizeof(hand_ack),rate,FATHER_PORT,hand_ack);	//��������ȷ������

			GPIO_1(4) = 0;
		}else if( (serial_buffer[0] == data_request[0]) && (serial_buffer[1] == data_request[1])){
			//���������
		  	send_queue_to_father(rate);	//���Ͷ�����������
		}else{
			//print_stream(sizeof("command error"),rate,FATHER_PORT,"command error");	
		}	 	  	  
   	 } 
  }


 














