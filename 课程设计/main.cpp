//
// Created by Administrator on 2023/10/17 0017.
//

extern "C" {
#include "MCTS.h"
}
#include <stdio.h>
#include <stdlib.h>
#include "board_paint.h"

int main() {
    resetBoard(REAL);
    drawBoard();
    for (int i = 0; i < 5; ++i) {
        playerMove();
    }
    game_terminate(REAL);
    drawBoard();
    system("pause");
}