/*
 * MAZE Game Framework
 * Written by Dr. Dhanyu Amarasinghe Spring 2018
 */


 /*-------------BUSH HEADER FILE SIMILAR TO WALL HEADER--------------*/
#include <bush.h>
#include <iostream>

using namespace std;


bush::bush()
{
    //ctor
    livebush = true;
}

bush::~bush()
{
    //dtor
}

void bush::bushInit(int grid,char* FileName)
{
    gridSize = grid;
    unitWidth = (float)2/grid;
    bushTex = TextureLoader(FileName);
}

void bush::drawbush()
{
    if(livebush)
    {

    glColor3f(1.0,1.0,1.0);
    glBindTexture(GL_TEXTURE_2D,bushTex);

    glPushMatrix();
    glTranslatef(bushBrk.x,bushBrk.y,0.0);

    glScalef(1.0/(float)gridSize,1.0/(float)gridSize,1);


     glBegin(GL_POLYGON);
            glTexCoord2f(0,0);
            glVertex3f(1,1,0.0f);

            glTexCoord2f(1,0);
            glVertex3f(-1,1,0.0f);

            glTexCoord2f(1,1);
            glVertex3f(-1,-1,0.0f);

            glTexCoord2f(0,1);
            glVertex3f(1,-1,0.0f);
    glEnd();
    glPopMatrix();
    }
}

void bush::placebush(int x, int y)
{
    GetbushLoc.x= x;
    GetbushLoc.y= y;

    x+=1;
    y+=1;

    bushBrk.x =  (unitWidth)*x-1-unitWidth/2;
    bushBrk.y =  (unitWidth)*y-1-unitWidth/2;
}








