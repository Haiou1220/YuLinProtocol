 #ifndef __RCV_FATHER_CMD_H__
 #define __RCV_FATHER_CMD_H__

 
/* �Ӹ��ڵ�������� */
 extern void rcv_father_data(const uchar_8 rate);

/* �򸸽ڵ㷢�����ݶ����������� */
 extern void send_queue_to_father(const uchar_8 rate);

/* ������ʱ */
 extern void send_delay(const uchar_8 delay_time ) ;

 extern  void temporary_rcv_sons(const uchar_8 rate);

 extern	 void  temporary_send_data(const uchar_8 rate,const uchar_8 number_port,uchar_8 *cmd );
 #endif //__RCV_FATHER_CMD_H__