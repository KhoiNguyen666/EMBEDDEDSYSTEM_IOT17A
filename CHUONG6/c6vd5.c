/*Ví dụ 5: Viết chương trình đọc chuỗi ký tự nhập từ bàn phím sau đó mở file 
mylog.txt để tiếp tục ghi chuỗi ký tự đọc này vào cuối file. 
/* fputs example */ 
#include <stdio.h> 
int main () 
{ 
 FILE * pFile; 
 char sentence [256]; 
 printf ("Enter sentence to append: "); 
 fgets (sentence,256,stdin); 
 pFile = fopen ("mylog.txt","a"); 
 fputs (sentence,pFile); 
 fclose (pFile); 
 return 0; 
}
