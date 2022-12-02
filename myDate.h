// Name: Aveline Villaganas
// Class (CECS 282-04)
// Project Name (Program 3 - Structs and Pointers)
// Due Date (3/15/2022)
//
// I certify that this program is my own original work. I did not copy any part of this program from any other source. 
// I further certify that I typed each and every line of code in this program.

#ifndef myDate_hpp
#define myDate_hpp
#include <string>
using namespace std;

class myDate{
  private:
    int month;
    int day;
    int year; 
  public:
    myDate();
    myDate(int M, int D, int Y);
    void display();
    void increaseDate(int N);
    void decreaseDate(int N);
    void addMonth();
    int daysBetween(myDate D);
    int getMonth();
    int getDay();
    int getYear();
    int dayOfYear();
    string dayName();
    string getDate();
};

#endif