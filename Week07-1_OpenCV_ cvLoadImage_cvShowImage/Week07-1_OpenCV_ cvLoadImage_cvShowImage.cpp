#include <opencv/highgui.h>

int main()
{
    IplImage * img = cvLoadImage("Image.jpg");///讀取照片
    cvShowImage("Week07",img);///顯示照片
    cvWaitKey(0);///停留視窗
}
