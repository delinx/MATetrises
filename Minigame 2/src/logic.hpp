#ifndef LOGIC_HPP
#define LOGIC_HPP
#include "log.hpp"
#include "raylib.h"
#include "types.hpp"
#include <iostream>

class LOGIC
{
      public:
    /// 2D array ofi32s with X/Y getters and setters
    struct Grid
    {
        u32 WIDTH;
        u32 HEIGHT;
        i32 *grid;

        /// make a newi32 array of X*Y size
        Grid(u32 width, u32 height);
        ~Grid();

        /// set XY to giveni32
        void set(u32 x, u32 y, i32 value);

        /// get XY value
        i32 get(u32 x, u32 y);

        /// override array with value
        void fill(i32 num);

        /// replace old value with new value
        void mask(i32 oldInt, i32 newInt);

        /// prints grids' values as rows and columns
        void print();

        /// rotates grid
        void rotate(bool clockwise);

        /// fill grid with checkered pattren of two valuer
        void checkFill(i32 v1, i32 v2);

        /// add bonus symbol
        void addSymbol(i32 id);

        /// ruturns pointer to a copy of itself
        Grid *copy();
    };

    struct Field
    {
        bool Debug = false;
        Grid *grid = NULL;
        Grid *shape = NULL;
        i32 xShape = 0;
        i32 yShape = 0;
        i32 score = 0;
        i32 realScore = 0;
        Field(u32 width, u32 height);
        ~Field();
        Sound specialSound;

        Grid *Shapes[7];

        /// check if shape can fit in the XY position of grid
        bool canFitShape(i32 x, i32 y, Grid *_shape);
        /// same as canFitShape but passes default shape
        bool canFit(i32 x, i32 y);
        /// resets positiong of shape to centered out of screen beginner pos
        void shapeResetPos();
        /// attemps to move shape with gravity on grid
        void gravityTick();
        /// debug print grid + shape
        void printWithShape(i32 x, i32 y);
        /// get random shape
        LOGIC::Grid *getRandomShape();
        /// find solved rows
        bool findSolvedRows();


        /// burn shape into grid
        void burnShapeIntoGrid();

        // i32 findSolvedRow();
    };
};

#endif  // LOGIC_HPP
