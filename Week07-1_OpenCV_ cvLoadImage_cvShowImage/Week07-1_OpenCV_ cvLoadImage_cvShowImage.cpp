#include <opencv/highgui.h>

int main()
{
    IplImage * img = cvLoadImage("Image.jpg");///Ū���Ӥ�
    cvShowImage("Week07",img);///��ܷӤ�
    cvWaitKey(0);///���d����
}
