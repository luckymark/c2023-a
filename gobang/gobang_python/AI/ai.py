import logging

from .static import *
import AI.config as config
from .negamax import deepenAll
from .board import Board

_aiLogger = logging.getLogger("GobangAI")


class WinError(Exception):
    pass


class AI:
    def __init__(self):
        _aiLogger.warning("init AI")
        self.board = Board()

    def begin(self):
        _aiLogger.info("AI's turn")
        if len(self.board.allSteps) > 1:
            # p = opening(self.board)
            ...
        p = deepenAll(self.board, None, config.searchDepth)
        _aiLogger.debug(f"AI's next step is Place({p.x}, {p.y}))")
        self.board.put(p, Role.COMPUTER, log=True)

        win = self.board.isWin(log=True)
        if win:
            role, p = win
            _aiLogger.info(f"{role.name()} at Place(x={p[0]}, y={p[1]})")
            raise WinError(role)

        return p

    def turn(self, place):
        _aiLogger.info(f"human's next step is Place({place.x}, {place.y})")
        self.set(place, Role.HUMAN)

        win = self.board.isWin(log=True)
        if win:
            role, p = win
            _aiLogger.info(f"{role.name()} at Place(x={p[0]}, y={p[1]})")
            raise WinError(role)

        return self.begin()

    def set(self, place, role):
        _aiLogger.debug(f"set Place({place.x}, {place.y}) to {role.name()}")
        self.board.put(place, role, log=True)
