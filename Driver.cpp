/*code to be renamed/organised once we get it running,
 * took example code from http://csl.skku.edu/uploads/SWE2004S15/Lecture11.pdf */

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

#define MAXLEN 
#define MATCH 0 /* enumerated type symbol for match */
#define INS   1 /* enumerated type symbol for insert */
#define DEL   2 /* enumerated type symbol for delete */
#define TRANS 3 /* enumerated type symbol for transposing */

typedef struct 
{
    int cost; //cost of reaching this cell
    int parent; //parent cell
} cell;

cell m[MAXLEN+1][MAXLEN+1]; /* dynamic programming table */

typedef struct {
    int row;
    int column; //10 total columns, 0-9
    bool hand; //left: 0, right: 1
    int fingerPosition; // 0-pinky, 1-ring, 2-mid, 3-index
    char key; //key on keyboard
} buttons;

button keys[4][10]; //2D matrix of keys on keyboard - standard
 
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
        

    
