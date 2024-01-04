import logging
import datetime

import AI.config as config
from AI.ai import AI
from AI.board import Board, PlacePermissionError
from AI.static import *

map_ = Board()
gobang_ai: AI or None = None
logging.basicConfig(filename=datetime.date.today().strftime("./log/%Y%m%d.log"), filemode="a", encoding="utf-8",
                    datefmt="%y.%m.%d %H:%M:%S", level=logging.INFO,
                    format="%(lineno)d|%(asctime)s|%(levelname)s|%(name)s-%(threadName)s: %(message)s")
while True:
    d = input(">>>").lower().strip()
    if d == "start":
        gobang_ai = AI()
    elif d == "begin":
        print(gobang_ai.begin())
    elif d == "go":
        try:
            x, y = map(int, input().split())
        except Exception:
            continue
        print("AI's turn")
        try:
            print(gobang_ai.turn(Place(x, y)))
        except PlacePermissionError:
            print(f"You can't put chess here(x={x}, y={y})")
    elif d == "print":
        print(map_)
    elif d == "eval":
        try:
            print(eval(input()))
        except Exception as e:
            print(f"{e.__class__.__name__}: {e}")
    elif d == "exit":
        break
