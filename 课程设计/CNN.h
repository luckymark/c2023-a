#ifndef GOBANG_CNN_H
#define GOBANG_CNN_H

#include <torch/torch.h>
#include <tuple>
#include <torch/serialize.h>
extern "C" {
#include "board.h"
}

// 声明 unflatten 函数
torch::Tensor unflatten(torch::Tensor input, int64_t height, int64_t width);

// 定义 GobangCNN 类
struct GobangCNN : torch::nn::Module {
    GobangCNN();
    std::tuple<torch::Tensor, torch::Tensor> forward(torch::Tensor x);

    torch::nn::Sequential publicConv, value, policy;
};

// 定义 ValuePolicyLoss 类
struct ValuePolicyLoss : torch::nn::Module {
    explicit ValuePolicyLoss(float lambda_reg = 0.01);
    torch::Tensor forward(torch::nn::Module &model, torch::Tensor p_cnn, torch::Tensor v_cnn,
                          torch::Tensor p_mcts, torch::Tensor v_mcts);

private:
    float lambda_reg;
};

#endif //GOBANG_CNN_H
