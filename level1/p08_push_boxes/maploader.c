#include <stdio.h>

typedef struct {
    int x;
    int y;
}point;

void load(char* file, point *_player, int* _targets,point *_target, char (*_walls)[10]){
    FILE *map = fopen(file, "r");
    if (map) {
//fscanf(map,"%*[^:]:%d,%d\n%*[^:]:%d\n",&player.x,&player.y,&targets);
        point player;
        for (int i; (i = fgetc(map)) != ':';);
        fscanf(map, "%d,%d", &player.x, &player.y);

        int targets;
        for (char i; (i = fgetc(map)) != ':';);
        fscanf(map, "%d", &targets);

        point target[targets];
        for (char i; (i = fgetc(map)) != ':';);
        for (int count = 0; count < targets * 2;) {
            char i = fgetc(map);
            if (i == ',') {
                continue;
            }

            count++;

            if (count % 2) {
                fseek(map, -1, SEEK_CUR);
                fscanf(map, "%1d", &target[(count + 1) / 2 - 1].x);
            } else {
                fseek(map, -1, SEEK_CUR);
                fscanf(map, "%1d", &target[count / 2 - 1].y);
            }
        }

        int walls[10][10] = {0};
        int i = 0;
        int j = 0;

        for (char i; (i = fgetc(map)) != ':';);
        fgetc(map);
        for (char c; (c = fgetc(map)) != '.';) {
            if (c == '\n') {
                i++;
                j = 0;
            } else {
                fseek(map, -1, SEEK_CUR);
                fscanf(map, "%1d", &walls[i][j]);
                j++;
            }
        }

        /*printf("x:%d\n", player.x);
        printf("y:%d\n", player.y);
        printf("targets:%d\n", targets);

        for (int i = 0; i < targets; i++) {
            printf("target[%d].x = %d\n", i, target[i].x);
            printf("target[%d].y = %d\n", i, target[i].y);
        };

        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                printf("%d", walls[i][j]);
            }
            printf("\n");
        }*/

        *_player = player;
        *_targets = targets;
        _target = target;
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                *(_walls[i] + j) = walls[i][j];
            }
        }

        fclose(map);
    } else {
        printf("Fail");
    }
}