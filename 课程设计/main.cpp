#include "board_paint.h"

#define train_times 20

void createNewModel(std::string name) {
    GobangCNN model;
    torch::serialize::OutputArchive output;
    model.save(output);
    output.save_to(name);
}

int main() {
    createNewModel("model1.pth");
    createNewModel("model2.pth");
    int win1 = 0;
    int win2 = 0;
    for (int k = 0; k < train_times; ++k) {
        for (int i = 0; i < 3; ++i) {
            reset_HCD(REAL);
            resetBoard(REAL);
            resetBoard(VIRTUAL);
            reset_HCD(VIRTUAL);
            int now = 2;
            chess(7,7,B_BLACK,REAL);
            drawBoard();
            creatRoot(7,7,B_BLACK);
            drawBoard();
            while (game_terminate(REAL) == 0) {
                if (now == 1) {
                    EstimateAndBack("model1.pth","model1.pth");
                    inheritRoot();
                    drawBoard();
                    now = 2;
                } else if (now == 2) {
                    EstimateAndBack("model2.pth","model2.pth");
                    inheritRoot();
                    drawBoard();
                    now = 1;
                }
            }
            if (game_terminate(REAL) == 1) {
                win1++;
            }
            if (game_terminate(REAL) == 2) {
                win2++;
            }
            if (game_terminate(REAL) == 3) {
                i--;
            }
        }
        if (win1 < win2) {
            torch::serialize::InputArchive input;
            GobangCNN model;
            input.load_from("model2.pth");
            model.load(input);
            torch::serialize::OutputArchive output;
            model.save(output);
            output.save_to("model1.pth");
            createNewModel("model2.pth");
        } else if (win1 > win2) {
            createNewModel("model2.pth");
        }
    }
}