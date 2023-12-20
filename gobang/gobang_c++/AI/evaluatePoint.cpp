//
// Created by ycm on 2023/12/8.
//

#include "evaluatePoint.h"

Logger evaluatorLogger = Logger("BoardEvaluator");

double evaluateScore::countToScore(int count, int block, int empty/*=0*/) {
    if(empty <= 0){
        if(count>=5)return Score::FIVE;

        switch(block){
            case 0:
                switch(count){
                    case 1:return Score::ONE;
                    case 2:return Score::TWO;
                    case 3:return Score::THREE;
                    case 4:return Score::FOUR;
                    default:break;
            }break;
            case 1:
                switch (count) {
                    case 1:return Score::BLOCKED_ONE;
                    case 2:return Score::BLOCKED_TWO;
                    case 3:return Score::BLOCKED_THREE;
                    case 4:return Score::BLOCKED_FOUR;
                    default:break;
                }break;
            default:break;
        }
    }else if(empty == 1 || empty == count-1){
        if(count>=6)return Score::FIVE;

        switch(block){
            case 0:
                switch (count) {
                    case 2:return (double)Score::TWO/2;
                    case 3:return Score::THREE;
                    case 4:return Score::BLOCKED_FOUR;
                    case 5:return Score::FOUR;
                    default:break;
                }break;
            case 1:
                switch (count) {
                    case 2:return Score::BLOCKED_TWO;
                    case 3:return Score::BLOCKED_THREE;
                    case 4:case 5:return Score::BLOCKED_FOUR;
                    default:break;
                }break;
            default:break;
        }
    }else if(empty == 2 || empty == count-2){
        if(count>=7)return Score::FIVE;

        switch(block){
            case 0:
                switch (count) {
                    case 3:return Score::THREE;
                    case 4: case 5:return Score::BLOCKED_FOUR;
                    case 6:return Score::FOUR;
                    default:break;
                }break;
            case 1:
                switch (count) {
                    case 3:return Score::BLOCKED_THREE;
                    case 4: case 5: return Score::BLOCKED_FOUR;
                    case 6:return Score::FOUR;
                    default:break;
                }break;
            case 2:
                switch(count){
                    case 4: case 5: case 6:return Score::BLOCKED_FOUR;
                    default:break;
                }break;
            default:break;
            }
    }else if(empty == 3 || empty == count-3){
        if(count>=8)return Score::FIVE;

        switch (block) {
            case 0:
                switch(count){
                    case 4: case 5:return Score::THREE;
                    case 6:return Score::BLOCKED_FOUR;
                    case 7:return Score::FOUR;
                    default:break;
                }break;
            case 1:
                switch (count) {
                    case 4: case 5: case 6:return Score::BLOCKED_THREE;
                    case 7:return Score::FOUR;
                    default:break;
                }break;
            case 2:
                switch (count) {
                    case 4: case 5: case 6: case 7:return Score::BLOCKED_FOUR;
                    default:break;
                }break;
            default:break;
        }
    }else if(empty == 4 || empty == count-4){
        if(count>=9)return Score::FIVE;

        switch (block) {
            case 0:
                switch (count) {
                    case 5: case 6: case 7: case 8:return Score::FOUR;
                    default:break;
                }break;
            case 1:
                switch (count) {
                    case 4: case 5: case 6: case 7:return Score::BLOCKED_FOUR;
                    case 8:return Score::FOUR;
                    default:break;
                }break;
            case 2:
                switch (count) {
                    case 5: case 6: case 7: case 8:return Score::BLOCKED_FOUR;
                    default:break;
                }break;
            default:break;
        }
    }else if(empty == 5 || empty == count-5){
        return Score::FIVE;
    }

    return 0;
}

void evaluateScore::reset(int* count, int* block, int* empty, int* secondCount){
    *count = 1;
    *block = *secondCount = 0;
    *empty = -1;
}

double scorePoint(Board &board, int px, int py, Role role, int tmpDir/*=-1*/) {
    using namespace evaluateScore;
    if (!px && !py)evaluatorLogger.debug("scorePoint");
    double result = 0;
    int empty, count, block, secondCount, i;

    if (tmpDir < 0 || tmpDir == 0) {
        reset(&count, &block, &empty, &secondCount);

        for (i = py + 1; i < Board::Y; i++) {
            Role r = board.map[px][i];
            if (r == Role::NONE) {
                if (empty < 0 && i < Board::Y - 1 && board.map[px][i + 1] == role) {
                    empty = count;
                    continue;
                } else break;
            }
            if(r==role){
                count++;
                continue;
            }else{
                block++;
                break;
            }
        }
        if(i==Board::Y)block++;

        for(i=py-1;i>=0;i--){
            Role r = board.map[px][i];
            if(r==Role::NONE){
                if(empty<0 && i>0 && board.map[px][i-1]==role){
                    empty = 0;
                    continue;
                }else break;
            }
            if(r==role){
                secondCount++;
                if(empty>=0)empty++;
                continue;
            }else{
                block++;
                break;
            }
        }
        if(i==-1)block++;

        count += secondCount;
        board.scoreCache[(int)role][0][px][py] = countToScore(count, block, empty);
    }result += board.scoreCache[(int)role][0][px][py];

    if(tmpDir<0 || tmpDir==1){
        reset(&count, &block, &empty, &secondCount);

        for(i=px+1;i<Board::X;i++){
            Role r = board.map[i][py];
            if(r==Role::NONE){
                if(empty<0 && i<Board::X-1 && board.map[i+1][py]==role){
                    empty = count;
                    continue;
                }else break;
            }
            if(r==role){
                count++;
                continue;
            }else{
                block++;
                break;
            }
        }
        if(i==Board::X)block++;

        for(i=px-1;i>=0;i--){
            Role r = board.map[i][py];
            if(r==Role::NONE){
                if(empty<0 && i>0 && board.map[i-1][py]==role){
                    empty = 0;
                    continue;
                }else break;
            }
            if(r==role){
                secondCount++;
                if(empty>=0)empty++;
                continue;
            }else{
                block++;
                break;
            }
        }
        if(i==-1)block++;

        count += secondCount;
        board.scoreCache[(int)role][1][px][py] = countToScore(count, block, empty);
    }result += board.scoreCache[(int)role][1][px][py];

    if(tmpDir<0 || tmpDir==2){
        reset(&count, &block, &empty, &secondCount);
        for(i=1;i<Board::Y;i++){
            int tmpX= px + i, tmpY = py + i;
            if(tmpX >= Board::X || tmpY >= Board::Y) {
                block++;
                break;
            }
            Role r = board.map[tmpX][tmpY];
            if(r==Role::NONE){
                if(empty<0 && tmpX < Board::X - 1 && tmpY < Board::Y - 1 && board.map[tmpX + 1][tmpY + 1] == role){
                    empty = count;
                    continue;
                }else break;
            }
            if(r==role){
                count++;
                continue;
            }else{
                block++;
                break;
            }
        }if(i==Board::Y)block++;
        for(i=1;i<Board::Y;i++) {
            int tmpX = px - i, tmpY = py - i;
            if (tmpX < 0 || tmpY < 0) {
                block++;
                break;
            }
            Role r = board.map[tmpX][tmpY];
            if (r == Role::NONE) {
                if (empty < 0 && tmpX > 0 && tmpY > 0 && board.map[tmpX - 1][tmpY - 1] == role) {
                    empty = 0;
                    continue;
                } else break;
            }
            if (r == role) {
                secondCount++;
                if (empty >= 0)empty++;
                continue;
            }else{
                block++;
                break;
            }
        }if(i==Board::Y)block++;
        count += secondCount;
        board.scoreCache[(int)role][2][px][py] = countToScore(count, block, empty);
    }result += board.scoreCache[(int)role][2][px][py];

    if(tmpDir<0 || tmpDir==3) {
        reset(&count, &block, &empty, &secondCount);
        for (i = 1; i < Board::Y; i++) {
            int tmpX = px - i, tmpY = py + i;
            if (tmpX < 0 || tmpY >= Board::Y) {
                block++;
                break;
            }
            Role r = board.map[tmpX][tmpY];
            if (r == Role::NONE) {
                if (empty < 0 && tmpX > 0 && tmpY < Board::Y - 1 && board.map[tmpX - 1][tmpY + 1] == role) {
                    empty = count;
                    continue;
                } else break;
            }
            if (r == role) {
                count++;
                continue;
            } else {
                block++;
                break;
            }
        }
        if (i == Board::Y)block++;
        for (i = 1; i < Board::Y; i++) {
            int tmpX = px + i, tmpY = py - i;
            if (tmpX >= Board::X || tmpY < 0) {
                block++;
                break;
            }
            Role r = board.map[tmpX][tmpY];
            if (r == Role::NONE) {
                if (empty < 0 && tmpX < Board::X - 1 && tmpY > 0 && board.map[tmpX + 1][tmpY - 1] == role) {
                    empty = 0;
                    continue;
                } else break;
            }
            if (r == role) {
                secondCount++;
                if (empty >= 0)empty++;
                continue;
            } else {
                block++;
                break;
            }
        }
        if (i == Board::Y)block++;
        count += secondCount;
        board.scoreCache[(int)role][3][px][py] = countToScore(count, block, empty);
    }result += board.scoreCache[(int)role][3][px][py];

    return result;
}