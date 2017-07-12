/*code to be renamed/organised once we get it running,
 * took example code from book section 8.2 */

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

#define MAXLEN 14
#define MATCH 0 	        // enumerated type symbol for match 
#define INS   1 	        // enumerated type symbol for insert
#define DEL   2 	        // enumerated type symbol for delete 
#define TRANS 3 	        // enumerated type symbol for transposing

typedef struct 
{
    int cost; 		        //cost of reaching this cell
    int parent; 	        //parent cell
} cell;

cell m[MAXLEN+1][MAXLEN+1]; /* dynamic programming table */

typedef struct {
    int row;
    int column; 	        //10 total columns, 0-9
    bool hand; 		        //left: 0, right: 1
    int fingerPosition;     // 0-pinky, 1-ring, 2-mid, 3-index
    char key; 		        //key on keyboard
} buttons;

buttons keys[4][10]; 	    //2D matrix of keys on keyboard - standard
 
 //function to initialise all of the keys
 void initialiseKey()
 {
    int row = 0;
    int column = 0;
    bool hand = 0; 
    int fingerPosition = 0;
    char buttons[39] = { '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
		         'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p',
		         'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',
		         'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.' };
    
    for (int i = 0; i <39 ; i ++)
    {	
        //to determine what row you are on:
        column = i % 10;
        if (column = 0 && i > 0)
            row ++;
        
        if (column > 4)        //all columns 5 or higher are used by the right hand 
            hand = 1;
        else
            hand = 0;          //else the key is used by the left hand
        if (column < 4)        //if the finger position is equal to 
            fingerPosition = column; 
        else if (column < 7)   //accounting for the G and H keys that you use your index finger for
            fingerPosition = 3;
        else
            fingerPosition = 9 - column;
    }    
        
}       

    
