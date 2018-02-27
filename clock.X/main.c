/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC24 / dsPIC33 / PIC32MM MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - pic24-dspic-pic32mm : v1.45
        Device            :  PIC32MM0064GPL036
    The generated drivers are tested against the following:
        Compiler          :  XC32 1.43
        MPLAB             :  MPLAB X 3.61
*/

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

#include "mcc_generated_files/mcc.h"
#include <stdio.h>
 

struct tm currentTime,initialTime;
unsigned char i=0;
char hour[0],min[0],sec[0],year[0],mon[0],day[0],week[0];


void SPI_WriteByte(unsigned char data,unsigned char cmd)
{
    unsigned char i=0;
    OLED_DC_Clr();
    OLED_SCLK_Clr();
    for(i=0;i<8;i++)
    {
        OLED_SCLK_Clr();
        if(data&0x80)
            OLED_SDIN_Set(); 
        else OLED_SDIN_Clr();
        OLED_SCLK_Set();
        data<<=1;
    }
    OLED_SCLK_Set();
    OLED_DC_Set();
}




/* ************************************************************************** */

/** 
  @Function
    int ExampleLocalFunctionName ( int param1, int param2 ) 

  @Summary
    Brief one-line description of the function.

  @Description
    Full description, explaining the purpose and usage of the function.
    <p>
    Additional description in consecutive paragraphs separated by HTML 
    paragraph breaks, as necessary.
    <p>
    Type "JavaDoc" in the "How Do I?" IDE toolbar for more information on tags.

  @Precondition
    List and describe any required preconditions. If there are no preconditions,
    enter "None."

  @Parameters
    @param param1 Describe the first parameter to the function.
    
    @param param2 Describe the second parameter to the function.

  @Returns
    List (if feasible) and describe the return values of the function.
    <ul>
      <li>1   Indicates an error occurred
      <li>0   Indicates an error did not occur
    </ul>

  @Remarks
    Describe any special behavior not described above.
    <p>
    Any additional remarks.

  @Example
    @code
    if(ExampleFunctionName(1, 2) == 0)
    {
        return 3;
    }
 */
void OLED_WR_Byte(u8 dat,u8 cmd)
{	
	u8 i;			  
	if(cmd)
	  OLED_DC_Set();
	else 
	  OLED_DC_Clr();		  
	OLED_CS_Clr();
	for(i=0;i<8;i++)
	{			  
		OLED_SCLK_Clr();
		if(dat&0x80)
		   OLED_SDIN_Set();
		else 
		   OLED_SDIN_Clr();
		OLED_SCLK_Set();
		dat<<=1;   
	}				 		  
	OLED_CS_Set();
	OLED_DC_Set();   	  
} 


void OLED_Set_Pos(unsigned char x, unsigned char y) 
{ 
	OLED_WR_Byte(0xb0+y,OLED_CMD);
	OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);
	OLED_WR_Byte((x&0x0f)|0x01,OLED_CMD); 
}   	  


void OLED_Display_On(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  
	OLED_WR_Byte(0X14,OLED_CMD);  //DCDC ON
	OLED_WR_Byte(0XAF,OLED_CMD);  //DISPLAY ON
}
   
void OLED_Display_Off(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  
	OLED_WR_Byte(0X10,OLED_CMD);  //DCDC OFF
	OLED_WR_Byte(0XAE,OLED_CMD);  //DISPLAY OFF
}		   			 
	  
void OLED_Clear(void)  
{  
	u8 i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    
		OLED_WR_Byte (0x02,OLED_CMD);      
		OLED_WR_Byte (0x10,OLED_CMD);        
		for(n=0;n<128;n++)OLED_WR_Byte(0,OLED_DATA); 
	} 
}



void OLED_ShowChar(u8 x,u8 y,u8 chr)
{      	
	unsigned char c=0,i=0;	
		c=chr-' ';		
		if(x>Max_Column-1){x=0;y=y+2;}
		if(SIZE ==16)
			{
			OLED_Set_Pos(x,y);	
			for(i=0;i<8;i++)
			OLED_WR_Byte(F8X16[c*16+i],OLED_DATA);
			OLED_Set_Pos(x,y+1);
			for(i=0;i<8;i++)
			OLED_WR_Byte(F8X16[c*16+i+8],OLED_DATA);
			}
			else {	
				OLED_Set_Pos(x,y+1);
				for(i=0;i<6;i++)
				OLED_WR_Byte(F6x8[c][i],OLED_DATA);
				
			}
}

u32 oled_pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}				  

void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size)
{         	
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/oled_pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				OLED_ShowChar(x+(size/2)*t,y,' ');
				continue;
			}else enshow=1; 
		 	 
		}
	 	OLED_ShowChar(x+(size/2)*t,y,temp+'0'); 
	}
} 

void OLED_ShowString(u8 x,u8 y,u8 *chr)
{
	unsigned char j=0;
    
	while (chr[j]!='\0')
	{		OLED_ShowChar(x,y,chr[j]);
			x+=8;
		if(x>120){x=0;y+=2;}
			j++;
	}
}

void OLED_ShowCHinese(u8 x,u8 y,u8 no)
{      			    
	u8 t,adder=0;
	OLED_Set_Pos(x,y);	
    for(t=0;t<16;t++)
		{
				OLED_WR_Byte(Hzk[2*no][t],OLED_DATA);
				adder+=1;
     }	
		OLED_Set_Pos(x,y+1);	
    for(t=0;t<16;t++)
			{	
				OLED_WR_Byte(Hzk[2*no+1][t],OLED_DATA);
				adder+=1;
      }					
}


void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[])
{ 	
 unsigned int j=0;
 unsigned char x,y;
  
  if(y1%8==0) y=y1/8;      
  else y=y1/8+1;
	for(y=y0;y<y1;y++)
	{
		OLED_Set_Pos(x0,y);
    for(x=x0;x<x1;x++)
	    {      
	    	OLED_WR_Byte(BMP[j++],OLED_DATA);	    	
	    }
	}
}

void delay(uint x){
    
    uint a,b;
    for(a=x;a>0;a--)
        for(b=724;b>0;b--);
}


void OLED_Init(void)
{
    OLED_RST_Set();
	//__delay_ms(100);
	OLED_RST_Clr();
	//__delay_ms(100);
	OLED_RST_Set(); 
					  
	OLED_WR_Byte(0xAE,OLED_CMD);//--turn off oled panel
	OLED_WR_Byte(0x02,OLED_CMD);//---set low column address
	OLED_WR_Byte(0x10,OLED_CMD);//---set high column address
	OLED_WR_Byte(0x40,OLED_CMD);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_WR_Byte(0x81,OLED_CMD);//--set contrast control register
	OLED_WR_Byte(0xCF,OLED_CMD); // Set SEG Output Current Brightness
	OLED_WR_Byte(0xA1,OLED_CMD);//--Set SEG/Column Mapping     0xa0×óÓÒ·´ÖÃ 0xa1Õý³£
	OLED_WR_Byte(0xC8,OLED_CMD);//Set COM/Row Scan Direction   0xc0ÉÏÏÂ·´ÖÃ 0xc8Õý³£
	OLED_WR_Byte(0xA6,OLED_CMD);//--set normal display
	OLED_WR_Byte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
	OLED_WR_Byte(0x3f,OLED_CMD);//--1/64 duty
    OLED_WR_Byte(0x81,OLED_CMD); 
	OLED_WR_Byte(0xfF,OLED_CMD); //1~255;Ä¬ÈÏ0X7F (ÁÁ¶ÈÉèÖÃ,Ô½´óÔ½ÁÁ)
	OLED_WR_Byte(0xD3,OLED_CMD);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_WR_Byte(0x00,OLED_CMD);//-not offset
	OLED_WR_Byte(0xd5,OLED_CMD);//--set display clock divide ratio/oscillator frequency
	OLED_WR_Byte(0x80,OLED_CMD);//--set divide ratio, Set Clock as 100 Frames/Sec
	OLED_WR_Byte(0xD9,OLED_CMD);//--set pre-charge period
	OLED_WR_Byte(0xF1,OLED_CMD);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLED_WR_Byte(0xDA,OLED_CMD);//--set com pins hardware configuration
	OLED_WR_Byte(0x12,OLED_CMD);
	OLED_WR_Byte(0xDB,OLED_CMD);//--set vcomh
	OLED_WR_Byte(0x40,OLED_CMD);//Set VCOM Deselect Level
	OLED_WR_Byte(0x20,OLED_CMD);//-Set Page Addressing Mode (0x00/0x01/0x02)
	OLED_WR_Byte(0x02,OLED_CMD);//
	OLED_WR_Byte(0x8D,OLED_CMD);//--set Charge Pump enable/disable
	OLED_WR_Byte(0x14,OLED_CMD);//--set(0x10) disable
	OLED_WR_Byte(0xA4,OLED_CMD);// Disable Entire Display On (0xa4/0xa5)
	OLED_WR_Byte(0xA6,OLED_CMD);// Disable Inverse Display On (0xa6/a7) 
	OLED_WR_Byte(0xAF,OLED_CMD);//--turn on oled panel
	
	OLED_WR_Byte(0xAF,OLED_CMD); /*display ON*/ 
   // OLED_WR_Byte(0xA7,OLED_CMD);
	OLED_Clear();
	OLED_Set_Pos(0,0); 
    
}


void show_time(){

    if(RTCC_TimeGet(&currentTime)){
        sprintf(hour,"%02d",currentTime.tm_hour);OLED_ShowString(0,0,hour);
        OLED_ShowString(16,0,":");
        sprintf(min,"%02d",currentTime.tm_min);OLED_ShowString(24,0,min);
        OLED_ShowString(40,0,":");
        sprintf(sec,"%02d",currentTime.tm_sec);OLED_ShowString(48,0,sec);
            
        sprintf(week,"%d",currentTime.tm_wday);OLED_ShowString(112,0,week);
            
        sprintf(year,"20%02d",currentTime.tm_year);OLED_ShowString(22,3,year);
        OLED_ShowString(54,3,"-");
        sprintf(mon,"%02d",currentTime.tm_mon);OLED_ShowString(62,3,mon);
        OLED_ShowString(78,3,"-");
        sprintf(day,"%02d",currentTime.tm_mday);OLED_ShowString(86,3,day);
       
            
    }
    OLED_ShowCHinese(0,6,0);
	OLED_ShowCHinese(18,6,1);
	OLED_ShowCHinese(36,6,2);
	OLED_ShowCHinese(54,6,3);
	OLED_ShowCHinese(72,6,4);
	OLED_ShowCHinese(90,6,5);
	OLED_ShowCHinese(108,6,6);
}


void key_scan(){
    
    uint16_t portValue1 = KEY1_GetValue();
    uint16_t portValue2 = KEY2_GetValue();
    uint16_t portValue3 = KEY3_GetValue();
    uint16_t portValue4 = KEY4_GetValue();
    
    if(portValue3){
        delay(250);
        if(portValue3){   
           i++;
           if(i==7){
               i=0;
           }
        }
    }
    
   // while(portValue3);
    if(i==1&&portValue1){
        delay(250);
        while(!portValue1);
            initialTime.tm_hour = (currentTime.tm_hour+1<24)?(currentTime.tm_hour+1):0;
            initialTime.tm_min = currentTime.tm_min;initialTime.tm_sec = currentTime.tm_sec;
            initialTime.tm_year = currentTime.tm_year;initialTime.tm_mon = currentTime.tm_mon;
            initialTime.tm_mday = currentTime.tm_mday;initialTime.tm_wday = currentTime.tm_wday;
            RTCC_TimeSet(&initialTime);                   
    }
    if(i==1&&portValue2){
        delay(250);
        while(!portValue2);
            initialTime.tm_hour = (currentTime.tm_hour-1>=0)?(currentTime.tm_hour-1):23;
            initialTime.tm_min = currentTime.tm_min;initialTime.tm_sec = currentTime.tm_sec;
            initialTime.tm_year = currentTime.tm_year;initialTime.tm_mon = currentTime.tm_mon;
            initialTime.tm_mday = currentTime.tm_mday;initialTime.tm_wday = currentTime.tm_wday;
            RTCC_TimeSet(&initialTime);   
    }
    
    if(i==2&&portValue1){
        delay(250);
        while(!portValue1);
            initialTime.tm_min = (currentTime.tm_min+1<60)?(currentTime.tm_min+1):0;
            initialTime.tm_hour = currentTime.tm_hour;initialTime.tm_sec = currentTime.tm_sec;
            initialTime.tm_year = currentTime.tm_year;initialTime.tm_mon = currentTime.tm_mon;
            initialTime.tm_mday = currentTime.tm_mday;initialTime.tm_wday = currentTime.tm_wday;
            RTCC_TimeSet(&initialTime);          
    } 
    if(i==2&&portValue2){
        delay(250);
        while(!portValue2);
            initialTime.tm_min = (currentTime.tm_min-1>=0)?(currentTime.tm_min-1):59;
            initialTime.tm_hour = currentTime.tm_hour;initialTime.tm_sec = currentTime.tm_sec;
            initialTime.tm_year = currentTime.tm_year;initialTime.tm_mon = currentTime.tm_mon;
            initialTime.tm_mday = currentTime.tm_mday;initialTime.tm_wday = currentTime.tm_wday;
            RTCC_TimeSet(&initialTime); 
    }
    
    if(i==3&&portValue1){
        delay(250);
        while(!portValue1);
            initialTime.tm_wday = (currentTime.tm_wday+1<8)?(currentTime.tm_wday+1):1;
            initialTime.tm_hour = currentTime.tm_hour;initialTime.tm_sec = currentTime.tm_sec;
            initialTime.tm_year = currentTime.tm_year;initialTime.tm_mon = currentTime.tm_mon;
            initialTime.tm_mday = currentTime.tm_mday;initialTime.tm_min = currentTime.tm_min;
            RTCC_TimeSet(&initialTime);          
    } 
    if(i==3&&portValue2){
        delay(250);
        while(!portValue2);
            initialTime.tm_wday = (currentTime.tm_wday-1>0)?(currentTime.tm_wday-1):7;
            initialTime.tm_hour = currentTime.tm_hour;initialTime.tm_sec = currentTime.tm_sec;
            initialTime.tm_year = currentTime.tm_year;initialTime.tm_mon = currentTime.tm_mon;
            initialTime.tm_mday = currentTime.tm_mday;initialTime.tm_min = currentTime.tm_min;
            RTCC_TimeSet(&initialTime); 
    }
    
    if(i==4&&portValue1){
        delay(250);
        while(!portValue1); 
            initialTime.tm_year = (currentTime.tm_year+1<100)?(currentTime.tm_year+1):0;
            initialTime.tm_hour = currentTime.tm_hour;initialTime.tm_sec = currentTime.tm_sec;
            initialTime.tm_wday = currentTime.tm_wday;initialTime.tm_mon = currentTime.tm_mon;
            initialTime.tm_mday = currentTime.tm_mday;initialTime.tm_min = currentTime.tm_min;
            RTCC_TimeSet(&initialTime);          
    } 
    if(i==4&&portValue2){
        delay(250);
        while(!portValue2);
            initialTime.tm_year = (currentTime.tm_year-1>=0)?(currentTime.tm_year-1):99;
            initialTime.tm_hour = currentTime.tm_hour;initialTime.tm_sec = currentTime.tm_sec;
            initialTime.tm_wday = currentTime.tm_wday;initialTime.tm_mon = currentTime.tm_mon;
            initialTime.tm_mday = currentTime.tm_mday;initialTime.tm_min = currentTime.tm_min;
            RTCC_TimeSet(&initialTime); 
    }
    
    if(i==5&&portValue1){
        delay(250);
        while(!portValue1);
            initialTime.tm_mon = (currentTime.tm_mon+1<13)?(currentTime.tm_mon+1):1;
            initialTime.tm_hour = currentTime.tm_hour;initialTime.tm_sec = currentTime.tm_sec;
            initialTime.tm_year = currentTime.tm_year;initialTime.tm_wday = currentTime.tm_wday;
            initialTime.tm_mday = currentTime.tm_mday;initialTime.tm_min = currentTime.tm_min;
            RTCC_TimeSet(&initialTime);          
    } 
    if(i==5&&portValue2){
        delay(250);
        while(!portValue2);
            initialTime.tm_mon = (currentTime.tm_mon-1>0)?(currentTime.tm_mon-1):12;
            initialTime.tm_hour = currentTime.tm_hour;initialTime.tm_sec = currentTime.tm_sec;
            initialTime.tm_year = currentTime.tm_year;initialTime.tm_wday = currentTime.tm_wday;
            initialTime.tm_mday = currentTime.tm_mday;initialTime.tm_min = currentTime.tm_min;
            RTCC_TimeSet(&initialTime); 
    }
    
    if(i==6&&portValue1){
        delay(250);
        while(!portValue1);  
            initialTime.tm_mday = (currentTime.tm_mday+1<32)?(currentTime.tm_mday+1):1;
            initialTime.tm_hour = currentTime.tm_hour;initialTime.tm_sec = currentTime.tm_sec;
            initialTime.tm_year = currentTime.tm_year;initialTime.tm_mon = currentTime.tm_mon;
            initialTime.tm_wday = currentTime.tm_wday;initialTime.tm_min = currentTime.tm_min;
            RTCC_TimeSet(&initialTime);          
    } 
    if(i==6&&portValue2){
        delay(250);
        while(!portValue2);
            initialTime.tm_mday = (currentTime.tm_mday-1>0)?(currentTime.tm_mday-1):31;
            initialTime.tm_hour = currentTime.tm_hour;initialTime.tm_sec = currentTime.tm_sec;
            initialTime.tm_year = currentTime.tm_year;initialTime.tm_mon = currentTime.tm_mon;
            initialTime.tm_wday = currentTime.tm_wday;initialTime.tm_min = currentTime.tm_min;
            RTCC_TimeSet(&initialTime); 
    }
    
    if(portValue4){
        delay(250);
        if(portValue4){
            
            i=0;
        }
    }
}

/*
                         Main application
 */
int main(void)
{
     
    // initialize the device
    SYSTEM_Initialize();   
    // When using interrupts, you need to set the Global Interrupt Enable bits
    // Use the following macros to:
    OLED_Init();
    OLED_Clear();
    // Enable the Global Interrupts
    INTERRUPT_GlobalEnable();
  
    // Disable the Global Interrupts
    //INTERRUPT_GlobalDisable();
   // OLED_ShowString(25,0,"microchip");
    while (1)
    {
        // Add your application code 
       key_scan();
    }
}
/**
 End of File
*/