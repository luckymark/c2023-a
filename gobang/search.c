#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>
int map[15][15]={};
struct Chess
{
    int color;
    int atkValue;
    int defValue;
    int row;
    int col;
    bool isBoundry;
};
struct Chain_type
{
    bool linkfive;
    bool wakefour;
    bool rushfour;
    bool wakethree;
    bool sleepthree;
    bool waketwo;
    bool sleeptwo;
};
struct Chain_dir
{
    bool lay;
    bool stand;
    bool main;
    bool vice;
};
struct Chesschain
{
    struct Chain_dir;
    struct Chain_type;
    int len;
};
int main()
{

}
void evaluate()
{

}


