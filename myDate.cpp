// Name: Aveline Villaganas
// Class (CECS 282-04)
// Project Name (Program 3 - Structs and Pointers)
// Due Date (3/15/2022)
//
// I certify that this program is my own original work. I did not copy any part of this program from any other source. 
// I further certify that I typed each and every line of code in this program.

#include "myDate.h"
#include <iostream>
using namespace std;

// Calendar Conversions =============================================

/* Converts date from Gregorian to Julian Calendar 
 * IN: int month, int day, int year
 * OUT: int julian date 
 */
int Greg2Julian(int month, int day, int year){
  //double testTrunc = 17.835;
  //cout << (int)(testTrunc) << endl; 
  double signChunk = 100*year + month - 190002.5;
  int sign = 1; 
  if(signChunk < 0){
    sign = -1;
  }
  int i = year;
  int j = month; 
  int k = day; 
  double JD2 = k-32075+1461*(i+4800+(j-14)/12)/4+367*(j-2-(j-14)/12*12) / 12-3*((i+4900+(j-14)/12)/100)/4; 

  return JD2;
}

/* Converts date from Julian to Gregorian Calendar using pass by reference 
 * IN: int Julian Date, int& month, int& day, int& year
 * OUT: NONE
 */
void Julian2Greg(int JD, int& month, int& day, int& year){
  int i, j, k;
  int l = JD + 68569;
  int n = 4*l/146097;

  l=l-(146097*n+3) / 4;
  i = 4000 * (l+1) / 1461001; 
  l = l-1461*i/4+31;
  j = 80*l/2447;
  k = l-2447*j/80; 
  l=j/11;
  j=j+2-12*l;
  i=100*(n-49)+i+l;

  year = i;
  month = j;
  day = k;

  return; 
}
// ===================================================================


/* Default Constructor 
 * Set day to May 11, 1959
 */
myDate::myDate(){
  month = 5;  
  day = 11; 
  year = 1959; 
}

/* Overloaded Constructor 
 * Set the date to values passed through parameters for Month, Date, Year
 * Check if date is valid or not, if invalid pass to default constructor 
 */
myDate::myDate(int M, int D, int Y){
  // Check for invalid: 
  int monthStore = 0;
  int dayStore = 0; 
  int yearStore = 0; 
  
  int JDtest = Greg2Julian(M, D, Y); 
  Julian2Greg(JDtest, monthStore, dayStore, yearStore);
  
  // Not equal to original input -> invalid date  
  if(monthStore != M || dayStore != D || yearStore != Y){
    //cout << "This date is invalid" << endl; 
    // Set to default date
    month = 5;  
    day = 11; 
    year = 1959; 
  }else{
    month = M;
    day = D;
    year = Y; 
  }
} 

/* Displays the date in format "May, 11, 1959" without linefeed after date  
 * IN: NONE
 * OUT: NONE 
 */
void myDate::display(){ 
  string months[12] = {"January", "Febuary", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
  string theMonth = months[this->month-1];
  cout << theMonth << " " << this->day << ", " << this->year;
}

/* Increment date by N days  
 * IN: Integer to increment date 
 * OUT: NONE 
 */
void myDate::increaseDate(int N){
  //int monthDays[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
  int JD = Greg2Julian(this->month,this->day, this->year);
  JD+=N;
  Julian2Greg(JD,this->month,this->day, this->year);
}

/* Decrement date by N days  
 * IN: Integer to decrement date 
 * OUT: NONE 
 */
void myDate::decreaseDate(int N){
  //int monthDays[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
  int JD = Greg2Julian(this->month,this->day, this->year);
  JD-=N;
  Julian2Greg(JD,this->month,this->day, this->year);
}

/* Add one month to date. Accomodates for correct date at last day of 
 * month if next month has less days then current date.
 * IN: NONE
 * OUT: NONE 
 */
void myDate::addMonth(){
  bool isLeap = false; 
  int day = 0;
  int month = 0; 
  int JD = Greg2Julian(2, 29, this->year);
  Julian2Greg(JD, month, day, this->year);
  if(day == 29 && month == 2){
    isLeap = true; 
    //cout << "yeah it's a leap year" << endl; 
  }
  
  if(isLeap == true){
    int monthDays[12] = {31,29,31,30,31,30,31,31,30,31,30,31}; // Leap year 
    //cout << "leap year check" << endl; 
    
    if(this->month == 12){ // December(12) -> January(1) 
      this->month = 1;
    }else{
  
      this->month++; 
      //cout << "The value of month is : " << this->month << endl; 
      if(this->day >= monthDays[this->month - 1]){
        //cout << "Month add reached" << endl; 
        this->day = monthDays[this->month - 1];
      }
    }
    
  }else{
    //cout << " NOT A LEAP YEAR BRUH " << endl;
    int monthDays[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    
    if(this->month == 12){ // December(12) -> January(1) 
      this->month = 1;
    }else{
  
      this->month++; 
      //cout << "The value of month is : " << this->month << endl; 
      //cout << "The value of DAY is : " << this->day << endl;
      //cout << "The number of days during this month is : " << monthDays[this->month-1] << endl; 
      if(this->day > monthDays[this->month-1]){
        this->day = monthDays[this->month-1];
      }
    }
  }
}

/* Returns the number of days between this date and date D. If date D
 * is in the future, return positive integer. If date D is in the past,
 * return a negative integer. 
 * IN: myDate D
 * OUT: Integer of days between dates  
 */
int myDate::daysBetween(myDate D){
  int JD1 = Greg2Julian(D.getMonth(),D.getDay(),D.getYear());
  int JD2 = Greg2Julian(this->month,this->day, this->year);

  int daysBtwn = abs(JD1 - JD2); // take absolute value 
  
  // Check when date is earlier or later --> change pos or neg return value 
  if(JD1 > JD2){  // In the future 
    return daysBtwn;
  }else{ // In the past 
    return -1 * daysBtwn; 
  }
  return -420; // -420 if something is broken 
}

/* Returns the month in integer form   
 * IN: None
 * OUT: Integer 
 */
int myDate::getMonth(){
  return this->month;
}

/* Returns the day of the month in integer form   
 * IN: None
 * OUT: Integer 
 */
int myDate::getDay(){
  return this->day;
}

/* Returns the year in integer form   
 * IN: None
 * OUT: Integer 
 */
int myDate::getYear(){
  return this->year;
}

/* Returns the number of days since the year began
 * IN: None
 * OUT: Integer 
 */
int myDate::dayOfYear(){
  bool isLeap = false; 
  int day = 0;
  int month = 0; 
  int JD = Greg2Julian(2, 29, this->year);
  Julian2Greg(JD, month, day, this->year);
  if(day == 29 && month == 2){
    isLeap = true; 
    //cout << "yeah it's a leap year" << endl; 
  }
  
  int daySum = 0;
  if(isLeap == true){
    int monthDays[12] = {31,29,31,30,31,30,31,31,30,31,30,31};
    int monthPos = this->month - 1; 
     
    for(int i = 0; i < monthPos; i++){ // By months 
      daySum += monthDays[i];
    }
    daySum += this->day; // By days 
  }else{
    int monthDays[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    // count days to January 1 
    int monthPos = this->month - 1; 
    for(int i = 0; i < monthPos; i++){ // By months 
      daySum += monthDays[i];
    }
    daySum += this->day; // By days 
  }
  return daySum; 
}

/* Returns the name of the day according to the day of the week   
 * IN: None
 * OUT: String 
 */
string myDate::dayName(){
  string theDay[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
  int dayInJulian = Greg2Julian(this->month, this->day, this->year);
  string dayOfWeek = theDay[(dayInJulian + 1) % 7];
  // cout << "the day of the week is: " << dayOfWeek << endl; 
  return dayOfWeek;
}

/* Returns the date as a string in date format
 * IN: None
 * OUT: String
 */
string myDate::getDate(){
  string months[12] = {"January", "Febuary", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
  string theMonth = months[this->month-1];
  string formatted = theMonth + " " + to_string(this->day) + ", " + to_string(this->year);
  return formatted; 
}