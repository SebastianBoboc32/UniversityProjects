from texttable import Texttable
import random
import unittest
from table.pattern import Pattern


class Board:
    def __init__(self):
        self._data = []
        for row in range(6):
            self._data.append(6 * [" "])
        self.patterns = []
        self.most_used = None

    def __str__(self):
        tt = Texttable()
        for r in range(6):
            tt.add_row(self._data[r])
        return tt.draw()

    def __setitem__(self, key, value):
        if key[0] not in range(0, 6) or key[1] not in range(0, 6):
            raise ValueError("Invalid index")
        if value not in ["X", "0"]:
            raise ValueError("Invalid symbol")
        self._data[key[0]][key[1]] = value

    def __getitem__(self, key):
        if key[0] not in range(0, 6) or key[1] not in range(0, 6):
            raise ValueError("Invalid index")
        return self._data[key[0]][key[1]]

    def find_most_common(self):
        nr_x = 0
        nr_0 = 0
        for r in range(6):
            for c in range(6):
                if self._data[r][c] == "0":
                    nr_0 += 1
                elif self._data[r][c] == "X":
                    nr_x += 1
        if nr_0 >= nr_x:
            self.most_used = "0"
        else:
            self.most_used = "X"

    def check_chaos(self):
        nr_of_elements = 0
        for r in range(6):
            for c in range(6):
                if self._data[r][c] != " ":
                    nr_of_elements += 1
        return nr_of_elements == 36

    def check_order(self):
        for i in range(6):
            for j in range(2):
                patt = Pattern([i, j], [i, j+4], 5, "col", self._data)
                patt.search_for_xs()
                if patt.xs == 5:
                    return True
                else:
                    patt.search_for_zeros()
                    if patt.zeros == 5:
                        return True
        for i in range(6):
            for j in range(2):
                patt = Pattern([i, j], [i+4, j], 5, "row", self._data)
                patt.search_for_xs()
                if patt.xs == 5:
                    return True
                else:
                    patt.search_for_zeros()
                    if patt.zeros == 5:
                        return True
        patt = Pattern([0, 0], [4, 4], 5, "diag", self._data)
        patt.search_for_xs()
        if patt.xs == 5:
            return True
        else:
            patt.search_for_zeros()
            if patt.zeros == 5:
                return True
        patt = Pattern([1, 0], [5, 4], 5, "diag", self._data)
        patt.search_for_xs()
        if patt.xs == 5:
            return True
        else:
            patt.search_for_zeros()
            if patt.zeros == 5:
                return True
        patt = Pattern([0, 1], [4, 5], 5, "diag", self._data)
        patt.search_for_xs()
        if patt.xs == 5:
            return True
        else:
            patt.search_for_zeros()
            if patt.zeros == 5:
                return True
        patt = Pattern([5, 0], [0, 5], 5, "diag", self._data)
        patt.search_for_xs()
        if patt.xs == 5:
            return True
        else:
            patt.search_for_zeros()
            if patt.zeros == 5:
                return True
        patt = Pattern([4, 0], [0, 4], 5, "diag", self._data)
        patt.search_for_xs()
        if patt.xs == 5:
            return True
        else:
            patt.search_for_zeros()
            if patt.zeros == 5:
                return True
        patt = Pattern([5, 1], [1, 5], 5, "diag", self._data)
        patt.search_for_xs()
        if patt.xs == 5:
            return True
        else:
            patt.search_for_zeros()
            if patt.zeros == 5:
                return True
        return False


class TestBoard(unittest.TestCase):
    def setUp(self) -> None:
        self.board = Board()

    def test_str(self):
        print(str(self.board))

    def test_get_item(self):
        self.board[4, 2] = "X"
        self.assertEqual(self.board[4, 2], "X")
        with self.assertRaises(ValueError):
            print(self.board[6, 7])

    def test_set_item(self):
        self.board[3, 3] = "0"
        with self.assertRaises(ValueError):
            self.board[0, 6] = "0"
        with self.assertRaises(ValueError):
            self.board[2, 2] = "F"

    def test_check_chaos(self):
        symbols = ["X", "0"]
        for i in range(6):
            for j in range(6):
                self.board[i, j] = random.choice(symbols)
        self.assertEqual(self.board.check_chaos(), True)

    def test_check_order(self):
        for i in range(6):
            self.board[i, 0] = "X"
        self.assertEqual(self.board.check_order(), True)
        for i in range(6):
            self.board[i, i] = "0"
        self.assertEqual(self.board.check_order(), True)
        self.board[5, 1] = self.board[4, 2] = self.board[3, 3] = self.board[2, 4] = self.board[1, 5] = "0"
        self.assertEqual(self.board.check_order(), True)

    def test_find_most_used(self):
        for i in range(3):
            self.board[i, 0] = "0"
        for i in range(5):
            self.board[5, i] = "X"
        self.board.find_most_common()
        self.assertEqual(self.board.most_used, "X")


