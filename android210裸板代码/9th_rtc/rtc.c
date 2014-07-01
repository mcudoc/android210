
#include "rtc.h"
#include "stdio.h"


char *day[8] = {" ","Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};



struct RTC_TIMER Timer;

// ʹ��/�ر�rtc������
void rtc_enable(unsigned char bdata)
{
	unsigned long uread;
	uread = RTCCON;
	RTCCON = (uread&~(1<<0))|(bdata);
}

// ʹ��/�ر�Tick timer
void rtc_ticktime_enable(unsigned char bdata)
{
	unsigned long uread;
	uread = RTCCON;
	RTCCON = ( (uread&~(1<<8)) | (bdata<<8) );
}

//��ʾʱ��
void Dispay_time(void)
{
	unsigned char i;
	read_rtctime();
	i = Timer.day;
	printf("%2x : %2x : %2x  %10s,  %2x/%2x/%4x\n", Timer.hour, Timer.min, Timer.sec, day[i], Timer.month, Timer.date, Timer.year);
}

//��ȡRTCʱ��
void read_rtctime()
{
		// ʹ��rtc������
	rtc_enable(1);
	// ʹ��rtc tick timer
	rtc_ticktime_enable(1);

	Timer.year = 0x2000 + BCDYEAR;
	Timer.month= BCDMON;
	Timer.date = BCDDATE;
	Timer.day  = BCDDAY;
	Timer.hour = BCDHOUR;
	Timer.min  = BCDMIN;
	Timer.sec  = BCDSEC;
	
	// �ر�rtc������
	rtc_ticktime_enable(0);
	// �ر�rtc tick timer
	rtc_enable(0);
}

/* ����RTC */

void rtc_settime(void)
{
	// ��ʼֵΪ����ֵ
	unsigned long year = 14;
	unsigned long month = 07;
	unsigned long date = 1;
	unsigned long hour = 12;
	unsigned long min = 32;
	unsigned long sec = 10;
	unsigned long weekday= 2;

	//��ʱ��ת��ΪBCD��
	year = ( ((year/100)<<8) +(((year/10)%10)<<4) + (year%10)  );
	month  = ( ((month/10)<<4)+ (month%10) );
	date = ( ((date/10)<<4) + (date%10) );
	weekday = (weekday%10);							
	hour =( ((hour/10)<<4) + (hour%10) );
	min  =( ((min/10)<<4)  + (min%10) );
	sec  =( ((sec/10)<<4)  + (sec%10) );

	rtc_enable(1);
	// ����BCD��
	BCDSEC  = sec;
	BCDMIN  = min;
	BCDHOUR = hour;
	BCDDATE = date;
	BCDDAY  = weekday;
	BCDMON  = month;
	BCDYEAR = year;
	rtc_enable(0);
	
	printf("reset success\r\n");
}