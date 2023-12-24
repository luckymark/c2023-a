_threshold = 1.15
_delta = 0.1
_infinitesimal = 0.01  # 无穷小


def equal(x, y):
    y = _infinitesimal if y == 0 else y
    return y / _threshold <= x <= y * _threshold if y >= 0 else y * _threshold <= x <= y / _threshold


def greater(x, y):
    return x >= (y + _delta) * _threshold if y >= 0 else x >= (y + _delta) / _threshold


def greaterEqual(x, y):
    return equal(x, y) or greater(x, y)


def less(x, y):
    return x <= (y - _delta) / _threshold if y >= 0 else x <= (y - _delta) * _threshold


def lessEqual(x, y):
    return equal(x, y) or less(x, y)
