#ifndef __HELPER_DATETIME_H__
#define __HELPER_DATETIME_H__

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif


/* Useful Constants */
#define SECS_PER_MIN  (60UL)
#define SECS_PER_HOUR (3600UL)
#define SECS_PER_DAY  (SECS_PER_HOUR * 24L)
#define DAYS_PER_WEEK (7L)
#define SECS_PER_WEEK (SECS_PER_DAY * DAYS_PER_WEEK)
#define SECS_PER_YEAR (SECS_PER_WEEK * 52L)
#define SECS_YR_2000  (946681200UL)

#define LEAP_YEAR(_year) ((_year%4)==0)

static const byte monthDays[] PROGMEM = {31,28,31,30,31,30,31,31,30,31,30,31};

void unix_timestamp_to_local(uint32_t *epochp, byte *psec ,byte *pmin, byte *phour, byte *pday, byte *pwday, byte *pmonth, byte *pyear) {
// convert the given time_t to time components
// this is a more compact version of the C library localtime function
  // static byte monthDays[]={31,28,31,30,31,30,31,31,30,31,30,31};

  // time_t long epoch=*timep;
  uint32_t epoch = *epochp;
  
  byte year;
  byte month, monthLength;
  unsigned long days;
  
  *psec=epoch%60;
  epoch/=60; // now it is minutes
  *pmin=epoch%60;
  epoch/=60; // now it is hours
  *phour=epoch%24;
  epoch/=24; // now it is days
  *pwday=(epoch+4)%7;
  
  year=70;  
  days=0;
  while((unsigned)(days += (LEAP_YEAR(year) ? 366 : 365)) <= epoch) {
    year++;
  }
  *pyear=year; // *pyear is returned as years from 1900
  
  days -= LEAP_YEAR(year) ? 366 : 365;
  epoch -= days; // now it is days in this year, starting at 0
  //*pdayofyear=epoch;  // days since jan 1 this year
  
  days=0;
  month=0;
  monthLength=0;
  for (month=0; month<12; month++) {
    if (month==1) { // february
      if (LEAP_YEAR(year)) {
        monthLength=29;
      } else {
        monthLength=28;
      }
    } else {
      monthLength = pgm_read_byte_near(monthDays+month); // monthDays[month];
    }
    
    if (epoch>=monthLength) {
      epoch-=monthLength;
    } else {
        break;
    }
  }
  *pmonth=month+1;  // jan is month 1
  *pday=epoch+1;  // day of month
}

#endif