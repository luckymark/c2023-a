//
// Created by 10275 on 2023/10/

#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>

int chessboard[15][15];

int drawline(int a , int b , int c , int d)
{
    setlinestyle(PS_SOLID,3);
    setlinecolor(RED);
    line(a,b,c,d);
}

int check(int chessboard[15][15]) {
    int i, j, f = 0;
    for (i = 2; i < 13; i++) {
        for (j = 0; j < 15; j++) {
            if (chessboard[i - 2][j] + chessboard[i - 1][j] + chessboard[i][j] + chessboard[i + 1][j] +
                chessboard[i + 2][j] == 5) {
                f = 1;
                drawline(30 + j * 40, -50 + i * 40, 30 + j * 40, 110 + i * 40);
            }
        }
    }
    for (i = 0; i < 15; i++) {
        for (j = 2; j < 13; j++) {
            if (chessboard[i][j - 2] + chessboard[i][j - 1] + chessboard[i][j] + chessboard[i][j + 1] +
                chessboard[i][j + 2] == 5) {
                f = 1;
                drawline(-50 + j * 40, 30 + i * 40, 110 + j * 40, 30 + i * 40);
            }
        }
    }
    for (i = 2; i < 13; i++) {
        for (j = 2; j < 13; j++) {
            if (chessboard[i - 2][j - 2] + chessboard[i - 1][j - 1] + chessboard[i][j] + chessboard[i + 1][j + 1] +
                chessboard[i + 2][j + 2] == 5) {
                f = 1;
                drawline(-50 + j * 40, -50 + i * 40, 110 + j * 40, 110 + i * 40);
            }
        }
    }
    for (i = 2; i < 13; i++) {
        for (j = 2; j < 13; j++) {
            if (chessboard[i + 2][j - 2] + chessboard[i + 1][j - 1] + chessboard[i][j] + chessboard[i - 1][j + 1] +
                chessboard[i - 2][j + 2] == 5) {
                f = 1;
                drawline(-50 + j * 40, 110 + i * 40, 110 + j * 40, -50 + i * 40);
            }
        }
    }
    return f;
}


int check_AI(int chessboard[15][15])
{
    int i,j,f = 0;
    for (i = 2; i < 13; i++)
    {
        for (j = 0; j < 15; j++)
        {
            if (chessboard[i - 2][j] + chessboard[i - 1][j] + chessboard[i][j] + chessboard[i + 1][j] + chessboard[i + 2][j] == -5)
            {
                f = -1;
                drawline(30 + j * 40, -50 + i * 40, 30 + j * 40, 110 + i * 40);
            }
        }
    }
    for (i = 0; i < 15; i++)
    {
        for (j = 2; j < 13; j++)
        {
            if (chessboard[i][j-2] + chessboard[i][j-1] + chessboard[i][j] + chessboard[i][j+1] + chessboard[i][j+2] == -5)
            {
                f = -1;
                drawline(-50 + j * 40, 30 + i * 40, 110 + j * 40, 30 + i * 40);
            }
        }
    }
    for (i = 2; i < 13; i++)
    {
        for (j = 2; j < 13; j++)
        {
            if (chessboard[i-2][j-2] + chessboard[i-1][j-1] + chessboard[i][j] + chessboard[i+1][j+1] + chessboard[i+2][j+2] == -5)
            {
                f = -1;
                drawline(-50 + j * 40, -50 + i * 40, 110 + j * 40, -50 + i * 40);
            }
        }
    }
    for (i = 2; i < 13; i++)
    {
        for (j = 2; j < 13; j++)
        {
            if (chessboard[i+2][j-2] + chessboard[i+1][j-1] + chessboard[i][j] + chessboard[i-1][j+1] + chessboard[i-2][j+2] == -5)
            {
                f = -1;
                drawline(-50 + j * 40, 110 + i * 40, 110 + j * 40, 110 + i * 40);
            }
        }
    }
    return f;
}


void create()
{
    int i;
    initgraph(620,640,1);
    setbkcolor(RGB(230,200,170));
    cleardevice();
    setlinecolor(BLACK);
    for (i = 0; i < 16; i++)
    {
        line(10 + i * 40,10,10 + i * 40,610);
        line(10,10 + i * 40,610,10 + i * 40);
    }
}

void draw(int num)
{
    int i = 30 + num / 100 * 40;
    int j = 30 + num % 100 * 40;
    setfillcolor(WHITE);
    solidcircle(i , j , 16);
}

void draw_AI(int num)
{
    int p = 30 + num / 100 * 40;
    int q = 30 + num % 100 * 40;
    setfillcolor(BLACK);
    solidcircle(p , q , 16);
}

void action()
{
    int f = 0,i,j;
    MOUSEMSG msg;
    while (f == 0)
    {
        msg = GetMouseMsg();
        if (msg.mkLButton && msg.x > 10 && msg.x < 610 && msg.y > 10 && msg.y < 610)
        {
            i = (msg.x - 10) / 40;
            j = (msg.y - 10) / 40;
            if (chessboard[j][i] == 0)
            {
                chessboard[j][i] = 1;
                f = 1;
            }
        }
    }
    draw(i * 100 + j);
}
int distance(int a , int b , int c , int d) {
    if (a == c && (b + 1 == d || b - 1 == d)) {
        return 1;
    } else if (b == d && (a + 1 == c || c + 1 == a)) {
        return 1;
    } else {
        return 2;
    }
}

int use_position_find_help(int chessboard[15][15] , int i , int j , int f , int i0 , int j0) {
    if (chessboard[i][j] != 0 || f == 1 || f == 2) {
        return distance(i, j, i0, j0);
    } else {
        return 0;
    }
}
int use_position_find(int chessboard[15][15] , int i , int j) {
    int f = 0;
    if (i >= 1) {
        f = use_position_find_help(chessboard, i - 1, j, f, i, j);
    }
    if (i >= 2) {
        f = use_position_find_help(chessboard, i - 2, j, f, i, j);
    }
    if (i <= 13) {
        f = use_position_find_help(chessboard, i + 1, j, f, i, j);
    }
    if (i <= 12) {
        f = use_position_find_help(chessboard, i + 2, j, f, i, j);
    }


    if (j >= 1) {
        f = use_position_find_help(chessboard, i, j - 1, f, i, j);
    }
    if (j >= 2) {
        f = use_position_find_help(chessboard, i, j - 2, f, i, j);
    }
    if (j <= 13) {
        f = use_position_find_help(chessboard, i, j + 1, f, i, j);
    }
    if (j <= 12) {
        f = use_position_find_help(chessboard, i, j + 2, f, i, j);
    }

    if (i >= 1 && j >= 1) {
        f = use_position_find_help(chessboard, i - 1, j - 1, f, i, j);
    }
    if (i >= 1 && j <= 13) {
        f = use_position_find_help(chessboard, i - 1, j + 1, f, i, j);
    }
    if (i <= 13 && j >= 1) {
        f = use_position_find_help(chessboard, i + 1, j - 1, f, i, j);
    }
    if (i <= 13 && j <= 13) {
        f = use_position_find_help(chessboard, i + 1, j + 1, f, i, j);
    }

    if (chessboard[i][j] != 0) {
        f = 0;
    }
    return f;
}


int score_fomular(int n , int list[15] , int target)
{
    int j;
    int flag = 0;
    int num=0;
    for (j = 0; j < n - 1; j++)
    {
        if(flag == 0) {
            if (j <= n - 6 && list[j] + list[j + 1] + list[j + 2] + list[j + 3] + list[j + 4] + list[j + 5]== 6 * target) {
                num += 500000; flag = 6;
            }
            else if (j <= n - 5 && list[j] + list[j + 1] + list[j + 2] + list[j + 3] + list[j + 4] == 5 * target) {
                num += 100000; flag = 5;
            } else if (j <= n - 4 && list[j] + list[j + 1] + list[j + 2] + list[j + 3] == 4 * target &&
                       j >= 1 && j <= n - 5 && list[j - 1] == 0 && list[j + 4] == 0) {
                num += 50000; flag = 4;
            } else if (j <= n - 4 && list[j] + list[j + 1] + list[j + 2] + list[j + 3] == 4 * target &&
                       ((j == 0 && list[j + 4] == 0) || (j == n - 4 && list[j - 1] == 0))) {
                num += 5000; flag = 4;
            } else if (j <= n - 4 && list[j] + list[j + 1] + list[j + 2] + list[j + 3] == 4 * target &&
                       j >= 1 && j <= n - 5 && (list[j - 1] + list[j + 4] == -target)) {
                num += 5000; flag = 4;
            } else if (j <= n - 5 && list[j] == target && list[j + 4] == target &&
                       list[j] + list[j + 1] + list[j + 2] + list[j + 3] + list[j + 4] == 4 * target) {
                num += 5000; flag = 5;
            } else if (j <= n - 3 && list[j] + list[j + 1] + list[j + 2] == 3 * target &&
                       ((j == 0 && list[j + 3] == 0 && list[j + 4] == 0) ||
                        (j == n - 3 && list[j - 1] == 0 && list[j - 2] == 0))) {
                num += 100; flag = 3;
            } else if (j <= n - 3 && list[j] + list[j + 1] + list[j + 2] == 3 * target &&
                       j >= 1 && j <= n - 4 && (list[j - 1] + list[j + 3] == -target)) {
                num += 100; flag = 3;
            } else if (j <= n - 3 && list[j] + list[j + 1] + list[j + 2] == 3 * target &&
                       j >= 1 && j <= n - 4 && list[j - 1] == 0 && list[j + 3] == 0) {
                num += 1000; flag = 3;
            } else if (j <= n - 4 && list[j] == target && list[j + 3] == target &&
                       list[j + 1] + list[j + 2] == target &&
                       ((j == n - 4 && list[j - 1] == 0) || (j == 0 && list[j + 4] == 0))) {
                num += 100; flag = 4;
            } else if (j <= n - 4 && list[j] == target && list[j + 3] == target &&
                       list[j + 1] + list[j + 2] == target && j <= n - 5 && j >= 1 &&
                       list[j - 1] + list[j + 4] == -target) {
                num += 100; flag = 4;
            } else if (j <= n - 4 && list[j] == target && list[j + 3] == target &&
                       list[j + 1] + list[j + 2] == target && j <= n - 5 && j >= 1 && list[j - 1] == 0 &&
                       list[j + 4] == 0) {
                num += 1000; flag = 4;
            } else if (j <= n - 5 && list[j] + list[j + 4] == 2 * target &&
                       list[j + 1] * list[j + 2] * list[j + 3] == 0 &&
                       list[j + 1] + list[j + 2] + list[j + 3] == target) {
                num += 100; flag = 4;
            } else if (j < n - 2 && j > 0 && list[j] + list[j + 1] == 2 * target && list[j - 1] == 0 &&
                       list[j + 2] == 0) {
                num += 10; flag = 2;
            } else if (j < n - 3 && j > 0 && list[j] + list[j + 2] == 2 * target && list[j + 1] == 0 &&
                       list[j - 1] == 0 && list[j + 3] == 0) {
                num += 10; flag = 2;
            } else if (j == n - 2 && list[j] + list[j + 1] == 2 * target && list[j - 1] == 0 && list[j - 2] == 0) {
                num += 1; flag = 2;
            } else if (j >= 1 && j <= n - 2 && list[j - 1] == 0 && list[j + 1] == 0 && list[j] == target) {
                num += 1; flag = 1;
            }
        }
        if(flag > 0)
        {
            flag--;
        }
    }
    return num;
}

int score_count(int chessboard[15][15] , int id)
{
    int list_temporary[15];
    int i,j;
    int score = 0;
    for (i = 0; i < 15; i++)
    {
        for (j = 0; j < 15; j++)
        {
            list_temporary[j] = chessboard[i][j];
        }
        score += score_fomular(15 , list_temporary , id);
    }
    for (i = 0; i < 15; i++)
    {
        for (j = 0; j < 15; j++)
        {
            list_temporary[j] = chessboard[j][i];
        }
        score += score_fomular(15 , list_temporary , id);
    }
    for (i = 4; i < 15; i++)
    {
        for (j = 0; j < i + 1; j++)
        {
            list_temporary[j] = chessboard[i - j][j];
        }
        score += score_fomular(i + 1 , list_temporary , id);
    }
    for (i = 13; i > 3; i--)
    {
        for (j = 0; j < i + 1; j++)
        {
            list_temporary[j] = chessboard[14 - j][j + 14 - i];
        }
        score += score_fomular(i + 1 , list_temporary , id);
    }
    for (i = 4; i < 15; i++)
    {
        for (j = 0; j < i + 1; j++)
        {
            list_temporary[j] = chessboard[14 - i + j][j];
        }
        score += score_fomular(i + 1 , list_temporary , id);
    }
    for (i = 13; i > 3; i--)
    {
        for (j = 0; j < i + 1; j++)
        {
            list_temporary[j] = chessboard[j][14 - i + j];
        }
        score += score_fomular(i + 1 , list_temporary , id);
    }
    return score;
}

int score_count_real(int cheaaboard[15][15] , int s)
{
    return score_count(chessboard , s) - score_count(chessboard , -s);
}

int list_find_max(int list_input[15][15]) {
    int i, j, temp, f=1;
    int list_compare_help[15];
    int list[15][15];
    for (i = 0; i < 15; i++) {
        for (j = 0; j < 15; j++) {
            list[i][j] = list_input[i][j];
        }
    }
    for (i = 0; i < 15; i++) {
        for (j = 0; j < 14; j++) {
            if (list[i][j] > list[i][j + 1]) {
                temp = list[i][j];
                list[i][j] = list[i][j + 1];
                list[i][j + 1] = temp;
            }
        }
        list_compare_help[i] = list[i][14];
    }
    for (i = 0; i < 14; i++) {
        if (list_compare_help[i] > list_compare_help[i + 1]) {
            temp = list_compare_help[i];
            list_compare_help[i] = list_compare_help[i + 1];
            list_compare_help[i + 1] = temp;
        }
    }
    if (list_compare_help[14] < 0)
    {
        f = -1;
    }
    for (i = 0; i < 15; i++) {
        for (j = 0; j < 15; j++) {
            if (list_input[i][j] == list_compare_help[14]) {
                return f * (abs(list_compare_help[14]) * 10000 + j * 100 + i);
            }
        }
    }
}

int list_find_min(int list_input[15][15]) {
    int i, j, temp ,f=1;
    int list_compare_help[15];
    int list[15][15];
    for (i = 0; i < 15; i++) {
        for (j = 0; j < 15; j++) {
            list[i][j] = list_input[i][j];
        }
    }
    for (i = 0; i < 15; i++) {
        for (j = 0; j < 14; j++) {
            if (list[i][j] < list[i][j + 1]) {
                temp = list[i][j];
                list[i][j] = list[i][j + 1];
                list[i][j + 1] = temp;
            }
        }
        list_compare_help[i] = list[i][14];
    }
    for (i = 0; i < 14; i++) {
        if (list_compare_help[i] < list_compare_help[i + 1]) {
            temp = list_compare_help[i];
            list_compare_help[i] = list_compare_help[i + 1];
            list_compare_help[i + 1] = temp;
        }
    }
    if (list_compare_help[14] < 0)
    {
        f = -1;
    }
    for (i = 0; i < 15; i++) {
        for (j = 0; j < 15; j++) {
            if (list_input[i][j] == list_compare_help[14]) {
                return f * (abs(list_compare_help[14]) * 10000 + j * 100 + i);
            }
        }
    }
}


void action_AI()
{
    int i,j,k,l,p,q,k1,l1,p1,q1;
    int i1,j1,i2,j2;
    int f,f1,f2;
    int s1=0,s2;
    int temp , f_line;
    int list_use_position[225];
    int list_use_position1[225];
    int list_use_position2[15][15];
    int list_use_position3[15][15];
    int list_score[15][15];
    int list_score1[15][15];
    int list_score2[15][15];
    int list_score0[15][15];
    int list_score_another1[15][15];
    int max = -999999, min = 999999, max1 = -999999;
    int result;


    for (i = 0; i < 15; i++)
    {
        for (j = 0; j < 15; j++)
        {
            list_use_position[i * 15 + j] = use_position_find(chessboard , i , j) * 10000 + i * 100 + j;
        }
    }
    for (i = 224; i > 0; i--)
    {
        f_line = 0;
        for (j = i; j > 0; j--)
        {
            if ((list_use_position[j] >= 10000 && list_use_position[j] < list_use_position[j - 1]) || (list_use_position[j] >= 10000 && list_use_position[j - 1] < 10000))
            {
                temp = list_use_position[j];
                list_use_position[j] = list_use_position[j - 1];
                list_use_position[j - 1] = temp;
                f_line = 1;
            }
        }
        if(f_line == 0)
        {
            break;
        }
    }
    while (list_use_position[s1] >= 10000)
    {

            f = 1;
            min = 999999;
            l = list_use_position[s1] % 10000 / 100;
            k = list_use_position[s1] % 100;
            if(chessboard[l][k] == 0)
            {
                chessboard[l][k] = -1;

                for (i = 0; i < 15; i++) {
                    for (j = 0; j < 15; j++) {
                        list_use_position1[i * 15 + j] = use_position_find(chessboard, i, j) * 10000 + i * 100 + j;
                    }
                }
                for (i = 224; i > 0; i--) {
                    f_line = 0;
                    for (j = i; j > 0; j--) {
                        if (list_use_position1[j] > list_use_position1[j - 1]) {
                            temp = list_use_position1[j];
                            list_use_position1[j] = list_use_position1[j - 1];
                            list_use_position1[j - 1] = temp;
                            f_line = 1;
                        }
                    }
                    if (f_line == 0) {
                        break;
                    }
                }
                s2 = 0;
                while (list_use_position1[s2] >= 10000)
                {
                        f1 = 1;
                        max1 = -999999;
                        p = list_use_position1[s2] % 10000 / 100;
                        q = list_use_position1[s2] % 100;
                        if(chessboard[p][q] == 0)
                        {
                            chessboard[p][q] = 1;

                            for (i1 = 0; i1 < 15; i1++)
                            {
                                for (j1 = 0; j1 < 15; j1++)
                                {
                                    list_use_position2[i1][j1] = use_position_find(chessboard , i1 , j1);
                                }
                            }



                            for (l1 = 0; l1 < 15; l1++) {
                                for (k1 = 0; k1 < 15; k1++) {
                                    f2 = 1;
                                    if (chessboard[l1][k1] == 0 && list_use_position2[l1][k1] != 0) {
                                        chessboard[l1][k1] = -1;

                                        for (i2 = 0; i2 < 15; i2++) {
                                            for (j2 = 0; j2 < 15; j2++) {
                                                list_use_position3[i2][j2] = use_position_find(chessboard, i2, j2);
                                            }
                                        }

                                        for (p1 = 0; p1 < 15; p1++) {
                                            for (q1 = 0; q1 < 15; q1++) {
                                                if (chessboard[p1][q1] == 0 && list_use_position3[p1][q1] != 0) {
                                                    chessboard[p1][q1] = 1;
                                                    list_score0[p1][q1] = score_count_real(chessboard, -1);
                                                    chessboard[p1][q1] = 0;
                                                } else {
                                                    list_score0[p1][q1] = 1000000;
                                                }
                                                if (list_score0[p1][q1] < max1) {
                                                    f2 = 0;
                                                }
                                                if (f2 == 0) break;
                                            }
                                            if (f2 == 0) break;
                                        }
                                        list_score1[l1][k1] = abs(list_find_min(list_score0)) / 10000;
                                        if (list_find_min(list_score0) < 0) {
                                            list_score1[l1][k1] *= -1;
                                        }
                                        chessboard[l1][k1] = 0;
                                        if (list_score1[l1][k1] > max1) {
                                            max1 = list_score1[l1][k1];
                                        }
                                        if (list_score1[l1][k1] > min) {
                                            f1 = 0;
                                        }
                                    } else {
                                        list_score1[l1][k1] = -1000000;
                                    }
                                    if (f1 == 0) break;
                                }
                                if (f1 == 0) break;
                            }
                            list_score2[p][q] = abs(list_find_max(list_score1))/10000;
                            if (list_find_max(list_score1) < 0) {
                                list_score2[p][q] *= -1;
                            }
                            chessboard[p][q] = 0;
                            if (list_score2[p][q] < min) {
                                min = list_score2[p][q];
                            }
                            if (list_score2[p][q] < max) {
                                f = 0;
                            }





                        }
                        else
                        {
                            list_score2[p][q] = 1000000;
                        }
                    s2++;
                    if (f == 0) break;
                }
                while (s2 < 225)
                {
                    list_score2[list_use_position1[s2] % 10000 / 100][list_use_position1[s2] % 100] = 1000000;
                    s2++;
                }
                list_score[l][k] = abs(list_find_min(list_score2))/10000;
                if(list_find_min(list_score2) < 0)
                {
                    list_score[l][k] *= -1;
                }
                chessboard[l][k] = 0;

                if (list_score[l][k] > max)
                {
                    max = list_score[l][k];
                }
            }
            else
            {
                list_score[l][k] = -10000;
            }
        s1++;
    }
    while (s1 < 225)
    {
        list_score[list_use_position[s1] % 10000 / 100][list_use_position[s1] % 100] = -10000;
        s1++;
    }
    result = abs(list_find_max(list_score));
    chessboard[result % 100][result / 100 % 100] = -1;
    draw_AI(result % 10000);
}





int main()
{
    int i,j;
    for (i = 0; i < 15; i++)
    {
        for(j = 0; j < 15; j++)
        {
            chessboard[i][j] = 0;
        }
    }
    create();
    int win = 0;
    while (win == 0)
    {
        action();
        win = check(chessboard);
        if (win != 0)
        {
            break;
        }
        action_AI();
        win = check_AI(chessboard);
    }
    printf("%d",win);
    if (win == 1)
    {
        wchar_t print[50] = L"player win !";
        settextcolor(BLACK);
        outtextxy(260,630,print[50]);
    }
    else
    {
        wchar_t print[50] = L"AI win !";
        settextcolor(BLACK);
        outtextxy(260,630,print[50]);
    }
    system("pause");
    return 0;
}