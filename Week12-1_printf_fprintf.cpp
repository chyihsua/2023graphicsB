#include <stdio.h>

int main()
{
    printf("Hello World\n");

    FILE * fout =fopen("file.txt","w"); ///�}�ɮ� fopen(�ɦW�A�Ҧ�)
    fprintf(fout,"Hello World�b�ɮ׸�\n");
}
