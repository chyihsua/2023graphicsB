#include <opencv/highgui.h> 
#include <opencv/cv.h>
#include <GL/glut.h>

int myTexture(char * filename)
{
    IplImage * img = cvLoadImage(filename); 
    cvCvtColor(img,img, CV_BGR2RGB); 
    glEnable(GL_TEXTURE_2D); 
    GLuint id;
    glGenTextures(1, &id); 
    glBindTexture(GL_TEXTURE_2D, id); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img->width, img->height, 0, GL_RGB, GL_UNSIGNED_BYTE, img->imageData);
    return id;
}

#include <stdio.h>
#include <GL/glut.h>
#include "glm.h"
GLMmodel * gundam = NULL;
float teapotX = 0, teapotY = 0, angle = 0, oldX = 0, oldY = 0;
void mouse(int button, int state, int x, int y) {
    oldX = x;
    oldY = y;
}
void motion(int x, int y) {
    teapotX = (x-150)/150.0;
    teapotY = (150-y)/150.0;
    angle += x - oldX;
    oldX = x;
    glutPostRedisplay();
    printf("  glTranslatef( %.2f, %.2f, 0 ); \n", teapotX, teapotY );
}
void display() {
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
        glColor3f(1,1,1);
        glScalef(0.04, 0.04, 0.04);
        glRotatef(angle, 0, 1, 0);
        glmDraw(gundam, GLM_MATERIAL|GLM_TEXTURE);
    glPopMatrix();

    glColor3f(0,1,0);
    glutSolidTeapot( 0.02 );

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

    gundam = glmReadOBJ("model/Gundam.obj");
    myTexture("model/Diffuse.jpg");
    glEnable(GL_DEPTH_TEST);

    glutMainLoop();
}
