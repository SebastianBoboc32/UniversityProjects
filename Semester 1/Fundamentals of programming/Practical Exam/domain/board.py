from texttable import Texttable
import copy


class Board:
    def __init__(self):
        self.data = []
        for row in range(6):
            self.data.append(6 * [" "])
        self.most_used = None
        self.nr_of_symbols = 0

    def __str__(self):
        tt = Texttable()
        for r in range(6):
            tt.add_row(self.data[r])
        return tt.draw()

    def add(self, x, y, symbol):
        if x not in range(0, 6) or y not in range(0, 6) or symbol not in ["X", "0"]:
            raise ValueError("...")
        if self.data[x][y] in ["0", "X"]:
            raise ValueError("overwrite")
        self.data[x][y] = symbol
        self.nr_of_symbols += 1

    def ovr(self, x, y, symbol):
        if x not in range(0, 6) or y not in range(0, 6):
            raise ValueError("...")
        self.data[x][y] = symbol

    def get(self, x, y):
        if x not in range(0, 6) or y not in range(0, 6):
            raise ValueError("...")
        return self.data[x][y]

    def get_all(self):
        return copy.deepcopy(self.data)

    def find_most_common(self):
        nr_x = 0
        nr_0 = 0
        for r in range(6):
            for c in range(6):
                if self.data[r][c] == "0":
                    nr_0 += 1
                elif self.data[r][c] == "X":
                    nr_x += 1
        if nr_0 >= nr_x:
            self.most_used = "0"
        else:
            self.most_used = "X"

    def check_chaos(self):
        nr_of_elements = 0
        for r in range(6):
            for c in range(6):
                if self.data[r][c] != " ":
                    nr_of_elements += 1
        return nr_of_elements == 36

    def check_order(self):
        is_order = False
        for i in range(6):
            if self.data[0][i] == self.data[1][i] == self.data[2][i] == self.data[3][i] == self.data[4][i] and self.data[0][i] != " ":
                is_order = True
            elif self.data[i][0] == self.data[i][1] == self.data[i][2] == self.data[i][3] == self.data[i][4] and self.data[i][0] != " ":
                is_order = True
            elif self.data[1][i] == self.data[2][i] == self.data[3][i] == self.data[4][i] == self.data[5][i] and self.data[1][i] != " ":
                is_order = True
            elif self.data[i][1] == self.data[i][2] == self.data[i][3] == self.data[i][4] == self.data[i][5] and self.data[i][1] != " ":
                is_order = True

        if not is_order:
            if self.data[0][0] == self.data[1][1] == self.data[2][2] == self.data[3][3] == self.data[4][4] and self.data[0][0] != " ":
                is_order = True
            elif self.data[1][1] == self.data[2][2] == self.data[3][3] == self.data[4][4] == self.data[5][5] and self.data[1][1] != " ":
                is_order = True
            elif self.data[1][0] == self.data[2][1] == self.data[3][2] == self.data[4][3] == self.data[5][4] and self.data[1][0] != " ":
                is_order = True
            elif self.data[0][1] == self.data[1][2] == self.data[2][3] == self.data[3][4] == self.data[4][5] and self.data[0][1] != " ":
                is_order = True
            if self.data[0][5] == self.data[1][4] == self.data[2][3] == self.data[3][2] == self.data[4][1] and self.data[0][5] != " ":
                is_order = True
            elif self.data[1][5] == self.data[2][4] == self.data[3][3] == self.data[4][2] == self.data[5][1] and self.data[1][5] != " ":
                is_order = True
            elif self.data[5][0] == self.data[4][1] == self.data[3][2] == self.data[2][3] == self.data[1][4] and self.data[5][0] != " ":
                is_order = True
            elif self.data[0][4] == self.data[1][3] == self.data[2][2] == self.data[3][1] == self.data[4][0] and self.data[0][4] != " ":
                is_order = True

        return is_order



if __name__ == "__main__":
    board = Board()
    print(str(board))