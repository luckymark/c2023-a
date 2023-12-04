#include "CNN.h"

// ValuePolicyLoss 类的构造函数和 forward 方法的定义
ValuePolicyLoss::ValuePolicyLoss(float lambda_reg) : lambda_reg(lambda_reg) {
}

torch::Tensor ValuePolicyLoss::forward(torch::nn::Module &model, torch::Tensor p_cnn, torch::Tensor v_cnn,
                                       torch::Tensor p_mcts, torch::Tensor v_mcts) {
    torch::Tensor l2_reg = torch::tensor(0.0);

    // 计算 L2 正则化项
    for (const auto& param : model.parameters()) {
        l2_reg = l2_reg + param.norm(2);
    }

    // 展平输入张量
    auto p_cnn_tensor = torch::flatten(p_cnn);
    auto p_mcts_tensor = torch::flatten(p_mcts);
    auto v_cnn_tensor = torch::flatten(v_cnn);
    auto v_mcts_tensor = torch::flatten(v_mcts);

    // 计算损失
    auto loss = torch::norm(v_mcts_tensor - v_cnn_tensor, 2).pow(2) -
                torch::dot(p_mcts_tensor, torch::log(p_cnn_tensor)) +
                lambda_reg * l2_reg;

    return loss;
}