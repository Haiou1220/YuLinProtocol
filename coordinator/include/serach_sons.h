 #ifndef __SERACH_SONS_H__
 #define __SERACH_SONS_H__

//�����ӽڵ�
 extern  void serach_sons( const uchar_8 rate );

 extern  void link_son(const uchar_8 rate,const uchar_8 linked_port);

/* �������ְ� */
 extern  void send_hand_cmd(const uchar_8 rate, const uchar_8 linked_port );

 extern uint_16 byte_time_out_cnt;
 #endif //__SERACH_SONS_H__