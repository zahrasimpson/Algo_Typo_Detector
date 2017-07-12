#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;
 
int editDistDP(string str1, string str2, int x, int y)
{
    int dp[x+1][y+1];
 
    for (int i=0; i<=x; i++)
    {
        for (int j=0; j<=y; j++)
        {

            if (i==0)
                dp[i][j] = j;  

            else if (j==0)
                dp[i][j] = i; 
 
            else if (str1[i-1] == str2[j-1])
                dp[i][j] = dp[i-1][j-1];

	    if ((str1[i-1] == str2[j-1]) && (str1[i] == str1[i-1]) && (str2[j] != str2[j-1])) //Repeated character
			{
                dp[i][j] = 1 + (dp[i][j-1]); // insert
			
			}

            //dp[i][j] = 1 + (dp[i-1][j]); // Remove

            //dp[i][j] = 1 + (dp[i-1][j-1]); // Replace
        }
    }
 
    return dp[x][y];
}
 
//Edits to Kathy's file with a different method of FileIO
void takeInputs()
{
    string target = "";
	string typo = "";
	//string str3 = "";
	string junk = "";
	int loopCount = 0;

    ifstream input("input.txt"); //sets the input stream to input file
    
	//ofstream myfile("output.txt"); //sets output stream to output file
	if (input.is_open())
	{
		input >> loopCount;
		getline(input, junk);
		while(loopCount > 0)
		{
			getline(input, str3);
			getline(input, str1);
			getline(input, str2);
			cout << str1 << endl << str2 << endl << endl;
			cout << editDistDP(str1, str2, str1.length(), str2.length()) << endl;
            
			//myfile << editDistDP(str1, str2, str1.length(), str2.length()) << endl;
            
			loopCount--;
		}
	}
}	

//driver program

int main ()
{ 
    takeInputs();
    
    cout << loopCount << endl << target << endl << typo;
    return 0;

}
    
