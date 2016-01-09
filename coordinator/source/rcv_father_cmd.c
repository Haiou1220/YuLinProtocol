/***********************************************************************************
 *	
 * ������code�ǽ������Ը��ڵ�����������Ӧ���ݻ�����������ڵ�
 * ��δ�����task1
 *
 */

 #include "..\\include\\config.h" 
 #include "..\\include\\hardware_config.h"
 #include "..\\include\\serial.h" 
 #include "..\\include\\environment.h"

 #define TIMEOUT 100		//�ȴ����ݽ��ճ�ʱʱ��(ms)

 /* �򸸽ڵ㷢�����ݶ����������� */
 void send_queue_to_father(const uchar_8 rate)
 {
 	//  while( !queue_estimate_empty() ){
	 // 	queue_read(); 		//���������ݶ���������
	 // 	if( data_processed.dirty == 0 ){	
			print_stream(sizeof(data_processed.cmd),rate,FATHER_PORT,data_processed.cmd);			 
	  		data_processed.dirty = 1;		//��������������
	//	}
	//  }
 }

 void rcv_father_data(const uchar_8 rate)
 {
 	uchar_8 i = 0;
	uchar_8 data_ack_cnt = 0;
	
		
 	if( outside_data_coming() ){

		for( i=0;i<9;i++){				
			serial_buffer[i] = serial_read_byte(0,rate);

			while( (!outside_data_coming()) && (i < MESSAGE_LENGTH - 1) );  //�ȴ���һbyte����
		  	/*timeout_cnt = 0;	//	��ʱ������
			while( (timeout_cnt < TIMEOUT) && (!outside_data_coming()) && (i < MESSAGE_LENGTH - 1) );  //�ȴ���һbyte����
		*/}

		 
		for( i=0;i<MESSAGE_LENGTH;i++ ){
			if( serial_buffer[i] == hand_cmd[i] )
				data_ack_cnt ++;
		}

		if( data_ack_cnt == MESSAGE_LENGTH ){
			print_stream(sizeof(hand_ack),rate,FATHER_PORT,hand_ack);	//��������ȷ������
		}else{
			data_ack_cnt = 0;

			for( i=0;i<MESSAGE_LENGTH;i++ ){
				if( serial_buffer[i] == data_request[i] )
					data_ack_cnt ++;
			}

			if( data_ack_cnt == MESSAGE_LENGTH ){
				//���Ͷ����������ݸ����ڵ�();
				if( !queue_estimate_empty() ){
					send_queue_to_father(rate);
				}else{
					print_stream(sizeof("queue emptied"),rate,FATHER_PORT,"queue emptied");	
				}
			}else{
				print_stream(sizeof("command error"),rate,FATHER_PORT,"command error");
			} 
		}  	  
   	 }
  }

 















