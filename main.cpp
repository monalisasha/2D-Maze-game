/*
 * MAZE Game Framework
 * By Monalisa Sha (Spring 2019)
 */

#include <string.h>
#include <CommonThings.h>
#include <Maze.h>
#include <iostream>
#include <Timer.h>
#include <player.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <Enemies.h>

#include <wall.h>
#include <bush.h>
#include <math.h>
#define numberofwalls 11

/* GLUT callback Handlers */

using namespace std;

Maze *M = new Maze(10);                         // Set Maze grid size
Player *P = new Player();                       // create player

wall W[100];                                    // wall with number of bricks
bush B[5];                                      //bush with number of bushes
Enemies E[10];
//static bool E_alive[10] = {true};                                 // create number of enemies
Timer *T0 = new Timer();                        // animation timer

float wWidth, wHeight;                          // display window width and Height
float xPos,yPos;
static bool lose = false;
static bool win = false;
static bool start = false;
int FPS = 60.00;
int time_now,time_prev;                         //time
int time_now1,time_prev1;                         //time


int matrix[10][10];
int result = 0;
void display(void);                             // Main Display : this runs in a loop

void resize(int width, int height)              // resizing case on the window
{
    wWidth = width;
    wHeight = height;

    if(width<=height)
        glViewport(0,(GLsizei) (height-width)/2,(GLsizei) width,(GLsizei) width);
    else
        glViewport((GLsizei) (width-height)/2 ,0 ,(GLsizei) height,(GLsizei) height);
}



void init(void)
{
    glEnable(GL_COLOR_MATERIAL);

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearColor(0.0,0.0,0.0,0.0);
    gluOrtho2D(0, wWidth, 0, wHeight);

    T0->Start();                                        // set timer to 0

    glEnable(GL_BLEND);                                 //display images with transparent
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    M->loadBackgroundImage("images/bak.jpg");
    M->loadLoseImage("images/bak_Lose.jpg");           // Load maze background image
    M->loadWinImage("images/bak_Win.jpg");           // Load maze background image
    M->loadChestImage("images/chest.png");              // load chest image

    /*-------------------------CALLING FUNCTION TO LOAD TOUCH IMAGES---------------------*/

    M->loadUpImage("images/Up.png");                    //Load Up arrow image
    M->loadDownImage("images/Down.png");                //Load Down arrow image
    M->loadLeftImage("images/Left.png");                //Load Left arrow image
    M->loadRightImage("images/Right.png");              //Load Right arrow image

    /*------------------------------------DONE LOADING-----------------------------------*/


    M->placeChest(5,2);                                 // place chest in a grid


    /*--------------------------PLACING THE TOUCH ARROWS ON THE MAZE-------------------------*/

    M->placeUp(8,2);                                    /*------PLACE UP ARROW------*/
    M->placeDown(8,0);                                  /*------PLACE DOWN ARROW------*/
    M->placeLeft(9,1);                                  /*-------PLACE LEFT ARROW-------*/
    M->placeRight(7,1);                                 /*-------PLACE RIGHT ARROW-------*/
    /*---------------------------PLACE ARROWS DONE----------------------------------------------*/


    M->loadSetOfArrowsImage("images/arrwset.png");      // load set of arrows image
    M->placeStArrws(7,7);                               // place set of arrows

    P->initPlayer(M->getGridSize(),6,"images/p.png");   // initialize player pass grid size,image and number of frames
    P->loadArrowImage("images/arr.png");                // Load arrow image
    P->placePlayer(9,9);                                // Place player



/*PLACING WALLS*/
 /*   int i = 1;
    while(i<M->getGridSize()-2){       //decreasing the number of walls
      W[i].wallInit(M->getGridSize(),"images/wall.png");// Load walls
      W[i].placeWall(i,4);      //place each wall
      i = i + 2;    //leaving space between two walls
    }*/



    for(int i=1; i< 11;i++)
    {
      W[i].wallInit(M->getGridSize(),"images/wall.png");// Load walls
      W[i].placeWall(i,5);                              // place each brick
    }                           //function which places the wall in a single line without any space


    /*----------------------PLACING WALLS AT SPECIFIC POSITION --------------------------------------*/

    W[9].wallInit(M->getGridSize(),"images/wall.png");
    W[9].placeWall(0,9);
    W[10].wallInit(M->getGridSize(),"images/wall.png");
    W[10].placeWall(0,0);
    /*----------------------PLACING WALLS DONE--------------------------------------*/


/*--------------------------PLACING BUSH AT SPECIFIC POSITION------------------------------*/

      B[1].bushInit(M->getGridSize(),"images/bush.png");
      B[1].placebush(2,3);                              // place each bush

/*---------------------------PLACING BUSH DONE-----------------------------------*/


    for(int i=0; i<6;i++)
    {
        E[i].initEnm(M->getGridSize(),4,"images/e.png"); //Load enemy image

    }
    /*---------------------PLACING ENEMIES AT SPECIFIC POSITION---------------------*/
     E[0].placeEnemy(2,2);
      E[1].placeEnemy(2,6);
       E[2].placeEnemy(6,3);
        E[3].placeEnemy(9,2);
         E[4].placeEnemy(7,9);
          E[5].placeEnemy(1,9);
    /*----------------------PLACING ENEMIES DONE --------------------------------*/

    P->numberofwallsN = 11;      //NUMBER OF WALLS TO USE IN COLLISION
    E->numberofwallsN = 11;      //NUMBER OF WALLS TO USE IN COLLISION
}

void display(void)
{
    /*-----------------------------------IF THE GAME IS STILL ON------------------------------------*/
        if (!lose) {                            //IF WE HAVEN'T LOST YET
                if (!win) {                        //IF WE HAVEN'T WIN YET
                    time_now = glutGet(GLUT_ELAPSED_TIME);  //get the current time
                    time_now1 = glutGet(GLUT_ELAPSED_TIME);  //get the current time
                if ((time_now1 - time_prev1)> 100000/FPS) {    //THE SPEED OF THE ENEMY
                            for(int i=0; i<10 ;i++) {
                                        if (E[i].live && start) {      //IF THE ENEMY IS ALIVE AND THE PLAYER HAS MOVED ONCE
                                    if (sqrt(pow(P->getPlayerLoc().x - E[i].getEnemyLoc().x, 2) +
                                                pow(P->getPlayerLoc().y - E[i].getEnemyLoc().y, 2) * 1.0) <=6) //WHEN THE DISTANCE IS LESS THAN 5
                                                {
                                                if ((P->getPlayerLoc().y == E[i].getEnemyLoc().y) && (P->getPlayerLoc().x == E[i].getEnemyLoc().x))
                                                        lose = true;    //IF THE ENEMY REACHED THE PLAYER CALL 'lose' FUNCTION TO DISPLAYER LOSE SCREEN

                                    // check if enemy entering bush
                                    cout << "Enemy x:" << E[i].getEnemyLoc().x << "  y:" << E[i].getEnemyLoc().y << endl;
                                                if(P->getPlayerLoc().y > E[i].getEnemyLoc().y) {   //WHEN THE PLAYER HAS GREATER y COORDINATE
                                                        bool bush = false;                          //INTIALIZE BUSH TO BE FALSE
                                                        for (int j=0; j< M->getGridSize()-1;j=j+2)
                                                        if (((j + 1 - (int)E[i].getEnemyLoc().y) == 1) && (j == E[i].getEnemyLoc().x)) //TO CHECK IT ENEMY IS AT BUSH
                                                            bush = true;                    //IF THE ENEMY IS AT BUSH WE MAKE BUSH TRUE
                                                        if (!bush) E[i].moveEnemy("up");    //IF THE ENEMY IS NOT AT BUSH INCREASE THE y COORDINATE(MOVE UP)
                                                }
                                                if(P->getPlayerLoc().y < E[i].getEnemyLoc().y) {  //WHEN THE PLAYER HAS SMALLER y COORDINATE
                                                        bool bush = false;                        //INTIALIZE BUSH TO BE FALSE
                                                        for (int j=0; j< M->getGridSize()-1;j=j+2)
                                                        if ((((int)E[i].getEnemyLoc().y -j -1) == 1) && (j == E[i].getEnemyLoc().x))  //TO CHECK IT ENEMY IS AT BUSH
                                                            bush = true;                            //IF THE ENEMY IS AT BUSH WE MAKE BUSH TRUE
                                                        if(!bush) E[i].moveEnemy("down");           //IF THE ENEMY IS NOT AT BUSH DECREASE THE y COORDINATE(MOVE DOWN)
                                                }
                                                if(P->getPlayerLoc().y == E[i].getEnemyLoc().y) {
                                                    if(P->getPlayerLoc().x > E[i].getEnemyLoc().x){  //WHEN THE PLAYER HAS GREATER x COORDINATE
                                                        bool bush = false;                              //INTIALIZE BUSH TO BE FALSE
                                                        for (int j=0; j< M->getGridSize()-1;j=j+2)
                                                        if (((j - (int)E[i].getEnemyLoc().x) == 1) && ((j+1) == E[i].getEnemyLoc().y))  //TO CHECK IT ENEMY IS AT BUSH
                                                            bush = true;
                                                        if(!bush)   E[i].moveEnemy("right");        //IF THE ENEMY IS NOT AT BUSH INCREASE THE x COORDINATE(MOVE RIGHT)
                                                    }
                                                    else {
                                                        bool bush = false;                              //INTIALIZE BUSH TO BE FALSE
                                                        for (int j=0; j< M->getGridSize()-1;j=j+2)
                                                        if ((((int)E[i].getEnemyLoc().x - j) == 1) && ((j+1) == E[i].getEnemyLoc().y))  //TO CHECK IT ENEMY IS AT BUSH
                                                            bush = true;
                                                        if (!bush) E[i].moveEnemy("left");         //IF THE ENEMY IS NOT AT BUSH DECREASE THE x COORDINATE(MOVE UP)
                                                    }
                                                }
                                    }
                            }
                                }
                                time_prev1 = time_now1;
                        }
            if ((time_now - time_prev)> 1000/FPS) {     //THE SPEED OF THE PLAYER

                            glClear (GL_COLOR_BUFFER_BIT);        // clear display screen

                    glPushMatrix();
                    M->drawBackground();
                    glPopMatrix();


                    for(int i=0; i<11;i++) {
                        W[i].drawWall();
                    }

                    glPushMatrix();
                M->drawGrid();
                    glPopMatrix();

                    glPushMatrix();
                P->drawplayer();
                    glPopMatrix();

        for(int i=0; i<M->getGridSize();i++)
        {
           B[i].drawbush();    //DRAWING THE BUSH IN THE MAZE
        }
                    for(int i=0; i<10 ;i++) {
                                    if(E[i].live){
        //                                  cout << "draw enemey>>>>>>>  " << i<< endl;
                                E[i].drawEnemy();
                                    }
                            }
                    //for(int i=0; i<10 ;i++) {
                                    //if((P->getArrowLoc().y == abs(9 - (int)E[i].getEnemyLoc().y)) && (P->getArrowLoc().x == E[i].getEnemyLoc().x)) {
                                    //      cout << "arrow hit >>>>>>>  " << i<< endl;
                                    //      E[i].live=false;
                                    //      glDeleteTextures(1, &(E[i].enmTex));//Even if deleting tex not working
                                   //}
                    //}

                    glPushMatrix();
                P->drawArrow();
                    glPopMatrix();

                    glPushMatrix();
                M->drawChest();
                    glPopMatrix();

    /*-------------------------------------DRAWING ARROWS ON THE MAZE--------------------------*/

                    glPushMatrix();
                M->drawUp();
                    glPopMatrix();

                    glPushMatrix();
                M->drawDown();
                    glPopMatrix();

                    glPushMatrix();
                M->drawLeft();
                    glPopMatrix();

                    glPushMatrix();
                M->drawRight();
                    glPopMatrix();

    /*--------------------------------DRAWING ARROWS DONE-------------------------------------*/

                    glPushMatrix();
                M->drawArrows();
                    glPopMatrix();

                        glutSwapBuffers();
                        time_prev = time_now;
                }//End  if timer
                } else {

    /*----------------------------------------DRAWING WIN IF THE PLAYER REACHES CHEST---------------------*/
                        glClear (GL_COLOR_BUFFER_BIT);        // clear display screen
                        glPushMatrix();
                        M->drawWin();
                        glPopMatrix();
                        glutSwapBuffers();
                    }

    /*----------------------------------------------DRAWING WIN DONE------------------------------*/

        } else {

    /*---------------------------------------DRAWING LOSE IF THE ENEMY REACHES PLAYER---------------------*/

            glClear (GL_COLOR_BUFFER_BIT);        // clear display screen
            glPushMatrix();
            M->drawLose();
            glPopMatrix();
            glutSwapBuffers();
            }
    /*----------------------------------------------DRAWING LOSE DONE------------------------------------*/

}

void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case ' ':

    /*--------------------------------------GETTING POWER TO SHOOT FIRE----------------------------------*/

          if((P->getPlayerLoc().x == M->GetStArrwsLoc().x) && (P->getPlayerLoc().y == M->GetStArrwsLoc().y))
            //
                M->liveSetOfArrws =false;      //PICKING UP THE POWER TO SHOOT BY PRESSING SPACE BAR
           if(!M->liveSetOfArrws)      // if set of arrows were picked by player
             P->shootArrow();       //PLAYER CAN SHOOT FIRE

     /*-------------------------------------GETTING POWER DONE-----------------------------------------*/

        break;
        case 27 :                       // esc key to exit
        case 'q':
            exit(0);
            break;
    }

    glutPostRedisplay();
}

      /*--------------------------CHANGING GetOGLPos TO MAKE THE PLAYER MOVE WITH TOUCH-----------------------------*/

 loc GetOGLPos(int x,int y)    //RETURNING THE LOCATION INSTEAD OF VOID
{
    GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];
    GLfloat winX, winY, winZ;
    GLdouble posX, posY, posZ;

    glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
    glGetDoublev( GL_PROJECTION_MATRIX, projection );
    glGetIntegerv( GL_VIEWPORT, viewport );

    winX = (float)x;
    winY = (float)viewport[3] - (float)y;
    glReadPixels( x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );

    gluUnProject( winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);
    loc toglpos;                                    //INTIALIZING THE NEW loc TO STORE THE xPos AND yPos
    xPos =posX ;
    yPos =posY ;
    toglpos.x=xPos;                                 //STORING xPos TO x VALUE OF toglpos
    toglpos.y=yPos;                                 //STORING yPos TO y VALUE OF toglpos
    return toglpos;
    cout<< toglpos.x <<"    "<<toglpos.y <<endl;
}
    /*---------------------------------CHANGING GetOGLPos DONE--------------------------------------*/


 void idle(void)
{
    /*---------------------------------KILLING THE ENEMY BY SHOOTING THE FIRE-------------------------*/

    for (int i=0;i<6;i++)
    {
        if(P->getArrowLoc().x == E[i].getEnemyLoc().x && P->getArrowLoc().y == E[i].getEnemyLoc().y){
            E[i].live = false;
        }
    }

    /*------------------------------------KILLING ENEMY DONE-------------------------------------------*/


    glutPostRedisplay();
}

void mouse(int btn, int state, int x, int y){

    switch(btn){
        case GLUT_LEFT_BUTTON:

        if(state==GLUT_DOWN){
             loc tog=GetOGLPos(x,y);
             cout<<tog.x<<" loc "<<tog.y<<endl;
    cout<<M->GetLeftLoc().x<<" "<<M->GetLeftLoc().y<<endl;

    /*------------------------------MAKING THE PLAYER MOVE WHEN WE PRESS TOUCH BUTTONS---------------------------*/

    if((0.3 < tog.x && tog.x< 0.7) && (-0.8< tog.y && tog.y < -0.4))      //IF THE PLAYER IS IN LEFT BUTTON GRID
    {
        P->movePlayer("left");     //PLAYER MOVES LEFT
    }
    else if ((0.8 < tog.x && tog.x< 1) && (-0.8< tog.y && tog.y < -0.6))  //IF THE PLAYER IS IN RIGHT BUTTON GRID
    {
        P->movePlayer("right");     //PLAYER MOVES RIGHT
    }
    else if ((0.6 < tog.x && tog.x< 0.8) && (-0.6< tog.y && tog.y < -0.4))  //IF THE PLAYER IS IN UP BUTTON GRID
    {
        P->movePlayer("up");        //PLAYER MOVES UP
    }
    else if((0.5 < tog.x && tog.x< 0.8) && (-0.9<= tog.y && tog.y <= -0.8))  //IF THE PLAYER IS IN DOWN BUTTON GRID
    {
        P->movePlayer("down");       //PLAYER MOVES DOWN
    }
    //ENEMIES CAN BE MOVED THE SAME WAY

    /*----------------------------------PLAYER MOVING WITH TOUCH BUTTONS------------------------------------------*/

    break;

      /*case GLUT_RIGHT_BUTTON:

        if(state==GLUT_DOWN){

              GetOGLPos(x,y);
            }
            break;*/
    }
     glutPostRedisplay();
    }
};

void Specialkeys(int key, int x, int y)
{

    // Your Code here
    switch(key)
    {
    case GLUT_KEY_UP:
//         cout<< P->getPlayerLoc().x<< "    "<<P->getPlayerLoc().y<<endl;

         if (!start)
            start = true;
         if ((P->getPlayerLoc().y == 2) && (P->getPlayerLoc().x == 5))
            //IF THE PLAYER REACHES THE HEART LOCATION
            win = true; //MAKE WIN TRUE TO DISPLAY WIN IMAGE

    /*-------------------MOVING THE PLAYERS & ENEMIES AND CHECKING COLLISION---------------------------*/
            P->movePlayer("up");
            P->checkCollision(W);
         E[0].moveEnemy("up");
          E[0].checkCollision("up",W);
         E[1].moveEnemy("up");
           E[1].checkCollision("up",W);
         E[2].moveEnemy("up");
          E[2].checkCollision("up",W);
         E[3].moveEnemy("up");
        E[3].checkCollision("up",W);
        E[4].moveEnemy("up");
        E[4].checkCollision("up",W);
        E[5].moveEnemy("up");
        E[5].checkCollision("up",W);
        E[6].moveEnemy("up");
        E[6].checkCollision("up",W);

    break;

    case GLUT_KEY_DOWN:
  //       cout<< P->getPlayerLoc().x<< "    "<<P->getPlayerLoc().y<<endl;
         if (!start)
            start = true;
         if ((P->getPlayerLoc().y == 2) && (P->getPlayerLoc().x == 5))
            win = true;
            P->movePlayer("down");
            P->checkCollision(W);
         E[0].moveEnemy("down");
          E[0].checkCollision("down",W);
         E[1].moveEnemy("down");
          E[1].checkCollision("down",W);
         E[2].moveEnemy("down");
          E[2].checkCollision("down",W);
         E[3].moveEnemy("down");
         E[3].checkCollision("down",W);
         E[4].moveEnemy("down");
        E[4].checkCollision("down",W);
        E[5].moveEnemy("down");
        E[5].checkCollision("down",W);
        E[6].moveEnemy("down");
        E[6].checkCollision("down",W);

    break;


    case GLUT_KEY_LEFT:
      //   cout<< P->getPlayerLoc().x<< "    "<<P->getPlayerLoc().y<<endl;
         if (!start)
            start = true;
         if ((P->getPlayerLoc().y == 2) && (P->getPlayerLoc().x == 5))
            win = true;
            P->movePlayer("left");
             P->checkCollision(W);
         E[0].moveEnemy("left");
         E[0].checkCollision("left",W);
         E[1].moveEnemy("left");
        E[1].checkCollision("left",W);
         E[2].moveEnemy("left");
         E[2].checkCollision("left",W);
         E[3].moveEnemy("left");
        E[3].checkCollision("left",W);
        E[4].moveEnemy("left");
        E[4].checkCollision("left",W);
        E[5].moveEnemy("left");
        E[5].checkCollision("left",W);
        E[6].moveEnemy("left");
        E[6].checkCollision("left",W);
   break;

    case GLUT_KEY_RIGHT:
        // cout<< P->getPlayerLoc().x<< "    "<<P->getPlayerLoc().y<<endl;
         if (!start)
            start = true;
         if ((P->getPlayerLoc().y == 2) && (P->getPlayerLoc().x == 5))
            win = true;
                 P->movePlayer("right");

         P->checkCollision(W);
         E[0].moveEnemy("right");
         E[0].checkCollision("right",W);
         E[1].moveEnemy("right");
         E[1].checkCollision("right",W);
         E[2].moveEnemy("right");
        E[2].checkCollision("right",W);
         E[3].moveEnemy("right");
         E[3].checkCollision("right",W);
         E[4].moveEnemy("right");
        E[4].checkCollision("right",W);
        E[5].moveEnemy("right");
        E[5].checkCollision("right",W);
        E[6].moveEnemy("right");
        E[6].checkCollision("right",W);
    break;

    /* ------------------------------------MOVING AND CHECKING COLLISION DONE----------------------------------*/


   }
  glutPostRedisplay();
}


/* Program entry point */

int main(int argc, char *argv[])
{
   glutInit(&argc, argv);

   glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
   glutInitWindowSize (800, 800);                //window screen
   glutInitWindowPosition (100, 100);            //window position
   glutCreateWindow ("Maze");                    //program title
   init();

   glutDisplayFunc(display);                     //callback function for display
   glutReshapeFunc(resize);                      //callback for reshape
   glutKeyboardFunc(key);                        //callback function for keyboard
   glutSpecialFunc(Specialkeys);
   glutMouseFunc(mouse);
   glutIdleFunc(idle);
   glutMainLoop();

   return EXIT_SUCCESS;
}


