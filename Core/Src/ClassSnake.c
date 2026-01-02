#include <ClassSnake.h>

/* Initialise snake data structures and allocate dynamic memory.
 * - Allocates: screen[height][length] and snakeBody[height*length][2]
 * - Returns 1 on success, 0 on failure.
 * Note: This function performs multiple malloc calls. If a later allocation fails,
 *       earlier allocations are not freed here (caller should ensure this is only
 *       called once, or add a dedicated cleanup routine if needed).
 */
int Snake_SetUp(Snake *s, int height, int length)
{
    if(!s) return 0;

    s->state = 0;                 /* 0 typically indicates game-over/uninitialised state */
    s->screenHeight = height;     /* grid height */
    s->screenLength = length;     /* grid width  */
    s->bodyLength = 0;            /* current body length */
    s->sHeadDirect = dRight;      /* default start direction */

    /* Allocate 2D screen buffer (grid) storing PointState for each cell */
    s->screen = (PointState**)malloc((size_t)height * sizeof(PointState*));
    if(!s->screen) return 0;

    for(int h = 0; h < height; h++)
    {
        s->screen[h] = (PointState*)malloc((size_t)length * sizeof(PointState));
        if(!s->screen[h]) return 0;
        for(int l = 0; l < length; l++)
        {
            s->screen[h][l] = pEmpty; /* initialise all cells to empty */
        }
    }

    /* Allocate snake body buffer.
     * Each element is a pair {row, col}; capacity = height*length (max possible).
     */
    int cap = height * length;
    s->snakeBody = (int**)malloc((size_t)cap * sizeof(int*));
    if(!s->snakeBody) return 0;

    for(int i = 0; i < cap; i++)
    {
        s->snakeBody[i] = (int*)malloc(2u * sizeof(int));
        if(!s->snakeBody[i]) return 0;
        s->snakeBody[i][0] = -1;  /* -1 means unused slot */
        s->snakeBody[i][1] = -1;
    }

    /* Place initial head in the centre of the grid */
    s->snakeBody[0][0] = height / 2;
    s->snakeBody[0][1] = length / 2;
    s->screen[s->snakeBody[0][0]][s->snakeBody[0][1]] = pBody;

    s->bodyLength = 0;
    return 1;
}

/* Set movement direction with "no immediate reverse" constraint.
 * Prevents direction change to the exact opposite (e.g., left -> right).
 */
void Snake_SetDir(Snake *s, Direction dir)
{
    if(!s) return;
    if((int)dir != -((int)s->sHeadDirect))
    {
        s->sHeadDirect = dir;
    }
}

/* Place food on a random empty cell.
 * - Builds a list of all empty cells, then randomly selects one.
 * - Returns 1 on success, 0 if no empty cell or allocation failure.
 * Note: Uses malloc/free per call; acceptable for coursework but could be optimised
 *       by using a static buffer or a different placement strategy.
 */
int Snake_SetFood(Snake *s)
{
    if(!s) return 0;

    int total = s->screenHeight * s->screenLength;
    int *emptyPointX = (int*)malloc((size_t)total * sizeof(int));
    int *emptyPointY = (int*)malloc((size_t)total * sizeof(int));

    if(!emptyPointX || !emptyPointY)
    {
        free(emptyPointX);
        free(emptyPointY);
        return 0;
    }

    /* Scan the grid to collect all empty positions */
    int numEmpty = 0;
    for(int h = 0; h < s->screenHeight; h++)
    {
        for(int l = 0; l < s->screenLength; l++)
        {
            if(s->screen[h][l] == pEmpty)
            {
                emptyPointX[numEmpty] = h;
                emptyPointY[numEmpty] = l;
                numEmpty++;
            }
        }
    }

    /* If the grid is full, no place to spawn food */
    if(numEmpty == 0)
    {
        free(emptyPointX);
        free(emptyPointY);
        return 0;
    }

    /* Randomly choose one empty location */
    int orderEmpty = rand() % numEmpty;
    s->screen[emptyPointX[orderEmpty]][emptyPointY[orderEmpty]] = pFood;

    free(emptyPointX);
    free(emptyPointY);
    return 1;
}

/* Detect what is in the next cell in the given direction.
 * Returns: pEmpty / pFood / pBody.
 * Boundary is treated as collision (pBody) to simplify logic.
 */
PointState Snake_Detect(Snake *s, Direction dir)
{
    int headRow = s->snakeBody[0][0];
    int headCol = s->snakeBody[0][1];

    switch(dir)
    {
        case dUp:    headRow--; break;
        case dDown:  headRow++; break;
        case dLeft:  headCol--; break;
        case dRight: headCol++; break;
        default: break;
    }

    /* Out-of-bounds -> collision */
    if(headRow < 0 || headCol < 0 ||
       headRow >= s->screenHeight || headCol >= s->screenLength)
    {
        return pBody;
    }

    return s->screen[headRow][headCol];
}

/* Advance the snake by one step according to current direction.
 * Return value indicates the move result:
 * - 1: moved into empty cell
 * - 2: ate food (snake grows and new food is generated)
 * - 0: collision (game over)
 *
 * Side effects:
 * - Updates snakeBody positions
 * - Updates screen grid (pEmpty / pBody / pFood)
 * - Updates s->state (0/1/2)
 *
 * Concurrency note:
 * If screen buffer is shared with a display task, caller should protect access
 * with a mutex around calls to Snake_Move / Snake_Restart.
 */
int Snake_Move(Snake *s)
{
    if(!s) return 0;

    Direction dir = s->sHeadDirect;
    int headRow = s->snakeBody[0][0];
    int headCol = s->snakeBody[0][1];

    /* Compute the next head position */
    switch(dir)
    {
        case dUp:    headRow--; break;
        case dDown:  headRow++; break;
        case dLeft:  headCol--; break;
        case dRight: headCol++; break;
        default: break;
    }

    switch(Snake_Detect(s, dir))
    {
        case pEmpty:
            /* Shift body positions forward (tail moves) */
            for(int i = s->bodyLength; i >= 0; i--)
            {
                s->snakeBody[i + 1][0] = s->snakeBody[i][0];
                s->snakeBody[i + 1][1] = s->snakeBody[i][1];
            }

            /* Clear the last tail cell on screen */
            s->screen[s->snakeBody[s->bodyLength + 1][0]]
                     [s->snakeBody[s->bodyLength + 1][1]] = pEmpty;

            /* Mark the freed slot */
            s->snakeBody[s->bodyLength + 1][0] = -1;
            s->snakeBody[s->bodyLength + 1][1] = -1;

            /* Write new head */
            s->snakeBody[0][0] = headRow;
            s->snakeBody[0][1] = headCol;
            s->screen[headRow][headCol] = pBody;

            s->state = 1;
            return 1;

        case pBody:
            /* Collision: game over */
            s->state = 0;
            return 0;

        case pFood:
            /* Grow: shift body but do NOT clear tail */
            for(int i = s->bodyLength; i >= 0; i--)
            {
                s->snakeBody[i + 1][0] = s->snakeBody[i][0];
                s->snakeBody[i + 1][1] = s->snakeBody[i][1];
            }

            s->bodyLength++;

            /* Write new head */
            s->snakeBody[0][0] = headRow;
            s->snakeBody[0][1] = headCol;
            s->screen[headRow][headCol] = pBody;

            s->state = 2;

            /* Spawn next food after eating */
            Snake_SetFood(s);
            return 2;
    }

    /* Fallback: treat as game over */
    s->state = 0;
    return 0;
}

/* Reset game state without reallocating buffers.
 * - Clears screen to empty
 * - Resets snake to centre
 * - Resets length and direction
 * - Spawns initial food
 */
void Snake_Restart(Snake *s)
{
    if(!s) return;

    s->state = 1;
    s->sHeadDirect = dRight;

    /* Clear entire screen buffer */
    for(int h = 0; h < s->screenHeight; h++)
    {
        for(int l = 0; l < s->screenLength; l++)
        {
            s->screen[h][l] = pEmpty;
        }
    }

    /* Clear body buffer */
    for(int i = 0; i < s->screenHeight * s->screenLength; i++)
    {
        s->snakeBody[i][0] = -1;
        s->snakeBody[i][1] = -1;
    }

    /* Reset head position */
    s->snakeBody[0][0] = s->screenHeight / 2;
    s->snakeBody[0][1] = s->screenLength / 2;
    s->screen[s->snakeBody[0][0]][s->snakeBody[0][1]] = pBody;

    s->bodyLength = 0;

    /* Spawn first food item */
    Snake_SetFood(s);
}
