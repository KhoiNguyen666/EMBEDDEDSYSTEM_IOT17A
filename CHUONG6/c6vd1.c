/*Ví dụ 1: Đếm xem file myfile.txt có bao nhiêu ký tự $
fgetc example: money counter */ 
#include <stdio.h> 
int main () 
{ 
 FILE * pFile; 
 int c; 
 int n = 0; 
 pFile=fopen("myfile.txt","r"); 
 if (pFile==NULL) perror ("Error opening file"); 
 else 
 { 
 do 
 { 
 c = fgetc (pFile); 
 if (c == '$') n++; 
 } while (c != EOF); 
 fclose (pFile); 
 printf ("The file contains %d dollar sign characters ($).\n",n); 
 } 
 return 0; 
}
