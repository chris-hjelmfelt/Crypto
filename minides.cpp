// minides.cpp
// by Ashley Conger and Chris Hjelmfelt
// Fall 2015   CSC-412 Cryptography
// Usage: "cat key.txt message.txt | ./minides -[e/d] > output.txt"
// key.txt should be a binary number 9 digits long
// message.txt should be a binary number 12 digits long
// choose -e to encrypt and -d to decrypt
/////////////////////////////////////////////////////////////
 
#include<iostream>
#include<string.h>
#include<stdlib.h>
 
using namespace std;
 
// Public Variables
int plain[12];
int key[9];
int xorx[8];
int f[6]={0};
int round = 0;
int currKey[8];
 
void encipher();
void decipher();
void sBoxes();
void getKey();
 
int main(int argc, char* argv[])
{
  // error
  if( argc != 2)
  {
    cout << "wrong number of arguments. Input should look like this: " << endl;
    cout << "cat key.txt message.txt | ./minides -[e/d] > output.txt" << endl;
    return 0;
  }
 
  // get input
  char message[12];
  char charKey[9];
 
  cin >> charKey;
  cin >> message;
 
  // take message from input
  for (int j = 0; j < 12; j++)
    plain[j] = message[j]-'0';
  // take key from input
  for (int i = 0; i < 12; i++)
    key[i] = charKey[i]-'0';
 
  // encipher/decipher flag
  switch (argv[1][1]) {
      case 'e':
          encipher();
          encipher();
          encipher();
          encipher();
          for ( int p = 0; p < 12; p++)
          cout << plain[p];
          break;
 
      case 'd':
      round = 3;
          decipher();
          decipher();
          decipher();
          decipher();
          for ( int p = 0; p < 12; p++)
          cout << plain[p];
          break;
  }
  return 0;
}
 
 
void encipher()
{
  // Variables
  int R[6];
  int L[6];
  int expR[8];
  int lorf[6];
 
  // put inputs in R, L, key
  for (int i = 0; i < 6; i++)
  {
    L[i] = plain[i];
    R[i] = plain[i+6];
  }
 
  // Expand R
  expR[0] = R[0];
  expR[1] = R[1];
  expR[2] = R[3];
  expR[3] = R[2];
  expR[4] = R[3];
  expR[5] = R[2];
  expR[6] = R[4];
  expR[7] = R[5];  
 
  getKey();
 
  // E(R) xor K1
  for(int j=0; j<8; j++)
  {
    xorx[j] = expR[j] + currKey[j];
    if(xorx[j] == 2)
      xorx[j] = 0;
  }
 
  // Send xorx through sBoxes
  sBoxes();
 
  // L0 xor f
  for (int m = 0; m < 6; m++)
  {
    lorf[m] = L[m] + f[m];
    if (lorf[m] == 2)
      lorf[m] = 0;
  }
 
  // put L0 xor f with R0 to get the cipher
  for (int n = 0; n < 6; n++)
  {
    plain[n] = R[n];
    plain[n + 6] = lorf[n];
  }
 
  round++;
} 
 
 
void decipher() {
  // Variables  
  int R[6];
  int L[6];
  int expR[8];
  int lorf[6];
 
  // put inputs in R, L, key
  for (int i = 0; i < 6; i++)
  {
    R[i] = plain[i];
    L[i] = plain[i+6];
  }
 
  // Expand R
  expR[0] = R[0];
  expR[1] = R[1];
  expR[2] = R[3];
  expR[3] = R[2];
  expR[4] = R[3];
  expR[5] = R[2];
  expR[6] = R[4];
  expR[7] = R[5];  
 
  getKey();
 
  // E(R) xor K1
  for(int j=0; j<8; j++)
  {
    xorx[j] = expR[j] + currKey[j];
    if(xorx[j] == 2)
      xorx[j] = 0;      
  }  
 
  // Send xorx through sBoxes
  sBoxes();
 
  // L0 xor f
  for (int m = 0; m < 6; m++)
  {
    lorf[m] = L[m] + f[m];
    if (lorf[m] == 2)
      lorf[m] = 0;    
  }
 
  // put L0 xor f with R0 to get the cipher
  for (int n = 0; n < 6; n++)
  {
    plain[n] = lorf[n];
    plain[n + 6] = R[n];
  }  
 
  round--;
}
 
 
void sBoxes() // puts the xorx function through the S boxes to get the function f(L2,K)
{
  int s1[16][3]={0};
  for ( int i1 = 0; i1 < 16; i1++) {
    if ( i1==0 || i1==3 || i1==5 || i1==6 || i1==9 || i1==10 || i1==13 || i1==14)
        s1[i1][0]=1;
    else
        s1[i1][0]=0;
  }
  for ( int i2 = 0; i2 < 16; i2++) {
    if ( i2==1 || i2==3 || i2==4 || i2==6 || i2==10 || i2==11 || i2==13 || i2==15)
        s1[i2][1]=1;
    else
        s1[i2][1]=0;
  }
  for ( int i3 = 0; i3 < 16; i3++) {
    if ( i3==0 || i3==2 || i3==4 || i3==6 || i3==8 || i3==13 || i3==14 || i3==15)
        s1[i3][2]=1;
    else
        s1[i3][2]=0;
  }
 
  int s2[16][3];
  for ( int i4 = 0; i4 < 16; i4++) {
    if ( i4==0 || i4==2 || i4==3 || i4==4 || i4==8 || i4==11 || i4==12 || i4==15)
        s2[i4][0]=1;
    else
        s2[i4][0]=0;
  }
  for ( int i5 = 0; i5 < 16; i5++) {
    if ( i5==2 || i5==4 || i5==6 || i5==7 || i5==9 || i5==11 || i5==12 || i5==13)
        s2[i5][1]=1;
    else
        s2[i5][1]=0;
  }
  for ( int i6 = 0; i6 < 16; i6++) {
    if ( i6==3 || i6==4 || i6==5 || i6==6 || i6==8 || i6==9 || i6==11 || i6==14)
        s2[i6][2]=1;
    else
        s2[i6][2]=0;
  }
 
  int index1=0;
  int index2=0;
  index1 = 8*xorx[0]+4*xorx[1]+2*xorx[2]+xorx[3];
  index2 = 8*xorx[4]+4*xorx[5]+2*xorx[6]+xorx[7];
 
  f[0] = s1[index1][0];
  f[1] = s1[index1][1];
  f[2] = s1[index1][2];
  f[3] = s2[index2][0];
  f[4] = s2[index2][1];
  f[5] = s2[index2][2];  
}
 
 
void getKey()
{
  for(int i =0; i < 8; i++)
  {
    currKey[i]= key[(i + round) % 9];
  }
}