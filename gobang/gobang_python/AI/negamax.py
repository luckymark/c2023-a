import time
import logging

import AI.config as config
import AI.comparer as comparer
from .static import *
from .board import Board

MAX = float("inf")
MIN = -MAX
_cache: dict[int, Leaf] = {}

_negamaxLogger = logging.getLogger("Negamax")


def _r(board: Board, depth: int, alpha: float, beta: float, role: Role, step: int):  # , steps, spread) -> Leaf:
    """
    if config.cache:
        c = _cache.get(board.zobrist.code)
        if c is not None:
            if c.depth >= depth:  # 如果缓存中的结果搜索深度不比当前小，则结果完全可用
                return Leaf(c.score, step + c.step, steps)

            else:  # 如果缓存的结果中搜索深度比当前小，那么任何一方出现双三及以上结果的情况下可用
                if comparer.greatOrEqualThan(c.score, Score.FOUR) or comparer.littleOrEqualThan(c.score, -Score.FOUR):
                    return Leaf(c.score, step + c.step, steps)
    """

    score = board.evaluate(role)
    leaf = Leaf(score, step)  # , steps)
    if depth <= 0 or comparer.greaterEqual(score, Score.FIVE) or comparer.lessEqual(score, -Score.FIVE):
        # 可以试着在这里加算杀
        return leaf

    best = Leaf(MIN, step)  # , steps)
    # 双方个下两个子之后，开启 star spread 模式
    candidates = board.generator(role, step > 1 if board.turn > 10 else step > 3, step > 1)
    if not candidates:
        return leaf

    for candidate in candidates:
        _depth = depth - 1
        # _spread = spread
        #
        # if spread < config.spreadLimit:
        #   # 冲四延伸
        #   if (role == Role.COMPUTER and candidate.scoreHum >= Score.FIVE) or \
        #         (role == Role.HUMAN and candidate.scoreCom >= Score.FIVE):
        #       _depth += 2
        #       _spread += 1
        #
        # _steps = steps + [candidate]
        board.put(candidate, role)
        v = _r(board, _depth, -beta, -alpha, Role(1 - role), step + 1)  # , _steps, _spread)
        board.remove(candidate)
        v.score = -v.score
        if v.score > best.score:  # 原作者是大于
            best = v
        alpha = max(alpha, best.score)
        if comparer.greaterEqual(v.score, beta):
            v.score = MAX - 1  # 剪枝,标记为极大值;原作者是 MAX-1
            v.abCut = True
            return v  # 不做缓存
    # """
    # 缓存
    _cacheLeaf(board, best, depth)
    # """
    return best


def _cacheLeaf(board: Board, leaf: Leaf, depth: int):
    if not config.cache:
        return
    if leaf.abCut:
        return
    obj = Leaf(leaf.score, leaf.step)  # , leaf.steps)
    obj.depth = depth
    _cache[board.zobrist.code] = obj


def negamax(board: Board, candidates: list[Place], role: Role, depth: int, alpha: float, beta: float) -> float or int:
    _negamaxLogger.debug(f"negamax(candidates={candidates}, role={role}, depth={depth}, alpha={alpha}, beta={beta}")
    start = time.time()
    board.currentSteps = []

    for candidate in candidates:
        board.put(candidate, role)
        # steps = [candidate]
        v = _r(board, depth, -beta, -alpha, Role(1 - role), 1)  # , steps[:], 0)
        v.score = -v.score
        alpha = max(alpha, v.score)
        board.remove(candidate)
        # candidate.v = v  # 此处修改了candidates
        candidate.score = v.score
        candidate.step = v.step
        _negamaxLogger.debug(f"Place({candidate.x}, {candidate.y}): value={v}, score={v.score}, step={v.step}")

        # 超时
        if time.time() - start > config.timeLimit * 1000:
            _negamaxLogger.warning(f"negamax timeout({time.time() - start} > {config.timeLimit * 1000})")
            break

    return alpha


def deepening(board: Board, candidates: list[Place], role: Role, depth: int) -> Place:
    _negamaxLogger.debug(f"deepening(candidates={candidates}, role={role}, depth={depth})")
    _cache.clear()
    # score = float("-inf")
    for d in range(1, depth + 1):
        score = negamax(board, candidates, role, d, MIN, MAX)
        if comparer.greaterEqual(score, Score.FIVE):
            break  # 必胜

    # candidate.score>0 时有优势, step 越短越好; <0 则是劣势,需要 step 越长越好
    # candidates = sorted(candidates, key=lambda x: (x.score, x.step * int(x.step < 0)), reverse=True)
    # for j in range(len(candidates) - 1, 0, -1):
    a = candidates[0]
    for j in range(1, len(candidates)):
        # a, b = candidates[j - 1], candidates[j]
        b = candidates[j]
        if comparer.equal(a.score, b.score):
            if a.score >= 0:
                if a.step != b.step:
                    if a.step <= b.step:
                        continue
                else:
                    if b.score <= a.score:
                        continue
            else:
                if a.step != b.step:
                    if b.step <= a.step:
                        continue
                else:
                    if b.score <= a.score:
                        continue
        else:
            if b.score <= a.score:
                continue

        # candidates[j], candidates[j - 1] = candidates[j - 1], candidates[j]
        a = b

    # return candidates[0]
    return a


def deepenAll(board: Board, role: Role or None, depth: int or None = None) -> Place:
    role = role if role else Role.COMPUTER
    depth = config.searchDepth if depth is None else depth
    candidates = board.generator(role, log=True)

    _negamaxLogger.info(f"deepenAll(role={role.name()}, depth={depth}, candidates={candidates})")
    if len(candidates) == 1:
        result = candidates[0]
    else:
        result = deepening(board, candidates, role, depth)

    _negamaxLogger.info(f"result={result}, candidates={[str(i) for i in candidates]}")
    return result
