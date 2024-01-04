import enum


class Color(enum.IntEnum):
    BLANK = 2
    BLACK = 0
    WHITE = 1


class Char(enum.Enum):
    BLANK = " "
    BLACK = "■"
    WHITE = "o"


class Role(enum.IntEnum):
    HUMAN = 0
    COMPUTER = 1
    BLANK = 2

    def name(self) -> str:
        return ("HUMAN", "COMPUTER", "BLANK")[self]


class Leaf:
    def __init__(self, score, step=None, steps=None):
        self.score = score
        self.step = step
        # self.steps = steps
        self.abCut = False
        self.depth = 0

    def __repr__(self):
        return f"Leaf({self.score}, {self.step})"  # , {self.steps})"


class Place:
    def __init__(self, x, y, v: Leaf = None, role: Role = Role.BLANK):
        self.x = x
        self.y = y
        self.v = v
        self.role = role
        self.score = self.scoreCom = self.scoreHum = 0
        self.step = self.min = 0

    def __str__(self):
        result = f"Place({self.x}, {self.y}, role={self.role.name()}"
        if self.score:
            result += f", score={self.score}"
        if self.scoreCom:
            result += f", Computer's score={self.scoreCom}"
        if self.scoreHum:
            result += f", Human's score={self.scoreHum}"
        if self.step:
            result += f", step={self.step}"
        if self.min:
            result += f", min={self.min}"
        result += ")"
        return result

    def __repr__(self):
        result = f"Place({self.x}, {self.y}"
        if self.role != Role.BLANK:
            result += f", role={self.role.name()}"
        result += ")"
        return result

    def __iter__(self):
        yield self.x
        yield self.y

    def __getitem__(self, key):
        if key == 0:
            return self.x
        elif key == 1:
            return self.y
        else:
            raise KeyError(f"bad key '{key}'")

    def __hash__(self):
        return hash((self.x, self.y))

    def __eq__(self, other):
        try:
            it = iter(other)
            x = next(it)
            y = next(it)
            return self.x == x and self.y == y
        except Exception:
            return NotImplemented


class Score(enum.IntEnum):
    ONE = 10
    TWO = 100
    THREE = 1000
    FOUR = 10000
    FIVE = 100000
    BLOCKED_ONE = 1
    BLOCKED_TWO = 10
    BLOCKED_THREE = 100
    BLOCKED_FOUR = 10000
