#include <windows.h>
#include <stdio.h>

int main()
{
    ///������|�g�kPlaySound("C:\\Users\\Administrator\\Desktop\\do-re-mi\\re.wav",NULL,SND_SYNC);
    ///�۹���|�g�k(�ؿ��׽u�i�H�g/�άO\\)
    PlaySound("do-re-mi/re.wav",NULL,SND_SYNC);
    printf("Hello World");
}
