//地图相关
void set_map(const char* map_str);
void print_map();
//概率相关
void set_rate(float rate_v, float rate_s, float rate_i);
bool judge_rate(int num);
int get_int_rate(int maxnum, int remove = -1);
//个体相关
const int gene_max = 500;
typedef struct path{
    char gene[gene_max];    //从0开始
    int score;
    int gen_len;
    void examine();
    void print();
    void random_gen();
    int return_score();
}path;
//遗传相关
