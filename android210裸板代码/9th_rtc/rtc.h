#ifndef RTC_H_
#define RTC_H_

#define RTC_BASE				(0xE2800000)
#define		INTP      		 ( *((volatile unsigned long *)(RTC_BASE + 0x30)) )
#define		RTCCON    	 ( *((volatile unsigned long *)(RTC_BASE + 0x40)) )
#define		TICCNT    	 ( *((volatile unsigned long *)(RTC_BASE + 0x44)) )
#define		RTCALM    	 ( *((volatile unsigned long *)(RTC_BASE + 0x50)) )
#define		ALMSEC    	 ( *((volatile unsigned long *)(RTC_BASE + 0x54)) )
#define		ALMMIN    	 ( *((volatile unsigned long *)(RTC_BASE + 0x58)) )
#define		ALMHOUR  	 ( *((volatile unsigned long *)(RTC_BASE + 0x5c)) )
#define		ALMDATE    	 ( *((volatile unsigned long *)(RTC_BASE + 0x60)) )
#define		ALMMON    	 ( *((volatile unsigned long *)(RTC_BASE + 0x64)) )
#define		ALMYEAR  	 ( *((volatile unsigned long *)(RTC_BASE + 0x68)) )
#define		RTCRST     	 ( *((volatile unsigned long *)(RTC_BASE + 0x6c)) )
#define		BCDSEC    	 ( *((volatile unsigned long *)(RTC_BASE + 0x70)) )
#define		BCDMIN   	 ( *((volatile unsigned long *)(RTC_BASE + 0x74)) )
#define		BCDHOUR    	 ( *((volatile unsigned long *)(RTC_BASE + 0x78)) )
#define		BCDDATE    	 ( *((volatile unsigned long *)(RTC_BASE + 0x7c)) )
#define		BCDDAY     	 ( *((volatile unsigned long *)(RTC_BASE + 0x80)) )
#define		BCDMON     	 ( *((volatile unsigned long *)(RTC_BASE + 0x84)) )
#define		BCDYEAR     	 ( *((volatile unsigned long *)(RTC_BASE + 0x88)) )
#define		CURTICCNT   	 ( *((volatile unsigned long *)(RTC_BASE + 0x90)) )
#define		RTCLVD    	 ( *((volatile unsigned long *)(RTC_BASE + 0x94)) )

typedef unsigned long u32 ;
void rtc_enable(unsigned char bdata);
void rtc_ticktime_enable(unsigned char bdata);
void Dispay_time(void);
void rtc_settime(void);
typedef struct RTC_TIMER{
	unsigned long year;
	unsigned long month;
	unsigned long date;
	unsigned long day;
	unsigned long hour;
	unsigned long min;
	unsigned long sec;
	};
#endif