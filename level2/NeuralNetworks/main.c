#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include "extract_methods.h"
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
    int count[4];
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
    struct feat feature;
    feature.x_cen = extract_x_cen(Canvas);
    feature.y_cen = extract_y_cen(Canvas);
    feature.count[0] = scan_0(Canvas);
    feature.count[1] = scan_90(Canvas);
    feature.count[2] = scan_45(Canvas);
    feature.count[3] = scan_135(Canvas);
    feature.fft = EFT(Canvas);
    feature.label = 0;
    sample_trans(feature);
    data_read();
    cal_r1();
    cal_r2();
    cal_r3();
    cal_r4();
    printf("\nThe number you enter is %d",output());
}

int main() {
    printf("\nChoose your next action\n1 - Paint Mode\n2 - Training Mode\nAny other characters - Exit\n Enter your choice: ");
    int choice;
    time_t start, end;
    struct feat features[1797];
    scanf("%d",&choice);
    switch (choice) {
        case 1:
            paint(Canvas);
            draw();
            break;
        case 2:
            time(&start);
    FILE* img_file = fopen("images.dat", "rb");
    unsigned char pixels[8][8];
    int images[1797][8][8];
    for(int n=0; n<1797; n++) {
        for(int i=0; i<8; i++) {
            for(int j=0; j<8; j++) {
                fread(&pixels[i][j], 1, 1, img_file);
                images[n][i][j] = pixels[i][j];
            }
        }
    }
    int labels[1797];
    FILE* label_file = fopen("labels.dat", "rb");
    unsigned char label;
    for(int n=0; n<1797; n++) {
        fread(&label, 1, 1, label_file);
        labels[n] = label;
    }
    fclose(img_file);
    fclose(label_file);
    struct feat features[1797];
    for (int i = 0; i < 1797; ++i) {
        features[i].x_cen = extract_x_cen(images[i]);
        features[i].y_cen = extract_y_cen(images[i]);
        features[i].count[0] = scan_0(images[i]);
        features[i].count[1] = scan_90(images[i]);
        features[i].count[2] = scan_45(images[i]);
        features[i].count[3] = scan_135(images[i]);
        features[i].fft = EFT(images[i]);
        features[i].label = labels[i];
    }
    para_reset();
    for (int i = 0; i < 1797; ++i) {
        sample_trans(features[i]);
        cal_r1();
        cal_r2();
        cal_r3();
        cal_r4();
        cal_D_2();
        cal_D_1();
        Adam((double)i);
    }
    data_write();
            time(&end);
            printf("Done.(%.3f seconds)", difftime(end,start));
            break;
        default:
            printf("\nExited.\n");
            break;
    }
    system("pause");
    return 0;
}