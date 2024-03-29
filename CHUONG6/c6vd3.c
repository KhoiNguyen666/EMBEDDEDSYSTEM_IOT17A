/*Ví dụ 3: Viết chương trình ghi các ký tự từ A-Z vaoffile alphabet.txt 
/* fputc example: alphabet writer */ 
#include <stdio.h> 
#include <string.h>
int main () 
{ 
 FILE * pFile; 
 char c, mystring[100]; 
 pFile = fopen ("alphabet.txt","w"); 
 if (pFile!=NULL) 
 { 
 for (c = 'A' ; c <= 'Z' ; c++) 
 fputc ( c , pFile ); 
 fclose (pFile); 
 } 

 pFile = fopen ("alphabet.txt","r"); 
 if (pFile!=NULL) 
 { 
 if ( fgets (mystring , 100 , pFile) != NULL ) 
 puts (mystring);  
 fclose (pFile); 
 } 

 return 0; 
}
