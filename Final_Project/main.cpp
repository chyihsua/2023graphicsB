#include <opencv/highgui.h> ///使用 OpenCV 2.1 比較簡單, 只要用 High GUI 即可
#include <opencv/cv.h>
#include <stdio.h>
#include <GL/glut.h>
#include "glm.h"

GLMmodel * Lleg = NULL;
GLMmodel * Lhand = NULL;
GLMmodel * Larm = NULL;
GLMmodel * Rleg = NULL;
GLMmodel * Rhand = NULL;
GLMmodel * Rarm = NULL;
GLMmodel * Leye = NULL;
GLMmodel * Reye = NULL;
GLMmodel * body = NULL;

float teapotX = 0, teapotY = 0, oldX = 0, oldY = 0;
float angle[20] = {}, angle2[20] = {};
float NewAngle[20] = {}, NewAngle2[20] = {};
float OldAngle[20] = {}, OldAngle2[20] = {};
int ID=0;
FILE * fout = NULL;
FILE * fin = NULL;

void timer(int t) {
    printf("現在timer(%d)\n", t);
    glutTimerFunc(20, timer, t+1); ///馬上設定下一個鬧鐘

    float alpha = (t%50) / 50.0; ///0.0 ~ 1.0

    if(t%50==0){
        if(fin == NULL) fin = fopen("motion.txt", "r");
        for(int i=0; i<20; i++){
            OldAngle[i] = NewAngle[i];
            OldAngle2[i] = NewAngle2[i];
            fscanf(fin, "%f", &NewAngle[i] );
            fscanf(fin, "%f", &NewAngle2[i] );
        }
    }
    for(int i=0; i<20; i++){
        angle[i] = NewAngle[i] * alpha + OldAngle[i] * (1-alpha);
        angle2[i] = NewAngle2[i] * alpha + OldAngle2[i] * (1-alpha);
    }

    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    if(key=='0') ID = 0;
    if(key=='1') ID = 1;
    if(key=='2') ID = 2;
    if(key=='3') ID = 3;
    if(key=='4') ID = 4;
    if(key=='5') ID = 5;
    if(key=='6') ID = 6;
    if(key=='7') ID = 7;
    if(key=='8') ID = 8;
    if(key=='9') ID = 9;
    if(key=='s'){ ///save存檔 也會動到檔案
        if(fout == NULL) fout = fopen("motion.txt", "w");
        for(int i=0; i<20; i++){
            fprintf(fout, "%.2f ", angle[i] );
            fprintf(fout, "%.2f ", angle2[i] );
        }
        fprintf(fout, "\n");
        printf("寫了一行\n");
    }
    if(key=='r'){ ///read讀檔 也會動到檔案
        if(fin == NULL) fin = fopen("motion.txt", "r");
        for(int i=0; i<20; i++){
            fscanf(fin, "%f", &angle[i] );
            fscanf(fin, "%f", &angle2[i] );
        }
        glutPostRedisplay();
    }
    if(key=='p'){ ///play播放 也會動到檔案
        glutTimerFunc(0, timer, 0);
    }
}



int myTexture(char * filename)
{
    IplImage * img = cvLoadImage(filename); ///OpenCV讀圖
    cvCvtColor(img,img, CV_BGR2RGB); ///OpenCV轉色彩 (需要cv.h)
    glEnable(GL_TEXTURE_2D); ///1. 開啟貼圖功能
    GLuint id; ///準備一個 unsigned int 整數, 叫 貼圖ID
    glGenTextures(1, &id); /// 產生Generate 貼圖ID
    glBindTexture(GL_TEXTURE_2D, id); ///綁定bind 貼圖ID
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); /// 貼圖參數, 超過包裝的範圖T, 就重覆貼圖
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); /// 貼圖參數, 超過包裝的範圖S, 就重覆貼圖
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); /// 貼圖參數, 放大時的內插, 用最近點
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); /// 貼圖參數, 縮小時的內插, 用最近點
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img->width, img->height, 0, GL_RGB, GL_UNSIGNED_BYTE, img->imageData);
    return id;
}
void mouse(int button, int state, int x, int y) {
    oldX = x;
    oldY = y;
}
void motion(int x, int y) {
    teapotX += (x - oldX) / 150.0 * 10; ///teapotX = (x-150)/150.0;
    teapotY += (oldY - y) / 150.0 * 10; ///teapotY = (150-y)/150.0;
    angle[ID] += x - oldX;
    angle2[ID] += oldY - y;
    oldX = x;
    oldY = y;
    glutPostRedisplay();
    printf("  glTranslatef( %.2f, %.2f, 0 ); \n", teapotX, teapotY );
}
void display() {
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
        glScalef(0.3, 0.3, 0.3);

        //glTranslatef(0, -0.5, 0);///往下一半
        glPushMatrix();
            glColor3f(1,1,1);
            glRotatef(angle[0], 0, 1, 0);
            glmDraw(Reye,GLM_MATERIAL);
            glColor3f(1,1,0);
            glRotatef(angle[0], 0, 1, 0);
            glmDraw(body, GLM_MATERIAL);///glmDraw(gundam, GLM_MATERIAL|GLM_TEXTURE);

            glPushMatrix(); ///小小兵方向的右手
                //glTranslatef(teapotX, teapotY, 0);
                glTranslatef( -1.13, -0.60, 0 );
                glRotatef(angle[1], 0, 1, 0);
                glRotatef(angle2[1], 1, 0, 0);
                glTranslatef(  1.13, 0.60, 0 );///glTranslatef(teapotX, teapotY, 0);
                glmDraw(Rarm, GLM_MATERIAL);

                glPushMatrix();
                    //glTranslatef(teapotX, teapotY, 0);
                    glTranslatef(  -1.9, -0.60, 0 );
                    glRotatef(angle[2], 0, 1, 0);
                    glRotatef(angle2[2], 1, 0, 0);
                    glTranslatef(   1.9, 0.60, 0 );///glTranslatef(teapotX, teapotY, 0);
                    glColor3f(0.4,0.4,0.4);
                    glmDraw(Rhand, GLM_MATERIAL);
                glPopMatrix();
            glPopMatrix();

            glPushMatrix(); ///小小兵方向的左手
                //glTranslatef(teapotX, teapotY, 0);
                glTranslatef( 1.13, -0.60, 0 );
                glRotatef(angle[3], 0, 1, 0);
                glRotatef(angle2[3], 1, 0, 0);
                glTranslatef(  -1.13, 0.60, 0 );///glTranslatef(teapotX, teapotY, 0);
                glColor3f(1,1,0);
                glmDraw(Larm, GLM_MATERIAL);

                glPushMatrix();
                    //glTranslatef(teapotX, teapotY, 0);
                    glTranslatef(  2.13, -0.60, 0 );
                    glRotatef(angle[4], 0, 1, 0);
                    glRotatef(angle2[4], 1, 0, 0);
                    glTranslatef(   -2.13, 0.60, 0 );///glTranslatef(teapotX, teapotY, 0);
                    glColor3f(0.4,0.4,0.4);
                    glmDraw(Lhand, GLM_MATERIAL);
                glPopMatrix();
            glPopMatrix();

            glPushMatrix(); ///小小兵方向的右腳
                //glTranslatef(teapotX, teapotY, 0);
                glTranslatef( -0.40, -1.80, 0 );
                glRotatef(angle[5], 0, 1, 0);
                glRotatef(angle2[5], 1, 0, 0);
                glTranslatef(  0.40, 1.80, 0 );///glTranslatef(teapotX, teapotY, 0);
                glmDraw(Rleg, GLM_MATERIAL);
            glPopMatrix();

            glPushMatrix(); ///小小兵方向的左腳
                //glTranslatef(teapotX, teapotY, 0);
                glTranslatef( 0.40, -1.80, 0 );
                glRotatef(angle[6], 0, 1, 0);
                glRotatef(angle2[6], 1, 0, 0);
                glTranslatef(  -0.40, 1.80, 0 );///glTranslatef(teapotX, teapotY, 0);
                glmDraw(Lleg, GLM_MATERIAL);
            glPopMatrix();

        glPopMatrix();
        glColor3f(0,1,0);
        glutSolidTeapot( 0.02 );
    glPopMatrix();
    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_DEPTH);
    glutCreateWindow("week16");

    glutDisplayFunc(display);
    glutMotionFunc(motion);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);

    Lleg = glmReadOBJ("CGmodel/L_leg.obj");
    Lhand = glmReadOBJ("CGmodel/L_hand.obj");
    Larm = glmReadOBJ("CGmodel/L_arm.obj");
    Rleg = glmReadOBJ("CGmodel/R_leg.obj");
    Rhand = glmReadOBJ("CGmodel/R_hand.obj");
    Rarm = glmReadOBJ("CGmodel/R_arm.obj");
    Leye = glmReadOBJ("CGmodel/L_eyeball.obj");
    Reye = glmReadOBJ("CGmodel/R_eyeball.obj");
    body = glmReadOBJ("CGmodel/body.obj");

    //myTexture("model/Diffuse.jpg");
    glEnable(GL_DEPTH_TEST);

    glutMainLoop();
}
