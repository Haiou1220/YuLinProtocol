
 #ifndef __DS18B20_H__
 #define __DS18B20_H__

//=======================��������==================================
 extern	unsigned char	data	IntgerM;
 extern	unsigned char	data	IntgerL;
 extern	unsigned char	data	DecimalH;
 extern	unsigned char	data	DecimalMH;			
//=======================���ú���===================================

 extern  bit Init18B20(void);		//��ʼ��
 extern  void	MnDS18B20(void);

 #endif //__DS18B20_H__