//
// Created by Administrator on 2023/9/30 0030.
//

#include <stdio.h>
#include "data_process.h"
#include "extract_methods.h"
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
void data_process() {
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
    FILE * f_sample = fopen("sample.dat","wb");
    for (int i = 0; i < 1797; ++i) {
        fwrite(&features[i],sizeof(struct feat),1,f_sample);
    }
    fclose(f_sample);
}
