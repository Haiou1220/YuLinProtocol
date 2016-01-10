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
			while( (timeout_cnt < WAIT_DATA_TIMEOUT ) && (!outside_data_coming(FATHER_PORT)) && (i < MESSAGE_LENGTH - 1) );  //�ȴ���һbyte����
		 }

		 // print_stream(sizeof(serial_buffer),rate,FATHER_PORT,serial_buffer);	 
		if( (serial_buffer[0] == hand_cmd[0]) && (serial_buffer[1] == hand_cmd[1])){

			rcv_father_hand_creat_host_id(serial_buffer);	//��ȡ���ڵ�id�����ɱ���id
			id_insert_data();
			//���ְ�����
			hand_ack[8] = (hand_ack[0] + hand_ack[1] + hand_ack[2] + hand_ack[3] + hand_ack[4] + hand_ack[5] );
			print_stream(sizeof(hand_ack),rate,FATHER_PORT,hand_ack);	//��������ȷ������
			print_stream(sizeof(hand_ack),rate,1,hand_ack);	//��������ȷ������

			sons_status.linked_father = FATHER_CONNECTED;
			clean_serial_buffer();
		}else if( (serial_buffer[0] == data_request[0]) && (serial_buffer[1] == data_request[1])){
			//���������
		  	send_queue_to_father(rate);	//���Ͷ�����������
		}else{
			//print_stream(sizeof("command error"),rate,FATHER_PORT,"command error");	
		}	 	  	  
   	 } 
  }


 void temporary_rcv_sons(const uchar_8 rate)
 {
 	uchar_8 i = 0,
			f1 = 0;
	timeout_cnt = 0;	//	��ʱ������
	if( outside_data_coming( PORT(1) ) ){
		f1 = 1;
		for( i=0;i<MESSAGE_LENGTH;i++){				
			serial_buffer[i] = serial_read_byte(rate,PORT(1));
			
			while(  (!outside_data_coming(PORT(1))) && (i < MESSAGE_LENGTH - 1) );  //�ȴ���һbyte����
			if( timeout_cnt > WAIT_DATA_TIMEOUT + 500 ){
				goto out;
			}
		}	
	} 
	if( f1 == 1){
		f1 = 0;
		print_stream(sizeof(serial_buffer),BAUD_9600,0,serial_buffer);
	}
	out: f1 = 0;			
 }
extern void delay_for_debug(void);
 void  temporary_send_data(const uchar_8 rate,const uchar_8 number_port,uchar_8 *cmd )
 {
 			serial_write_byte(rate,number_port, *(cmd + 0) );
			delay_for_debug();  
			serial_write_byte(rate,number_port, *(cmd + 1) );
			delay_for_debug();
			serial_write_byte(rate,number_port, *(cmd + 2) );
			delay_for_debug();
			serial_write_byte(rate,number_port, *(cmd + 3) );
			delay_for_debug();
			serial_write_byte(rate,number_port, *(cmd + 4) );
			delay_for_debug();
			serial_write_byte(rate,number_port, *(cmd + 5) );
			delay_for_debug();
			serial_write_byte(rate,number_port, *(cmd + 6) );
			delay_for_debug();
			serial_write_byte(rate,number_port, *(cmd + 7) );
			delay_for_debug();
			serial_write_byte(rate,number_port, *(cmd + 8) );
			delay_for_debug();  
		
 		delay_for_debug();
	 	delay_for_debug();
		delay_for_debug();
		delay_for_debug();
		delay_for_debug();	
 }












