/*---------------------------------------------------------------------------------
  --
  ---------------------------------------------------------------------------------
  --                                        
  --
  --
  --
  ---------------------------------------------------------------------------------
 */

/*************************************************************************************************************
 * 
 * YuLinProtocol,simulate Zigebee Protocol,
 * Because of unbeknown reasons , the begin of system may occur error.
 * frist sending a '0'. 
 * 
 */
 #include <REGX52.H>
 #include "..\\include\\config.h" 
 #include "..\\include\\hardware_config.h"
 #include "..\\include\\serial.h" 
 #include "..\\include\\environment.h"
 #include "..\\include\\req_son_data.h" 
 #include "..\\include\\rcv_father_cmd.h" 
 #include "..\\include\\serach_sons.h"
 #include "..\\application\\ds18b20.h"  	 


 void delay_for_debug(void);
	
 sbit test_led_7 = P1^7;

 void main(void)
 {
 	uchar_8 q1[9] = {"zhangte  "},
			q2[9] = {"world   "}; 
	
	uchar_8 a = 0;	
			 
	delay_for_debug();
	hardware_launch();
	environment_launch();
	
	queue_append(q1);
	queue_append(q2);	
	  
	/* oh my god , who will able to give me some lovely gree pot in github??  */
    /* i am so sorrow */
	print_stream(sizeof("system have be launched by ����:\r\n"),BAUD_4800,0,"system have be launched by ����:\r\n");

	send_hand_cmd(BAUD_4800,FATHER_PORT);

	GPIO_1(0) = 1;
	GPIO_1(1) = 1;

	GPIO_1(4) = 1;
	GPIO_1(6) = 1;

	/* 
	 * �໥�����Ѿ��ɹ� 
	 * Ŀǰ����ծ��: ��Ҫȷ����ʼ���������ţ�������������debug�õ�ledȫ����������Ǳ���ϵͳ����ָʾ��
	 * 				 Ȼ���������
	 *				 ������ݴ������񣬲���װAPI
	 */
	for( ;; ){

		//if(GPIO_1(0) == 1){
		//	GPIO_1(5) = 0;
		//}  
	//	GPIO_1(0) = 1;
		//hao hhhh
		//print_stream(sizeof("hello,world!"),BAUD_4800,0,"hello,world!");
	//	delay_for_debug(); 
	//	rcv_father_data(BAUD_4800);

	//	link_son(BAUD_4800,FATHER_PORT);
		//	send_queue_to_father(BAUD_4800);
		serach_sons(BAUD_4800);	
	//	link_son(BAUD_4800,FATHER_PORT);			
	//	delay_for_debug();
	//	send_hand_cmd(BAUD_4800,FATHER_PORT);
	//	serial_write_byte( BAUD_4800,FATHER_PORT,' ' );
		/*if( outside_data_coming() ){
		//	a = serial_0_read_byte(BAUD_4800);
 			a = serial_read_byte(BAUD_4800,FATHER_PORT);
			serial_write_byte( BAUD_4800,FATHER_PORT,a );
 		}  */
	} 
 }



/********************
 * ��������ʱ����
 */
 void delay_for_debug(void)
 {
	unsigned char 	i,
					j;

	for( i=0; i<250; i++ )
		for( j=0; j<120; j++ )
		;
 }



/* 	                                                                                                    
                          =   ==   => /                                                             
                         +# = #= +  $=>>  =                                                         
                     =+%>=$%=/#%+%>%+/ +>/+>+=                                                      
                    >=+$%#+#>%$#%##$=+$$/+$+=  >=                                                   
                  >>/%#%###########+#######>==+#>  /                                                
             =%+//>$%#%#########################%%#/==                         
              +$+##+#########%##################$$%+/=                        
             ==/+$#########=  =$#######>>#######$##>=                             
          //=/%#$#########                +######$%%++$+                       
         =>/+$############=                #########%%>=                        
           /$##############%=             %######$#$+>=/+                        
         =>>+%$###############%/>     =/$############$+%/=                  
        =>/%%$$#########################################/                 
         ==>+%#######################################$%/>=                    
        =>+##$$######################################++>=                   
         /+++$#####################################$%$%/+>                    
          >>>++####################################+>/+%=                                           
            >>%#####################################$%/=                                            
             >$##################################/+>/==>                                            
            /#%/>################################+>//                                        
            =   %+$%##$######################$$//+%%>>                        
                = >$#/$$#####################$+=                                 
                  >>/+=##############%/+#+$##%+>                                 
                      +%%###%%##%%%#% > +//= //%                               
                     >  +>=+>+=%>=##$=> = =                                    
                          =   =   #>//                                          
            >//=                =$                                                
               /%+             =%     >/+++/>                                     
                 =$%          >%  +###$+>====>=                                              
                   /#>       >%/##$>                                                                
                    =#+     >###/                                                                   
                     =#%   >#%=                                                         
                      =#+  #                                                   
                       %#>+/                                                 
                        ###                                                     
                        /#%                                                   
                         #/                                                 
                         /+    //=                                                
                         >%  %+                                                
                          # #+                                                
                          $+#                                                  
                           #%                                                                  
                           >$                                                                   
                            #                                                                       
                            /+                                                                      
                             #                                                                      
                             $                                                                      
                             %                                                                      
                             = 
*/

































