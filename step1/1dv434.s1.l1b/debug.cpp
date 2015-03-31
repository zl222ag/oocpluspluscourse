/**********************************************************************/
// File:	debug.cpp
// Summary:	Practice file for Lab 1, Step 1
//			The program reads a string of characters. Prints all 
//			occurrences of letters and numbers, sorted in alphabetical 
//			and numerical order. Letters will be converted to uppercase.
//			Other characters are filtered out, while number of white 
//			spaces are counted.
// Version: Version 1.1 - 2013-03-17
// Author:	Anne Norling
// -------------------------------------------
// Log:	2003-08-11	Created the file. Anne
//		2013-03-17	Uppdate  Version 1.1 by Anne. 
//					Converted to English and VS 2012 
//		2015-03-05	Revised by Anne. Converted to VS 2013
//		2015-03-31 Update Version 1.1.1 by Zlatko.
/**********************************************************************/

#include <iostream>
const int SIZE = 100;

using namespace std;

int main()
{
	char *pStr, str[SIZE] = "", newStr[SIZE] = "", ch;
	int count = 0, i = 0, j = 0;

	cout << "Enter a number of mixed characters: ";
	cin.getline(str, SIZE);
	pStr = str;
	
	while (*pStr != '\0')
	{
		if (isalnum(*pStr)) {
			ch = toupper(*pStr);
			newStr[i++] = ch;
		}
		
		if (*pStr == ' ') {
			count++;
		}
		pStr++;
	}
	newStr[i] = '\0';

	cout << strlen(str) - strlen(newStr) << " characters were filtered out,"
		<< " out of which " << count << " whitespaces were encountered.\n";
	
	int temp;

	for (i = 0; i < strlen(newStr) - 1; i++)
	{
		for (j = i + 1; j < strlen(newStr); j++)
		{
			if (newStr[j] < newStr[i])	// sorts in alphabetical
			{						// and numerical order 
				temp = newStr[i];			
				newStr[i] = newStr[j];
				newStr[j] = temp;
			}
		}
	}
	cout << "New sorted string: " << newStr << endl;
	return 0;
}
