#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include "extract_methods.h"
#include "data_process.h"
#include "Network.h"

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
void reset_Canvas() {
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            Canvas[i][j] = 0;
        }
    }
}
void paint(int input[HEIGHT][WIDTH]) {
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
    printf("Use WASD to move, F to draw, R to delete, C to clear, and G to confirm.\n");
}
void draw() {
    char choice;
    int w = 1;
    while (w) {
        choice = getch();
        switch (choice) {
            case 'w':
                if (y-1>=0) {
                    y--;
                }
                paint(Canvas);
                break;
            case 's':
                if (y+1<=7) {
                    y++;
                }
                paint(Canvas);
                break;
            case 'a':
                if (x-1>=0) {
                    x--;
                }
                paint(Canvas);
                break;
            case 'd':
                if (x+1<=7) {
                    x++;
                }
                paint(Canvas);
                break;
            case 'f':
                Canvas[y][x] = 1;
                paint(Canvas);
                break;
            case 'r':
                Canvas[y][x] = 0;
                paint(Canvas);
                break;
            case 'c':
                reset_Canvas();
                paint(Canvas);
                break;
            default:
                paint(Canvas);
                w = 0;
                break;
        }
    }
    struct feat features;
    features.x_cen = extract_x_cen(Canvas);
    features.y_cen = extract_y_cen(Canvas);
    features.count[0] = scan_0(Canvas);
    features.count[1] = scan_90(Canvas);
    features.count[2] = scan_45(Canvas);
    features.count[3] = scan_135(Canvas);
    features.fft = EFT(Canvas);
    features.label = 0;
    sample_trans(features);
    data_read();
    cal_r1();
    cal_r2();
    cal_r3();
    cal_r4();
    printf("\nThe number you enter is %d",output());
}
int main() {
    printf("\nChoose your next action\n1 - Paint Mode\n2 - Data Processing Mode\n3 - Training Mode\nAny other characters - Exit\n Enter your choice: ");
    int choice;
    time_t start, end;
    struct feat feature[1797];
    scanf("%d",&choice);
    switch (choice) {
        case 1:
            para_reset();
            paint(Canvas);
            draw();
            break;
        case 2:
            printf("\nExplanation: the data should be stored in files named \"images.dat\" and \"labels.dat\", \nand after converting the data, it will be out put as a \"sample.dat\" file.\n");
            system("pause");
            data_process();
            break;
        case 3:
            time(&start);
            para_reset();
            FILE * fp;
            fp = fopen("sample.dat","rb");
            for (int i = 0; i < 1797; ++i) {
                fread(&feature[i],sizeof(struct feat),1,fp);
            }
            fclose(fp);
            for (int i = 0; i < 1797; ++i) {
                sample_trans(feature[i]);
                cal_r1();
                cal_r2();
                cal_r3();
                cal_r4();
                cal_D_1();
                cal_D_2();
                Adam(i);
            }
            data_write();
            printf("Done.");
            break;
        default:
            printf("\nExited.\n");
            break;
    }
    system("pause");
    return 0;
}