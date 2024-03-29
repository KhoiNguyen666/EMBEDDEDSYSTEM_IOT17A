/*Ví dụ 2: Viết chương trình mở file myfile.txt để đọc 100 ký tự dòng đầu tiên và 
xuất ra màn hình 
/* fgets example */ 
#include <stdio.h> 
int main() 
{ 
 FILE * pFile; 
 char mystring [100]; 
 pFile = fopen ("myfile.txt" , "r"); 
 if (pFile == NULL) perror ("Error opening file"); 
 else 
 { 
 if ( fgets (mystring , 100 , pFile) != NULL ) 
 puts (mystring); 
 fclose (pFile); 
 } 
 return 0; 
}
