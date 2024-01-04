//
// Created by ycm on 2023/12/8.
//

#include "negamax.h"

Logger negamaxLogger("negamax");
const int MAX = INT_MAX;
const int MIN = INT_MIN;


Place deepenAll(Board &board, Role role/*=Role::COMPUTER*/, int depth/*=-1*/){
    if(depth==-1)depth = config::searchDepth;
    auto candidates = board.generator(role, false, false, true);
    Place result;

    std::string logMsg = "deepenAll(role=";
    logMsg += (role==Role::COMPUTER)?"Computer":((role==Role::HUMAN)?"Human":"None");
    logMsg += ", depth=";
    logMsg += std::to_string(depth);
    logMsg += ")";
    negamaxLogger.info(logMsg);
    if(candidates.size()<=1){
        result = candidates.front();
    }else{
        result = negamax::deepening(board, candidates, role, depth);
    }
    logMsg.clear();
    logMsg += "deepenAll result = ";
    logMsg += result.toString();
    logMsg += ", candidates = ";
    for(auto &candidate: candidates){
        logMsg += candidate.toString();
        logMsg += " ";
    }
    negamaxLogger.info(logMsg);

    std::destroy(candidates.begin(), candidates.end());
    return *(new Place(result));
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"
Leaf &negamax::_r(Board &board, int depth, double alpha, double beta, Role role, int step){
    double score = board.evaluate(role);
    Leaf &best = *(new Leaf{score, step});//此处best充当了leaf的角色,作为返回对象

    if(depth<=0 || comparer::greaterEqual(score, Score::FIVE) || comparer::lessEqual(score, -Score::FIVE)){
        //可以在此处加算杀(?)
        return best;
    }
    auto &candidates = board.generator(role, bool((board.turn > config::starSpread)?(step>1):(step>3)), step>1);
    if(candidates.empty()){
        std::destroy(candidates.begin(), candidates.end());
        delete &candidates;//析构candidates
        return best;
    }

    //初始化best
    best.score = MIN;
    best.step = step;

    for(auto &candidate: candidates){
        board.put(candidate, role);
        auto &v = _r(board, depth-1, -beta, -alpha, Role(1-(int)role), step+1);
        board.remove(candidate);
        v.score = -v.score;
        if(v.score>best.score){
            best = v;
        }
        alpha = (alpha>best.score)?alpha:best.score;
        if(comparer::greaterEqual(v.score, beta)){
            best = v;
            best.score = MAX - 1;
            best.abCut = true;
            delete &v;//析构v
            goto negamax_rReturn;
//            return best;
        }
        delete &v;//析构v
    }

    negamax_rReturn:
    std::destroy(candidates.begin(), candidates.end());
    delete &candidates;//析构candidates
    return best;
}
#pragma clang diagnostic pop

double negamax::negamax(Board &board, std::list<Place> &candidates, Role role, int depth, double alpha, double beta) {
    auto start = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();//记录开始时间(单位:毫秒)
//    std::chrono::milliseconds end;
    board.currentSteps.clear();

    for(auto &candidate: candidates){
        board.put(candidate, role);
        auto &v = _r(board, depth, -beta, -alpha, Role(1-(int)role), 1);
        v.score = -v.score;
        alpha = (alpha>v.score)?alpha:v.score;
        board.remove(candidate);
        // 我欲在此修改candidates,但成没成功就不知道了
        candidate.v = nullptr;
        candidate.score = v.score;
        candidate.step = v.step;
        delete &v;//析构v

        auto end = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();//记录结束时间(单位:毫秒)
        if(end-start>=config::timeLimit*1000){
            negamaxLogger.warn("time out");
            break;
        }
    }

    return alpha;
}
Place &negamax::deepening(Board &board, std::list<Place>&candidates, Role role, int depth) {

    double score;
    for(int d=1; d<=depth; d++){
        score = negamax(board, candidates, role, d, MIN, MAX);
        if(comparer::greaterEqual(score, Score::FIVE))break;
    }

    // 找到最佳结果
    Place result = candidates.front();
    candidates.pop_front();
    for(auto &candidate: candidates){
        if(comparer::equal(result.score, candidate.score)){
            if(result.score>=0){
                if(result.step!=candidate.step && result.step<=candidate.step){
                    continue;
                }else if(result.score<=candidate.score)continue;
            }else{
                if(result.step!=candidate.step && result.step>=candidate.step){
                    continue;
                }else if(result.score>=candidate.score)continue;
            }
        }else if(result.score>=candidate.score)continue;

        result = candidate;
    }

    return *(new Place(result));//TODO: 语法检查
}
