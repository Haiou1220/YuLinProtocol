 //#include "..\\include\\config.h" 
 #ifndef __SERIAL_H__
 #define __SERIAL_H__

/* ����0����һ���ַ� */ 
 extern void serial_0_write_byte(const uchar_8 rate,uchar_8 input);

/* ���ڷ���byte����  */
 extern void serial_write_byte(const uchar_8 rate,const uchar_8 serial_number,uchar_8 input);

/* ���ڽ���byte���� */
 extern uchar_8 serial_read_byte(const uchar_8 rate,const uchar_8 serial_number);

/* RXD_0����һ���ַ� */  
 extern uchar_8 serial_0_read_byte(const uchar_8 rate);
 
/* �ⲿ���������� */
 extern uchar_8 outside_data_coming(void); 

/* ����ַ��� */ 
 extern void print_stream(const uchar_8 data_size,const uchar_8 rate,const uchar_8 serial_number, uchar_8 * pstream);  
 
/* ����������� */ 
 extern uchar_8 idata hand_cmd_buffer[9];

/* ����ȷ���źŻ����� */
 extern uchar_8 idata hand_ack_buffer[9]; 

 #define BYTE_TIME_OUT 50		//����һ��byte�ĳ�ʱʱ��

 #define BAUD_4800 1			//������4800����
 #define BAUD_9600 2			//������9600����

 #endif //__SERIAL_H__