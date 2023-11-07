#include <iostream>
#include "ga.h"
#include <vector>
#include <ctime>

using namespace std;
vector<path> path_list;
const int initial_group_max = 400;  //种群数量
const int max_run_num = 700; //计算轮数
const int increase_num = 10;

int main() {
    //传入地图
    char map_str[400] = "++-+++++++++++++++++++++++++++\n+  +                         +\n+  +                         +\n+  +                         +\n+  +                         +\n+  ++++++++++++++++++        +\n+  +            +            +\n+  +            +            +\n+  +            +            +\n+                            +\n+                            >\n++++++++++++++++++++++++++++++\n";
    set_map(map_str);
    //print_map();
    //概率初始化
    set_rate(0.6f, 0.3f, 0.8f);
    //初始化种群
    for (int i = 1; i <= initial_group_max; i++) {
        path new_path;
        new_path.random_gen();
        new_path.examine();
        path_list.push_back(new_path);
    }

    int lastscore = 100000;
    //算法主体
    for (int run_i = 1; run_i <= max_run_num; run_i++) {
        //给结构体再写一个返回分数的函数，用一次循环找到分数最小的路径的下标，分数越小越好
        int max_score = -100000;
        int min_score = 100000;
        path *min_score_path = nullptr;
        for (auto &it: path_list) {    //找到得分最小的路线
            int score = it.return_score();
            max_score = max(max_score, score);
            if (score < min_score) {
                min_score = score;
                min_score_path = &it;
            }
        }

        if(min_score_path->score < lastscore) {
            lastscore = min_score_path->score;
            min_score_path->print();
            if(lastscore == 1) {
                break;
            }
        }

        if(min_score_path->score == 1) {
            break;
        }
        //以下三个函数待完成
        //筛选一半，挑选最高分个体填补位置
        for (auto &it: path_list) {
            int score = it.return_score();
            if (rand() / (RAND_MAX + 1.0f) >
                (1.0f - (float) (score - min_score) / (float) (max_score - min_score))) {
                it = *min_score_path;
            }
        }
        //交叉操作
        for (auto &it: path_list) {
            if (judge_rate(2)) {
                int index_swap = get_int_rate(path_list.size() - 1);
                int start_point = get_int_rate(it.gen_len);
                while (path_list[index_swap].gene[start_point] != 0) {
                    it.gene[start_point] = path_list[index_swap].gene[start_point];
                    start_point++;
                }
                it.examine();
            }
        }
        //变异操作
        for (auto &it: path_list) {
            if (judge_rate(1)) {
                int i = 1;  //跳过第一个数
                while (it.gene[i] != 0) {
                    if (!judge_rate(1)) {    //设置的变异概率越小，每个点改变的概率越大
                        it.gene[i] = get_int_rate(4, it.gene[i - 1]);
                    }
                    i++;
                }
                it.examine();
            }
        }
        //增长操作
        for (auto &it: path_list) {
            if (judge_rate(3)) {
                for (int i = 1; i <= increase_num; i++) {
                    it.gene[it.gen_len + i] = get_int_rate(4, it.gene[it.gen_len + i - 1]);
                }
                it.examine();
            }
        }
        //min_score_path->print();
    }
    path *min_score_path = nullptr;
    int min_score = 1000000;
    for (auto &it: path_list) {    //找到得分最小的路线
        int score = it.return_score();
        if (score < min_score) {
            min_score = score;
            min_score_path = &it;
        }
    }
    getchar();
    return 0;
}
