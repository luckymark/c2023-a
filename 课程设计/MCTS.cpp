/*
 * 蒙特卡洛树搜索
 */
#include "MCTS.h"

//当前访问节点
Node* target;

//价值分布
double value[SIZE][SIZE];

//策略分布
double policy[SIZE][SIZE];

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

//显示进度条
void showProgressBar(int inter_times, int inter_times_total, std::string model_name, int i, int es_times, int chessPieceType) {
// 清空屏幕
    clearScreen();

// 计算进度百分比
    int percentage = (i * 1000) / es_times;

// 显示进度条
    std::cout << "Gobang AI Based on MCTS and Policy-Value Network by Mgepahmge" << std::endl;
    std::cout << "Mode: Training" << std::endl;
// 检查CUDA是否可用
    if (torch::cuda::is_available()) {
        // 如果CUDA可用，则使用CUDA设备
        torch::Device device(torch::kCUDA);
        std::cout << "CUDA is available! Using CUDA device: " << device << std::endl;
    } else {
        std::cout << "CUDA is not available! Using CPU device" << std::endl;
    }

    std::cout << "Interation: " << inter_times << "/" << inter_times_total << std::endl;
    std::cout << "Model: " << "[" << model_name << "] Estimate Progress:\n";
    std::cout << "<";
    for (int j = 0; j < 100; ++j) {
        if (j < percentage/10) {
            std::cout << "=";
        } else {
            std::cout << " ";
        }
    }
    std::cout << "| " << (double)percentage/10 << "%> [" << i << "/" << es_times << "]" << std::endl;

// 显示棋子类型
    std::string chessPiece;
    if (chessPieceType == 1) {
        chessPiece = "Black";
    } else if (chessPieceType == 2) {
        chessPiece = "White";
    } else {
        chessPiece = "Unknown";
    }
    std::cout << "Chess piece type: " << chessPiece << std::endl;
}

//数据转换：int -> tensor(KFloat32)
torch::Tensor convertBoardDataToTensor(int array[17][15][15]) {
    // 创建一个空的 Tensor，大小为 1x17x15x15
    torch::Tensor tensor = torch::empty({1, 17, 15, 15}, torch::kFloat32);

    // 填充 Tensor
    for (int i = 0; i < 17; ++i) {
        for (int j = 0; j < 15; ++j) {
            for (int k = 0; k < 15; ++k) {
                // 显式转换 int 为 float
                tensor[0][i][j][k] = static_cast<float>(array[i][j][k]);
            }
        }
    }
    return tensor;
}

//数据转换：double -> tensor(KFloat32)
torch::Tensor convertMCTSResultToTensor(double array[15][15]) {
    // 创建一个空的 Tensor，大小为 1x15x15
    torch::Tensor tensor = torch::empty({1, 15, 15}, torch::kFloat32);

    // 填充 Tensor
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            // 显式转换 double 为 float
            tensor[0][i][j] = static_cast<float>(array[i][j]);
        }
    }

    return tensor;
}

//数据转换：tensor -> double（策略）
void trans_policy(torch::Tensor input) {
    input = input.to(torch::kDouble);
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            policy[i][j] = input[0][i][j].item<double>();
        }
    }
}

//数据转换：tensor -> double（价值）
void trans_value(torch::Tensor input) {
    input = input.to(torch::kDouble);
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            value[i][j] = input[0][i][j].item<double>();
        }
    }
}

//无用の蜜汁小函数（返回当前根节点所有子节点的搜索次数总和）
double sum_N() {
    double sum = 0;
    for (int i = 0; i < childrenNum; ++i) {
        if (target->children[i] != NULL) {
            sum += (double) target->children[i]->N;
        }
    }
    return sum;
}

//创建根节点
void creatRoot(int x,int y,int type) {
    target = (Node*) malloc(sizeof(Node));
    target -> X = x;
    target -> Y = y;
    target -> Q = 0;
    target -> v = 0;
    target -> N = 0;
    target -> P = 0;
    target -> P_real = 0;
    target -> type = type;
    target -> father = NULL;
    for (int j = 0; j < childrenNum; ++j) {
        target -> children[j] = NULL;
    }
}

//释放内存
void freeTree(Node* input) {

    if (input == NULL) return;

    for (int i = 0; i < childrenNum; i++) {
        if (input->children[i] != NULL) {
            freeTree(input->children[i]);
        }
    }
    free(input);
}

/*
 * 根据拓展、评估、回传阶段的结果选择最佳move作为下一步的根节点
 */
void inheritRoot() {
    int max_N = 0;
    for (int i = 0; i < childrenNum; ++i) {
        if (target->children[i]!=NULL) {
            max_N = max_N>target->children[i]->N ? max_N : target->children[i]->N;
        } else {
            break;
        }
    }
    int j;
    for (j = 0; j < childrenNum; ++j) {
        if (target->children[j]->N==max_N) {
            target = target->children[j];
            break;
        }
    }
    for (int i = 0; i < childrenNum; ++i) {
        if (i!=j) {
            free(target->father->children[i]);
            target->father->children[i] = NULL;
        }
    }
    free(target->father);
    target->father = NULL;
    target->N = 0;
    chess(target->X,target->Y,target->type,REAL);
}

//为当前节点创建一个子节点
void createNode(int x,int y,double Q,double v,int N,double P,double P_real,int type) {
    for (int i = 0; i < childrenNum; ++i) {
        if (target->children[i] == NULL) {
            Node* newNode = (Node*) malloc(sizeof(Node));
            newNode -> X = x;
            newNode -> Y = y;
            newNode -> Q = Q;
            newNode -> v = v;
            newNode -> N = N;
            newNode -> P = P;
            newNode -> P_real = P_real;
            newNode -> type = type;
            newNode -> father = target;
            for (int j = 0; j < childrenNum; ++j) {
                newNode -> children[j] = NULL;
            }
            target -> children[i] = newNode;
            break;
        }
    }
}

//根据UCT算法选择节点
void chooseNode() {
    double max;
    for (int i = 0; i < childrenNum; ++i) {
        if (target -> children[i] != NULL) {
            max = max > target->children[i]->P_real ? max : target->children[i]->P_real;
        } else {
            break;
        }
    }
    for (int j = 0; j < childrenNum; ++j) {
        if (target->children[j] != NULL) {
            if (target->children[j]->P_real == max) {
                target = target->children[j];
            }
        } else {
            break;
        }
    }
}

//判断当前节点是否为根节点
int is_root() {
    if (target->father == NULL) {
        return 1;
    } else {
        return 0;
    }
}

//判断当前节点是否为下一步行动
int is_next_move() {
    if (target->father->father == NULL) {
        return 1;
    } else {
        return 0;
    }
}

//返回根节点
Node* root() {
    Node* now = target;
    while (!is_root()) {
        target = target -> father;
    }
    Node* result = target;
    target = now;
    return result;
}

//回退至根节点
void back_to_root() {
    while (!is_root()) {
        target = target->father;
    }
}

/*
 * 根据模拟所得的价值来更新下一步行动的价值
 */
void back_value() {
    Node* now = target;
    double v = target->v;
    while (!is_next_move()) {
         target = target -> father;
    }
    target -> Q = (v+((double)target->N-1)*target->Q)/(double)target->N;
    target = now;
}

/*
 * 最大置信上界算法搜索(Upper Confidence Bound Apply to Tree, UCT)
 * 一次只执行一步
 */
void UCT() {
    for (int i = 0; i < childrenNum; ++i) {
        if(target -> children[i] != NULL) {
            target -> children[i] -> P_real = C_UCT * target->children[i]->P * ( sqrt((double)root()->N)/(1+(double)target->children[i]->N) );
            target -> children[i] -> P_real += target -> children[i] -> Q;
        } else {
            break;
        }
    }
    chooseNode();
}

//展开
void expand() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (policy[i][j] != 0) {
                createNode(j,i,0,value[i][j],0,policy[i][j],0,(target->type==B_BLACK?B_WHITE:B_BLACK));
            }
        }
    }
}

//评估与回传
void EstimateAndBack(int inter_times,int inter_times_total,std::string model_name,std::string model_save_name) {
    //初始化神经网络
    GobangCNN gobangCNN;
    ValuePolicyLoss lossFunc;
    if (!model_name.empty()) {
        torch::serialize::InputArchive input_archive;
        input_archive.load_from(model_name);
        gobangCNN.load(input_archive);
    }
    torch::optim::Adam optimizer(gobangCNN.parameters(), torch::optim::AdamOptions(1e-4));
    data_trans((target->type == B_BLACK ? B_WHITE : B_BLACK),REAL);
    auto input = convertBoardDataToTensor(NN_input);
    //第一次神经网络评估，此时应保存第一次的结果供后续损失函数使用
    auto [v, p] = gobangCNN.forward(input);
    auto orin_v = v.detach();
    auto orin_p = p.detach();
    trans_policy(v);
    trans_value(p);
    //第一次展开，生成所有可能的move;
    expand();
    for (int i = 0; i < E_times; ++i) {
        showProgressBar(inter_times,inter_times_total,model_name,i+1,E_times,root()->type==B_BLACK?B_WHITE:B_BLACK);
        //重置虚拟棋盘与虚拟历史落子数据
        resetBoard(VIRTUAL);
        reset_HCD(VIRTUAL);
        //选择一个move
        back_to_root();
        target -> N++;
        UCT();
        target->N++;
        //存储下一步落子颜色
        int type = target -> type;
        //落子
        chess(target->X,target->Y,target->type,VIRTUAL);
        data_trans((target->type == B_BLACK ? B_WHITE : B_BLACK),VIRTUAL);
        //开始评估
        for (int j = 0; j < MCTS_times; ++j) {
            //神经网络评估
            auto input1 = convertBoardDataToTensor(NN_input);
            auto [v1, p1] = gobangCNN.forward(input1);
            trans_value(v1);
            trans_policy(p1);
            //拓展
            expand();
            //选择
            UCT();
            //落子
            chess(target->X,target->Y,target->type,VIRTUAL);
            data_trans((target->type == B_BLACK ? B_WHITE : B_BLACK),VIRTUAL);
            //判断游戏是否到达终局
            game_terminate(VIRTUAL);
            if (win != 0) {
                if (win==3) {
                    target->v = 0;
                } else {
                    target->v = win == type ? 1 : -1;
                }
                back_value();
                break;
            }
            //回传
            back_value();
        }
        //释放内存，清除用无节点
        while (!is_next_move()) {
            target = target->father;
        }
        for (int j = 0; j < childrenNum; ++j) {
            if (target->children[j] != NULL) {
                freeTree(target->children[j]);
                target->children[j] = NULL;
            }
        }
    }
    //评估结束，返回根节点
    back_to_root();
    //生成落子概率与价值矩阵
    double P_mcts[SIZE][SIZE];
    double V_mcts[SIZE][SIZE];
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            P_mcts[i][j] = 0;
            V_mcts[i][j] = 0;
        }
    }
    for (int i = 0; i < childrenNum; ++i) {
        if (target->children[i] != NULL) {
            P_mcts[target->children[i]->Y][target->children[i]->X] = ((double)target->children[i]->N) / sum_N();
            V_mcts[target->children[i]->Y][target->children[i]->X] = target->children[i]->Q;
        }
    }
    //反向传播更新神经网络
    auto p_mcts = convertMCTSResultToTensor(P_mcts);
    auto v_mcts = convertMCTSResultToTensor(V_mcts);
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (orin_p[0][i][j].item<float>() == 0) {
                orin_p[0][i][j] = 1;
            }
        }
    }
    auto loss = lossFunc.forward(gobangCNN,orin_p,orin_v, p_mcts, v_mcts);
    optimizer.zero_grad();  // 清除之前的梯度
    loss.backward();
    optimizer.step();
    torch::serialize::OutputArchive output_archive;
    gobangCNN.save(output_archive);
    output_archive.save_to(model_save_name);
}