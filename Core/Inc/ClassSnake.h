#ifndef _ClassSnake_H_
#define _ClassSnake_H_

#include <stdlib.h>

typedef enum
{
    dUp = -1,
    dDown = 1,
    dLeft = -2,
    dRight = 2
} Direction;

typedef enum
{
    pEmpty = 0,
    pBody  = 1,
    pFood  = 2
} PointState;

typedef struct
{
    int state;
    int screenHeight;
    int screenLength;

    int **snakeBody;
    int bodyLength;

    Direction sHeadDirect;
    PointState **screen;
} Snake;

int  Snake_SetUp(Snake *s, int height, int length);

void Snake_SetDir(Snake *s, Direction dir);

int  Snake_SetFood(Snake *s);
int  Snake_Move(Snake *s);

PointState Snake_Detect(Snake *s, Direction dir);
void Snake_Restart(Snake *s);

#endif
