#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include "extract_methods.h"
#include "data_process.h"

#define WIDTH 8
#define HEIGHT 8
#define N 8
struct feat {
    //x质心
    double x_cen;
    //y质心
    double y_cen;
    //扫描线
    int count[8];
    //傅里叶特征
    double* fft;
    //标签
    int label;
};
int x = 0;
int y = 0;
int Canvas[HEIGHT][WIDTH];
void reset() {
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            Canvas[i][j] = 0;
        }
    }
}
void paint(int sample,int input[HEIGHT][WIDTH]) {
    system("cls");
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            if (input[i][j] == 1) {
                printf("# ");
            } else {
                printf("  ");
            }
        }
        printf("\n");
    }
    printf("x: %d, y: %d, sample: %d\n",x+1,y+1,sample+1);
    printf("Use WASD to move, F to draw, R to delete, C to clear, and G to confirm.\n");
}
void draw(char choice,int sample,int input[HEIGHT][WIDTH]) {
    switch (choice) {
        case 'w':
            if (y-1>=0) {
                y--;
            }
            paint(sample, input);
            break;
        case 's':
            if (y+1<=7) {
                y++;
            }
            paint(sample, input);
            break;
        case 'a':
            if (x-1>=0) {
                x--;
            }
            paint(sample, input);
            break;
        case 'd':
            if (x+1<=7) {
                x++;
            }
            paint(sample,input);
            break;
        case 'f':
            Canvas[y][x] = 1;
            paint(sample,input);
            break;
        case 'r':
            Canvas[y][x] = 0;
            paint(sample,input);
            break;
        case 'c':
            reset();
            paint(sample,input);
            break;
        default:
            paint(sample,input);
            break;
    }
}


int main() {
    data_process();
    printf("Finished");
    system("pause");
    return 0;
}+