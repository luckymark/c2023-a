#include "ga.h"
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <algorithm>
//���ʲ���
float rate_variation; //�������
float rate_swap;  //�������
float rate_increase;
void set_rate(float rate_v, float rate_s,float rate_i) { //���ø��ʣ���ʼ�����������
    srand(std::time(nullptr));
    rate_swap = rate_s;
    rate_variation = rate_v;
    rate_increase = rate_i;
}
//1��ʾ������ʣ�2��ʾ�������, 3 ����
bool judge_rate(int num) {   //��������˸��ʣ�������
    //���ø���
    float rate;
    switch (num) {
        case 1:
            rate = rate_variation;
            break;
        case 2:
            rate = rate_swap;
            break;
        case 3:
            rate = rate_increase;
            break;
        default:
            printf("rate input error");
            return false;
    }
    float rand_rate = rand()/(RAND_MAX+1.0f);
    if(rand_rate < rate) {
        return true;
    }else {
        return false;
    }
}
int get_int_rate(int maxnum, int remove) {  //���ɴ�1��maxnum ���� ������ remove ȡ -1 ��ʾû��Ҫ��ȥ����
    if(remove == -1) {
        float rand_rate = rand()/(RAND_MAX+1.0f);
        return int(rand_rate*float(maxnum))+1;
    }else {
        float rand_rate = rand()/(RAND_MAX+1.0f);
        int num = int(rand_rate*float(maxnum-1))+1;
        if(num == remove) {
            num = maxnum;
        }
        return num;
    }
}
//��ͼ����
const int map_max_x = 12;
const int map_max_y = 30;
const int start_x = 1;
const int start_y = 3;
//Ϊ�򻯳��򣬱�֤�յ��x��y��Ϊ���ߵ������ֵ
const int end_x = 11;
const int end_y = 30;
char map[map_max_x+2][map_max_y+2];

void set_map(const char* map_str) {   //�����ַ������õ�ͼ
    int i = 0;  //�ַ��±�
    int x = 1, y = 1;
    while(map_str[i] != '\0') {
        if(map_str[i] == '\n') {
            x++;
            y = 1;
        }else {
            map[x][y] = map_str[i];
            y++;
        }
        i++;
    }
}

void print_map() {  //��ӡ��ͼ
    for(int i = 1; i <= map_max_x; i++) {
        for(int j = 1; j <= map_max_y; j++) {
            printf("%c", map[i][j]);
        }
        printf("\n");
    }
}

//���岿��
//1 �� 2 �� 3 �� 4 �� 0 ����
//ÿһ�ֶ����������Сֵ
void path::examine() {    //�ض�·�� ���÷���
    int now_x = start_x, now_y = start_y;
    int gen_index = 0;
    while((map[now_x][now_y]==' '||map[now_x][now_y] == '-')&&now_x<=map_max_x&&now_x>=1&&now_y<=map_max_y&&now_y>=1) {
        switch (gene[gen_index]) {
            case 1:
                now_y++;
                break;
            case 2:
                now_x++;
                break;
            case 3:
                now_y--;
                break;
            case 4:
                now_x--;
                break;
            case 0: //˵���Ѿ��������ˣ�û��ײǽ
                return;
            default:
                printf("gene print error");
                break;
        }
        gen_index++;
    }
    switch (gene[gen_index-1]) {    //����һ�������ڼ������շ���
        case 1:
            now_y--;
            break;
        case 2:
            now_x--;
            break;
        case 3:
            now_y++;
            break;
        case 4:
            now_x++;
            break;
    }
    gen_len = gen_index - 1;
    score = end_x-now_x+end_y-now_y;
    gene[gen_index] = 0;
}

void path::print() {  //�����ͼ��·��
    printf("distance:%d\n",score);
    char map_copy[map_max_x+1][map_max_y+1];
    for(int i = 1; i <= map_max_x; i++) {
        for(int j = 1; j <= map_max_y; j++) {
            map_copy[i][j] = map[i][j];
        }
    }
    int gen_index = 0;
    int now_x = start_x, now_y = start_y;
    while(gene[gen_index] != 0) {
        //����
        printf("%c,",gene[gen_index]+'0');
        //
        map_copy[now_x][now_y] = gen_index%('z'-'a'-1)+'a';
        switch (gene[gen_index]) {
            case 1:
                now_y++;
                break;
            case 2:
                now_x++;
                break;
            case 3:
                now_y--;
                break;
            case 4:
                now_x--;
                break;
            case 0:
                break;
            default:
                printf("gene error");
                break;
        }
        gen_index++;
    }
    printf("%c",gene[gen_index]+'0');
    //����
    printf("\n");
    //
    for(int i = 1; i <= map_max_x; i++) {
        for(int j = 1; j <= map_max_y; j++) {
            printf("%c",map_copy[i][j]);
        }
        printf("\n");
    }
}
void path::random_gen() { //�������һ��·��
    memset(gene, 0 ,sizeof(gene));
    int maxnum = get_int_rate(gene_max*2/3)+gene_max/3;
    for(int i = 0; i < maxnum; i++) {
        //���뼸��ֵ
        if(i == 0) {
            gene[i] = 2;
            continue;
        }else {
            char remove;
            switch (gene[i-1]) {
                case 1:
                    remove = 3;
                    break;
                case 2:
                    remove = 4;
                    break;
                case 3:
                    remove = 1;
                    break;
                case 4:
                    remove = 2;
                    break;
            }
            gene[i] = (char)get_int_rate(4, (int)remove);
        }
    }
}
int path::return_score() {
    return score;
}