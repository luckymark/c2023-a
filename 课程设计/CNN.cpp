#include "CNN.h"

// 手动Unflatten
torch::Tensor unflatten(torch::Tensor input, int64_t height, int64_t width) {
    // 获取 batch_size
    int64_t batch_size = input.size(0);

    // 使用 view 方法重新塑形 Tensor
    return input.view({batch_size, height, width});
}