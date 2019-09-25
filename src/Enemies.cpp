/*
 * MAZE Game Framework
 * By Monalisa Sha (Spring 2019)
 */

#include <Enemies.h>
#include <iostream>
#include<wall.h>
#include<player.h>
using namespace std;

Timer *T1 = new Timer();
                            // Set Timer for animation
Enemies::Enemies()
{
    //ctor
    enmLoc.x=0;
    enmLoc.y=0;

    xmax =1;
    ymax =0.25;
    xmin =0;
    ymin =0;
    up= down = left=right=false;
    live = true;

}

Enemies::~Enemies()
{
    //dtor
}

void Enemies::initEnm(int grid,int numFrames, char * FileName)
{
    gridSize = grid;
    frames = numFrames;
    xmax =1/(float)frames;
    T1->Start();
    t = (float)(2.0/grid)/frames;
    unitWidth = (float)2.0/gridSize;
    enmTex = TextureLoader(FileName);
}


void Enemies::drawEnemy()
{
    if(live){
    glColor3f(1.0,1.0,1.0);
    glBindTexture(GL_TEXTURE_2D,enmTex);


    glPushMatrix();
    animate();
    glTranslatef(enmLoc.x,enmLoc.y,0.0);

    glScaled(1.0/(float)gridSize,1.0/(float)gridSize,1);

    glBegin(GL_POLYGON);
        glTexCoord2f(xmin,ymin);
        glVertex3f(1,1,0.0f);

        glTexCoord2f(xmax,ymin);
        glVertex3f(-1,1,0.0f);

        glTexCoord2f(xmax,ymax);
        glVertex3f(-1,-1,0.0f);

        glTexCoord2f(xmin,ymax);
        glVertex3f(1,-1,0.0f);
     glEnd();
     glPopMatrix();
}
}
void Enemies::placeEnemy(int x, int y)
{
    unitWidth = 2.0/gridSize;
    x+=1;
    y+=1;
    enmLoc.x =  -1-unitWidth/2+(unitWidth)*x;
    enmLoc.y =  -1-unitWidth/2+(unitWidth)*y;
}

void Enemies::moveEnemy(string dir)
{
  if(moveDis<=0){
   cout << "moveDis " << dir <<endl;
   if(dir=="up"){up=true; down=left=right=false;}
   else if(dir=="down"){down=true; up=left=right=false;}
   else if(dir=="left"){left=true; down=up=right=false;}
   else if(dir=="right"){right=true; down=left=up=false;}
   else{up=left=right=false;}
    }
}

void Enemies::animate()
{
   // cout << "Enemy1: " << enmLoc.x <<"  "<<enmLoc.y << up<<endl;

if(moveDis < unitWidth)
{
   // cout << "Enemy2: " << enmLoc.x <<"  "<<enmLoc.y << up<< endl;

if(T1->GetTicks()<1000)
{
    //cout << "Enemy3: " << enmLoc.x <<"  "<<enmLoc.y << up <<endl;


if(up)
   {
       //cout << "Enemy4>>>>>>: " << enmLoc.x <<"  "<<enmLoc.y << up<< endl;
      // if((enmLoc.y< 1-unitWidth/2)&&  !collision && (enmLoc.y < -0.15 || enmLoc.y > 0.2) || (enmLoc.x < -0.8))
        if(enmLoc.y< 1-unitWidth/2 &&  !collision)
        {
            enmLoc.y += t;
         }   moveDis +=t;

        xmin +=1/(float)frames;
        xmax +=1/(float)frames;
        ymin =0.0;
        ymax =0.25;
        if(xmax>1){
                xmax =1/(float)frames;
                xmin =0;
            }
    }

  else if(down)
   {
         //cout << "Enemy: " << enmLoc.x <<"  "<<enmLoc.y << endl;
         if((enmLoc.y > -1+unitWidth/2) &&!collision && (enmLoc.y > 0.3 || enmLoc.y < 0.1) || (enmLoc.x < -0.8))
         // if(enmLoc.y< 1-unitWidth/2 &&  !collision)
           {
              enmLoc.y -= t;
           }  moveDis +=t;

            xmin +=1/(float)frames;
            xmax +=1/(float)frames;
            ymin =0.25;
            ymax =0.5;

            if(xmax>1){
                xmax =1/(float)frames;
                xmin =0;
            }
            //cout << "Enemy: " << enmLoc.x <<"  "<<enmLoc.y << endl;

   }
   else if(left)
   {
       if(enmLoc.x>-1+unitWidth/2 && !collision)
        {
            enmLoc.x -= t;
         }   moveDis +=t;

        xmin +=1/(float)frames;
        xmax +=1/(float)frames;
        ymin =0.75;
        ymax =1.0;

        if(xmax>1){
                xmax =1/(float)frames;
                xmin =0;
            }
   }

   else if(right)
   {
       if(enmLoc.x<1-unitWidth/2 && !collision)
          {
              enmLoc.x += t;
           }   moveDis +=t;

            xmin +=1/(float)frames;
            xmax +=1/(float)frames;
            ymin =0.5;
            ymax =0.75;

            if(xmax>1){
                xmax =1/(float)frames;
                xmin =0;
              }
     }

  }else T1->Reset();
}
 else {moveDis =0;down=up=left=right=false; }
}


GridLoc Enemies::getEnemyLoc()
{
   GridLoc val;
   val.x = (int)(ceil((enmLoc.x +(1-unitWidth))/unitWidth));
   val.y = (int)(ceil((enmLoc.y +(1-unitWidth))/unitWidth));
   //cout << "Enemy loc x:" << val.x << " y:" << val.y<<endl;
    return val;
}

bool Enemies::checkCollision(string enmDir,wall *W)
{
    collision = true;

    for(int i =0; i< 10; i++){

        if(enmDir.compare("up")==0)
        {
            if((enmLoc.y - (W[i].wallBrk.y - unitWidth/2 )< unitWidth/2)&&
               (-enmLoc.y+ (W[i].wallBrk.y - unitWidth/2 )< unitWidth/2))
            {
                if((W[i].wallBrk.x + 3*unitWidth/4 > enmLoc.x)&&
                   (W[i].wallBrk.x - 3*unitWidth/4 < enmLoc.x))
                {
                    return true;
                }
            }

        }

        if(enmDir.compare("down")==0)
        {
            if((enmLoc.y - (W[i].wallBrk.y + unitWidth/2 )< unitWidth/2)&&
               (-enmLoc.y+ (W[i].wallBrk.y + unitWidth/2 )< unitWidth/2))
            {
                if((W[i].wallBrk.x + 3*unitWidth/4 > enmLoc.x)&&
                   ( W[i].wallBrk.x - 3*unitWidth/4 < enmLoc.x))
                {
                    return true;
                }
            }
        }

        if(enmDir.compare("left")==0)
        {
            if((enmLoc.x - (W[i].wallBrk.x + unitWidth/2 )< unitWidth/2)&&
               (-enmLoc.x+ (W[i].wallBrk.x + unitWidth/2 )< unitWidth/2))
            {
                if((W[i].wallBrk.y + 3*unitWidth/4 > enmLoc.y )&&
                   ( W[i].wallBrk.y - 3*unitWidth/4 < enmLoc.y))
                {
                    return true;
                }
            }
        }

        if(enmDir.compare("right")==0)
        {
            if((enmLoc.x - (W[i].wallBrk.x - unitWidth/2) < unitWidth/2)&&
               (-enmLoc.x+ (W[i].wallBrk.x - unitWidth/2 )< unitWidth/2))
            {
                if((W[i].wallBrk.y + 3*unitWidth/4 > enmLoc.y)&&
                   ( W[i].wallBrk.y - 3*unitWidth/4 < enmLoc.y))

                {
                    return true;
                }
            }
        }
    }
    collision = false;
    return false;
    }

