#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "extract_methods.h"

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
void paint(int sample) {
    system("cls");
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            printf("%d ",Canvas[i][j]);
        }
        printf("\n");
    }
    printf("x: %d, y: %d, sample: %d\n",x+1,y+1,sample+1);
    printf("Use WASD to move, F to draw, R to delete, C to clear, and G to confirm.\n");
}
void draw(char choice,int sample) {
    switch (choice) {
        case 'w':
            if (y-1>=0) {
                y--;
            }
            paint(sample);
            break;
        case 's':
            if (y+1<=7) {
                y++;
            }
            paint(sample);
            break;
        case 'a':
            if (x-1>=0) {
                x--;
            }
            paint(sample);
            break;
        case 'd':
            if (x+1<=7) {
                x++;
            }
            paint(sample);
            break;
        case 'f':
            Canvas[y][x] = 1;
            paint(sample);
            break;
        case 'r':
            Canvas[y][x] = 0;
            paint(sample);
            break;
        case 'c':
            reset();
            paint(sample);
            break;
        default:
            paint(sample);
            break;
    }
}
int main() {
    int sample_amount = 0;
    printf("Enter the amout of the samples: ");
    scanf("%d",&sample_amount);
    printf("\n");
    struct feat features[sample_amount];
    int label[sample_amount];
    for (int i = 0; i < sample_amount; ++i) {
        x = 0;
        y = 0;
        reset();
        paint(i);
        while (1) {
            char choice = getch();
            if (choice == 'g') {
                break;
            } else {
                draw(choice,i);
            }
        }
        printf("\nEnter the label: ");
        scanf("%d",&label[i]);
        features[i].x_cen = extract_x_cen(Canvas);
        features[i].y_cen = extract_y_cen(Canvas);
        features[i].count[0] = scan_0(Canvas);
        features[i].count[1] = scan_90(Canvas);
        features[i].count[2] = scan_45(Canvas);
        features[i].count[3] = scan_135(Canvas);
        features[i].fft = EFT(Canvas);
    }
    FILE * fp = fopen("sample.dat","wb");
    fwrite(&sample_amount,sizeof(int),1,fp);
    for (int i = 0; i < sample_amount; ++i) {
        fwrite(&label[i],sizeof(int),1,fp);
        fwrite(&features[i],sizeof(struct feat),1,fp);
    }
    fclose(fp);
    return 0;
}