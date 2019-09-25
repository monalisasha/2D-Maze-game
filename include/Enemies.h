/*
 * MAZE Game Framework
 * By Monalisa Sha (Spring 2019)
 */
#ifndef ENEMIES_H
#define ENEMIES_H

#include<CommonThings.h>
#include <Maze.h>
#include <time.h>
#include <thread>
#include <string>
#include <math.h>       /* ceil */
#include<wall.h>

class Enemies
{
    public:
        Enemies();                          // constructor
        virtual ~Enemies();                 // DeConstructor
        void initEnm(int, int, char *);     // Initialize Enemy

        void placeEnemy(int,int);           // place enemy
        void drawEnemy();                   // Draw Enemy with Animation
        void moveEnemy(string);             // move Enemy left,right,up,down
        void animate();                     // Animate sprite
        GridLoc getEnemyLoc();              // Return Enemy current grid location
        int numberofwallsN;

        GLuint enmTex;                     // Image Texture


        int gridSize;                       // Grid size of the maze
        float unitWidth;                    // Unit width of the grid
        int stepsPerMove;                   // Step count for animation
        bool live;                          // Status of the Enemy
        bool checkCollision(string,wall *);
        bool collision;
    protected:

    private:
         int frames;                        // number of frames generally
         float t;                           // steps for animation count
         float xmax, xmin,ymax,ymin;        // Animated Texture mapping
         bool up,down,left,right;           // move direction
         float moveDis=0;                   // Moving distance for animation
         loc enmLoc;                        // Location of the enemy

};

#endif // ENEMIES_H
