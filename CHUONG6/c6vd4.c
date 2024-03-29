/*Ví dụ 4: Viết chương trình mở file file.txt để ghi nội dung vào file. Sau đó đọc 
file đã ghi. Kết quả đọc file sẽ xuất ra màn hình. */
#include <stdio.h> 
#include <string.h> 
int main() 
{ 
 FILE *fp; 
 char c[] = "Example for function fread and fwrite"; 
 char buffer[100]; 
 /* Open file for both reading and writing */ 
 fp = fopen("file.txt", "r+"); 
 /* Write data to the file */ 
 fwrite(c, sizeof(c), 1, fp); 
 /* Seek to the beginning of the file */ 
 fseek(fp, SEEK_SET, 0); 
 /* Read and display data */ 
 fread(buffer, strlen(c)+1, 1, fp); 
 printf("%s\n", buffer); 
 fclose(fp); 
 return(0); 
}
