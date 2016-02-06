#ifndef __PARAM__
#define __PARAM__

enum Direction { L, R,U,D };
enum Level {SIMPLE = 10, MEDIUM = 20, HARD = 30};
enum Side {UP,DOWN,LEFT,RIGHT,FRONT,BACK};

static const unsigned int DEFAULT_SCREENWIDTH = 800;
static const unsigned int DEFAULT_SCREENHEIGHT = 600;
static const unsigned int DEFAULT_SCREENDEPTH = 5000;

static const int size=3;

#endif