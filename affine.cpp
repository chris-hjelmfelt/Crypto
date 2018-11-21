//////////////////////////////////////////////////////////
// Affine Cipher
// Authors: Samuel Carroll, Zach Norstedt and Chris Hjelmfelt
// CSC 512/412 - Cryptography
// Dr. Brent Deschamp
// Date Due: September 9, 2015
// Date Written: September 8, 2015 
// This program will read in a key and some plain text and create a ciphertext 
// alternatively it reads in cypher text and a key and returns the plaintext
//
// It uses the equation (ax + b) mod 26
// Keys are numbers a and b where a must be coprime to 26  (they share only 1 as a factor)
//
// Usage
//  keys and plaintext go into commandline
//  example:
//  ./affine 5 6 "thisismyplaintext"
//  or else
//  keys and "ciphertext.txt" go into commandline
//  example:
//  ./affine 19 122 ciphertext.txt
//  
//  This works best without spaces or punctuation
/////////////////////////////////////////////////////////////
 
#include<iostream>
#include<fstream>
#include<string>
#include<string.h>
#include <stdlib.h>
using namespace std;
 
void encipheraffine(int keymult, int keyadd, char* plain);
void decipheraffine(int keymult, int keyadd);
int findInverse(int keymult);
 
 
int main(int argc, char** argv)
{
  if(strcmp(argv[3], "ciphertext.txt") == 0)
  {
    decipheraffine(atoi(argv[1]), atoi(argv[2]));
  }
  else
  {
    encipheraffine(atoi(argv[1]), atoi(argv[2]), argv[3]);
  }  
  return 0;
}
 
 
void decipheraffine(int keymult, int keyadd)
{
  int inverse;
  ifstream fin;
  fin.open("ciphertext.txt");
  ofstream fout;
  fout.open("plaintext.txt");
  if( !fin)
  {
    cout << "no such file\n";
  }
  else
  {
    char currChar;
    inverse = findInverse(keymult);
    while(fin >> currChar)
    {
      currChar -= 'a';
      if (currChar <= keyadd)
        currChar = currChar + 26;
      currChar = (inverse * (currChar - keyadd))%26;      
      if(currChar < 0)
         currChar = currChar + 26;
      currChar += 'a';      
      fout << currChar;
      cout << currChar;
    }
    cout << endl;
 
    fin.close();
    fout.close();
  }
}
 
 
void encipheraffine(int keymult, int keyadd, char* plain)
{
  int plainLength = strlen(plain);
  int thisChar;
  ofstream fout;
  fout.open("ciphertext.txt");
 
  for (int i=0; i < plainLength; i++)
  {
    thisChar = plain[i];
    thisChar -= 'a';
    thisChar = thisChar * keymult;
    thisChar += keyadd;
    thisChar = thisChar % 26;
    thisChar += 'a';
    fout << ((char)thisChar);
  }
  fout.close();
 
  cout << "Your file is ready\n";
}
 
 
int findInverse(int keymult)
{
  int i=0;
  for (i = 1; ((keymult * i) % 26) != 1; i++)
  {
      // Do nothing
  }
 
  return i;
}