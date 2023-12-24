import secrets


class Zobrist:
    _instance = None

    def __new__(cls, *args, **kwargs):
        if cls._instance is None:
            cls._instance = super().__new__(cls)
        return cls._instance

    def __init__(self, size=15):
        self.size = size
        self._init()

    def _init(self):
        self.map = [[self._rand() for _ in range(self.size ** 2)] for _ in range(2)]
        self.code = self._rand()

    @staticmethod
    def _rand():
        return secrets.randbits(64)

    def go(self, x, y, role):
        index = self.size * x + y
        self.code ^= self.map[role][index]
        return self.code
