//初始化，定义常量
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <list>
#include <ctime>
using namespace std;
//测试用
float time_dfs = 0;
//棋盘参数
#define MAX 15
//状态表
#define EMPTY 0
#define AIBLACK 1
#define AIWHITE 2
//评分表
#define SCOREMAX 99999909
#define SA 5000000
#define SB 43200
#define SC 720
#define SD 10
#define SE 2
//六个子的棋形
const int sixchess_num = 10;
const int score_six[sixchess_num] = {SB,SC,SC,SC,SC,SD,SD,SD,SE,SE};
const list<int> sixchess_list[sixchess_num]={{0,1,1,1,1,0},{2,1,1,1,1,0},{0,1,1,1,1,2},{0,1,1,0,1,0},{0,1,0,1,1,0},{0,0,1,1,0,0},{2,1,1,1,0,0},{0,0,1,1,1,2},{2,1,1,0,0,0},{0,0,0,1,1,2}};
//五个子的棋形
const int fivechess_num = 4;
const int score_five[fivechess_num] = {SA,SB,SE,SC};
const list<int> fivechess_list[fivechess_num]={{1,1,1,1,1,},{1,1,0,1,1},{0,0,1,0,0},{0,1,1,1,0}};
//极大极小搜索相关
int MAXlayer = 2; //设置成偶数层
typedef struct location location;
typedef struct location  //用一个特定函数生成含可落子点的坐标的链表，返回头节点，每用一个释放一个
{
    int x;
    int y;
    int score;  //这个位置的分数
}location;
int AIchess = 0;
int HUchess = 0;
//初始化函数
int** AI_start(int AI, int HU)
{
    int** chessboard = (int**)malloc((MAX+2) * sizeof(int*));
    for (int i = 0; i < MAX+2; i++)
    {
        chessboard[i] = (int*)malloc((MAX+2) * sizeof(int));
    }
    for(int i = 0; i < MAX+2; i++)
    {
        for(int j = 0; j < MAX+2; j++)
        {
            chessboard[i][j] = 0;
        }
    }
    AIchess = AI;
    HUchess = HU;
    return chessboard;
}

float max(float num1, float num2)
{
    return num1 > num2 ? num1 : num2;
}

float min(float num1, float num2)
{
    return num1 < num2 ? num1 : num2;
}

int max(int num1, int num2)
{
    return num1 > num2 ? num1 : num2;
}

int min(int num1, int num2)
{
    return num1 < num2 ? num1 : num2;
}

void afterchess_update(int& ltx,int& lty,int& rbx,int& rby,int x, int y)
{
    ltx = min(ltx,x);
    rbx = max(rbx,x);
    lty = min(lty,y);
    rby = max(rby,y);
}

//引入 boardscore和score_location，这两个都只能判断一方，需要相减
//整个过程不涉及棋盘的更改
//---------------------------------------------------------------------------------------------------------
//以下几个函数用来计算局面分数
int compare(int num, list<int> &list)
{
    if(num == 5)
    {
        for(int i = 0; i < fivechess_num; i++)
        {
            if(list == fivechess_list[i])
            {
                return score_five[i];
            }
        }
    }
    else if(num == 6)
    {
        for(int i = 0; i < sixchess_num; i++)
        {
            if(list == sixchess_list[i])
            {
                return score_six[i];
            }
        }
    }
    return 0;
}
int get_locationscore(int **board,const int x,const int y, int player)
{
    int score = 0;
    list<int> compare_six;
    list<int> compare_five;
    //行搜索
    for(int i = y-5; i <= y; i++)   //i表示左起点
    {
        if(i == y-5)  //只比较六个的
        {
            for(int j = 0; j < 6; j++)
            {
                if(j < 5)
                {
                    compare_five.push_back(i+j<1||i+j>MAX?2:(board[x][i+j]==player?1:board[x][i+j]==0?0:2));
                }
                compare_six.push_back(i+j<1||i+j>MAX?2:(board[x][i+j]==player?1:board[x][i+j]==0?0:2));
            }
            score += compare(6,compare_six);
        }
        else
        {
            compare_six.pop_front();
            compare_six.push_back(i+5<1||i+5>MAX?2:(board[x][i+5]==player?1:board[x][i+5]==0?0:2));
            compare_five.pop_front();
            compare_five.push_back(i+4<1||i+4>MAX?2:(board[x][i+4]==player?1:board[x][i+4]==0?0:2));
            score += compare(6,compare_six);
            score += compare(5,compare_five);
        }
    }
    //列搜索
    compare_six.clear();
    compare_five.clear();
    for(int i = x-5; i <= x; i++)   //i表示上起点
    {
        if(i == x-5)  //只比较六个的
        {
            for(int j = 0; j < 6; j++)
            {
                if(j < 5)
                {
                    compare_five.push_back(i+j<1||i+j>MAX?2:(board[i+j][y]==player?1:board[i+j][y]==0?0:2));
                }
                compare_six.push_back(i+j<1||i+j>MAX?2:(board[i+j][y]==player?1:board[i+j][y]==0?0:2));
            }
            score += compare(6,compare_six);
        }
        else
        {
            compare_six.pop_front();
            compare_six.push_back(i+5<1||i+5>MAX?2:(board[i+5][y]==player?1:board[i+5][y]==0?0:2));
            compare_five.pop_front();
            compare_five.push_back(i+4<1||i+4>MAX?2:(board[i+4][y]==player?1:board[i+4][y]==0?0:2));
            score += compare(6,compare_six);
            score += compare(5,compare_five);
        }
    }
    // \搜索
    compare_six.clear();
    compare_five.clear();
    for(int i = 1; i <= 6; i++)
    {
        if(i == 1)  //只比较六个的
        {
            for(int j = 0; j < 6; j++)
            {
                if(j < 5)
                {
                    compare_five.push_back(x-6+i+j<1||x-6+i+j>MAX||y-6+i+j<1||y-6+i+j>MAX?2:(board[x-6+i+j][y-6+i+j]==player?1:board[x-6+i+j][y-6+i+j]==0?0:2));
                }
                compare_six.push_back(x-6+i+j<1||x-6+i+j>MAX||y-6+i+j<1||y-6+i+j>MAX?2:(board[x-6+i+j][y-6+i+j]==player?1:board[x-6+i+j][y-6+i+j]==0?0:2));
            }
            score += compare(6,compare_six);
        }
        else
        {
            compare_six.pop_front();
            compare_six.push_back(x-6+i+5<1||x-6+i+5>MAX||y-6+i+5<1||y-6+i+5>MAX?2:(board[x-6+i+5][y-6+i+5]==player?1:board[x-6+i+5][y-6+i+5]==0?0:2));
            compare_five.pop_front();
            compare_five.push_back(x-6+i+4<1||x-6+i+4>MAX||y-6+i+4<1||y-6+i+4>MAX?2:(board[x-6+i+4][y-6+i+4]==player?1:board[x-6+i+4][y-6+i+4]==0?0:2));
            score += compare(6,compare_six);
            score += compare(5,compare_five);
        }
    }
    // /搜索
    compare_six.clear();
    compare_five.clear();
    for(int i = 1; i <= 6; i++)
    {
        if(i == 1)  //只比较六个的
        {
            for(int j = 0; j < 6; j++)
            {
                if(j < 5)
                {
                    compare_five.push_back(x-6+i+j<1||x-6+i+j>MAX||y+6-i-j<1||y+6-i-j>MAX?2:(board[x-6+i+j][y+6-i-j]==player?1:board[x-6+i+j][y+6-i-j]==0?0:2));
                }
                compare_six.push_back(x-6+i+j<1||x-6+i+j>MAX||y+6-i-j<1||y+6-i-j>MAX?2:(board[x-6+i+j][y+6-i-j]==player?1:board[x-6+i+j][y+6-i-j]==0?0:2));
            }
            score += compare(6,compare_six);
        }
        else
        {
            compare_six.pop_front();
            compare_six.push_back(x-6+i+5<1||x-6+i+5>MAX||y+6-i-5<1||y+6-i-5>MAX?2:(board[x-6+i+5][y+6-i-5]==player?1:board[x-6+i+5][y+6-i-5]==0?0:2));
            compare_five.pop_front();
            compare_five.push_back(x-6+i+4<1||x-6+i+4>MAX||y+6-i-4<1||y+6-i-4>MAX?2:(board[x-6+i+4][y+6-i-4]==player?1:board[x-6+i+4][y+6-i-4]==0?0:2));
            score += compare(6,compare_six);
            score += compare(5,compare_five);
        }
    }
    return score;
}
//---------------------------------------------------------------------------------------------------------
//极大极小搜索相关函数
bool location_cmp(location a, location b)
{
    return a.score>b.score;
}
location* search_generate(int** board,int chess,int ltx,int lty,int rbx,int rby)    //左上，右下坐标
{
    int pointnum = 1;
    auto* location_list = (location*)malloc(sizeof(location)*180);
    ltx = ltx == 1 ? 1 : ltx-1;
    lty = lty == 1 ? 1 : lty-1;
    rbx = rbx == MAX ? MAX : rbx+1;
    rby = rby == MAX ? MAX : rby+1;
    for(int i = ltx; i <= rbx; i++)
    {
        for(int j = lty; j <= rby; j++)
        {
            if(pointnum > 177)
            {
                break;
            }
            if(board[i][j] == EMPTY)
            {
                location_list[pointnum].x = i;
                location_list[pointnum].y = j;
                board[i][j] = chess;
                location_list[pointnum].score = get_locationscore(board,i,j,AIchess)-get_locationscore(board,i,j,HUchess);
                board[i][j] = EMPTY;
                pointnum++;
            }
        }
    }
    pointnum--;
    location_list[0].x = pointnum;  //这个用来存放数量
    sort(location_list+1,location_list+pointnum,location_cmp);
    return location_list;
}
int** search_copy(int** from)
{
    int** to = (int**)malloc((MAX+2) * sizeof(int*));
    for (int i = 0; i < MAX+2; i++)
    {
        to[i] = (int*)malloc((MAX+2) * sizeof(int));
    }
    for(int i = 0; i < MAX+2; i++)
    {
        for(int j = 0; j < MAX+2; j++)
        {
            to[i][j] = from[i][j];
        }
    }
    return to;
}
void search_freeboard(int** mfree)   //模仿申请空间的方式释放空间
{
    for (int i = 0; i < MAX+2; i++)
    {
        free(mfree[i]);
    }
    free(mfree);
}
location search_result;
int search_DFS(location* now_list,int layer, int** board,int lastmax,int lastmin,int score,int ltx,int lty,int rbx,int rby)
{
    int num = 1;
    int num_max = now_list[0].x;
    if(layer == MAXlayer)   //传入的是最大偶数，MIN层
    {
        int minnum = SCOREMAX;
        while(num <= num_max)
        {
            int **newboard = search_copy(board);
            int last_score = get_locationscore(newboard,now_list[num].x,now_list[num].y,AIchess) - get_locationscore(newboard,now_list[num].x,now_list[num].y,HUchess);
            newboard[now_list[num].x][now_list[num].y] = HUchess;
            minnum = min(minnum, score + now_list[num].score-last_score);
            if(minnum <= lastmax){
                return minnum;
            }
            search_freeboard(newboard);
            num++;
        }
        return minnum;
    }
    else
    {
        //偶数，MIN层
        if(layer%2 == 0)
        {
            int minnum = SCOREMAX;
            while(num <= num_max)
            {
                int** newboard = search_copy(board);
                int last_score = get_locationscore(newboard,now_list[num].x,now_list[num].y,AIchess) - get_locationscore(newboard,now_list[num].x,now_list[num].y,HUchess);
                newboard[now_list[num].x][now_list[num].y] = HUchess;
                int ltx2,lty2,rbx2,rby2;
                ltx2 = ltx;
                lty2 = lty;
                rbx2 = rbx;
                rby2 = rby;
                afterchess_update(ltx2,lty2,rbx2,rby2,now_list[num].x,now_list[num].y);
                minnum = min(minnum, search_DFS(search_generate(newboard,AIchess,ltx2,lty2,rbx2,rby2),layer+1,newboard,lastmax,minnum,score+now_list[num].score - last_score,ltx2,lty2,rbx2,rby2));
                if(minnum <= lastmax)
                {
                    return minnum;
                }
                search_freeboard(newboard);
                num++;
            }
            return minnum;
        }
        else    //奇数，MAX层
        {
            int maxnum = -SCOREMAX;
            while(num <= num_max)
            {
                int** newboard = search_copy(board);
                int last_score = get_locationscore(newboard,now_list[num].x,now_list[num].y,AIchess) - get_locationscore(newboard,now_list[num].x,now_list[num].y,HUchess);
                newboard[now_list[num].x][now_list[num].y] = AIchess;
                int ltx2,lty2,rbx2,rby2;
                ltx2 = ltx;
                lty2 = lty;
                rbx2 = rbx;
                rby2 = rby;
                afterchess_update(ltx2,lty2,rbx2,rby2,now_list[num].x,now_list[num].y);
                if(layer == 1)
                {
                    int searchscore = search_DFS(search_generate(newboard,HUchess,ltx,lty,rbx,rby),layer+1,newboard,maxnum,lastmin,score + now_list[num].score-last_score,ltx2,lty2,rbx2,rby2);
                    if(maxnum < searchscore)
                    {
                        search_result.x = now_list[num].x;
                        search_result.y = now_list[num].y;
                        maxnum = searchscore;
                    }
                }
                else
                {
                    maxnum = max(maxnum, search_DFS(search_generate(newboard,HUchess,ltx,lty,rbx,rby),layer+1,newboard,maxnum,lastmin,score + now_list[num].score-last_score,ltx2,lty2,rbx2,rby2));
                }
                if(maxnum >= lastmin){
                    return maxnum;
                }
                search_freeboard(newboard);
                num++;
            }
            return maxnum;
        }
    }
}
//-------------------------------------------------------------------------------------------------------------------
//待：实现胜负判断
//记录最左上和最右下的棋子,在+1的方形范围内搜索
//待：完成迭代加深
//待完成：实现哈希表，算杀