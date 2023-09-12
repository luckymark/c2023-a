#include <stdio.h>
#include <unistd.h>

void move_letter(char letter, float speed) {
    int position = 0;
    int direction = 1;  // 1表示向右移动，-1表示向左移动

    while (1) {
        // 清空控制台输出
        printf("\033c");

        // 输出字母前的空格
        for (int i = 0; i < position; ++i) {
            printf(" ");
        }

        // 输出字母
        printf("%c\n", letter);

        // 停顿一段时间
        usleep(speed * 1000000);

        // 根据方向和位置更新下一个位置
        position += direction;

        // 检查是否到达边界，如果是则改变方向
        if (position >= 79 - 1) {  // 79是典型控制台窗口宽度，减去1是为了避免边界溢出
            direction = -1;
        } else if (position <= 0) {
            direction = 1;
        }
    }
}

// 调用函数进行测试，传入要移动的字母和速度（单位为秒）
int main() {
    move_letter('A', 0.1);
    return 0;
}