#pragma GCC optimize(3,"Ofast","inline")
//bug:下几个棋就不下了  已解决，原因：分数超过设置的最大值了
//待办：注意着法生成的结果中已经有这个点的分数了，不用再算一次
//调用ai库
#include "ai.h"
//调用easyx图形库
#include <graphics.h>

const int gui_length = 30;

void test_showboard(int** chessboard)
{
    for(int i = 1; i<=MAX;i++)
    {
        for(int j = 1; j<=MAX; j++)
        {
            printf("%d ",chessboard[i][j]);
        }
        printf("\n");
    }
}

//绘制棋盘
void gui_drawwindow()
{
    cleardevice();
    setlinecolor(BLUE);
    for(int i = 1; i <= MAX; i++)
    {
        line(gui_length*i,gui_length,gui_length*i,gui_length*MAX);
    }
    for(int i = 1; i <= MAX; i++)
    {
        line(gui_length,gui_length*i,gui_length*MAX,gui_length*i);
    }
}
//绘制棋子,传入坐标,执棋方
void gui_drawchess(int x, int y, int player)
{
    setfillcolor(player == AIchess ? BLACK : WHITE);
    solidcircle(x*gui_length,y*gui_length,gui_length/2-2);
}



int main()
{
    int ltx,lty,rbx,rby;

    int score = 0;
    //初始化棋盘
    int** chessboard = AI_start(AIBLACK, AIWHITE);
/*
    chessboard[6][5] = chessboard[3][6] = chessboard[3][4]=chessboard[4][4] = 1;
    chessboard[4][5] = chessboard[5][4] = chessboard[6][3]=chessboard[7][2]=2;
    for(int i = 1; i<=MAX;i++)
    {
        for(int j = 1; j<=MAX; j++)
        {
            printf("%d ",chessboard[i][j]);
        }
        printf("\n");
    }
    score = -716.0f;
    printf("%f", search_DFS(search_generate(chessboard),1,chessboard,-SCOREMAX,SCOREMAX,score));
    printf("\n %d, %d",search_result.x,search_result.y);
    getchar();
    */

    //初始化窗体
    initgraph(gui_length*(MAX+1), gui_length*(MAX+1));
    setbkcolor(GREEN);
    MOUSEMSG m{};
    gui_drawwindow();
    //ai在靠近中心的位置落第一颗棋子
    chessboard[MAX/2][MAX/2] = AIchess;

    ltx=lty=rbx=rby = MAX/2;

    score+=SE;
    gui_drawchess(MAX/2,MAX/2,AIchess);
    //和search_result的结果保持一致
    //循环
    MAXlayer = 2;
    while(true)
    {
        //获取鼠标参数
        m = GetMouseMsg();
        if(m.uMsg == WM_LBUTTONDOWN)    //按下左键
        {
            int isfind = 0; //标记是否找到按的点
            for(int i = 1; i <= MAX; i++)
            {
                for (int j = 1; j <= MAX; j++)
                {
                    if (abs(j * gui_length - m.y) < 10 && abs(i * gui_length - m.x) < 10)
                    {
                        if(chessboard[j][i] == EMPTY)
                        {
                            gui_drawchess(i, j, HUchess);
                            int location_score = get_locationscore(chessboard,j,i,AIchess)-get_locationscore(chessboard,j,i,HUchess);
                            chessboard[j][i] = HUchess;
                            afterchess_update(ltx,lty,rbx,rby,j,i);
                            int now_score = get_locationscore(chessboard,j,i,AIchess)-get_locationscore(chessboard,j,i,HUchess);
                            score = score + now_score - location_score;
                            if(score < -SA*0.7)
                            {
                                printf("human win\n");
                                getchar();
                                return 0;
                            }
                            printf("score: %d \n",score);

                            time_dfs=0;
                            clock_t start,end;
                            start = clock();
                            int search_score = search_DFS(search_generate(chessboard,AIchess,ltx,lty,rbx,rby),1,chessboard,-SCOREMAX, SCOREMAX, score,ltx,lty,rbx,rby);
                            end = clock();
                            time_dfs = (float)(end-start)/CLOCKS_PER_SEC;

                            if(time_dfs < 0.04f && search_score<SA*0.7) //动态选择4层还是2层
                            {
                                MAXlayer = 4;
                                search_DFS(search_generate(chessboard,AIchess,ltx,lty,rbx,rby),1,chessboard,-SCOREMAX, SCOREMAX, score,ltx,lty,rbx,rby);
                                MAXlayer = 2;
                            }

                            printf("dfs: %f \n",time_dfs);
                            location_score = get_locationscore(chessboard,search_result.x,search_result.y,AIchess)-get_locationscore(chessboard,search_result.x,search_result.y,HUchess);
                            chessboard[search_result.x][search_result.y] = AIchess;
                            afterchess_update(ltx,lty,rbx,rby,search_result.x,search_result.y);
                            now_score = get_locationscore(chessboard,search_result.x,search_result.y,AIchess)-get_locationscore(chessboard,search_result.x,search_result.y,HUchess);
                            score = score + now_score - location_score;
                            //搜索算法不太合适，AI防的很好，但不会去赢，极有可能是哪个参数写错了，设计一种AI只要一步就能赢得情况，手动在控制台条件下模拟，追溯AI的争个过程
                            //初始分数由原始版本中的全局分数计算函数得到
                            //已上已完成，先不写胜利判断，先想办法减少点的个数
                            //编写胜利判断
                            //除了哈希表，想不出别的优化方案，只能是尝试结合多种方法优化着法生成函数，尽量让点位少，同时改变MAXlayer的判断逻辑，判断一下是奇数还是偶数，先突破到三层再说
                            //同时改写着法生成里的排序，改为自己写的快排或sort直接排序
                            //另一种方式，不用随机数，固定一组数用来写哈希算法，同时在本地存储大量的运算好的结果，打开程序时先读入
                            gui_drawchess(search_result.y,search_result.x,AIchess);
                            if(score > SA*0.7)
                            {
                                printf("computer win\n");
                                getchar();
                                return 0;
                            }
                            isfind = 1;
                            break;
                        }
                    }
                }
                if(isfind == 1)
                {
                    break;
                }
            }
        }
    }

}