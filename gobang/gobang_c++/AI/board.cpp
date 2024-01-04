//
// Created by ycm on 2023/12/8.
//

#include <algorithm>
#include "board.h"

Logger boardLogger("Board");

template <typename T> T board::abs(T x){
    return x>0?x:-x;
}

double board::fixScore(double score){
    if(score <= Score::FOUR && score >= Score::BLOCKED_FOUR) {
        if (score >= Score::BLOCKED_FOUR && score < Score::BLOCKED_FOUR + Score::THREE) {
            return Score::THREE;
        } else if (score >= Score::BLOCKED_FOUR + Score::THREE && score < Score::BLOCKED_FOUR * 2) {
            return Score::FOUR;
        } else {
            return Score::FOUR * 2;
        }
    }
    return score;
}

bool board::starTo(const Place &point, const std::list<Place> &points/*=std::vector<Place>{}*/){
    if(points.empty()){
        return false;
    }
    for(auto & p2 : points){ // NOLINT(*-use-anyofallof)
        if(abs(point.x - p2.x) > 4 || abs(point.y - p2.y) > 4){
            return false;
        }if(point.x != p2.x && point.y != p2.y && abs(point.x - p2.x) != abs(point.y - p2.y)){
            return false;
        }
    }
    return true;
}

Board::Board():map{}, comScore{}, humScore{}, comMaxScore(0), humMaxScore(0), turn(0), allSteps(), currentSteps(), scoreCache{} {
    boardLogger.warn("init board");
    for(auto & i : this->map)for(auto & j : i)j = Role::NONE;
    for(auto & i: this->comScore)for(auto & j : i)j = 0;
    for(auto & i: this->humScore)for(auto & j : i)j = 0;
    this->comMaxScore = this->humMaxScore = 0;
    this->turn = 0;

    this->allSteps.clear();
    this->currentSteps.clear();
    for(auto & i : this->scoreCache)for(auto & j : i)for(auto & k : j)for(auto & l : k)l = 0;

    boardLogger.debug("init board score");
    for(int i=0;i<Board::X;i++)for(int j=0;j<Board::Y;j++){
        switch(this->map[i][j]) {
            case Role::NONE:if(this->hasNeighbor(i, j, 2, 2)){
                this->comScore[i][j] = scorePoint(*this, i, j, Role::COMPUTER);
                this->humScore[i][j] = scorePoint(*this, i, j, Role::HUMAN);
                }break;
            case Role::COMPUTER:this->comScore[i][j] = scorePoint(*this, i, j, Role::COMPUTER);
                this->humScore[i][j] = 0;
                break;
            case Role::HUMAN:this->comScore[i][j] = 0;
                this->humScore[i][j] = scorePoint(*this, i, j, Role::HUMAN);
                break;
            default:break;
    }}
}

Board::Board(const Board &board) {

}

Board::~Board() {
    std::destroy(this->allSteps.begin(), this->allSteps.end());
    std::destroy(this->currentSteps.begin(), this->currentSteps.end());
}

Board &Board::operator=(const Board &board) {return *this;}

std::string Board::toString() {
    std::string str;
    str += " ";
    for(char i='A'; i<'A'+Board::X; i++) {
        str += " ";
        str += i;
    }
    str += "\n";
//    int i = 0,j;
    for(int i=0;i<Board::X;i++){
        if(i<10)str+="0";
        str+=std::to_string(i);
        for(int j=0;j<Board::Y;j++){
            switch(this->map[i][j]){
                case Role::NONE:str+=" ";break;
                case Role::COMPUTER:str+="X";break;
                case Role::HUMAN:str+="O";break;
                default:break;
            }
            if(j<Board::Y-1)str+=" ";
        }str+="\n";
    }return str;
}

void Board::updateScore(Place &place) {
    boardLogger.debug(std::string("update score of place(")+std::to_string(place.x)+", "+std::to_string(place.y)+")");
    int radius = 4;

    for(int i=-radius; i<=radius; i++){
        if(place.y+i<0)continue;
        if(place.y+i>=Board::Y)break;
        this->update(place.x, place.y+i, 0);
    }

    for(int i=-radius; i<=radius; i++){
        if(place.x+i<0)continue;
        if(place.x+i>=Board::X)break;
        this->update(place.x+i, place.y, 1);
    }

    for(int i=-radius; i<=radius; i++){
        if(place.x+i<0 || place.y+i<0)continue;
        if(place.x+i>=Board::X || place.y+i>=Board::Y)break;
        this->update(place.x+i, place.y+i, 2);
    }

    for(int i=-radius; i<=radius; i++){
        if(place.x+i<0 || place.y-i<0)continue;
        if(place.x+i>=Board::X || place.y-i>=Board::Y)break;
        this->update(place.x+i, place.y-i, 3);
    }
}

bool Board::put(Place &place, Role role, bool log/*=false*/) {
    if(log)boardLogger.debug(std::string("role ")+(role==Role::COMPUTER?"Computer":(role==Role::HUMAN?"Human":"None"))+"try to put chess at");
    int x=place.x, y=place.y;
    place.role = role;
    if(this->map[x][y]!=Role::NONE){
        boardLogger.error("place is not blank");
        return false;
    }
    this->map[x][y] = role;

    this->updateScore(place);
    this->allSteps.push_back(place);
    this->currentSteps.push_back(place);
    this->turn++;
    if(log)boardLogger.info(std::string("current turn is ")+std::to_string(this->turn));
    return true;
}

bool Board::remove(Place &place, bool log) {
    if(log)boardLogger.info(std::string("remove chess at ")+place.toString());
    int x=place.x, y=place.y;
    if(this->map[x][y]!=Role::NONE){
        this->updateScore(place);
        this->currentSteps.pop_back();
        this->allSteps.pop_back();
        this->turn--;
        this->map[x][y] = Role::NONE;
        return true;
    }else return false;
}

bool Board::hasNeighbor(int px, int py, int distance, int count) {
    boardLogger.debug("hasNeighbor");
    int startX = px - distance, endX = px + distance, startY = py - distance, endY = py + distance;
    for(int i=startX;i<=endX;i++) {
        if(i<0 || i>=Board::X)continue;
        for (int j=startY; j <= endY; j++) {
            if(j>=0 && j<Board::Y && (i != px || j != py) && this->map[i][j] != Role::NONE){
                count--;
                if(count <= 0)return true;
            }
        }
    }return false;
}

void Board::update(int x, int y, int updateDir) {
    Role role = this->map[x][y];
    if(role != Role::HUMAN){
        this->comScore[x][y] = scorePoint(*this, x, y, Role::COMPUTER, updateDir);
    }else{
        this->comScore[x][y] = 0;
    }

    if(role != Role::COMPUTER){
        this->humScore[x][y] = scorePoint(*this, x, y, Role::HUMAN, updateDir);
    }else{
        this->humScore[x][y] = 0;
    }
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "Simplify"
std::list<Place> &Board::generator(Role role, bool onlyThrees/*=false*/, bool starSpread/*=false*/, bool log/*=false*/){
    boardLogger.debug("get candidates");
    std::list<Place> fives, comFours, humFours, fours, comBlockedFours, humBlockedFours, blockedFours, comTwoThrees,
    humTwoThrees, comThrees, humThrees, comTwos, humTwos, twos, neighbors, attackPoints, defendPoints;
    auto &result = *(new std::list<Place>{});

    unsigned tmpNum;

    if (this->turn <= 0) {
        result.push_back(*(new Place{7, 7}));//TODO: 结构体初始化
        goto boardGeneratorReturn;
    }
    if(starSpread && config::star){
        for(auto it=this->currentSteps.end()-1;it>=this->currentSteps.begin();it-=2){
            if(role==Role::HUMAN && it->scoreCom >= Score::THREE || role == Role::COMPUTER && it->scoreHum >= Score::THREE){
                defendPoints.push_back(*it);
                break;
            }
        }

        for(auto it=this->currentSteps.end()-2;it>=this->currentSteps.begin();it-=2){
            if(role==Role::COMPUTER && it->scoreCom >= Score::THREE || role == Role::HUMAN && it->scoreHum >= Score::THREE){
                attackPoints.push_back(*it);
                break;
            }
        }

        if(attackPoints.empty()){
            attackPoints.push_back((this->currentSteps[0].role==role)?this->currentSteps[0]:this->currentSteps[1]);
        }
        if(defendPoints.empty()){
            defendPoints.push_back((this->currentSteps[0].role!=role)?this->currentSteps[0]:this->currentSteps[1]);
        }
    }

    for(int i=0;i<Board::X;i++){
        for(int j=0;j<Board::Y;j++){
            if(this->map[i][j] == Role::NONE){
                if(this->allSteps.size() < 6){
                    if(!this->hasNeighbor(i, j, 1, 1))continue;
                }else
                if(!this->hasNeighbor(i, j, 2, 2))continue;

            double scoreHum = this->humScore[i][j];
            double scoreCom = this->comScore[i][j];
            double scoreMax = scoreHum > scoreCom ? scoreHum : scoreCom;
            if(onlyThrees && scoreMax < Score::THREE)continue;

            auto p = new Place{i, j};//TODO: 结构体初始化
            p->scoreHum = scoreHum;
            p->scoreCom = scoreCom;
            p->score = scoreMax;
            p->role = role;

            if(starSpread && config::star){
                if(scoreMax < Score::FOUR && (scoreMax < Score::BLOCKED_FOUR || !board::starTo(this->currentSteps.back()) && !board::starTo(*p, attackPoints)) && !board::starTo(*p, defendPoints)){
                    delete p;
                    continue;
                }
            }

            if(scoreCom>=Score::FIVE || scoreHum>=Score::FIVE)fives.push_back(*p);
            else if(scoreCom>=Score::FOUR)comFours.push_back(*p);
            else if(scoreHum>=Score::FOUR)humFours.push_back(*p);
            else if(scoreCom>=Score::BLOCKED_FOUR)comBlockedFours.push_back(*p);
            else if(scoreHum>=Score::BLOCKED_FOUR)humBlockedFours.push_back(*p);
            else if(scoreCom>=Score::THREE*2)comTwoThrees.push_back(*p);
            else if(scoreHum>=Score::THREE*2)humTwoThrees.push_back(*p);
            else if(scoreCom>=Score::THREE)comThrees.push_back(*p);
            else if(scoreHum>=Score::THREE)humThrees.push_back(*p);
            else if(scoreCom>=Score::TWO)comTwos.push_front(*p);
            else if(scoreHum>=Score::TWO)humTwos.push_front(*p);
            else neighbors.push_back(*p);

            delete p;
            }
        }
    }

    if(!fives.empty()){
        if(log){
            boardLogger.info("generator: five");
        }
        result.swap(fives);
        goto boardGeneratorReturn;
    }

    if(role==Role::COMPUTER && !comFours.empty()){
        if(log){
            boardLogger.info("generator: computer has four");
        }
        result.swap(comFours);
        goto boardGeneratorReturn;
    }
    if(role==Role::HUMAN && !humFours.empty()){
        if(log){
            boardLogger.info("generator: human has four");
        }
        result.swap(humFours);
        goto boardGeneratorReturn;
    }

    // 对面活四冲四,自己无冲四,只考虑对面活四
    if(role==Role::COMPUTER && !humFours.empty() && !comBlockedFours.empty()){
        if(log){
            boardLogger.info("generator: computer hasn't four and human has");
        }
        result.swap(humFours);
        goto boardGeneratorReturn;
    }
    if(role==Role::HUMAN && !comFours.empty() &&!humBlockedFours.empty()){
        if(log){
            boardLogger.info("generator: human hasn't four and computer has");
        }
        result.swap(comFours);
        goto boardGeneratorReturn;
    }

    // 自己有活四,考虑活四冲四
    fours.swap(comFours);
    blockedFours.swap(comBlockedFours);
    // fours = comFours + humFours if role == COMPUTER else humFours + comFours
    fours.splice((role==Role::COMPUTER)?fours.end():fours.begin(), humFours);
    // blockedFours = comBlockedFours + humBlockedFours if role == COMPUTER else humBlockedFours + comBlockedFours
    blockedFours.splice((role==Role::COMPUTER)?blockedFours.end():blockedFours.begin(), humBlockedFours);
    if(!fours.empty()){
        result.swap(fours);
        result.splice(result.end(), blockedFours);
        goto boardGeneratorReturn;
    }

    if(role==Role::COMPUTER){
        result.splice(result.end(), comTwoThrees);
        result.splice(result.end(), humTwoThrees);
        result.splice(result.end(), comBlockedFours);
        result.splice(result.end(), humBlockedFours);
        result.splice(result.end(), comThrees);
        result.splice(result.end(), humThrees);
    }else{
        result.splice(result.end(), humTwoThrees);
        result.splice(result.end(), comTwoThrees);
        result.splice(result.end(), humBlockedFours);
        result.splice(result.end(), comBlockedFours);
        result.splice(result.end(), humThrees);
        result.splice(result.end(), comThrees);
    }

    // 双三特殊处理,其不一定比一个活三强
    if(!comTwoThrees.empty() || !humTwoThrees.empty()){
        if(log){
            boardLogger.info("generator: two threes");
        }
        goto boardGeneratorReturn;
    }

    // 只返回大于等于活三的棋
    if(onlyThrees){
        if(log){
            boardLogger.info("generator: only threes");
        }
        goto boardGeneratorReturn;
    }

    twos.swap(comTwos);
    // two = comTwos + humTwos if role == Role.COMPUTER else humTwos + comTwos
    twos.splice((role==Role::COMPUTER)?twos.end():twos.begin(), humTwos);

    twos.sort([](const Place &a, const Place &b){return a.score < b.score;});
    tmpNum = twos.size() + result.size();
    tmpNum = (tmpNum > config::candidatesLimit) ? config::candidatesLimit - result.size() : twos.size();
    for(auto &it: twos){
        if(tmpNum-- <= 0)break;
        result.push_back(it);
    }

    if(log){
        boardLogger.info("generator: twos");
    }
    boardGeneratorReturn:
    std::destroy(fives.begin(), fives.end());
    std::destroy(comFours.begin(), comFours.end());
    std::destroy(humFours.begin(), humFours.end());
    std::destroy(fours.begin(), fours.end());
    std::destroy(comBlockedFours.begin(), comBlockedFours.end());
    std::destroy(humBlockedFours.begin(), humBlockedFours.end());
    std::destroy(blockedFours.begin(), blockedFours.end());
    std::destroy(comTwoThrees.begin(), comTwoThrees.end());
    std::destroy(humTwoThrees.begin(), humTwoThrees.end());
    std::destroy(comThrees.begin(), comThrees.end());
    std::destroy(humThrees.begin(), humThrees.end());
    std::destroy(comTwos.begin(), comTwos.end());
    std::destroy(humTwos.begin(), humTwos.end());
    std::destroy(twos.begin(), twos.end());
    std::destroy(neighbors.begin(), neighbors.end());
    std::destroy(attackPoints.begin(), attackPoints.end());
    std::destroy(defendPoints.begin(), defendPoints.end());

    if(log){
        std::string logStr = "generator: ";
        for(auto &it: result){
            logStr += it.toString()+", ";
        }
        boardLogger.info(logStr);
    }
    return result;
}
#pragma clang diagnostic pop

double Board::evaluate(Role role){
    boardLogger.debug("evaluate");
    // TODO: 增加缓存

    this->comMaxScore = this->humMaxScore = 0;
    for(int i=0;i<Board::X;i++){
        for(int j=0;j<Board::Y;j++){
            switch(this->map[i][j]){
                case Role::COMPUTER:this->comMaxScore += board::fixScore(this->comScore[i][j]);
                    break;
                case Role::HUMAN:this->humMaxScore += board::fixScore(this->humScore[i][j]);
                    break;
                default:break;
            }
        }
    }

    double result = (2 * (int)role - 1) * (this->comMaxScore - this->humMaxScore * 10);// TODO: 调整玩家权重
    return result;
}

int Board::isFive(const Place &place, Role role){
    int count = 1, delta = place.y + 1;
    while(delta<Board::Y && this->map[place.x][delta] == role){
        count++;
        delta++;
    }
    delta = place.y - 1;
    while(delta>= 0 && this->map[place.x][delta] == role){
        count++;
        delta--;
    }
    if(count>=5)return 1;//横向

    count = 1;
    delta = place.x + 1;
    while(delta<Board::X && this->map[delta][place.y] == role){
        count++;
        delta++;
    }
    delta = place.x - 1;
    while(delta>= 0 && this->map[delta][place.y] == role){
        count++;
        delta--;
    }
    if(count>=5)return 2;//纵向

    count=1;
    delta=1;
    while(place.x+delta<Board::X && place.y+delta<Board::Y && this->map[place.x+delta][place.y+delta] == role){
        count++;
        delta++;
    }
    delta=1;
    while(place.x-delta>=0 && place.y-delta>=0 && this->map[place.x-delta][place.y-delta] == role){
        count++;
        delta++;
    }
    if(count>=5)return 3;//斜向

    count=1;
    delta=1;
    while(place.x+delta<Board::X && place.y-delta>=0 && this->map[place.x+delta][place.y-delta] == role){
        count++;
        delta++;
    }
    delta=1;
    while(place.x-delta>=0 && place.y+delta<Board::Y && this->map[place.x-delta][place.y+delta] == role){
        count++;
        delta++;
    }
    if(count>=5)return 4;//反斜向

    return 0;
}

Role Board::isWin(bool log/*=false*/){
    if(log){
        boardLogger.debug("check winner");
    }

    int d=0;
    Place *p;
    Role r = Role::NONE;
    for(int i=0;i<Board::X;i++){
        for(int j=0;j<Board::Y;j++){
            r = this->map[i][j];
            p = new Place{i, j};//TODO: 结构体初始化
            if(r!=Role::NONE){
                d = isFive(*p, r);
                if(d){
                    goto boardIsFiveReturn;
                }
            }
            delete p;
        }
    }
    boardIsFiveReturn:
    Role result = d?this->map[p->x][p->y]:Role::NONE;
    return result;
}