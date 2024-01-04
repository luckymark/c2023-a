
#ifndef C2023_CHALLENGE_EVALUATE_H
#define C2023_CHALLENGE_EVALUATE_H
int Count_linkfive(int i,int j,int map[][15]);
int Count_wakefour(int i,int j,int map[][15]);
int Count_rushfour(int i,int j,int map[][15]);
int Count_wakethree(int i,int j,int map[][15]);
int Count_sleepthree(int i,int j,int map[][15]);
int Count_waketwo(int i,int j,int map[][15]);
int Count_sleeptwo(int i,int j,int map[][15]);
int GiveValue(int i,int j,int map[][15]);
bool Is_GiveValue(int x,int y,int map[][15]);
int Evaluate(int map[][15]);
#endif //C2023_CHALLENGE_EVALUATE_H
