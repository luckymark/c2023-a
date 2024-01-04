

#ifndef C2023_CHALLENGE_MINIMAX_SEARCH_H
#define C2023_CHALLENGE_MINIMAX_SEARCH_H
bool Is_drop(int x,int y,int map[][15]);
typedef struct Root
{
    bool IsMax;
    int depth;
    int pre;
    int score;
    int x;
    int y;
}Root;
typedef struct Node
{
    bool IsMax;
    int depth;
    int alpha;
    int beta;
    int pre;
    int score;
}Node;
typedef struct Feedback
{
    int score;
    int* present_map;
}Feedback;
Feedback* AI_drop(int i,int j,int map[][15]);
Root* Create_Root(int map[][15]);
int Create_children(bool Is_Father_Max,int Father_depth,int pre,int map[][15]);
Node* Give_Max_Value(int map[][15]);
int Search(int pre_alpha,int map[][15]);
#endif //C2023_CHALLENGE_MINIMAX_SEARCH_H
