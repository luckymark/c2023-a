#include "ga.h"
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <algorithm>
//概率部分
float rate_variation; //变异概率
float rate_swap;  //交叉概率
float rate_increase;
void set_rate(float rate_v, float rate_s,float rate_i) { //设置概率，初始化随机数种子
    srand(std::time(nullptr));
    rate_swap = rate_s;
    rate_variation = rate_v;
    rate_increase = rate_i;
}
//1表示变异概率，2表示交叉概率, 3 增长
bool judge_rate(int num) {   //如果命中了概率，返回真
    //设置概率
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
int get_int_rate(int maxnum, int remove) {  //生成从1到maxnum 包含 的整数 remove 取 -1 表示没有要除去的数
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
//地图部分
const int map_max_x = 12;
const int map_max_y = 30;
const int start_x = 1;
const int start_y = 3;
//为简化程序，保证终点的x和y均为能走到的最大值
const int end_x = 11;
const int end_y = 30;
char map[map_max_x+2][map_max_y+2];

void set_map(const char* map_str) {   //根据字符串设置地图
    int i = 0;  //字符下标
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

void print_map() {  //打印地图
    for(int i = 1; i <= map_max_x; i++) {
        for(int j = 1; j <= map_max_y; j++) {
            printf("%c", map[i][j]);
        }
        printf("\n");
    }
}

//个体部分
//1 右 2 下 3 左 4 上 0 结束
//每一轮都更新最大最小值
void path::examine() {    //截断路径 设置分数
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
            case 0: //说明已经遍历完了，没有撞墙
                return;
            default:
                printf("gene print error");
                break;
        }
        gen_index++;
    }
    switch (gene[gen_index-1]) {    //回退一步，用于计算最终分数
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

void path::print() {  //输出地图和路径
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
        //测试
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
    //测试
    printf("\n");
    //
    for(int i = 1; i <= map_max_x; i++) {
        for(int j = 1; j <= map_max_y; j++) {
            printf("%c",map_copy[i][j]);
        }
        printf("\n");
    }
}
void path::random_gen() { //随机生成一条路径
    memset(gene, 0 ,sizeof(gene));
    int maxnum = get_int_rate(gene_max*2/3)+gene_max/3;
    for(int i = 0; i < maxnum; i++) {
        //插入几个值
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