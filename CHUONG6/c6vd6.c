/*Ví dụ 6: Xem nội dung file example.txt sau khi chạy đoạn code sau: 
/* fseek example */ 
#include <stdio.h> 
int main () 
{ 
 FILE * pFile; 
 pFile = fopen ( "example.txt" , "wb" ); 
 fputs ( "This is an apple." , pFile ); 
 fseek ( pFile , 9 , SEEK_SET ); 
 fputs ( " sam" , pFile ); 
 fclose ( pFile ); 
 return 0; 
}
