/*************************************************************************************************************
 * 
 * ����ά��һ�����ݶ��У�һ�������б�ṹ�壬һ����־�ṹ��Ĵ�����ʹ��ϵͳ������������	
 * 
 */
 #include <REGX52.H>
 #include "..\\include\\config.h"
 #include "..\\include\\serial.h" 

 #define QUEUE_BUFF_SIZE 10			//��Ϣ���д�С(ʵ�ʶ��д�СΪ��ֵ��һ)
 #define MESSAGE_LENGTH 9			//һ�����ݳ���


 
 uint_16 timeout_cnt = 0;	 		//���ӳ�ʱ������ 

 uchar_8 //hand_cmd[9] 		= {"hq000xxxx"},
 		 hand_cmd[9] 		= {"hhhhhhhhh"},
 		 hand_ack[9] 		= {"ha000001x"},
		 //data_request[9] 	= {"dq000222x"},
		 data_request[9] 	= {"ddddddddd"},
		 data_respond[9] 	= {"da000254x"}; 

/* ���ڽ������ݻ����� */
 uchar_8 idata serial_buffer[MESSAGE_LENGTH] = {0};
 




 /*  ����������cache */
 typedef struct  data_processed_struct{
  		uchar_8 cmd[MESSAGE_LENGTH];
		uchar_8 dirty;				//�����Ƿ�Ϊ��
 }data_processed_type;

 data_processed_type  data_processed;





 typedef struct data_queue_struct{	  
 	/*
	 *  �����Ϣ���д洢��·������������Ϣ�����������ն���ת��
	 */
	uchar_8  data_buff[QUEUE_BUFF_SIZE][MESSAGE_LENGTH]; 		
	uchar_8  data_queue_rear;					   	//��β
	uchar_8  data_queue_head;					   	//��ͷ
 }data_queue_type; 
 								     
 data_queue_type idata data_queue;					//�������ݶ���


 

 typedef struct sons_struct{
 	/*
	 *  router����״̬
	 */
 	uchar_8 linked_1 : 1;
	uchar_8 linked_2 : 1;
	uchar_8 linked_3 : 1;	
	uchar_8 : 0;

	uchar_8 amount;	//����ڵ��������
 }sons_status_type;

 sons_status_type idata sons_status;

 /* �ӽڵ�����״̬��־�Ĵ�����ʼ�� */

 void sons_status_init(void)
 {
 	sons_status.linked_1 = SON_DISCONNECTED;
	sons_status.linked_2 = SON_DISCONNECTED;
	sons_status.linked_3 = SON_DISCONNECTED;
	sons_status.amount = SONS_AMOUNT;	
 }

/* ����������buffer��ʼ�� */
 void  data_processed_init(void)
 {
	data_processed.dirty = 1;
 	return;
 }



 /*
 struct task{
 	/*
	 *  ����ִ��״̬
	 */
 /*	uint_16 task_1 : 1;
	uint_16 task_2 : 1;
	uint_16 task_3 : 1;	
	uchar_8  : 0;
 }task_status; */



/* ����(task)״̬�Ĵ�����ʼ�� */
 /*void task_status_init(void)
 {
 	task_status.task_1 = TASK_OVER;
	task_status.task_2 = TASK_OVER;
	task_status.task_3 = TASK_OVER;
 }



/* router����״̬�Ĵ�����ʼ�� */
 /*void router_status_init(void)
 {
 	router_status.router_1 = ROUTER_DISCONNECTED;
	router_status.router_2 = ROUTER_DISCONNECTED;
	router_status.router_3 = ROUTER_DISCONNECTED;
 }

/* ��ն��� */
 void empty_queue(void)
 {
 	//data_queue.data_queue_length = 0;
	data_queue.data_queue_rear = 0;
	data_queue.data_queue_head = 0;
	return;	 	
 }

/* ���г�ʼ�� */
 void queue_init(void)
 {
	uchar_8 i,j;


	for( i=0;i<QUEUE_BUFF_SIZE;i++ ){
		for( j=0;j<MESSAGE_LENGTH;j++ ){

			data_queue.data_buff[i][j] = 0;	
		}
	}

//	data_queue.data_queue_length = 0;
	empty_queue();
	return;		
 }



/* �ж϶��Ƿ�Ϊ�� */
 bit queue_estimate_empty(void)
 {
 	 if( data_queue.data_queue_rear == data_queue.data_queue_head ){
	 	return 1;
	 }else{
	 	return 0;
	 }
 }


/* �ж϶��Ƿ�Ϊ�� */
 bit queue_estimate_full(void)
 {
 	 if( data_queue.data_queue_rear + 1 == data_queue.data_queue_head ){
	 	return 1;
	 }else{
	 	return 0;
	 }
 }



/* д��һ֡���� */ 
 void queue_append( uchar_8 *message )
 {
 	uchar_8 i = 0;
 	if( !queue_estimate_full() ){
 
		for( i=0;i<MESSAGE_LENGTH;i++ ){	
			data_queue.data_buff[data_queue.data_queue_rear][i] = *(message + i);	
		}
    
		/* ��β��һ  */
		data_queue.data_queue_rear = ( data_queue.data_queue_rear + 1) % QUEUE_BUFF_SIZE;
	}
	return;
 }




/* ������ͷһ֡���ݵ�����������cache */
 void queue_read(void)
 {
 	uchar_8 i = 0;;

	if( !queue_estimate_empty() ){
		
		for( i=0;i<MESSAGE_LENGTH;i++ ){
			data_processed.cmd[i] = data_queue.data_buff[data_queue.data_queue_head][i];
		}

		data_queue.data_queue_head = (data_queue.data_queue_head + 1) %	MESSAGE_LENGTH;	
			
	}else{
		for( i=0;i<MESSAGE_LENGTH;i++ ){
			data_processed.cmd[i] = '0'; 	//����ӿգ�ȫд��0
		}
	}
	data_processed.dirty = 0;			//����������cache������	
 } 


/* ����������� */
 void environment_launch(void)
 {
 //	task_status_init();
//	router_status_init();
	data_processed_init();
 	queue_init();
	sons_status_init();
	/*do something */
	return; 
 }		

 
 

/*X088MM@B@8BMM8MM8MMMMMM8M88WZ...::i:i:::::::::i.
X22X2SaSX0WMMM8M8MW80W0W00aX2X2    ...............
X2XXWXXSS2SXZ8BM888WMWWWZXXSaS0XX27:..:::::::::::.
2SSXWX2X00X22S0M8MMMMMW8W0XZZ0XaWW02i..:.::::::::.
222222aSa2X088MMMMM88M@WaX0XXS27228XX2i..::::::.:.
0XXX222222XMBBMM8MMWXWX022XS7222222Xa02:.:.:.:.::.
MZ80M8W0XXMBMMMXX0W0X22222SS88Z8M0WXaS02..:.:::::.
MM80WM8MZ08M0WS2XS2XX0MWMMXWZMMBMBBM0000i..:.:.::.
808X8WMMXS0S2a0880XS22M2XBBZXS0ZM8MMM8MM7...:.:.:.
Z0Z8W800S08XXMM8ZX22770a70X2SX2SXXXMMBM@2..:.:.:..
8XX0808ZSSW8MB82XS2227X222XS2SXaXaX0M8BB2 ....... 
88S008B@0XWMMBX2S2r7:.ri7277:.irr220ZMB@27:. ... i
80M88W@BMX88M8S77i:i::i:r7iirirrri720M@B77ii..:.7M
WZ8808B@B8M@M277722aWMZ0a0a0XM8ZX0SSaMB2 7SZX0X2X8
808000BB@X0W2XZ28808@M88W2800M@MM80SWW87::27200SSa
8ZWZXWB@B020X7277aZMMM0@2.S@XW0XS2727WX227222XX0XS
MZMW8M@BB8S2Xi::  :72722  r0277ri..770S.280XSS0XSa
MMWZMB27M@0XX2r7::...ir    .227777722Xi  r00Sa2220
W0W2MZ .SS8222S272aS80:r7;777222X22222S022MX80S7XX
: 7772.i2X80SX222XX2r.S@MW8@2  :7S222S00aXX0MZ2X0X
. ii7..:i7ri7;a2222.   :7XXai.ii72222222SSXS00S222
 .i70r.:r022aiiX22272X222aXXS8Wa2222222a2Sa22S22XM
. .:. .:::i:i. 22222X002rr772aa22222a2XSSSaS228B@0
   ..:.    ... r227222222XSS22222228ZXX0X0XaSXM87.
  . .:i.  ::::. 22272222S2222222220W8WWXaX00aa0722
  .. .:727riri:;2S2277777272222a22a7 .::77r;;rr772
.  .  :X  222222S2222222222SaSXSS2a7  ..00XX022227
.      :.:222Z8X222222222aSS2S2S2aXS7.  7:  7MMM7;
i . .i7r22222 .X2777222222222222S2SSX2Z02:   7:.77
 :X22S22772a:  .Sa2222222222222S222Xa0S8B@@077;r77
 72777777727    .2X222222222222222aa27.iBMS2222227
r7777777722.     .;72SSS2S22222S2S27:..:aW72727227
27777777727       .::i77222227277r:.::ii:222277727
7777777772.        ..:::.:.....:.::i:ir: r22227777
2r7777772r            .:::i:::::iii.:;:  rS2272227
777277722                 .iiii;:.  ::  ..2S227222
27277722                    ii:.          7a222222
227772S:                                   2222222
..r72a7                                    7X22222
r722X7       .;:.   :.       .             :Xa2222
272Xr        iiii.  :::.   ..               2X2222
272;         :  ..:   .                      a22*/
  

