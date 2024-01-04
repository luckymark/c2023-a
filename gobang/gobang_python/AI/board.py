import logging
import AI.config as config

from .zobrist import Zobrist
from .evaluate_point import scorePoint
from .static import *

# _total = _count = 0
_boardLogger = logging.getLogger("Board")


def _fixScore(score: int or float):
    if Score.FOUR > score >= Score.BLOCKED_FOUR:  # TODO: 无法访问的代码?
        if Score.BLOCKED_FOUR <= score < Score.BLOCKED_FOUR + Score.THREE:  # 单独冲四,意义不大
            return Score.THREE
        elif Score.BLOCKED_FOUR + Score.THREE <= score < Score.BLOCKED_FOUR * 2:  # 冲四活三,比双三分高,相当于自己形成活四
            return Score.FOUR
        else:  # 双冲四,比活四分数高
            return Score.FOUR * 2
    return score


def _starTo(point: Place, points: list[Place] = None):
    if not points:
        return False
    for p2 in points:
        # 五步以内
        if abs(point[0] - p2[0]) > 4 or abs(point[1] - p2[1]) > 4:
            return False
        # 对角线上
        if not (point[0] == p2[0] or point[1] == p2[1] or
                abs(point[0] - p2[0]) == abs(point[1] - p2[1])):
            return False
    return True


class PlacePermissionError(Exception):
    pass


# class Persistence:
#     def __init__(self, size):
#         self.X, self.Y = size
#         self.map = [[0][:] * self.Y for _ in range(self.X)]


class Board:
    _instance = None
    X = Y = 15

    def __new__(cls, *args, **kwargs):
        if cls._instance is None:
            cls._instance = super().__new__(cls)
        return cls._instance

    def __init__(self):
        _boardLogger.warning("init board")
        self.map = [[Role.BLANK][:] * self.Y for _ in range(self.X)]
        self.comScore = [[0][:] * self.Y for _ in range(self.X)]
        self.humScore = [[0][:] * self.Y for _ in range(self.X)]
        self.comMaxScore = self.humMaxScore = 0
        # self.start_role = role
        # self.score = 0
        self.turn = 0
        # self._close = False

        self.allSteps: list[Place] = []
        self.currentSteps: list[Place] = []
        # self.stepsTail = []
        self.scoreCache = [[[[0][:] * self.Y for _ in range(self.X)]  # 棋盘大小,第一个无需占位符,我的hum和com定义不同
                            for _ in range(4)]
                           for _ in range(2)]  # 黑棋 白棋
        self.zobrist = Zobrist(self.X)
        self._evaluateCache = {}
        # self._stack = []
        # self._persistence = Persistence((self.X, self.Y))

        self._initScore()

    def __str__(self):
        _boardLogger.debug("print board")
        result = "  " + " ".join(chr(i) for i in range(ord("A"), ord("A") + self.X)) + "\n"
        for i, x in enumerate(self.map):
            result += f"{i:0>2d}" + " ".join(("H", "C", " ")[int(y)] for y in x) + "\n"
        return result  # "\n".join((" ".join([("H", "C", " ")[int(y)] for y in x]) for x in self.map))

    def _initScore(self):
        _boardLogger.debug("init score")
        map_ = self.map

        for i in range(self.X):
            for j in range(self.Y):
                if map_[i][j] == Role.BLANK:  # 空位，对双方都打分
                    if self.hasNeighbor(i, j, 2, 2):  # 2x2的邻居
                        cs = scorePoint(self, i, j, Role.COMPUTER)
                        hs = scorePoint(self, i, j, Role.HUMAN)
                        self.comScore[i][j] = cs
                        self.humScore[i][j] = hs
                elif map_[i][j] == Role.COMPUTER:  # 对电脑打分，玩家此位置分数为0
                    self.comScore[i][j] = scorePoint(self, i, j, Role.COMPUTER)
                    self.humScore[i][j] = 0
                elif map_[i][j] == Role.HUMAN:  # 对玩家打分，电脑此位置分数为0
                    self.humScore[i][j] = scorePoint(self, i, j, Role.HUMAN)
                    self.comScore[i][j] = 0

    def hasNeighbor(self, px: int, py: int, distance: int, count: int) -> bool:
        _boardLogger.debug(f"check if Place({px}, {py}) has {count} neighbors within {distance} grids")
        map_ = self.map
        startX = px - distance
        endX = px + distance
        startY = py - distance
        endY = py + distance
        for i in range(startX, endX + 1):
            if not 0 <= i < self.X:
                continue
            for j in range(startY, endY + 1):
                if 0 <= j < self.Y and (i != px or j != py) and map_[i][j] != Role.BLANK:
                    count -= 1
                    if count <= 0:
                        return True
        return False

    def updateScore(self, place: Place) -> None:
        _boardLogger.debug(f"update score of Place({place.x}, {place.y})")
        radius = 4
        map_ = self.map

        def update(x: int, y: int, update_dir: int or None):
            role = map_[x][y]
            if role != Role.HUMAN:
                cs = scorePoint(self, x, y, Role.COMPUTER, update_dir)
                self.comScore[x][y] = cs
                # self._persistence.map[x][y] += cs
            else:
                self.comScore[x][y] = 0

            if role != Role.COMPUTER:
                hs = scorePoint(self, x, y, Role.HUMAN, update_dir)
                self.humScore[x][y] = hs
                # self._persistence.map[x][y] += hs
            else:
                self.humScore[x][y] = 0

        for i in range(-radius, radius + 1):
            px, py = place
            py += i
            if py < 0:
                continue
            if py >= self.Y:
                break
            update(px, py, 0)

        for i in range(-radius, radius + 1):
            px, py = place
            px += i
            if px < 0:
                continue
            if px >= self.X:
                break
            update(px, py, 1)

        for i in range(-radius, radius + 1):
            px, py = place
            px += i
            py += i
            if px < 0 or py < 0:
                continue
            if px >= self.X or py >= self.Y:
                break
            update(px, py, 2)

        for i in range(-radius, radius + 1):
            px, py = place
            px += i
            py -= i
            if px < 0 or py < 0:
                continue
            if px >= self.X or py >= self.Y:
                break
            update(px, py, 3)

    def put(self, place: Place, role: Role, log: bool = False):
        if log:
            _boardLogger.info(f"{role.name()} try to put chess at Place({place.x}, {place.y})")
        x, y = place
        place.role = role  # 原代码如此,用于表示currentSteps内的角色
        if self.map[x][y] != Role.BLANK:
            _boardLogger.error(f"Place({place.x}, {place.y})={role.name()} is not blank")
            raise PlacePermissionError("place is not blank")
        self.map[x][y] = role
        self.zobrist.go(x, y, role)
        self.updateScore(place)
        self.allSteps.append(place)
        self.currentSteps.append(place)
        self.turn += 1
        if log:
            _boardLogger.info(f"current turn: {self.turn}")

    def remove(self, place: Place, log: bool = False):
        if log:
            _boardLogger.info(f"remove Place({place.x}, {place.y})")
        x, y = place
        if self.map[x][y] != Role.BLANK:
            self.zobrist.go(x, y, self.map[x][y])
            self.updateScore(place)
            self.allSteps.pop()
            self.currentSteps.pop()
            self.turn -= 1

        self.map[x][y] = Role.BLANK

    """
    def backward(self):
        _boardLogger.info("backward")
        if len(self.allSteps) < 2:
            return
        for _ in range(2):
            s = self.allSteps[-1]
            self.remove(s)
            self.stepsTail.append(s)
    """

    """
    def forward(self):
        _boardLogger.info("forward")
        if len(self.stepsTail) < 2:
            return
        for _ in range(2):
            s = self.stepsTail.pop()
            self.put(s, s.role)
    """

    # 启发函数
    # generator 的排序十分重要,可以极大提升 Alpha-Beta 剪枝的效率
    # 对结果的排序依赖 role
    # 变量 starBread 用于进行米子计算--若第一步尝试了 A ,则接下来尝试 1. 大于等于活三; 2. 在 A 的米子位置上
    # 仅对小于活三的棋做 starSpread 优化
    def generator(self, role: Role, onlyThrees: bool = False, starSpread: bool = False, log: bool = False,
                  ) -> list[Place]:
        _boardLogger.debug(f"get candidates for {role.name()} (onlyThrees={onlyThrees}, starSpread={starSpread})")
        # global _total, _count
        if self.turn <= 0:
            return [Place(7, 7)]
        fives = []
        comFours = []
        humFours = []
        comBlockedFours = []
        humBlockedFours = []
        comTwoThrees = []
        humTwoThrees = []
        comThrees = []
        humThrees = []
        comTwos = []
        humTwos = []
        neighbors = []
        map_ = self.map
        # reversedRole = Role(1 - role)

        attackPoints = []
        defendPoints = []

        # 默认情况下 我们遍历整个棋盘。但是在开启star模式下，我们遍历的范围就会小很多
        # 只需要遍历以两个点为中心正方形。
        # 注意除非专门处理重叠区域，否则不要把两个正方形分开算，因为一般情况下这两个正方形会有相当大的重叠面积，别重复计算了
        if starSpread and config.star:
            for i in range(len(self.currentSteps) - 1, -1, -2):
                p = self.currentSteps[i]
                if (role == Role.HUMAN and p.scoreCom >= Score.THREE) or \
                        (role == Role.COMPUTER and p.scoreHum >= Score.THREE):
                    defendPoints.append(p)
                    break

            for i in range(len(self.currentSteps) - 2, -1, -2):
                p = self.currentSteps[i]
                if (role == Role.COMPUTER and p.scoreCom >= Score.THREE) or \
                        (role == Role.HUMAN and p.scoreHum >= Score.THREE):
                    attackPoints.append(p)
                    break

            if not attackPoints:
                attackPoints.append(self.currentSteps[0] if self.currentSteps[0].role == role else self.currentSteps[1])
            if not defendPoints:
                defendPoints.append(self.currentSteps[0] if self.currentSteps[0].role == Role(1 - role) else
                                    self.currentSteps[1])

        for i in range(self.X):
            for j in range(self.Y):
                if map_[i][j] == Role.BLANK:
                    if len(self.allSteps) < 6:
                        if not self.hasNeighbor(i, j, 1, 1):
                            continue
                    elif not self.hasNeighbor(i, j, 2, 2):
                        continue

                    scoreHum = self.humScore[i][j]
                    scoreCom = self.comScore[i][j]
                    maxScore = max(scoreHum, scoreCom)

                    if onlyThrees and maxScore < Score.THREE:
                        continue

                    p = Place(i, j)
                    p.scoreCom = scoreCom
                    p.scoreHum = scoreHum
                    p.score = maxScore
                    p.role = role
                    # _total += 1
                    """双星延伸，以提升性能
                    思路：每次下的子，只可能是自己进攻，或者防守对面（也就是对面进攻点）
                    我们假定任何时候，绝大多数情况下进攻的路线都可以按次序连城一条折线，那么每次每一个子，一定都是在上一个己方棋子的八个方向之一。
                    因为既可能自己进攻，也可能防守对面，所以是最后两个子的米子方向上
                    那么极少数情况，进攻路线无法连成一条折线呢?很简单，我们对前双方两步不作star限制就好，这样可以 兼容一条折线中间伸出一段的情况
                    """
                    if starSpread and config.star:
                        if maxScore < Score.FOUR and (
                                maxScore < Score.BLOCKED_FOUR or not _starTo(self.currentSteps[-1])) and not \
                                _starTo(p, attackPoints) and not _starTo(p, defendPoints):
                            # _count += 1
                            continue

                    if scoreCom >= Score.FIVE:  # 先看电脑能不能连成5
                        fives.append(p)
                    elif scoreHum >= Score.FIVE:  # 再看玩家能不能连成5
                        # 不急返回,可能电脑能成5
                        fives.append(p)
                    elif scoreCom >= Score.FOUR:
                        comFours.append(p)
                    elif scoreHum >= Score.FOUR:
                        humFours.append(p)
                    elif scoreCom >= Score.BLOCKED_FOUR:
                        comBlockedFours.append(p)
                    elif scoreHum >= Score.BLOCKED_FOUR:
                        humBlockedFours.append(p)
                    elif scoreCom >= Score.THREE * 2:  # 双三
                        comTwoThrees.append(p)
                    elif scoreHum >= Score.THREE * 2:
                        humTwoThrees.append(p)
                    elif scoreCom >= Score.THREE:
                        comThrees.append(p)
                    elif scoreHum >= Score.THREE:
                        humThrees.append(p)
                    elif scoreCom >= Score.TWO:
                        comTwos.insert(0, p)  # 原文如此,下同
                    elif scoreHum >= Score.TWO:
                        humTwos.insert(0, p)
                    else:
                        neighbors.append(p)

        # 成5必杀
        if fives:
            if log:
                _boardLogger.debug(f"candidates: {fives}")
                _boardLogger.info("generator: five")
            return fives

        # 自己活四,直接活四
        if role == Role.COMPUTER and comFours:
            if log:
                _boardLogger.debug(f"candidates: {comFours}")
                _boardLogger.info("generator: computer has four")
            return comFours
        if role == Role.HUMAN and humFours:
            if log:
                _boardLogger.debug(f"candidates: {humFours}")
                _boardLogger.info("generator: human has four")
            return humFours

        # 对面活四冲四,自己无冲四,只考虑对面活四
        if role == Role.COMPUTER and humFours and not comBlockedFours:
            if log:
                _boardLogger.debug(f"candidates: {humFours}")
                _boardLogger.info("generator: computer hasn't four and human has four")
            return humFours
        if role == Role.HUMAN and comFours and not humBlockedFours:
            if log:
                _boardLogger.debug(f"candidates: {comFours}")
                _boardLogger.info("generator: human hasn't four and computer has four")
            return comFours

        # 自己有活四,考虑活四冲四
        fours = comFours + humFours if role == Role.COMPUTER else humFours + comFours
        blockedFours = comBlockedFours + humBlockedFours if role == Role.COMPUTER else humBlockedFours + comBlockedFours
        if fours:
            result = fours + blockedFours
            if log:
                _boardLogger.debug(f"candidates: {result}")
                _boardLogger.info("generator: computer has four and blocked four")
            return result

        result = None
        if role == Role.COMPUTER:
            result = comTwoThrees + humTwoThrees + comBlockedFours + humBlockedFours + comThrees + humThrees
        if role == Role.HUMAN:
            result = humTwoThrees + comTwoThrees + humBlockedFours + comBlockedFours + humThrees + comThrees

        # result.sort(key=lambda p: p.score, reverse=True)

        # 双三特殊处理,其不一定比一个活三强
        if comTwoThrees or humTwoThrees:
            if log:
                _boardLogger.debug(f"candidates: {result}")
                _boardLogger.info("generator: two threes")
            return result

        # 只返回大于等于活三的棋
        if onlyThrees:
            if log:
                _boardLogger.debug(f"candidates: {result}")
                _boardLogger.info("generator: greater than three")
            return result

        twos = None
        if role == Role.COMPUTER:
            twos = comTwos + humTwos
        if role == Role.HUMAN:
            twos = humTwos + comTwos

        twos.sort(key=lambda x: x.score, reverse=True)
        result += twos[:config.candidatesLimit - len(result)]

        if log:
            _boardLogger.debug(f"candidates: {result}")
            _boardLogger.info("generator: rubbish")
        # 收益太低,选一些计算得了
        return result

    # 评估棋面
    # 这里只算当前分，而不是在空位下一步之后的分
    def evaluate(self, role):  # 棋面估分
        _boardLogger.debug(f"evaluate {role.name()}")
        # TODO 这里加了缓存,但是并没有提升速度(原注如此)
        cache = self._evaluateCache.get(self.zobrist.code)
        if config.cache and cache:
            return cache

        self.comMaxScore = self.humMaxScore = 0  # 这里都是用正整数初始化的，所以初始值是0
        map_ = self.map
        for i in range(self.X):
            for j in range(self.Y):
                if map_[i][j] == Role.COMPUTER:
                    self.comMaxScore += _fixScore(self.comScore[i][j])  # 未作分数修正,下同
                elif self.map[i][j] == Role.HUMAN:
                    self.humMaxScore += _fixScore(self.humScore[i][j])
        # 有冲四延伸了，不需要专门处理冲四活三
        # 不过这里做了这一步，可以减少电脑胡乱冲四的毛病
        # _comMaxScore = _fixScore(self.comMaxScore)
        # _humMaxScore = _fixScore(self.humMaxScore)
        # HUMAN 0 COMPUTER 1
        result = (2 * role - 1) * (self.comMaxScore - self.humMaxScore * 10)  # TODO 玩家的权重

        # TODO 这里加了缓存,但是并没有提升速度(原注如此)
        if config.cache:
            self._evaluateCache[self.zobrist.code] = result

        return result

    def isWin(self, log=False):
        if log:
            _boardLogger.debug("check winner")

        def isFive(tmp_p: Place, role: Role):
            X, Y = self.X, self.Y
            count = 1

            delta = tmp_p[1] + 1
            while True:
                if delta >= Y or self.map[tmp_p[0]][delta] != role:
                    break
                count += 1
                delta += 1

            delta = tmp_p[1] - 1
            while True:
                if delta < 0 or self.map[tmp_p[0]][delta] != role:
                    break
                count += 1
                delta -= 1

            if count >= 5:
                return 1  # 横向

            count = 1
            delta = tmp_p[0] + 1
            while True:
                if delta >= X or self.map[delta][tmp_p[1]] != role:
                    break
                count += 1
                delta += 1
            delta = tmp_p[0] - 1
            while True:
                if delta < 0 or self.map[delta][tmp_p[1]] != role:
                    break
                count += 1
                delta -= 1

            if count >= 5:
                return 2  # 纵向

            count = 1
            delta = 1
            while True:
                if tmp_p[0] + delta >= X or tmp_p[1] + delta >= Y or self.map[tmp_p[0] + delta][tmp_p[1] + delta] != \
                        role:
                    break
                count += 1
                delta += 1
            delta = 1
            while True:
                if tmp_p[0] - delta < 0 or tmp_p[1] - delta < 0 or self.map[tmp_p[0] - delta][tmp_p[1] - delta] != role:
                    break
                count += 1
                delta += 1
            if count >= 5:
                return 3

            count = 1
            delta = 1
            while True:
                if tmp_p[0] + delta >= X or tmp_p[1] - delta < 0 or self.map[tmp_p[0] + delta][tmp_p[1] - delta] != \
                        role:
                    break
                count += 1
                delta += 1
            delta = 1
            while True:
                if tmp_p[0] - delta < 0 or tmp_p[1] + delta >= Y or self.map[tmp_p[0] - delta][tmp_p[1] + delta] != \
                        role:
                    break
                count += 1
                delta += 1
            if count >= 5:
                return 4

            return 0

        d = 0
        flag = False
        p: Place = Place(0, 0)
        r: Role = Role.BLANK
        for i in range(self.X):
            if flag:
                break
            for j in range(self.Y):
                r = self.map[i][j]
                p = Place(i, j)
                if r != Role.BLANK:
                    d = isFive(p, r)
                    if d:
                        flag = True
                        break

        match d:
            case 0:
                return ()
            case _:
                _boardLogger.warning(f"{r.name()} wins at Place(x={p[0]}, y={p[1]})")
                return r, p
