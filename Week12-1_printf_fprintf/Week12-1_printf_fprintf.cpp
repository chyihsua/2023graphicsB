#include <stdio.h>

int main()
{
    printf("Hello World\n");

    FILE * fout =fopen("file.txt","w"); ///開檔案 fopen(檔名，模式)
    fprintf(fout,"Hello World在檔案裡\n");
}
