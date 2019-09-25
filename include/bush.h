/*
 * MAZE Game Framework
 * By Monalisa Sha (Spring 2019)
 */


/*------------------------BUSH CPP FILE SIMILAR TO WALL CPP-------------------------------------*/

#ifndef BUSH_H
#define BUSH_H

#include<CommonThings.h>
#include<string.h>
#include<gl/gl.h>
#include<GL/glut.h>
#include<SOIL.h>
#include<iostream>
#include <Timer.h>
#include <math.h>       /* ceil */


class bush
{
    public:
        bush();                            // constructor
        virtual ~bush();                   // De constructor
        bush(int);                         // overload constructor

            void drawbush();               // Draw the Maze bush
            void bushInit(int, char *);    // initialize the bush
            void placebush(int, int);
                  // place the bush

            float unitWidth;               // unit width of the grid cell
            int gridSize;                  // grid size

            bool livebush;                 // bush status (broken or not)
    protected:

    private:
              loc bushBrk;                 // viewport location of the bush
              GLuint bushTex;              // bush texture handler
              GridLoc GetbushLoc;          // Grid Location of the bush
};

#endif // BUSH_H

