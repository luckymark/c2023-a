#include "CNN.h"

// GobangCNN 类的构造函数的定义
GobangCNN::GobangCNN() {
    // 定义和初始化网络层
    publicConv = torch::nn::Sequential(
            torch::nn::Conv2d(torch::nn::Conv2dOptions(17, 32, 3).padding(1)),
            torch::nn::BatchNorm2d(32),
            torch::nn::ReLU(),
            torch::nn::Conv2d(torch::nn::Conv2dOptions(32, 64, 3).padding(1)),
            torch::nn::BatchNorm2d(64),
            torch::nn::ReLU(),
            torch::nn::Conv2d(torch::nn::Conv2dOptions(64, 128, 3).padding(1)),
            torch::nn::BatchNorm2d(128),
            torch::nn::ReLU()
    );

    value = torch::nn::Sequential(
            torch::nn::Conv2d(torch::nn::Conv2dOptions(128, 2, 1)),
            torch::nn::BatchNorm2d(2),
            torch::nn::ReLU(),
            torch::nn::Flatten(),
            torch::nn::Linear(2 * 15 * 15, 64),
            torch::nn::ReLU(),
            torch::nn::Linear(64, 15 * 15),
            torch::nn::Tanh()
    );

    policy = torch::nn::Sequential(
            torch::nn::Conv2d(torch::nn::Conv2dOptions(128, 4, 1)),
            torch::nn::BatchNorm2d(4),
            torch::nn::ReLU(),
            torch::nn::Flatten(),
            torch::nn::Linear(4 * 15 * 15, 15 * 15),
            torch::nn::Softmax(1)
    );

    // 注册模块
    register_module("publicConv", publicConv);
    register_module("value", value);
    register_module("policy", policy);
}

// GobangCNN 类的 forward 方法的定义
std::tuple<torch::Tensor, torch::Tensor> GobangCNN::forward(torch::Tensor x) {
    auto y = publicConv->forward(x);
    auto v = value->forward(y);
    auto p = policy->forward(y);

    v = unflatten(v, 15, 15);
    p = unflatten(p, 15, 15);

    // 遍历并更新 v 和 p Tensor 的值
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            if (x[0][0][i][j].item<float>() != 0) {
                v[0][i][j] = 0;
                p[0][i][j] = 0;
            }
            if (x[0][1][i][j].item<float>() != 0) {
                v[0][i][j] = 0;
                p[0][i][j] = 0;
            }
        }
    }
    return std::make_tuple(v, p);
}