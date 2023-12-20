#include <iostream>
#include <vector>

class Game {
public:
    Game(int level) : level(level), steps(0) {
        loadLevel();
        playerPosition = findPlayerPosition();
    }

    void loadLevel() {
        switch (level) {
            case 1:
                map = {
                        "######",
                        "# BP #",
                        "# P  #",
                        "#   B#",
                        "#   ##",
                        "######"
                };
                break;

            case 2:
                map = {
                        "######",
                        "# BP #",
                        "#   P#",
                        "#   B#",
                        "#   ##",
                        "######"
                };
                break;

            case 3:
                map = {
                        "########",
                        "# P    #",
                        "# B    #",
                        "# B    #",
                        "#   B  #",
                        "#      #",
                        "#   ####",
                        "########"
                };
                break;

            default:
                std::cerr << "未知关卡：" << level << std::endl;
                exit(EXIT_FAILURE);
        }
    }

    std::pair<int, int> findPlayerPosition() const {
        for (int i = 0; i < map.size(); ++i) {
            for (int j = 0; j < map[i].size(); ++j) {
                if (map[i][j] == 'P') {
                    return std::make_pair(i, j);
                }
            }
        }
        return std::make_pair(-1, -1); // 玩家位置未找到
    }

    void displayMap() const {
        for (const std::string& row : map) {
            std::cout << row << '\n';
        }
    }

    void movePlayer(char direction) {
        int x = playerPosition.second;
        int y = playerPosition.first;

        int new_x = x, new_y = y;

        switch (direction) {
            case 'W': new_y--; break;
            case 'S': new_y++; break;
            case 'A': new_x--; break;
            case 'D': new_x++; break;
            default: return;
        }

        if (isValidMove(new_y, new_x)) {
            steps++;
            map[y][x] = ' ';
            playerPosition = std::make_pair(new_y, new_x);
            map[new_y][new_x] = 'P';
        }
    }

    bool checkWin() const {
        for (const std::string& row : map) {
            if (row.find('B') != std::string::npos) {
                return false;
            }
        }
        return true;
    }

    int getSteps() const {
        return steps;
    }

private:
    int level;
    int steps;
    std::vector<std::string> map;
    std::pair<int, int> playerPosition;

    bool isValidMove(int y, int x) const {
        return y >= 0 && y < static_cast<int>(map.size()) &&
               x >= 0 && x < static_cast<int>(map[y].size()) &&
               map[y][x] != '#';
    }
};

int main() {
    int totalLevels = 3;
    int currentLevel = 1;

    while (currentLevel <= totalLevels) {
        Game game(currentLevel);

        std::cout << "The" << currentLevel << ":\n";
        while (!game.checkWin()) {
            std::cout << "current map:\n";
            game.displayMap();

            std::cout << "Input direction:(WASD)";
            char move;
            std::cin >> move;

            game.movePlayer(move);
        }

        std::cout << "You win" << currentLevel << "with" << game.getSteps() << "steps \n";
        currentLevel++;
    }

    return 0;
}