 #ifndef __ENVIRONMENT_H__
 #define __ENVIRONMENT_H__

 #define QUEUE_BUFF_SIZE 10			//��Ϣ���д�С
 #define MESSAGE_LENGTH 9			//һ�����ݳ���





/*  ����������cache */
 typedef struct  data_processed_type{
  		uchar_8 cmd[MESSAGE_LENGTH];
		uchar_8 dirty;				//�����Ƿ�Ϊ��
 }data_processed_type;
 extern data_processed_type  data_processed;






 typedef struct data_queue_struct{	  
 	/*
	 *  �����Ϣ���д洢��·������������Ϣ�����������ն���ת��
	 */
	uchar_8  data_buff[QUEUE_BUFF_SIZE][MESSAGE_LENGTH]; 		
	//uchar_8  data_queue_length;				   //���ݶӳ���
	uchar_8  data_queue_rear;					   //��β
	uchar_8  data_queue_head;					   //��ͷ
 }data_queue_type; 								     
 extern data_queue_type idata data_queue;					   //�������ݶ���

 

 
  typedef struct sons_struct{
 	/*
	 *  router����״̬
	 */
	uchar_8 linked_father : 1;
 	uchar_8 linked_1 : 1;
	uchar_8 linked_2 : 1;
	uchar_8 linked_3 : 1;	
	uchar_8 : 0;
	
	uchar_8 linked_amount;	//�������ӽڵ�����
 }sons_status_type;
 extern sons_status_type idata sons_status;


 extern uchar_8 host_id[3];


 extern uchar_8 hand_cmd[9] ,
 				hand_ack[9],
				data_request[9],
		 		data_respond[9];




/* ��ն��� */
 extern void empty_queue(void);

/* ������ͷһ֡���ݵ�����������cache */
 extern void queue_read(void);

/* д��һ֡���� */
 extern void queue_append( uchar_8 *message );

/* �ж϶��Ƿ�Ϊ�� */
 extern bit queue_estimate_empty(void);

 extern void clean_serial_buffer(void);

/* �ж϶��Ƿ�Ϊ�� */
 extern bit queue_estimate_full(void);

/* ����������� */
 extern void environment_launch(void);

/* �����յ��ĸ��ڵ�����������ȡ������id */
 extern void rcv_father_hand_creat_host_id(uchar_8 * cmd);

/* ���ݱ���id���ɱ������� */
 extern void id_insert_data(void);

 /* ���ڵ�������ʾ */
 extern void chaeck_linked_worked(void);

/* ���ڽ������ݻ����� */
 extern uchar_8 idata serial_buffer[MESSAGE_LENGTH];

/* �ȴ����շ������ݼ����� */
  extern uint_16 timeout_cnt;

 #endif //__ENVIRONMENT_H__