#include <windows.h>
#include <stdio.h>

int main()
{
    ///絕對路徑寫法PlaySound("C:\\Users\\Administrator\\Desktop\\do-re-mi\\re.wav",NULL,SND_SYNC);
    ///相對路徑寫法(目錄斜線可以寫/或是\\)
    PlaySound("do-re-mi/re.wav",NULL,SND_SYNC);
    printf("Hello World");
}
