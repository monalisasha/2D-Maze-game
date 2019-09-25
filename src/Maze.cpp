/*
 * MAZE Game Framework
 * By Monalisa Sha (Spring 2019)
 */

#include <Maze.h>


Maze::Maze()
{

}

Maze::Maze(int gSize)                                        // Constructor
{
    //ctor
    gridSize =gSize;

    unitWidth = (float)2/gridSize;
    liveChest = true;
    liveSetOfArrws=true;
}

Maze::~Maze()
{
    //dtor
}
void Maze::loadChestImage(char* FileName)
{
    chestTex = TextureLoader(FileName);
}


/*-------------------------LOAD THE TOUCH ARROW IMAGES-----------------------------*/


void Maze::loadUpImage(char* FileName)
{
    UpTex = TextureLoader(FileName);
}

void Maze::loadDownImage(char* FileName)
{
    DownTex = TextureLoader(FileName);
}

void Maze::loadLeftImage(char* FileName)
{
    LeftTex = TextureLoader(FileName);
}
void Maze::loadRightImage(char* FileName)
{
    RightTex = TextureLoader(FileName);
}


/*------------------------------DONE LOADING TOUCH ARROW IMAGES----------------------------*/


void Maze::loadBackgroundImage(char* FileName)
{
   bakTex = TextureLoader(FileName);
}

/*---------------------FUNCTION TO LOAD WIN AND LOSE IMAGES-----------------------*/

void Maze::loadLoseImage(char* FileName)
{
   loseTex = TextureLoader(FileName);
}

void Maze::loadWinImage(char* FileName)
{
   winTex = TextureLoader(FileName);
}

/*---------------------------LOADING DONE--------------------------------------------*/

void Maze::loadSetOfArrowsImage(char* FileName)
{
    ArrBnchTex =  TextureLoader(FileName);
}


/*---------------------------FUNCTIONS TO PLACE TOUCH ARROWS---------------------------*/


void Maze::placeUp(int x, int y)
{
   UpLoc.x =  converter(x,y).x;
   UpLoc.y =  converter(x,y).y;
}

void Maze::placeDown(int x, int y)
{
   DownLoc.x =  converter(x,y).x;
   DownLoc.y =  converter(x,y).y;
}

void Maze::placeLeft(int x, int y)
{
   LeftLoc.x =  converter(x,y).x;
   LeftLoc.y =  converter(x,y).y;
}
void Maze::placeRight(int x, int y)
{
   RightLoc.x =  converter(x,y).x;
   RightLoc.y =  converter(x,y).y;
}

/*------------------------------------------------------------------------------------*/


void Maze::placeChest(int x, int y)
{
   chestLoc.x =  converter(x,y).x;
   chestLoc.y =  converter(x,y).y;
}

void Maze::placeStArrws(int x, int y)
{
   setOfArrsLoc.x =  converter(x,y).x;
   setOfArrsLoc.y =  converter(x,y).y;
}



GridLoc Maze::GetChestLoc()
{
   GridLoc val;

   val.x = (int)(ceil((chestLoc.x +(1-unitWidth))/unitWidth));
   val.y = (int)(ceil((chestLoc.y +(1-unitWidth))/unitWidth));

   return val;
}

/*-------------------------------GETTING LOCATION OF EACH TOUCH ARROW-------------------------------------*/

GridLoc Maze::GetUpLoc()
{
   GridLoc val;

   val.x = (int)(ceil((UpLoc.x +(1-unitWidth))/unitWidth));
   val.y = (int)(ceil((UpLoc.y +(1-unitWidth))/unitWidth));

   return val;
}
GridLoc Maze::GetDownLoc()
{
   GridLoc val;

   val.x = (int)(ceil((DownLoc.x +(1-unitWidth))/unitWidth));
   val.y = (int)(ceil((DownLoc.y +(1-unitWidth))/unitWidth));

   return val;
}
GridLoc Maze::GetRightLoc()
{
   GridLoc val;

   val.x = (int)(ceil((RightLoc.x +(1-unitWidth))/unitWidth));
   val.y = (int)(ceil((RightLoc.y +(1-unitWidth))/unitWidth));

   return val;
}
GridLoc Maze::GetLeftLoc()
{
   GridLoc val;

   val.x = (int)(ceil((LeftLoc.x +(1-unitWidth))/unitWidth));
   val.y = (int)(ceil((LeftLoc.y +(1-unitWidth))/unitWidth));

   return val;
}

/*----------------------------GETTING LOCATION DONE-----------------------------------*/


GridLoc Maze::GetStArrwsLoc()
{
    GridLoc val;

   val.x = (int)(ceil((setOfArrsLoc.x +(1-unitWidth))/unitWidth));
   val.y = (int)(ceil((setOfArrsLoc.y +(1-unitWidth))/unitWidth));

   return val;
}

int Maze::getGridSize()
{
  return gridSize;
}


void Maze::drawBackground()
{
    glColor3f(1.0,1.0,1.0);
    glBindTexture(GL_TEXTURE_2D,bakTex);

    glBegin(GL_QUADS);
        glTexCoord2f(0,1);
        glVertex3f(1,-1,0.0f);

       glTexCoord2f(0,0);
        glVertex3f(1,1,0.0f);

        glTexCoord2f(1,0);
        glVertex3f(-1,1,0.0f);

        glTexCoord2f(1,1);
        glVertex3f(-1,-1,0.0f);
     glEnd();
}

void Maze::drawLose()
{
    glColor3f(1.0,1.0,1.0);
    glBindTexture(GL_TEXTURE_2D,loseTex);
    glBegin(GL_QUADS);
        glTexCoord2f(1,1);
        glVertex3f(1,-1,0.0f);
       glTexCoord2f(1,0);
        glVertex3f(1,1,0.0f);
        glTexCoord2f(0,0);
        glVertex3f(-1,1,0.0f);
        glTexCoord2f(0,1);
        glVertex3f(-1,-1,0.0f);
     glEnd();
}
void Maze::drawWin()
{
    glColor3f(1.0,1.0,1.0);
    glBindTexture(GL_TEXTURE_2D,winTex);
    glBegin(GL_QUADS);
        glTexCoord2f(1,1);
        glVertex3f(1,-1,0.0f);
       glTexCoord2f(1,0);
        glVertex3f(1,1,0.0f);
        glTexCoord2f(0,0);
        glVertex3f(-1,1,0.0f);
        glTexCoord2f(0,1);
        glVertex3f(-1,-1,0.0f);
     glEnd();
}

void Maze::drawGrid()
{
   float a;
   glColor4f(1.0,1.0,1.0,0.2);
   glDisable(GL_TEXTURE_2D);
   glPointSize(1);
   glBegin(GL_LINES);

   for(int i =0;i<gridSize;i++)
    {
         a = -1+(float)unitWidth*i;
         glVertex3f(a,1,-0.4);
         glVertex3f(a,-1,-0.4);
         glVertex3f(-1,a,0.4);
         glVertex3f(1,a,0.4);
    }
    glEnd();
    glEnable(GL_TEXTURE_2D);
}

void Maze::drawArrows()
{
    if(liveSetOfArrws)
    {

    glColor3f(1.0,1.0,1.0);

    glTranslatef(setOfArrsLoc.x,setOfArrsLoc.y,1.0);
    glRotated(-spin,0,0,1);

    glBindTexture(GL_TEXTURE_2D,ArrBnchTex);
    glScaled(1.0/(float)(gridSize),1.0/(float)(gridSize),1.0);

    glBegin(GL_QUADS);
        glTexCoord2f(0,1);
        glVertex3f(1,-1,0.0f);

       glTexCoord2f(0,0);
        glVertex3f(1,1,0.0f);

        glTexCoord2f(1,0);
        glVertex3f(-1,1,0.0f);

        glTexCoord2f(1,1);
        glVertex3f(-1,-1,0.0f);
     glEnd();
    }
}

void Maze::drawChest()
{
    if(liveChest){
    glColor3f(1.0,1.0,1.0);

    glTranslatef(chestLoc.x,chestLoc.y,1.0);

    glBindTexture(GL_TEXTURE_2D,chestTex);
    glScaled(1.0/(float)(gridSize+5),1.0/(float)(gridSize+5),1.0);
    glRotated(spin,0,0,1);

    glBegin(GL_QUADS);
        glTexCoord2f(0,1);
        glVertex3f(1,-1,0.0f);

       glTexCoord2f(0,0);
        glVertex3f(1,1,0.0f);

        glTexCoord2f(1,0);
        glVertex3f(-1,1,0.0f);

        glTexCoord2f(1,1);
        glVertex3f(-1,-1,0.0f);
     glEnd();

     spin +=0.5;
    }
}

/*---------------------------FUNCTIONS TO DRAW TOUCH ARROWS--------------------------------*/


void Maze::drawUp()
{
    glColor3f(1.0,1.0,1.0);

    glTranslatef(UpLoc.x,UpLoc.y,1.0);

    glBindTexture(GL_TEXTURE_2D,UpTex);
    glScaled(1.0/(float)(gridSize+1),1.0/(float)(gridSize+1),1.0);

    glBegin(GL_QUADS);
        glTexCoord2f(0,1);
        glVertex3f(1,-1,0.0f);

       glTexCoord2f(0,0);
        glVertex3f(1,1,0.0f);

        glTexCoord2f(1,0);
        glVertex3f(-1,1,0.0f);

        glTexCoord2f(1,1);
        glVertex3f(-1,-1,0.0f);
     glEnd();

}

void Maze::drawDown()
{
    glColor3f(1.0,1.0,1.0);

    glTranslatef(DownLoc.x,DownLoc.y,1.0);

    glBindTexture(GL_TEXTURE_2D,DownTex);
    glScaled(1.0/(float)(gridSize+1),1.0/(float)(gridSize+1),1.0);

    glBegin(GL_QUADS);
        glTexCoord2f(0,1);
        glVertex3f(1,-1,0.0f);

       glTexCoord2f(0,0);
        glVertex3f(1,1,0.0f);

        glTexCoord2f(1,0);
        glVertex3f(-1,1,0.0f);

        glTexCoord2f(1,1);
        glVertex3f(-1,-1,0.0f);
     glEnd();

}

void Maze::drawLeft()
{
    glColor3f(1.0,1.0,1.0);

    glTranslatef(LeftLoc.x,LeftLoc.y,1.0);

    glBindTexture(GL_TEXTURE_2D,LeftTex);
    glScaled(1.0/(float)(gridSize+1),1.0/(float)(gridSize+1),1.0);

    glBegin(GL_QUADS);
        glTexCoord2f(0,1);
        glVertex3f(1,-1,0.0f);

       glTexCoord2f(0,0);
        glVertex3f(1,1,0.0f);

        glTexCoord2f(1,0);
        glVertex3f(-1,1,0.0f);

        glTexCoord2f(1,1);
        glVertex3f(-1,-1,0.0f);
     glEnd();

}

void Maze::drawRight()
{
    glColor3f(1.0,1.0,1.0);

    glTranslatef(RightLoc.x,RightLoc.y,1.0);

    glBindTexture(GL_TEXTURE_2D,RightTex);
    glScaled(1.0/(float)(gridSize+1),1.0/(float)(gridSize+1),1.0);

    glBegin(GL_QUADS);
        glTexCoord2f(0,1);
        glVertex3f(1,-1,0.0f);

       glTexCoord2f(0,0);
        glVertex3f(1,1,0.0f);

        glTexCoord2f(1,0);
        glVertex3f(-1,1,0.0f);

        glTexCoord2f(1,1);
        glVertex3f(-1,-1,0.0f);
     glEnd();

}

/*-------------------------------------------------------------------------------------*/


loc Maze::converter(int x, int y)
{
       loc val;

        x+=1;
        y+=1;
       val.x = -1-unitWidth/2+(unitWidth)*x;
       val.y = -1-unitWidth/2+(unitWidth)*y;
       return val;
}


