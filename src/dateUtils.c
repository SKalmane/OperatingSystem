#include "dateUtils.h"

struct monthFromDays {
  char *monthName;
  int daysInMonth;
} listOfMonths[] = {{"January", 31},
		    {"February", 28},
		    {"March", 31},
		    {"April", 30},
		    {"May", 31},
		    {"June", 30},
		    {"July", 31},
		    {"August", 31},
		    {"September", 30},
		    {"October", 31},
		    {"November", 30},
		    {"December", 31}};

int IsLeapYear(int year) {
  return ((year % 4) == 0 &&
	  ((year % 100 != 0) ||
	   (year % 400) == 0));
}

char *getMonthFromDays(long *days,long int year) {
  int monthIndex = 0, daysInMonth = 0;
  while(monthIndex < 12) {
    daysInMonth =
      listOfMonths[monthIndex].daysInMonth +
      ((monthIndex == 1) ? IsLeapYear(year) : 0);
    if(*days >= daysInMonth) {
      monthIndex++;
      *days -= daysInMonth;
      continue;
    } else {
      break;
    }
  }

  return listOfMonths[monthIndex].monthName;
}

long int getYearFromDays(long int *days) {
  long int years = 0, numOfLeapYears = 0, numOfNonLeapYears = 0,
    yearIndex = 0, addExtraDayForLeapYear = 0;
  long int dayVal = *days;
  
  // Let us first get an estimate of the number of years
  years = (long) (dayVal/366);
  
  for(yearIndex = 1970; yearIndex < 1970 + (int)(years); yearIndex++) {
    if(IsLeapYear(yearIndex)) {
      numOfLeapYears++;
    } else {
      numOfNonLeapYears++;
    }
  }

  years = (long) (1970 + years);
  dayVal = dayVal - (numOfNonLeapYears * 365 + numOfLeapYears * 366);
  
  if(dayVal >= 365) {
    yearIndex = years;
    while(dayVal >= 365) {
      yearIndex++;
      if(IsLeapYear(yearIndex)) {
	addExtraDayForLeapYear = 1;
      } else {
	addExtraDayForLeapYear = 0;
      }
      dayVal = dayVal - (365 + addExtraDayForLeapYear);      
    }
    years = yearIndex;
  }
  *days = dayVal;
  
  return years;
}
