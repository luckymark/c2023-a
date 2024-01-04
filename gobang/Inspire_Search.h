

#ifndef C2023_CHALLENGE_INSPIRE_SEARCH_H
#define C2023_CHALLENGE_INSPIRE_SEARCH_H
typedef struct position
{
    int x;
    int y;
}pos;
pos* Search_list_black(int map[][15]);
pos* Search_list_white(int map[][15]);
bool Is_linkfive_black(int i,int j,int map[][15]);
bool Is_linkfive_white(int i,int j,int map[][15]);
bool Is_wakefour_black(int i,int j,int map[][15]);
bool Is_wakefour_white(int i,int j,int map[][15]);
bool Is_wakethree_black(int i,int j,int map[][15]);
bool Is_wakethree_white(int i,int j,int map[][15]);
#endif //C2023_CHALLENGE_INSPIRE_SEARCH_H
