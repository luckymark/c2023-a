//
// Created by ycm on 2023/10/9.
//

#include "push_boxes.h"

//char FILE_NAME[] = "001.bin";
Place player = {0, 0};
Place MAP_SIZE = {0,0};
Place goals[200] = {};
bool bgoals[200] = {};
char** MAP;
unsigned box_num = 0;

char** init_map(char* filename){
    MAP = read_map(filename);
//    MAP_SIZE = read_size(filename);
    if(MAP == NULL){
        return NULL;
    }
    unsigned igoal = 0;
    for(unsigned x=0;x<MAP_SIZE.x;x++)for(unsigned y=0;y<MAP_SIZE.y;y++){
            switch (MAP[x][y]) {
                case PLAYER: player.x = x;player.y = y;break;
                case BOX: box_num += 1;break;
                case GOAL: goals[igoal].x = x;goals[igoal++].y = y;break;
                case FILL: box_num += 1;goals[igoal].x = x;goals[igoal].y = y;bgoals[igoal++] = true;break;
                default:break;
            }
    }
    return MAP;
}

void draw_map(char** map/*, Place size*/) {
    Place size = MAP_SIZE;
    for(unsigned x=0;x<size.x;x++) {
        for (unsigned y = 0; y < size.y; y++) {
            switch (map[x][y]) {
                case PLAYER:
                    printf("\x1b[36m%c\x1b[0m", PLAYER_C);break;
                case BOX:
                    printf("\x1b[33m%c\x1b[0m", BOX_C);break;
                case PATH:
                    printf("%c", PATH_C);break;
                case EMPTY:
                    printf("%c", EMPTY_C);break;
                case GOAL:
                    printf("\x1b[33m%c\x1b[0m", GOAL_C);break;
                case FILL:
                    printf("%c", FILL_C);break;
                case WALL:
                    //打印边框
                    if ((x == 0 || x == size.x - 1) && (y == 0 || y == size.y - 1)) {
                        printf("+");
                        break;
                    } else if (x == 0 || x == size.x - 1) {
                        printf("-");
                        break;
                    } else if (y == 0 || y == size.y - 1) {
                        printf("|");
                        break;
                    }

                    char l_wall = (char) (map[x][y - 1] == WALL);
                    char r_wall = (char) (map[x][y + 1] == WALL);
                    char u_wall = (char) (map[x - 1][y] == WALL);
                    char d_wall = (char) (map[x + 1][y] == WALL);
                    if (l_wall && r_wall && !u_wall && !d_wall) {
                        printf("-");
                        break;
                    } else if (u_wall && d_wall && !l_wall && !r_wall) {
                        printf("|");
                        break;
                    } else {
                        printf("+");
                        break;
                    }
                default:
                    printf("I can't analyse this char '%d'", map[x][y]);
                    break;
            }
        }
        printf("\n");
    }
}

char move(char** map,/*Place pc,*/ Place delta, unsigned * score) {
    Place new_pc = {0,0};
    Place pc = player;
    unsigned i;
    new_pc.x = pc.x+delta.x;new_pc.y=pc.y+delta.y;
    if(map[new_pc.x][new_pc.y]==WALL)return 0;//新位置是墙
    if(map[new_pc.x][new_pc.y]==BOX||map[new_pc.x][new_pc.y]==FILL){//新位置是箱子
        switch (map[new_pc.x+delta.x][new_pc.y+delta.y]) {
            case BOX:
            case WALL:
            case FILL:return 0;
            default:break;
        }
        //移出箱子
        //如果箱子已在目标点，则将目标点标记为false
        for(i=0;i<box_num;i++){
            if(goals[i].x==new_pc.x&&goals[i].y==new_pc.y){
                bgoals[i] = false;
                map[new_pc.x][new_pc.y]=GOAL;
                break;
            }
        }
        //移动箱子
        for(i=0;i<box_num;i++){
            if(goals[i].x==new_pc.x+delta.x&&goals[i].y==new_pc.y+delta.y){
                bgoals[i] = true;
                map[new_pc.x+delta.x][new_pc.y+delta.y]=FILL;
                break;
            }
        }
        if(i==box_num)map[new_pc.x+delta.x][new_pc.y+delta.y]=BOX;
    }
    //新位置是路或目标点(箱子已移动)
    //如果玩家位置是目标点就把目标点补全
    for(i=0;i<box_num;i++)if(goals[i].x==pc.x&&goals[i].y==pc.y){map[pc.x][pc.y]=GOAL;break;}
    if(i==box_num)map[pc.x][pc.y]=PATH;
    map[new_pc.x][new_pc.y]=PLAYER;
    player.x = new_pc.x;
    player.y = new_pc.y;

    //更新分数
    if(score!=NULL)*score += 1;

    for(i=0;i<box_num;i++)if(!bgoals[i])return 1;
    return 2;//玩家获胜
}

char** read_map(char* filename){
    FILE* pfile = fopen(filename, "rb");
    if (pfile == NULL) {fprintf(stderr, "ERROR: cannot open file '%s'\n", filename);return NULL;}
    fseek(pfile, 0L, SEEK_SET);
    unsigned X, Y;
    unsigned res = fread(&X, sizeof(unsigned), 1, pfile);
    res += fread(&Y, sizeof(unsigned), 1, pfile);
    if (res != 2) {fprintf(stderr, "ERROR: cannot read file '%s'\n", filename);return NULL;}
    MAP_SIZE.x = X;
    MAP_SIZE.y = Y;
    char** map = (char**)malloc(sizeof(char*) * X);
    for(unsigned i = 0; i < X; i++)map[i] = (char*)malloc(sizeof(char) * Y);
    for(unsigned i = 0; i < X; i++)for(unsigned j = 0; j < Y; j++)fread(&map[i][j], sizeof(char), 1, pfile);
    fclose(pfile);
    pfile = NULL;
    return map;
}

Place read_size(char* filename){
    Place blank_place = {0,0};
    FILE* pfile = fopen(filename, "rb");
    if (pfile == NULL) {fprintf(stderr, "ERROR: cannot open file '%s'\n", filename);return blank_place;}
    fseek(pfile, 0L, SEEK_SET);
    unsigned X, Y;
    unsigned res = fread(&X, sizeof(unsigned), 1, pfile);
    res += fread(&Y, sizeof(unsigned), 1, pfile);
    if (res != 2) {fprintf(stderr, "ERROR: cannot read file '%s'\n", filename);return blank_place;}
    return MAP_SIZE;
}

void destroy_map(char** map){
    unsigned i;
    if(map!=NULL){
        for(i = 0; i < MAP_SIZE.x; i++)free(map[i]);
        free(map);
    }
    for(i=0;i<box_num;i++)bgoals[i]=0;
    box_num=0;
    player=MAP_SIZE=(Place){0,0};
}


void write_score(char* filename, NameScore* name) {
    ;
}
NameScore* read_score(char* filename, unsigned length) {
    ;
}
