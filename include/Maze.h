/*
 * MAZE Game Framework
 * By Monalisa Sha (Spring 2019)
 */
#ifndef MAZE_H
#define MAZE_H

#include<CommonThings.h>
#include<string.h>
#include<gl/gl.h>
#include<GL/glut.h>
#include<SOIL.h>
#include<iostream>
#include <Timer.h>
#include <math.h>       /* ceil */

using namespace std;



class Maze
{
    public:
        Maze();                           // Constructor
        Maze(int);                        // Overload Constructor
        virtual ~Maze();                  // Deconstructor

      void loadBackgroundImage(char *);   // set an image for the background
      void loadLoseImage(char *);   // set an image for the background
      void loadWinImage(char *);   // set an image for the background
      void loadSetOfArrowsImage(char *);  // set an image for the Arrow Bundle
      void loadChestImage(char *);        // set an image for the Arrow
      void loadUpImage(char *);
      void loadDownImage(char *);
      void loadLeftImage(char *);
      void loadRightImage(char *);


      void drawBackground();
      void drawLose();              // Draw background image
      void drawWin();              // Draw background image              // Draw background image
      void drawGrid();                    // Draw Grid
      void drawArrows();                  // Draw set of Arrows
      void drawChest();                   // Draw Chest

      void drawUp();
      void drawDown();
      void drawLeft();
      void drawRight();

      int getGridSize();                  // return grid size

      void placeChest(int,int);           // Place Chest
      void placeUp(int,int);
      void placeDown(int,int);
      void placeLeft(int,int);
      void placeRight(int,int);

      GridLoc GetChestLoc();              // Return grid location of the chest

      GridLoc GetUpLoc();
      GridLoc GetDownLoc();
      GridLoc GetLeftLoc();
      GridLoc GetRightLoc();

      void placeStArrws(int,int);         // Place set of arrows
      GridLoc GetStArrwsLoc();            // Return grid location of the arrows

      float spin;                         // for spin chest
      bool liveChest;                     // status of the chest (collected or not)
      bool liveSetOfArrws;                // status of the arrows(collected or not)


    protected:

      int gridSize;                       // grid size
      float unitWidth;                    // Unit width of the grid

    private:

      GLuint bakTex;
      GLuint loseTex;                       // Handler for background texture
      GLuint winTex;                       // Handler for background texture                       // Handler for background texture
      GLuint ArrBnchTex;                   // Handler for set of arrows texture
      GLuint chestTex;                     // Handler for Chest texture
      GLuint UpTex;
      GLuint DownTex;
      GLuint LeftTex;
      GLuint RightTex;

      loc chestLoc;                        // chest Location
      loc UpLoc;
      loc DownLoc;
      loc LeftLoc;
      loc RightLoc;

      loc setOfArrsLoc;                    // arrows Location
      loc converter(int, int);             // convert grid size to viewport
};

#endif // MAZE_H
