
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>
#include <fstream>

using namespace std;
#define MATCH       0 /* enumerated type symbol for match */
#define INSERT      1 /* enumerated type symbol for insert */
#define DELETE      2 /* enumerated type symbol for delete */
#define SUB			3 /* enumerated type symbol for sub */
#define TRANS       4 /* enumerated type symbol for trans */

 
typedef struct {
    int cost;     /* cost of reaching this cell */
    int parent;   /* parent cell */
} cell;
 

#define MAXLEN 5
cell m[MAXLEN+1][MAXLEN+1];

char keys[4][10] = {{'1','2','3','4','5','6','7','8','9','0'},
				   {'q','w','e','r','t','y','u','i','o','p'},
				   {'a','s','d','f','g','h','j','k','l',';'},
				   {'z','x','c','v','b','n','m',',','.'}};
 
/*********** initializations ***********/
void row_init (int i) {
    m[0][i].cost = i;
    if (i>0)
        m[0][i].parent =  INSERT;
    else
        m[0][i].parent = -1;
}
 
void column_init (int i) {
    m[i][0].cost = i;
    if (i>0)
        m[i][0].parent = DELETE;
    else
        m[i][0].parent = -1;
}
 
/*********** edit distance ***********/
void goal_cell(char *s, char *t, int *i, int *j) {
    *i = strlen(s) - 1;
    *j = strlen(t) - 1;
}
 
int match ( char s, char t ) {
    if ( s==t )
        return 0;
    else
        return 1;
}
 
int insert ( char c )
{
    return 1;
}

int del ( char c )
{
    return 1;
}

int sub ( char c )
{
    return 1;
}
 
int trans ( char *s, char *t, int *i, int *j ) {
    /* check for end of string */
    if ( !( (*i < MAXLEN) && (*j < MAXLEN) ))
        return 10;

    if ( s[*i] == t[(*j)+1] && s[(*i)+1] == t[*j] && (s[*i] != s[(*i)+1]) && (*i == *j) ) {
        return -1; 
    }
    else
        return 10;
}
 
int string_edit_distance (char *s, char *t)
{
    int i, j;
    int first = 0;
    int opt[5];             /* cost of the options */
    for (unsigned int i=0; i < MAXLEN; i++) {
        row_init(i);
        column_init(i);
    }
 
    for (i=1; i < (int) strlen(s); i++) 
    {
        for (j=1; j < (int) strlen(t); j++) 
        {
            opt[MATCH]  = m[i-1][j-1].cost + match(s[i],t[j]);
            
            if((s[j-1] == t[j-1]) && (t[j-1] == t[j]) && (s[j] != t[j]))
			{
				opt[INSERT] = m[i][j-1].cost + insert(t[j]);
				cout << opt[INSERT] << endl;
			}
			else if ((s[j-1] == t[j-1]) && (t[j] == ' ') && (s[j] != t[j]))
			{
				if(s[j-1] == 'z' || s[j-1] == 'x' || s[j-1] == 'c' || s[j-1] == 'v' || s[j-1] == 'b' || s[j-1] == 'n' || s[j-1] == 'm' || s[j-1] == ',' || s[j-1] == '.')
				{
					opt[INSERT] = m[i][j-1].cost + insert(t[j]) + 2;
					cout << opt[INSERT] << endl;
				}
				else
				{
					opt[INSERT] = m[i][j-1].cost + insert(t[j]) + 6;
					cout << opt[INSERT] << endl;
				}
			}
			else if((s[j-1] == t[j-1]) && (s[j] == ' ') && (t[j] != ' ') && (s[j+1] != t[j]))
			{
				opt[INSERT] = m[i][j-1].cost + insert(t[j]) + 6;
				cout << opt[INSERT] << endl;
			}
			else if(((s[j-1] == t[j-1]) && (s[j] != t[j]) && (t[j+1] == s[j])) && (s[j-1] == '1' || s[j-1] == '2'  || s[j-1] == '3' || s[j-1] == '3' || s[j-1] == '4' || s[j-1] == '5' || s[j-1] == 'q' || s[j-1] == 'w' || s[j-1] == 'e' || s[j-1] == 'r' || s[j-1] == 't' || s[j-1] == 'a' || s[j-1] == 's' || s[j-1] == 'd' || s[j-1] == 'f' || s[j-1] == 'g' || s[j-1] == 'z' || s[j-1] == 'x' || s[j-1] == 'c' || s[j-1] == 'v' || s[j-1] == 'b')) //left hand
			{
				if((s[j] != t[j]) && (s[j] == '6' || s[j] == '7'  || s[j] == '8' || s[j] == '9' || s[j] == '0' || s[j] == 'y' || s[j] == 'u' || s[j] == 'i' || s[j] == 'o' || s[j] == 'p' || s[j] == 'h' || s[j] == 'j' || s[j] == 'k' || s[j] == 'l' || s[j] == ';' || s[j] == 'n' || s[j] == 'm' || s[j] == ',' || s[j] == '.'))
				{
					opt[INSERT] = m[i][j-1].cost + insert(t[j]) + 5;
					cout << opt[INSERT] << endl;
				}
			}
			else if(((s[j-1] == t[j-1]) && (s[j] != t[j]) && (t[j+1] == s[j])) && (s[j-1] == '6' || s[j-1] == '7'  || s[j-1] == '8' || s[j-1] == '9' || s[j-1] == '0' || s[j-1] == 'y' || s[j-1] == 'u' || s[j-1] == 'i' || s[j-1] == 'o' || s[j-1] == 'p' || s[j-1] == 'h' || s[j-1] == 'j' || s[j-1] == 'k' || s[j-1] == 'l' || s[j-1] == ';' || s[j-1] == 'n' || s[j-1] == 'm' || s[j-1] == ',' || s[j-1] == '.')) // right hand
			{
				
				if((s[j] != t[j]) && (s[j] == '1' || s[j] == '2'  || s[j] == '3' || s[j] == '3' || s[j] == '4' || s[j] == '5' || s[j] == 'q' || s[j] == 'w' || s[j] == 'e' || s[j] == 'r' || s[j] == 't' || s[j] == 'a' || s[j] == 's' || s[j] == 'd' || s[j] == 'f' || s[j] == 'g' || s[j] == 'z' || s[j] == 'x' || s[j] == 'c' || s[j] == 'v' || s[j] == 'b'))
				{
					opt[INSERT] = m[i][j-1].cost + insert(t[j]) + 5;
					cout << opt[INSERT] << endl;
				}
			}
			else if(((s[j-1] == t[j]) && (s[j] != t[j]) && (s[j-1] != t[j-1]) && (t[j+1] == s[j])) && (s[j-1] == '1' || s[j-1] == '2'  || s[j-1] == '3' || s[j-1] == '3' || s[j-1] == '4' || s[j-1] == '5' || s[j-1] == 'q' || s[j-1] == 'w' || s[j-1] == 'e' || s[j-1] == 'r' || s[j-1] == 't' || s[j-1] == 'a' || s[j-1] == 's' || s[j-1] == 'd' || s[j-1] == 'f' || s[j-1] == 'g' || s[j-1] == 'z' || s[j-1] == 'x' || s[j-1] == 'c' || s[j-1] == 'v' || s[j-1] == 'b')) //left hand
			{
				if((s[j] != t[j]) && (s[j] == '6' || s[j] == '7'  || s[j] == '8' || s[j] == '9' || s[j] == '0' || s[j] == 'y' || s[j] == 'u' || s[j] == 'i' || s[j] == 'o' || s[j] == 'p' || s[j] == 'h' || s[j] == 'j' || s[j] == 'k' || s[j] == 'l' || s[j] == ';' || s[j] == 'n' || s[j] == 'm' || s[j] == ',' || s[j] == '.'))
				{
					opt[INSERT] = m[i][j-1].cost + insert(t[j]) + 5;
					cout << opt[INSERT] << endl;
				}
			}
			else if(((s[j-1] == t[j]) && (s[j] != t[j]) && (s[j-1] != t[j-1]) && (t[j+1] == s[j])) && (s[j-1] == '6' || s[j-1] == '7'  || s[j-1] == '8' || s[j-1] == '9' || s[j-1] == '0' || s[j-1] == 'y' || s[j-1] == 'u' || s[j-1] == 'i' || s[j-1] == 'o' || s[j-1] == 'p' || s[j-1] == 'h' || s[j-1] == 'j' || s[j-1] == 'k' || s[j-1] == 'l' || s[j-1] == ';' || s[j-1] == 'n' || s[j-1] == 'm' || s[j-1] == ',' || s[j-1] == '.')) // right hand
			{
				
				if((s[j] != t[j]) && (s[j] == '1' || s[j] == '2'  || s[j] == '3' || s[j] == '3' || s[j] == '4' || s[j] == '5' || s[j] == 'q' || s[j] == 'w' || s[j] == 'e' || s[j] == 'r' || s[j] == 't' || s[j] == 'a' || s[j] == 's' || s[j] == 'd' || s[j] == 'f' || s[j] == 'g' || s[j] == 'z' || s[j] == 'x' || s[j] == 'c' || s[j] == 'v' || s[j] == 'b'))
				{
					opt[INSERT] = m[i][j-1].cost + insert(t[j]) + 5;
					cout << opt[INSERT] << endl;
				}
			}
            else
            {
            	opt[INSERT] = m[i][j-1].cost + insert(t[j]);
            }
            //opt[INSERT] = m[i][j-1].cost + insert(t[j]);
            
            
            if((s[j-1] == t[j-1]) && (s[j-1] == s[j]) && (s[j] != t[j])) //Repeated Character
			{
				opt[DELETE] = m[i-1][j].cost + del(s[i]);
				cout << opt[DELETE] << endl;
			}
			else if ((s[j-1] == ' ') && (t[j-1] == s[j]) && (t[j] != s[j])) //Space removed
			{
				opt[DELETE] = m[i-1][j].cost + del(s[i]) + 3;
				cout << opt[DELETE] << endl;
			}
			else if((s[j] == t[j-1]) && (s[j+1] == t[j]) && (s[j-1] != t[j-1]) && (s[j-1] == '1' || s[j-1] == '2'  || s[j-1] == '3' || s[j-1] == '3' || s[j-1] == '4' || s[j-1] == '5' || s[j-1] == 'q' || s[j-1] == 'w' || s[j-1] == 'e' || s[j-1] == 'r' || s[j-1] == 't' || s[j-1] == 'a' || s[j-1] == 's' || s[j-1] == 'd' || s[j-1] == 'f' || s[j-1] == 'g' || s[j-1] == 'z' || s[j-1] == 'x' || s[j-1] == 'c' || s[j-1] == 'v' || s[j-1] == 'b')) //left hand
			{
				if((s[j] == t[j-1]) && (s[j+1] == t[j]) && (s[j-1] != t[j-1]) && (s[j] == '1' || s[j] == '2'  || s[j] == '3' || s[j] == '3' || s[j] == '4' || s[j] == '5' || s[j] == 'q' || s[j] == 'w' || s[j] == 'e' || s[j] == 'r' || s[j] == 't' || s[j] == 'a' || s[j] == 's' || s[j] == 'd' || s[j] == 'f' || s[j] == 'g' || s[j] == 'z' || s[j] == 'x' || s[j] == 'c' || s[j] == 'v' || s[j] == 'b')) //delete character after key on same hand
				{
					opt[DELETE] = m[i-1][j].cost + del(s[i]) + 2;
					cout << opt[DELETE] << endl;
				}
				else if(((s[j] == ' ') && (s[j] == t[j])) || (s[j-1] == '6' || s[j-1] == '7'  || s[j-1] == '8' || s[j-1] == '9' || s[j-1] == '0' || s[j-1] == 'y' || s[j-1] == 'u' || s[j-1] == 'i' || s[j-1] == 'o' || s[j-1] == 'p' || s[j-1] == 'h' || s[j-1] == 'j' || s[j-1] == 'k' || s[j-1] == 'l' || s[j-1] == ';' || s[j-1] == 'n' || s[j-1] == 'm' || s[j-1] == ',' || s[j-1] == '.')) //character after space or key on diff hand
				{
					opt[DELETE] = m[i-1][j].cost + del(s[i]) + 6;
					cout << opt[DELETE] << endl;
				}
			}
			else if((s[j] == t[j-1]) && (s[j+1] == t[j]) && (s[j-1] != t[j-1]) && (s[j-1] == '6' || s[j-1] == '7'  || s[j-1] == '8' || s[j-1] == '9' || s[j-1] == '0' || s[j-1] == 'y' || s[j-1] == 'u' || s[j-1] == 'i' || s[j-1] == 'o' || s[j-1] == 'p' || s[j-1] == 'h' || s[j-1] == 'j' || s[j-1] == 'k' || s[j-1] == 'l' || s[j-1] == ';' || s[j-1] == 'n' || s[j-1] == 'm' || s[j-1] == ',' || s[j-1] == '.')) // right hand
			{
				if((s[j] != t[j]) && (s[j] == '6' || s[j] == '7'  || s[j] == '8' || s[j] == '9' || s[j] == '0' || s[j] == 'y' || s[j] == 'u' || s[j] == 'i' || s[j] == 'o' || s[j] == 'p' || s[j] == 'h' || s[j] == 'j' || s[j] == 'k' || s[j] == 'l' || s[j] == ';' || s[j] == 'n' || s[j] == 'm' || s[j] == ',' || s[j] == '.'))//delete character after key on same hand
				{
					opt[DELETE] = m[i-1][j].cost + del(s[i]) + 2;
					cout << opt[DELETE] << endl;
				}
				else if(((s[j] == ' ') && (s[j] == t[j])) || (s[j] == '1' || s[j] == '2'  || s[j] == '3' || s[j] == '3' || s[j] == '4' || s[j] == '5' || s[j] == 'q' || s[j] == 'w' || s[j] == 'e' || s[j] == 'r' || s[j] == 't' || s[j] == 'a' || s[j] == 's' || s[j] == 'd' || s[j] == 'f' || s[j] == 'g' || s[j] == 'z' || s[j] == 'x' || s[j] == 'c' || s[j] == 'v' || s[j] == 'b')) //character after space or key on diff hand
				{
					opt[DELETE] = m[i-1][j].cost + del(s[i]) + 6;
					cout << opt[DELETE] << endl;
				}
			}
            else if((s[j] != t[j]) && i == 1 && j == 1) //first character in string
            {
            	opt[DELETE] = m[i-1][j].cost + del(s[i]) + 6;
            	first++;
            }
            
            //opt[DELETE] = m[i-1][j].cost + del(s[i]);
            if((s[j] != ' ' && t[j] == ' ') || (s[j] == ' ' && t[j] != ' '))
            {
            	opt[SUB] = m[i][j].cost + sub(s[i]) + 6;
            }
            	
            else if(((s[j] == '1' && t[j] != '1') || (s[j] == '2' && t[j] != '2')  || (s[j] == '3' && t[j] != '3') || (s[j] == '4' && t[j] != '4') || (s[j] == '5' && t[j] != '5') || (s[j] == 'q' && t[j] != 'q') || (s[j] == 'w' && t[j] != 'w') || (s[j] == 'e' && t[j] != 'e') || (s[j] == 'r' && t[j] != 'r') || (s[j] == 't' && t[j] != 't') || (s[j] == 'a' && t[j] != 'a') || (s[j] == 's' && t[j] != 's') || (s[j] == 'd' && t[j] != 'd') || (s[j] == 'f' && t[j] != 'f') || (s[j] == 'g' && t[j] != 'g') || (s[j] == 'z' && t[j] != 'z') || (s[j] == 'x' && t[j] != 'x') || (s[j] == 'c' && t[j] != 'c') || (s[j] == 'v' && t[j] != 'v') || (s[j] == 'b' && t[j] != 'b')))
        	{
        		if(((t[j] == '1' && s[j] != '1') || t[j] == '2' && s[j] != '2') || (t[j] == '3' && s[j] != '3') || (t[j] == '4' && s[j] != '4') || (t[j] == '5' && s[j] != '5') || (t[j] == 'q' && s[j] != 'q') || (t[j] == 'w' && s[j] != 'w') || (t[j] == 'e' && s[j] != 'e') || (t[j] == 'r' && s[j] != 'r') || (t[j] == 't' && s[j] != 't') || (t[j] == 'a' && s[j] != 'a') || (t[j] == 's' && s[j] != 's') || (t[j] == 'd' && s[j] != 'd') || (t[j] == 'f' && s[j] != 'f') || (t[j] == 'g' && s[j] != 'g') || (t[j] == 'z' && s[j] != 'z') || (t[j] == 'x' && s[j] != 'x') || (t[j] == 'c' && s[j] != 'c') || (t[j] == 'v' && s[j] != 'v') || (t[j] == 'b' && s[j] != 'b'))
        		{
        			cout << "Distance function1" << endl;
        		}
        	}
        	else if(((s[j] == '6' && t[j] != '6') || (s[j] == '7' && t[j] != '7') || (s[j] == '8' && t[j] != '8') || (s[j] == '9' && t[j] != '9') || (s[j] == '0' && t[j] != '0') || (s[j] == 'y' && t[j] != 'y') || (s[j] == 'u' && t[j] != 'u') || (s[j] == 'i' && t[j] != 'i') || (s[j] == 'o' && t[j] != 'o') || (s[j] == 'p' && t[j] != 'p') || (s[j] == 'h' && t[j] != 'h') || (s[j] == 'j' && t[j] != 'j') || (s[j] == 'k' && t[j] != 'k') || (s[j] == 'l' && t[j] != 'l') || (s[j] == ';' && t[j] != ';') || (s[j] == 'n' && t[j] != 'n') || (s[j] == 'm' && t[j] != 'm') || (s[j] == ',' && t[j] != ',') || (s[j] == '.' && t[j] != '.')))
        	{
        		if(((t[j] == '6' && s[j] != '6') || (t[j] == '7' && s[j] != '7') || (t[j] == '8' && s[j] != '8') || (t[j] == '9' && s[j] != '9') || (t[j] == '0' && s[j] != '0') || (t[j] == 'y' && s[j] != 'y') || (t[j] == 'u' && s[j] != 'u') || (t[j] == 'i' && s[j] != 'i') || (t[j] == 'o' && s[j] != 'o') || (t[j] == 'p' && s[j] != 'p') || (t[j] == 'h' && s[j] != 'h') || (t[j] == 'j' && s[j] != 'j') || (t[j] == 'k' && s[j] != 'k') || (t[j] == 'l' && s[j] != 'l') || (t[j] == ';' && s[j] != ';') || (t[j] == 'n' && s[j] != 'n') || (t[j] == 'm' && s[j] != 'm') || (t[j] == ',' && s[j] != ',') || (t[j] == '.' && s[j] != '.')))
        		{
        			cout << "Distance function2" << endl;
        		}
        	}
            
            //Key for another on same finger, other hand

        	if(s[j] != t[j])
        	{
		        if((s[j] == 'q' || s[j] == 'a' || s[j] == 'z' || s[j] == '1') || ((s[j] == 'p' || s[j] == ';' || s[j] == '0'))) //pinky finger
		        {
		        	if((((t[j] == 'p' || t[j] == ';' || t[j] == '0') && (s[j] != 'p' || s[j] != ';' || s[j] != '0')) || ((t[j] == 'q' || t[j] == 'a' || t[j] == 'z' || t[j] == '1') && (s[j] != 'q' || s[j] != 'a' || s[j] != 'z' || s[j] != '1')) ))
		        	{
		        		opt[SUB] = m[i][j].cost + sub(s[i]) + 1;	
		        	}
		        }
		        else if((s[j] == 'w' || s[j] == 's' || s[j] == 'x' || s[j] == '2') || ((s[j] == 'o' || s[j] == 'l' || s[j] == '.' || s[j] == '9'))) //ring finger
		        {
		        	if((((t[j] == 'o' || t[j] == 'l' || t[j] == '.' || t[j] == '2') && (s[j] != 'o' || s[j] != 'l' || s[j] != '.' || s[j] != '2')) || ((t[j] == 'w' || t[j] == 's' || t[j] == 'x' || t[j] == '9') && (s[j] != 'w' || s[j] != 's' || s[j] != 'x' || s[j] != '9'))))
		        	{
		        		opt[SUB] = m[i][j].cost + sub(s[i]) + 1;	
		        	}
		        }
		        else if((s[j] == 'e' || s[j] == 'd' || s[j] == 'c' || s[j] == '3') || ((s[j] == 'i' || s[j] == 'k' || s[j] == ',' || s[j] == '8'))) //middle finger
		        {
		        	if((((t[j] == 'i' || t[j] == 'k' || t[j] == ',' || t[j] == '8') && (s[j] != 'i' || s[j] != 'k' || s[j] != ',' || s[j] != '8')) || ((t[j] == 'e' || t[j] == 'd' || t[j] == 'c' || t[j] == '3') && (s[j] != 'e' || s[j] != 'd' || s[j] != 'c' || s[j] != '3'))))
		        	{
		        		opt[SUB] = m[i][j].cost + sub(s[i]) + 1;	
		        	}
		        }
		        else if((s[j] == 'r' || s[j] == 'f' || s[j] == 'v' || s[j] == 't' || s[j] == 'g' || s[j] == 'b' || s[j] == '4' || s[j] == '5') || ((s[j] == 'y' || s[j] == 'h' || s[j] == 'n' || s[j] == 'u' || s[j] == 'j' || s[j] == 'm' || s[j] == '6' || s[j] == '7'))) //index finger
		        {
		        	if((((t[j] == 'r' || t[j] == 'f' || t[j] == 'v' || t[j] == 't' || t[j] == 'g' || t[j] == 'b' || t[j] == '4' || t[j] == '5') && (s[j] != 'r' || s[j] != 'f' || s[j] != 'v' || s[j] != 't' || s[j] != 'g' || s[j] != 'b' || s[j] != '4' || s[j] != '5')) || ((t[j] == 'y' || t[j] == 'h' || t[j] == 'n' || t[j] == 'u' || t[j] == 'j' || t[j] == 'm' || t[j] == '6' || t[j] == '7') && (s[j] != 'y' || s[j] != 'h' || s[j] != 'n' || s[j] != 'u' || s[j] != 'j' || s[j] != 'm' || s[j] != '6' || s[j] != '7'))))
		        	{
		        		opt[SUB] = m[i][j].cost + sub(s[i]) + 1;	
		        	}
		        }
		        
		        //key for another on different finger, other hand
		        
		        if((s[j] == 'q' || s[j] == 'a' || s[j] == 'z' || s[j] == '1') || ((s[j] == 'p' || s[j] == ';' || s[j] == '0'))) //pinky finger
		        {
		        	if((((t[j] != 'p' || t[j] != ';' || t[j] != '0') && (s[j] != 'p' || s[j] != ';' || s[j] != '0')) || ((t[j] != 'q' || t[j] != 'a' || t[j] != 'z' || t[j] != '1') && (s[j] != 'q' || s[j] != 'a' || s[j] != 'z' || s[j] != '1'))))
		        	{
		        		opt[SUB] = m[i][j].cost + sub(s[i]) + 5;	
		        	}
		        }
		        else if((s[j] == 'w' || s[j] == 's' || s[j] == 'x' || s[j] == '2') || ((s[j] == 'o' || s[j] == 'l' || s[j] == '.' || s[j] == '9'))) //ring finger
		        {
		        	if((((t[j] != 'o' || t[j] != 'l' || t[j] != '.' || t[j] != '2') && (s[j] != 'o' || s[j] != 'l' || s[j] != '.' || s[j] != '2')) || ((t[j] != 'w' || t[j] != 's' || t[j] != 'x' || t[j] != '9') && (s[j] != 'w' || s[j] != 's' || s[j] != 'x' || s[j] != '9'))))
		        	{
		        		opt[SUB] = m[i][j].cost + sub(s[i]) + 5;	
		        	}
		        }
		        else if((s[j] == 'e' || s[j] == 'd' || s[j] == 'c' || s[j] == '3') || ((s[j] == 'i' || s[j] == 'k' || s[j] == ',' || s[j] == '8'))) //middle finger
		        {
		        	if((((t[j] != 'i' || t[j] != 'k' || t[j] != ',' || t[j] != '8') && (s[j] != 'i' || s[j] != 'k' || s[j] != ',' || s[j] != '8')) || ((t[j] != 'e' || t[j] != 'd' || t[j] != 'c' || t[j] != '3') && (s[j] != 'e' || s[j] != 'd' || s[j] != 'c' || s[j] != '3'))))
		        	{
		        		opt[SUB] = m[i][j].cost + sub(s[i]) + 5;	
		        	}
		        }
		        else if((s[j] == 'r' || s[j] == 'f' || s[j] == 'v' || s[j] == 't' || s[j] == 'g' || s[j] == 'b' || s[j] == '4' || s[j] == '5') || ((s[j] == 'y' || s[j] == 'h' || s[j] == 'n' || s[j] == 'u' || s[j] == 'j' || s[j] == 'm' || s[j] == '6' || s[j] == '7'))) //index finger
		        {
		        	if((((t[j] != 'r' || t[j] != 'f' || t[j] != 'v' || t[j] != 't' || t[j] != 'g' || t[j] != 'b' || t[j] != '4' || t[j] != '5') && (s[j] != 'r' || s[j] != 'f' || s[j] != 'v' || s[j] != 't' || s[j] != 'g' || s[j] != 'b' || s[j] != '4' || s[j] != '5')) || ((t[j] != 'y' || t[j] != 'h' || t[j] != 'n' || t[j] != 'u' || t[j] != 'j' || t[j] != 'm' || t[j] != '6' || t[j] != '7') && (s[j] != 'y' || s[j] != 'h' || s[j] != 'n' || s[j] != 'u' || s[j] != 'j' || s[j] != 'm' || s[j] != '6' || s[j] != '7'))))
		        	{
		        		opt[SUB] = m[i][j].cost + sub(s[i]) + 5;
		        	}
		        }
	        }
            
            
            //opt[SUB] = m[i][j].cost + sub(s[i]);
            
            opt[TRANS]   = m[i-1][j-1].cost + trans(s,t,&i,&j);
            m[i][j].cost = opt[MATCH];
            m[i][j].parent = MATCH;
            for (int k=INSERT; k<=TRANS; k++)
                if (opt[k] < m[i][j].cost) {
                	
                	//cout << m[i][j].parent << endl;
                    m[i][j].cost = opt[k];
                    m[i][j].parent = k;
                    //cout << m[i][j].parent << endl << endl;
                    if ( k == TRANS ) {
                        /* correct for the -1 added before */
                        m[i][j].cost += 1;
                        m[i][j].parent = k;
                        ++i, ++j;
                        m[i][j].cost = m[i-1][j-1].cost + 1;
                        m[i][j].parent = k;
                    }
                }
        }
    }
    cout << endl << endl;
    for (i=0; i<MAXLEN; i++)
	{
		for (j=0; j<MAXLEN; j++)
		{
			cout << m[i][j].cost;
		}
		cout << endl;
	}
	
	
	
	//cout << s[i-1] << s[i] << endl << t[j-1] << t[j] << endl;
	
    goal_cell(s,t,&i,&j);
    
    //cout << m[i][j].cost << endl << endl;
    cout << endl;
    return( m[i][j].cost );
}
 
/*********** reconstruction ***********/
void match_out(char *s, char *t, int i, int j) {
    if (s[i]==t[j]) printf("M");
    else printf("R");
    
}void insert_out(char *t, int j) {
    printf("I");
}
 
void delete_out(char *s, int i) {
    printf("D");
}
 
void sub_out(char *s, int i) {
    printf("S");
}
 
void trans_out(char *s, char *t, int i, int j) {
    printf("T");
}
 
void reconstruct_path(char *s, char *t, int i, int j) {
    if (m[i][j].parent == -1) return;
    if (m[i][j].parent == MATCH) {
        reconstruct_path(s,t,i-1,j-1);
        match_out(s, t, i, j);
        return;
    }
    if (m[i][j].parent == INSERT) {
        reconstruct_path(s,t,i,j-1);
        insert_out(t,j);
        return;
    }
    if (m[i][j].parent == DELETE) {
        reconstruct_path(s,t,i-1,j);
        delete_out(s,i);
        return;
    }
    if (m[i][j].parent == SUB) {
        reconstruct_path(s,t,i,j);
        delete_out(s,i);
        return;
    }
    if (m[i][j].parent == TRANS) {
        reconstruct_path(s,t,i-2,j-2);
        trans_out(s,t,i,j);
        return;
    }
}
 
/*********** main ***********/
int main () {

	string target = "";
	string typo = "";
	string junk = "";
	
	int loopCount = 0;


	ifstream input("input.txt"); //sets the input stream to input file
    
	ofstream myfile("output.txt"); //sets output stream to output file
	if (input.is_open())
	{
		input >> loopCount;
		getline(input, junk);
		while(loopCount > 0)
		{
			getline(input, junk);
			getline(input, target);
			getline(input, typo);
			char *newtar = new char[target.length() + 1];
			char *newtypo = new char[typo.length() + 1];
			strcpy(newtar, target.c_str());
			strcpy(newtypo, typo.c_str());
			cout << target << endl << typo << endl;
			cout << newtar << endl << newtypo << endl;
			cout << endl;
			//string_compare(newtar, newtypo);
			//myfile <<  << endl;
			reconstruct_path (newtar,newtypo,MAXLEN,MAXLEN);
			//cout << endl;
			//cout << newtar << endl << newtypo << endl << 
			string_edit_distance(newtar,newtypo);// << endl;
			//printf ("Edit distance of \"%s\" and \"%s\" is %i\n", newtar, newtypo, string_edit_distance (newtar,newtypo) );
    		//printf ("\n");
			loopCount--;
			delete [] newtar;
			delete [] newtypo;
		}
	}
    return 0;
}

