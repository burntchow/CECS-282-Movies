// Name: Aveline Villaganas
// Class (CECS 282-04)
// Project Name (Program 3 - Structs and Pointers)
// Due Date (3/15/2022)
//
// I certify that this program is my own original work. I did not copy any part of this program from any other source. 
// I further certify that I typed each and every line of code in this program.
#include "myDate.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <cstring>
using namespace std;

struct Movie{
  char name[50]; // figure out how many name characters for name 
  int rt; // Running time 
  double rating; // imdb
  myDate releaseDate; // reuse myDate
  string actor; 
};

/* Displays the list formatted with column names, left justified  
 * IN: Array
 * OUT: None 
 */
void display(Movie *arr[]){
  cout << setw(30) << left << "\033[4mName\033[0m" << setw(20) << left << "\033[4mRun Time\033[0m" << setw(17) << left << "\033[4mRating\033[0m" << setw(28) << left << "\033[4mRelease Date\033[0m" << setw(20) << left << "\033[4mMain Actor\033[0m" << endl;
  
  for(int i = 0; i < 10; i++){
    int hours = (*arr[i]).rt / 60;
    int mins = (*arr[i]).rt % 60; 
    string formatRT = to_string(hours)+"h " + to_string(mins)+"m";
    cout << setw(22) << left << (*arr[i]).name << setw(12) << left << formatRT << setw(9) << left << (*arr[i]).rating << setw(20) << ((*arr[i]).releaseDate).getDate() << setw(15) << (*arr[i]).actor << endl;
    //cout << "waffles" << endl;
  }
  cout << endl;
}

/* Populates the Movie array with movies of my choice
 * IN: Array
 * OUT: None
 */
void populate(Movie *arr[]){
  // Make a list of lists -> put into
  char movNames[10][25] = {{"The Lego Movie"}, {"Hotel For Dogs"}, {"Encanto"}, {"The Incredibles"}, {"Ratatouille"}, {"WALL-E"}, {"Ponyo"}, {"Megamind"}, {"Luca"}, {"Meet the Robinsons"}};
  int movRT[10] = {100, 100, 102, 115, 111, 98, 101, 95, 95, 95}; 
  double movRating[10] = {7.7, 5.5, 7.3, 8.1, 8.1, 8.4, 7.6, 7.3, 7.5, 6.8}; 
  myDate movRelease[10] = {myDate(2,9,2014), myDate(1,16,2009), myDate(11,24,2021), myDate(11,5,2004), myDate(6,29,2007), myDate(6,27,2008), myDate(8,14,2009), myDate(11,5,2010), myDate(6,18,2021), myDate(3,30,2007)};
  string movActor[10] = {"Chris Pratt", "Emma Roberts", "Stephanie Beatriz", "Craig T. Nelson", "Patton Oswalt", "Ben Burtt", "Yuria Nara", "Will Ferrel", "Jacob Tremblay", "Daniel Hansen"};
  //cout << "Populated" << endl;
  for(int i = 0; i < 10; i++){ 
    //cout << "pancakes" << endl;
    arr[i] = new Movie();
    strcpy((*arr[i]).name, movNames[i]);
    (*arr[i]).rt = movRT[i];
    (*arr[i]).rating = movRating[i];
    (*arr[i]).releaseDate = movRelease[i];
    (*arr[i]).actor = movActor[i];

    
  }
}

/* Creates a menu with 6 options.
 * IN: None
 * OUT: Int - user choice 
 */ 
int menu(){
  cout << "1) Display list sorted by Name\n2) Display list sorted by Running Time\n3) Display list sorted by IMDB Rating\n4) Display list sorted by Release Date\n5) Display list sorted by Main Actor\n6) Exit" << endl; 
  int userChoice;
  cin >> userChoice;
  return userChoice; 
} 

/* Sorts movies by name using strcmp and bubble sort.
 * IN: Movie pointer array
 * OUT: None 
 */ 
void sortName(Movie *arr[]){
  int l = 0;
  for(int i = 0; i < 9; i++){
    for(int j = 0; j < 9-i; j++){ 
      
      if(strcmp(arr[j]->name, arr[j+1]->name) > 0){
        Movie temp = *arr[j];
        *arr[j] = *arr[j+1];
        *arr[j+1] = temp;
      }
    }
  }
}

/* Sorts movies by run time using bubble sort.
 * IN: Movie pointer array
 * OUT: None 
 */ 
void sortRT(Movie *arr[]){
  for(int i = 0; i < 9; i++){
    for(int j = 0; j < 9-i; j++){
      if((*arr[j]).rt > (*arr[j+1]).rt){
        Movie temp = *arr[j];
        *arr[j] = *arr[j+1];
        *arr[j+1] = temp;
      }
    }
  }
}

/* Sorts movies by IMDB Rating using bubble sort.
 * IN: Movie pointer array
 * OUT: None 
 */ 
void sortRating(Movie *arr[]){
  for(int i = 0; i < 9; i++){
    for(int j = 0; j < 9-i; j++){
      if((*arr[j]).rating > (*arr[j+1]).rating){
        Movie temp = *arr[j];
        *arr[j] = *arr[j+1];
        *arr[j+1] = temp;
      }
    }
  }
}

/* Sorts movies by release date using bubble sort.
 * IN: Movie pointer array
 * OUT: None 
 */ 
void sortReleaseDate(Movie *arr[]){
  for(int i = 0; i < 9; i++){
    for(int j = 0; j < 9-i; j++){
      if(((*arr[j]).releaseDate).daysBetween((*arr[j+1]).releaseDate) < 0){
        Movie temp = *arr[j];
        *arr[j] = *arr[j+1];
        *arr[j+1] = temp;
      }
    }
  }
}

/* Sorts movies by main actor using bubble sort.
 * IN: Movie pointer array
 * OUT: None 
 */ 
void sortActor(Movie *arr[]){
  for(int i = 0; i < 9; i++){
    for(int j = 0; j < 9-i; j++){
      if((*arr[j]).actor > (*arr[j+1]).actor){
        Movie temp = *arr[j];
        *arr[j] = *arr[j+1];
        *arr[j+1] = temp;
      }
    }
  }
}

int main() {
  Movie *mov[10]; // astrix for array of POINTERS   
  populate(mov);
  //display(mov);
  int choice = menu(); 
  
  while(choice != 6){
    
    if(choice == 1){ // Movie Name 
      cout << "You chose sort by NAME:" << endl; 
      sortName(mov);
      display(mov);
    }else if(choice == 2){ // Run Time 
      cout << "You chose sort by RT:" << endl; 
      sortRT(mov);
      display(mov);
    }else if(choice == 3){ // IMDB Rating 
      cout << "You chose sort by IMDB RATING:" << endl; 
      sortRating(mov);
      display(mov);
    }else if(choice == 4){ // Release Date 
      cout << "You chose sort by RELEASE DATE:" << endl; 
      sortReleaseDate(mov);
      display(mov);
    }else if(choice == 5){ // Main Actor 
      cout << "You chose sort by MAIN ACTOR:" << endl; 
      sortActor(mov);
      display(mov);
    }else if(choice == 6){ // Exit 
      cout << "You chose to EXIT" << endl; 
      return 0; 
    }
    choice = menu();
  }
  return 0; 
}