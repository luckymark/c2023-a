import logging

from .static import *

_evaluatorLogger = logging.getLogger("BoardEvaluator")


def countToScore(count, block, empty=0) -> int or float:
    # _evaluatorLogger.debug(f"countToScore(count={count}, block={block}, empty={empty})")
    if empty is None:
        empty = 0

    # 没有空位
    if empty <= 0:
        if count >= 5:
            return Score.FIVE
        if block == 0:
            match count:
                case 1:
                    return Score.ONE
                case 2:
                    return Score.TWO
                case 3:
                    return Score.THREE
                case 4:
                    return Score.FOUR
        elif block == 1:
            match count:
                case 1:
                    return Score.BLOCKED_ONE
                case 2:
                    return Score.BLOCKED_TWO
                case 3:
                    return Score.BLOCKED_THREE
                case 4:
                    return Score.BLOCKED_FOUR
    elif empty == 1 or empty == count - 1:  # 第一个是空位
        if count >= 6:
            return Score.FIVE
        if block == 0:
            match count:
                case 2:
                    return Score.TWO / 2
                case 3:
                    return Score.THREE
                case 4:
                    return Score.BLOCKED_FOUR
                case 5:
                    return Score.FIVE
        elif block == 1:
            match count:
                case 2:
                    return Score.BLOCKED_TWO
                case 3:
                    return Score.BLOCKED_THREE
                case 4:
                    return Score.BLOCKED_FOUR
                case 5:
                    return Score.BLOCKED_FOUR
    elif empty == 2 or empty == count - 2:  # 第二个是空位
        if count >= 7:
            return Score.FIVE
        if block == 0:
            match count:
                case 3:
                    return Score.THREE
                case 4:
                    return Score.BLOCKED_FOUR
                case 5:
                    return Score.BLOCKED_FOUR
                case 6:
                    return Score.FOUR
        elif block == 1:
            match count:
                case 3:
                    return Score.BLOCKED_THREE
                case 4:
                    return Score.BLOCKED_FOUR
                case 5:
                    return Score.BLOCKED_FOUR
                case 6:
                    return Score.FOUR
        elif block == 2:
            match count:
                case 4:
                    return Score.BLOCKED_FOUR
                case 5:
                    return Score.BLOCKED_FOUR
                case 6:
                    return Score.BLOCKED_FOUR
    elif empty == 3 or empty == count - 3:  # 第三个是空位
        if count >= 8:
            return Score.FIVE
        if block == 0:
            match count:
                case 4:
                    return Score.THREE
                case 5:
                    return Score.THREE
                case 6:
                    return Score.BLOCKED_FOUR
                case 7:
                    return Score.FOUR
        elif block == 1:
            match count:
                case 4:
                    return Score.BLOCKED_FOUR
                case 5:
                    return Score.BLOCKED_FOUR
                case 6:
                    return Score.BLOCKED_FOUR
                case 7:
                    return Score.FOUR
        elif block == 2:
            match count:
                case 4:
                    return Score.BLOCKED_FOUR
                case 5:
                    return Score.BLOCKED_FOUR
                case 6:
                    return Score.BLOCKED_FOUR
                case 7:
                    return Score.BLOCKED_FOUR
    elif empty == 4 or empty == count - 4:
        if count >= 9:
            return Score.FIVE
        if block == 0:
            match count:
                case 5:
                    return Score.FOUR
                case 6:
                    return Score.FOUR
                case 7:
                    return Score.FOUR
                case 8:
                    return Score.FOUR
        elif block == 1:
            match count:
                case 4:
                    return Score.BLOCKED_FOUR
                case 5:
                    return Score.BLOCKED_FOUR
                case 6:
                    return Score.BLOCKED_FOUR
                case 7:
                    return Score.BLOCKED_FOUR
                case 8:
                    return Score.FOUR
        elif block == 2:
            match count:
                case 5:
                    return Score.BLOCKED_FOUR
                case 6:
                    return Score.BLOCKED_FOUR
                case 7:
                    return Score.BLOCKED_FOUR
                case 8:
                    return Score.BLOCKED_FOUR
    elif empty == 5 or empty == count - 5:
        return Score.FIVE

    return 0


def scorePoint(board, px, py, role, tmp_dir=None) -> float:
    if px == 0 and py == 0:
        _evaluatorLogger.debug(f"scorePoint(role={role.name()})")
    map_ = board.map
    result = empty = 0
    count = block = secondCount = 0  # secondCount - 另一个方向的计数

    X, Y = board.X, board.Y

    def reset():
        nonlocal empty, count, block, secondCount
        count = 1
        block = 0
        empty = -1
        secondCount = 0

    if tmp_dir is None or tmp_dir == 0:
        reset()

        for i in range(py + 1, Y):
            t = map_[px][i]
            if t == Role.BLANK:
                if empty == -1 and i < Y - 1 and map_[px][i + 1] == role:
                    empty = count
                    continue
                else:
                    break
            if t == role:
                count += 1
                continue
            else:
                block += 1
                break
        else:
            block += 1  # 结尾加上一个block

        for i in range(py - 1, -1, -1):
            t = map_[px][i]
            if t == Role.BLANK:
                if empty == -1 and i > 0 and map_[px][i - 1] == role:
                    empty = 0  # TODO 注意这里是0，因为是从右往左走的
                    continue
                else:
                    break
            if t == role:
                secondCount += 1
                empty += int(empty != -1)
                continue
            else:
                block += 1
                break
        else:
            block += 1

        count += secondCount
        board.scoreCache[role][0][px][py] = countToScore(count, block, empty)
    result += (board.scoreCache[role][0][px][py])

    if tmp_dir is None or tmp_dir == 1:
        reset()

        for i in range(px + 1, X):
            t = map_[i][py]
            if t == Role.BLANK:
                if empty == -1 and i < X - 1 and map_[i + 1][py] == role:
                    empty = count
                    continue
                else:
                    break
            if t == role:
                count += 1
                continue
            else:
                block += 1
                break
        else:
            block += 1

        for i in range(px - 1, -1, -1):
            t = map_[i][py]
            if t == Role.BLANK:
                if empty == -1 and i > 0 and map_[i - 1][py] == role:
                    empty = 0  # TODO 不懂
                    continue
                else:
                    break
            if t == role:
                secondCount += 1
                empty += int(empty != -1)
                continue
            else:
                block += 1
                break
        else:
            block += 1

        count += secondCount
        board.scoreCache[role][1][px][py] = countToScore(count, block, empty)
    result += board.scoreCache[role][1][px][py]

    if tmp_dir is None or tmp_dir == 2:
        reset()
        for i in range(1, Y):
            tmp_x, tmp_y = px + i, py + i
            if tmp_x >= X or tmp_y >= Y:
                block += 1
                break
            t = map_[tmp_x][tmp_y]
            if t == Role.BLANK:
                if empty == -1 and tmp_x < X - 1 and tmp_y < Y - 1 and map_[tmp_x + 1][tmp_y + 1] == role:
                    empty = count
                    continue
                else:
                    break
            if t == role:
                count += 1
                continue
            else:
                block += 1
                break
        else:
            block += 1

        for i in range(1, Y):
            tmp_x, tmp_y = px - i, py - i
            if tmp_x < 0 or tmp_y < 0:
                block += 1
                break
            t = map_[tmp_x][tmp_y]
            if t == Role.BLANK:
                if empty == -1 and tmp_x > 0 and tmp_y > 0 and map_[tmp_x - 1][tmp_y - 1] == role:
                    empty = 0  # TODO 不懂
                    continue
                else:
                    break
            if t == role:
                secondCount += 1
                empty += int(empty != -1)
                continue
            else:
                block += 1
                break
        else:
            block += 1

        count += secondCount
        board.scoreCache[role][2][px][py] = countToScore(count, block, empty)

    result += board.scoreCache[role][2][px][py]

    if tmp_dir is None or tmp_dir == 3:
        reset()
        for i in range(1, X):
            tmp_x, tmp_y = px + i, py - i
            if tmp_x < 0 or tmp_y < 0 or tmp_x >= X or tmp_y >= Y:
                block += 1
                break
            t = map_[tmp_x][tmp_y]
            if t == Role.BLANK:
                if empty == -1 and tmp_x < X - 1 and tmp_y > 0 and map_[tmp_x + 1][tmp_y - 1] == role:
                    empty = count
                    continue
                else:
                    break
            if t == role:
                count += 1
                continue
            else:
                block += 1
                break
        else:
            block += 1

        for i in range(1, X):
            tmp_x, tmp_y = px - i, py + i
            if tmp_x < 0 or tmp_y < 0 or tmp_x >= X or tmp_y >= Y:
                block += 1
                break
            t = map_[tmp_x][tmp_y]
            if t == Role.BLANK:
                if empty == -1 and tmp_x > 0 and tmp_y < Y - 1 and map_[tmp_x - 1][tmp_y + 1] == role:
                    empty = 0  # TODO 不懂
                    continue
                else:
                    break
            if t == role:
                secondCount += 1
                empty += int(empty != -1)  # 注意这里，如果左边又多了己方棋子，那么empty的位置就变大了
                continue
            else:
                block += 1
                break
        else:
            block += 1

        count += secondCount
        board.scoreCache[role][3][px][py] = countToScore(count, block, empty)
    result += board.scoreCache[role][3][px][py]
    return result
