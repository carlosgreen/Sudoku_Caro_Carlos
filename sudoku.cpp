// Solving Problems with Programming
// Professor Ken Bauer
//
// Sudoku

// Carlos Green
//A01328279
// Carolina Romo
// A01229797

// Standard libraries
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

const int BOARDSIZE = 9;
const int EMPTY = 0;

/*
 * creates a board filed with zeroes (empty spaces)
 * we will do this, then populate it from a file with
 * another function below
 */
void createZeroBoard(vector< vector<int> >& board){
  for(int r = 0; r < BOARDSIZE ; r++){
    // grab a full line from the file
    for(int c = 0; c < BOARDSIZE ; c++){
      board[r][c] = EMPTY;
    }
  }
}

/*
 * Populates the board from the contents of the file
 * The file must contain 9 lines with 9 values each line
 * The values must be either zero (0) for empty or values between 1 and 9
 */
void populateBoardFromFile(vector< vector<int> >& board, string filename){
  ifstream infile(filename.c_str()); // the c_str() is to convert from string to char*
  int cell;
  string line;
  if(infile.good()){
    for(int r = 0; r < BOARDSIZE ; r++){
      // grab a full line from the file
      for(int c = 0; c < BOARDSIZE ; c++){
  infile >> cell;
  board[r][c] = cell;
      }
    }
  } else {
    cout << "Something is wrong with the input file" << endl;
  }
}

/*
 * The function prints the board.
 * Each cell is a zero (for empty) or the value 1 to 9
 * Each cell is separated by a space
 * NO SPACE at end of row.
 */
void printBoard(vector< vector<int> >& board){
  string colorblue = "\x1b[34m";
  string coloryellow = "\x1b[30m";
  string colorred = "\x1b[31m";
  string colorgreen = "\x1b[32m";
  string colorwhite = "\x1b[47m";
  string colorreset = "\x1b[0m";
  // nothing for now, you will implement this for Partial 2 project deliver
  cout << colorwhite << endl;
  cout<<coloryellow<<"|||="<<colorblue<<"1"<<coloryellow<<"=|="<<colorblue<<"2";
  cout<<coloryellow<<"=|="<<colorblue<<"3"<<coloryellow<<"=||=";
  cout<<colorblue<<"4"<<coloryellow<<"=|="<<colorblue<<"5"<<coloryellow<<"=|=";
  cout<<colorblue<<"6"<<coloryellow<<"=||="<<colorblue<<"7"<<coloryellow<<"=|=";
  cout<<colorblue<<"8"<<coloryellow<<"=|="<<colorblue<<"9"<<coloryellow<<" ||"<<endl;

  cout<<"|||===|===|===||===|===|===||===|===|===||"<<endl;

  for(int r = 0; r < BOARDSIZE ; r++){
    cout<<colorblue<<r+1<<coloryellow;
    for(int c = 0; c < BOARDSIZE ; c++){

        if (c%3==0 && c!=0 ) {
          cout<<" || ";
        }
        else{
          cout<< " | ";
        }

      if(board[r][c] > 0){
        cout<<colorred;
      }
      else{
        cout<<colorgreen;
      }
      if(board[r][c]==0){
        cout<< " ";
      }
      else{
        cout<<abs(board[r][c]);
      }
      cout<<coloryellow;

      cout<< coloryellow;
    }
    cout<<endl;
    if(r==2 || r==5 || r==8){
      cout<<"|||===|===|===||===|===|===||===|===|===||"<<endl;
    }
    else{
      cout<<"|||___|___|___||___|___|___||___|___|___||"<<endl;
    }

  }
  cout<<colorreset;
}


/*
 * Your main program goes here.
 * first get the parameters, check if parameter size is 2
 * first parameter is always the program name in C/C++
 * second parameter is the filename to read in this program
 * any other number of parameters is illegal
 */

 void write (vector<vector<int> >& board, int r, int c, int n){
   if (board[r][c]>0){
     cout<< "That number is part of the original board"<<endl;
   }
   else {
     board[r][c]=-n;
   }
 }

 bool win (vector<vector<int> >& board, int r, int c){
   for(int r=0; r< BOARDSIZE; r++){
     for(int c = 0; c< BOARDSIZE; c++){
       if(board[r][c]==0){
         return false;
       }
     }
   }
   return true;
 }

 void erase (vector< vector<int> >& board, int r, int c){
   if (board[r][c]>0){
     cout<<"That number is part of the original board"<<endl;
   }
   else{
     board[r][c]=0;
   }
 }

 bool checkRegion(vector< vector<int> >& board, int r, int c, int n){
   int gr=r/3;
   int gc=c/3;
   for( int x=gr*3; x<=gr*3+2; x++){
     for(int y=gc*3; y<=gc*3+2; y++){
       if(board[x][y]==n){
         cout<< "This number is already in the region"<<endl;
         return false;
       }
     }
   }
   return true;
 }

 bool checkRow(vector<vector<int> >& board, int r, int n){
   for(int c=0; c<=8; c++){
     if(board[r][c] == n){
       cout<<"This number is already in the row"<<endl;
       return false;
     }
   }
   return true;
 }

 bool checkColumn(vector<vector<int> >& board, int c, int n){
   for(int r=0; r<=8; r++){
     if(board[r][c]==n){
       cout<<"This number is already in the column"<<endl;
       return false;
     }
   }
   return true;
 }

 bool isDigits(string s){
   int lenString = s.length();
   for(int i=0; i<lenString; i++){
     if(s[i]<'0' || s[i]>'9'){
       return false;
     }
   }
   return true;
 }

int main(int argc, char* argv[]) {
  string filename;
  int r, c, n;
  string s_r;
  string s_c;
  string s_n;

  vector< vector<int> > theBoard(BOARDSIZE,vector<int>(BOARDSIZE));

  switch(argc)
    {
    case 1:
      cout << "Please provide the parameters to the program, you must enter a filename to initiate the Sudoku." << endl;
      exit(1);
    case 2:
      filename = argv[1];
      break;
    default:
      cout << "Please provide the parameters to the program, you must enter a filename to initiate the Sudoku." << endl;
      exit(1);
    }

  createZeroBoard(theBoard);
  populateBoardFromFile(theBoard,filename);
  string answer;
  cout << "\x1b[47m\x1b[30mWelcome to the Game of Sudoku\x1b[39;49m" << endl;
  cout<<"\x1b[47m\x1b[30mInstructions\x1b[39;49m"<<endl;
  cout<<"\x1b[36mTo play, select one of the options given :)\x1b[39;49m"<< endl;
  cout<< "\x1b[31m **Print will display you a copy of the actual board"<<endl;
  cout<< "\x1b[34m **Write will ask you for a given row, column and number which will be added to the actual board only if the given number is not in the row, column or region\x1b[39;49m"<<endl;
  cout<< "\x1b[33m **Erase will ask you for a given row and column for you to erase the number in it in the actual board, only if it's not from the original board\x1b[39;49m"<<endl;
  cout<<"\x1b[35m **Restart will reset the board and erase all the numbers that you added to the board\x1b[39;49m"<<endl;
  cout<< "\x1b[37m **And finally quit will end the game"<<endl;
  cout<<"\x1b[32mPlease write down the option from the menu that you wish to execute:\x1b[39;49m"<<endl;

  // we changed the format a little bit just for the beggining but we are planing on following the one below
  string userChoice = "";
  do{
    string colorreset = "\x1b[0m";
    cout<<colorreset;
    cout << "What would you like to do (print, write, erase, restart or quit): ";
    cout<<colorreset;
    cin >> userChoice;
    if(userChoice == "print"){
      printBoard(theBoard);
      continue;
    }
    if(userChoice == "write"){
      // ask user for position (row,column) and number
      // check if valid (legal) and modify the board or notify that the move is invalid
      cout<<"Entr a row: "<<endl;
      cin>>s_r;
      while(isDigits(s_r)==0 || atoi(s_r.c_str() ) >=10 || atoi(s_r.c_str() )<1){
        cout<<"That is not a digit or is not between 1 and 9, please write again: "<<endl;
        cin>>s_r;
      }
      cout<<"Enter column: "<<endl;
      cin>>s_c;
      while(isDigits(s_c)==0 || atoi(s_c.c_str() ) >=10 || atoi(s_c.c_str() )<1){
        cout<<"That is not a digit or is not between 1 and 9, please write again: "<<endl;
        cin>>s_c;
      }
       cout<<"Enter number: "<<endl;
      cin>>s_n;
      while(isDigits(s_n)==0 || atoi(s_n.c_str() ) >=10){
        cout<<"That is not a digit or is not between 1 and 9, please write again: "<<endl;
        cin>>s_n;
      }


      r=atoi(s_r.c_str())-1;
      c=atoi(s_c.c_str())-1;
      n=atoi(s_n.c_str());
      bool cReg=checkRegion(theBoard, r, c, n);
      bool cRow=checkRow(theBoard, r,n);
      bool cCol=checkColumn(theBoard, c, n);
      if(cReg==false || cRow==false || cCol==false){
        cout<<"Change your options"<<endl;
      }
      else{
        write(theBoard, r, c, n);
      }
      if(win(theBoard, r, c)){
        cout<<"Congrats!! You won the game"<<endl;
        string T="\x1b[36m(:D)\x1b[39;49m";
        int rows,cols,norows,i;
        cout<<"give me the number of rows for your winner surprise :)"<<endl;
        cin>>norows;
        for(rows=1;rows<norows; rows++){
          for(cols=1; cols<=rows; cols++){
            cout<<T;
          }
          cout<<endl;
        }
      for(rows=norows-1; rows>0; rows--){
        for(cols=1; cols<=rows; cols++){
          cout<<T;
        }
        cout<<endl;
      }
        printBoard(theBoard);
        return 0;
      }
      cout<<"\x1b[32mThe has been a modification of the board:\x1b[39;49m "<<endl;
      printBoard(theBoard);
      continue;
    }
    if(userChoice == "erase"){
      // ask user for position (row,column) to erase
      // check if valid (legal) and modify the board or notify that the move is invalid
      cout<<"Enter row: "<<endl;
      cin>>s_r;
      while(isDigits(s_r)==0 || atoi(s_r.c_str() )>=10 || atoi(s_r.c_str() )<0){
        cout<<"That digit is not between the range, please write again: "<<endl;
        cin>> s_r;
      }
      cout<<"Enter column: "<<endl;
      cin>>s_c;
      while(isDigits(s_c)==0 || atoi(s_c.c_str() )>=10 || atoi(s_c.c_str() )<0){
        cout<<"That digit is not between the range, please write again: "<<endl;
        cin>> s_c;
      }
      r= atoi(s_r.c_str())-1;
      c= atoi(s_c.c_str())-1;
      erase(theBoard, r, c);
      continue;
    }
    if(userChoice == "restart"){
      createZeroBoard(theBoard);
      populateBoardFromFile(theBoard,filename);
      continue;
    }
    if(userChoice == "quit"){
      cout << "Thanks for playing our game, have a great day!" << endl;
      continue;
    }
    cout << "That was not a valid choice, try again." << endl;
  } while (userChoice != "quit");

  return 0;
}
