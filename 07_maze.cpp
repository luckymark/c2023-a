//迷宫，但只搭建了一个基本框架（生成迷宫的算法不太会）

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

const int WIDTH = 20; // 迷宫的宽度
const int HEIGHT = 9; // 迷宫的高度
const char WALL = '0';
const char EMPTY = ' ';
const char PLAYER = '1';
const char EXIT = 'E';

class Maze{
public:
    Maze();
    void generateMaze();
    void displayMaze();
    bool isExitReached();
    bool movePlayer(char direction);
private:
    std::vector<std::vector<char>> maze;
    int playerX, playerY;
    int exitX, exitY;
};

Maze::Maze()
{
    maze.resize(HEIGHT, vector<char>(WIDTH, EMPTY));
    playerX = 1;
    playerY = 1;
    exitX = HEIGHT - 1;
    exitY = WIDTH - 2;
}

void Maze::generateMaze()
{
    srand(static_cast<unsigned>(time(0)));//初始化伪随机数生成器的种子值

    for (int i=0;i<HEIGHT;i++)
    {
        maze[i][0] = maze[i][WIDTH-1] = WALL;
    }
    for (int i=0;i<=WIDTH-1;i++) {
        maze[0][i] = maze[HEIGHT-1][i] = WALL;
    }

    for(int i=1;i<=HEIGHT-1;i++){
        for(int j=1;j<=WIDTH-1;j++){
            if(rand()%2==0){  //%的数可以修改来改变迷宫疏密度
                maze[i][j]=WALL;
            }
        }
    }
    for(int i=1;i<=3;i++){
        for(int j=1;j<=3;j++){
            maze[i][j]=EMPTY;
        }
    }
    for(int i=0;i<=2;i++){
        for(int j=0;j<=2;j++){
            maze[exitX-i][exitY-i]=EMPTY;
        }
    }
    maze[exitX][exitY] = EXIT;
    maze[1][1] = PLAYER;
}

void Maze::displayMaze() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            std::cout<<maze[i][j];
        }
        std::cout<<std::endl;
    }
}

bool Maze::isExitReached()
{
    return (playerX == exitX) && (playerY == exitY);
}

bool Maze::movePlayer(char direction) {
    int newX = playerX;
    int newY = playerY;

    switch (direction) {
        case 'w':
            newX--;
            break;
        case 's':
            newX++;
            break;
        case 'a':
            newY--;
            break;
        case 'd':
            newY++;
            break;
        default:
            return false;
    }
    if(newX>=0 && newY>=0){
        if (maze[newX][newY] != WALL) {
            maze[playerX][playerY] = EMPTY;
            playerX = newX;
            playerY = newY;
            maze[playerX][playerY] = PLAYER;
            return true;
        }
    }
    return false;
}

int main() {
    Maze maze;
    maze.generateMaze();

    while (true) {
        system("cls"); // 清空控制台
        maze.displayMaze();

        char move; // 从控制台获取输入
        std::cin>>move;

        if (move == 'q') {
            break;
        }

        if (maze.movePlayer(move)) {
            if (maze.isExitReached()) {
                system("cls");
                maze.displayMaze();
                std::cout << "you win" <<std::endl;
                break;
            }
        }
    }

    return 0;
}
