import random
import copy
import unittest


class Board:
    def __init__(self):
        arr = []
        for _ in range(19):
            arr.append("*")
        self.table = []
        for _ in range(19):
            self.table.append(copy.deepcopy(arr))
        self._playable_positions = [(0, 0), (0, 9), (0, 18), (3, 3), (3, 9), (3, 15),
                                    (6, 6), (6, 9), (6, 12), (9, 0), (9, 3), (9, 6), (9, 12),
                                    (9, 15), (9, 18), (12, 6), (12, 9), (12, 12),
                                    (15, 3), (15, 9), (15, 15), (18, 0), (18, 9), (18, 18)]
        random.shuffle(self._playable_positions)
        self._rows = 18
        self._cols = 18

    @property
    def playable_positions(self):
        return self._playable_positions

    def make_move(self, new_x, new_y, old_x, old_y, symbol):
        if (new_x, new_y) not in self._playable_positions:
            raise ValueError("Can't play there")
        self.table[new_x][new_y] = symbol
        self.table[old_x][old_y] = "*"

    def add_a_piece(self, x_coord, y_coord, symbol):
        if (x_coord, y_coord) not in self._playable_positions:
            raise ValueError("Can't add there")
        new_table = copy.deepcopy(self.table)
        new_table[x_coord][y_coord] = symbol
        self.table = copy.deepcopy(new_table)

    @property
    def mill(self):
        if self.table[0][0] == self.table[0][9] == self.table[0][18] and self.table[0][18] in ["@", "#"]:
            return self.table[0][0]
        elif self.table[0][0] == self.table[9][0] == self.table[18][0] and self.table[0][0] in ["@", "#"]:
            return self.table[0][0]
        elif self.table[18][0] == self.table[18][9] == self.table[18][18] and self.table[18][18] in ["@", "#"]:
            return self.table[18][0]
        elif self.table[0][18] == self.table[9][18] == self.table[18][18] and self.table[0][18] in ["@", "#"]:
            return self.table[0][18]
        elif self.table[3][3] == self.table[3][9] == self.table[3][15] and self.table[3][3] in ["@", "#"]:
            return self.table[3][3]
        elif self.table[3][3] == self.table[9][3] == self.table[15][3] and self.table[3][3] in ["@", "#"]:
            return self.table[3][3]
        elif self.table[3][15] == self.table[9][15] == self.table[15][15] and self.table[3][15] in ["@", "#"]:
            return self.table[3][15]
        elif self.table[15][3] == self.table[15][9] == self.table[15][15] and self.table[15][3] in ["@", "#"]:
            return self.table[15][3]
        elif self.table[6][6] == self.table[6][9] == self.table[6][12] and self.table[6][6] in ["@", "#"]:
            return self.table[6][6]
        elif self.table[6][6] == self.table[9][6] == self.table[12][6] and self.table[6][6] in ["@", "#"]:
            return self.table[6][6]
        elif self.table[12][6] == self.table[12][9] == self.table[12][12] and self.table[12][6] in ["@", "#"]:
            return self.table[12][6]
        elif self.table[6][12] == self.table[9][12] == self.table[12][12] and self.table[6][12] in ["@", "#"]:
            return self.table[6][12]
        elif self.table[0][9] == self.table[3][9] == self.table[6][9] and self.table[0][9] in ["@", "#"]:
            return self.table[0][9]
        elif self.table[9][0] == self.table[9][3] == self.table[9][6] and self.table[0][18] in ["@", "#"]:
            return self.table[9][0]
        elif self.table[18][9] == self.table[15][9] == self.table[12][9] and self.table[18][9] in ["@", "#"]:
            return self.table[18][9]
        elif self.table[9][12] == self.table[9][15] == self.table[9][18] and self.table[9][12] in ["@", "#"]:
            return self.table[9][12]
        return False

    def __str__(self):
        table = "   0      3         6       9        12      15       18\n"
        table += "0  "+self.table[0][0] + "------------------------" + self.table[0][9] + "------------------------" + \
                 self.table[0][18]+"\n"
        for _ in range(2):
            table += "   |" + "                        " + "|" + "                        " + "| \n"
        table += "3  |      " + self.table[3][3] + "-----------------" + self.table[3][9] + "---------------" +\
                 self.table[3][15]+"        |\n"
        for _ in range(2):
            table += "   |      |                 |               |        |\n"
        table += "6  |      |        " + self.table[6][6] + "--------" + self.table[6][9] + "--------" + \
                 self.table[6][12] + "      |        |\n"

        for _ in range(2):
            table += "   |      |        |                 |      |        |\n"

        table += "9  " + self.table[9][0] + "------" + self.table[9][3] + "--------" + self.table[9][6] \
                 + "                 " + self.table[9][12] +\
            "------" + self.table[9][15] + "--------" + self.table[9][18]+"\n"

        for _ in range(2):
            table += "   |      |        |                 |      |        |\n"

        table += "12 |      |        " + self.table[12][6] + "--------" + self.table[12][9] + "--------" + \
                 self.table[12][
            12] + "      |        |\n"

        for _ in range(2):
            table += "   |      |                 |               |        |\n"
        table += "15 |      " + self.table[15][3] + "-----------------" + self.table[15][9] + "---------------" +\
                 self.table[15][15] + "        |\n"
        for _ in range(2):
            table += "   |" + "                        " + "|" + "                        " + "| \n"
        table += "18 " + self.table[18][0] + "------------------------" + self.table[18][9] + \
                 "------------------------" + self.table[18][18] + "\n"
        return table


class TestTable(unittest.TestCase):
    def setUp(self) -> None:
        board = Board()
        self.board = board

    def test_make_move(self):
        x1 = 0
        y1 = 0
        x2 = 9
        y2 = 0
        self.board.make_move(x2, y2, x1, y1, "#")
        with self.assertRaises(ValueError):
            x1 = 0
            y1 = 1
            x2 = 9
            y2 = 10
            self.board.make_move(x1, y1, x2, y2, "#")

    def test_add_piece(self):
        x_coord = 0
        y_coord = 0
        self.board.add_a_piece(x_coord, y_coord, "#")
        with self.assertRaises(ValueError):
            x_coord = 1
            y_coord = 1
            self.board.add_a_piece(x_coord, y_coord, "$")


if __name__ == "__main__":
    unittest.main()
