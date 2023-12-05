#include "CNN.h"
#include <iostream>
#include <torch/optim.h>
#include <torch/serialize.h>

int main() {
    // 创建一个简单的输入张量
    auto input = torch::randn({1, 17, 15, 15}); // 假设输入是一个随机张量
    // 实例化神经网络
    GobangCNN gobangCNN;

    // 创建优化器（这里使用Adam）
    torch::optim::Adam optimizer(gobangCNN.parameters(), torch::optim::AdamOptions(1e-4));

    // 创建假的目标值（MCTS输出）
    auto target_p = torch::randn({1, 15, 15});
    auto target_v = torch::randn({1, 15, 15});

    // 实例化损失函数
    ValuePolicyLoss lossFunc;

    // 第一次前向传播
    auto [v1, p1] = gobangCNN.forward(input);
    double c_array[15][15];

    // 确保张量在 CPU 上并且是 double 类型
    v1 = v1.to(torch::kDouble);

    // 将张量的内容复制到数组中
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            c_array[i][j] = v1[0][i][j].item<double>();
        }
    }

    // 打印数组来验证
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            std::cout << c_array[i][j] << " ";
        }
        std::cout << std::endl;
    }

    auto loss1 = lossFunc.forward(gobangCNN, p1, v1, target_p, target_v);
    std::cout << "Initial Loss: " << loss1.item<float>() << std::endl;

    // 反向传播
    optimizer.zero_grad();  // 清除之前的梯度
    loss1.backward();
    optimizer.step();  // 更新参数

    // 第二次前向传播
    auto [v2, p2] = gobangCNN.forward(input);
    auto loss2 = lossFunc.forward(gobangCNN, p2, v2, target_p, target_v);
    std::cout << "Loss after one backward pass and parameter update: " << loss2.item<float>() << std::endl;

    system("pause");
    return 0;
}
