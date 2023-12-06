#include "board_paint.h"

int main() {
    reset_HCD(REAL);
    resetBoard(REAL);
    resetBoard(VIRTUAL);
    reset_HCD(VIRTUAL);
    chess(7,7,B_BLACK,REAL);
    drawBoard();
    creatRoot(7,7,B_BLACK);
    EstimateAndBack("","model.pth");
    inheritRoot();
    drawBoard();
    system("pause");
}