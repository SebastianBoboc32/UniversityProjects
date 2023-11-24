from table.pattern import Pattern
import random


def inside(x_coord, y_coord):
    return x_coord in range(0, 6) and y_coord in range(0, 6)


class ComputerPlayer:
    def __init__(self, board):
        self.board = board

    def try_to_win(self):
        for i in range(6):
            for j in range(6):
                dx = [4, -4, 0, 0, 4, -4, 4, -4]
                dy = [0, 0, 4, -4, 4, -4, -4, 4]
                for q in range(2):
                    if inside(i, j) and inside(i+dx[q], j+dy[q]):
                        patt = Pattern([i, j], [i+dx[q], j+dy[q]], 5, "col", self.board)
                        patt.search_for_zeros()
                        if patt.zeros == 4:
                            if self.board[patt.prior_x, patt.prior_y] == " ":
                                self.board[patt.prior_x, patt.prior_y] = "0"
                                return True
                        else:
                            patt.search_for_xs()
                            if patt.xs == 4:
                                if self.board[patt.prior_x, patt.prior_y] == " ":
                                    self.board[patt.prior_x, patt.prior_y] = "X"
                                    return True
                for q in range(2, 4):
                    if inside(i, j) and inside(i+dx[q], j+dy[q]):
                        patt = Pattern([i, j], [i+dx[q], j+dy[q]], 5, "row", self.board)
                        patt.search_for_zeros()
                        if patt.zeros == 4:
                            if self.board[patt.prior_x, patt.prior_y] == " ":
                                self.board[patt.prior_x, patt.prior_y] = "0"
                                return True
                        else:
                            patt.search_for_xs()
                            if patt.xs == 4:
                                if self.board[patt.prior_x, patt.prior_y] == " ":
                                    self.board[patt.prior_x, patt.prior_y] = "X"
                                    return True
                for q in range(4, 8):
                    if inside(i, j) and inside(i + dx[q], j + dy[q]):
                        patt = Pattern([i, j], [i + dx[q], j + dy[q]], 5, "diag", self.board)
                        patt.search_for_zeros()
                        if patt.zeros == 4:
                            if self.board[patt.prior_x, patt.prior_y] == " ":
                                self.board[patt.prior_x, patt.prior_y] = "0"
                                return True
                        else:
                            patt.search_for_xs()
                            if patt.xs == 4:
                                if self.board[patt.prior_x, patt.prior_y] == " ":
                                    self.board[patt.prior_x, patt.prior_y] = "X"
                                    return True
        return False

    def second_best_move(self):
        for i in range(6):
            for j in range(6):
                dx = [3, -3, 0, 0, 3, -3, 3, -3]
                dy = [0, 0, 3, -3, 3, -3, -3, 3]
                for q in range(2):
                    if inside(i, j) and inside(i+dx[q], j+dy[q]):
                        patt = Pattern([i, j], [i+dx[q], j+dy[q]], 4, "col", self.board)
                        patt.search_for_zeros()
                        if patt.zeros == 3:
                            if self.board[patt.prior_x, patt.prior_y] == " ":
                                self.board[patt.prior_x, patt.prior_y] = "0"
                                return True
                        else:
                            patt.search_for_xs()
                            if patt.xs == 3:
                                if self.board[patt.prior_x, patt.prior_y] == " ":
                                    self.board[patt.prior_x, patt.prior_y] = "X"
                                    return True
                for q in range(2, 4):
                    if inside(i, j) and inside(i+dx[q], j+dy[q]):
                        patt = Pattern([i, j], [i+dx[q], j+dy[q]], 4, "row", self.board)
                        patt.search_for_zeros()
                        if patt.zeros == 3:
                            if self.board[patt.prior_x, patt.prior_y] == " ":
                                self.board[patt.prior_x, patt.prior_y] = "0"
                                return True
                        else:
                            patt.search_for_xs()
                            if patt.xs == 3:
                                if self.board[patt.prior_x, patt.prior_y] == " ":
                                    self.board[patt.prior_x, patt.prior_y] = "X"
                                    return True
                for q in range(4, 8):
                    if inside(i, j) and inside(i + dx[q], j + dy[q]):
                        patt = Pattern([i, j], [i + dx[q], j + dy[q]], 4, "diag", self.board)
                        patt.search_for_zeros()
                        if patt.zeros == 3:
                            if self.board[patt.prior_x, patt.prior_y] == " ":
                                self.board[patt.prior_x, patt.prior_y] = "0"
                                return True
                        else:
                            patt.search_for_xs()
                            if patt.xs == 3:
                                if self.board[patt.prior_x, patt.prior_y] == " ":
                                    self.board[patt.prior_x, patt.prior_y] = "X"
                                    return True
        return False

    def third_best_move(self):
        for i in range(6):
            for j in range(6):
                dx = [2, -2, 0, 0, 2, -2, 2, -2]
                dy = [0, 0, 2, -2, 2, -2, -2, 2]
                for q in range(2):
                    if inside(i, j) and inside(i+dx[q], j+dy[q]):
                        patt = Pattern([i, j], [i+dx[q], j+dy[q]], 3, "col", self.board)
                        patt.search_for_zeros()
                        if patt.zeros == 2:
                            if self.board[patt.prior_x, patt.prior_y] == " ":
                                self.board[patt.prior_x, patt.prior_y] = "0"
                                return True
                        else:
                            patt.search_for_xs()
                            if patt.xs == 2:
                                if self.board[patt.prior_x, patt.prior_y] == " ":
                                    self.board[patt.prior_x, patt.prior_y] = "X"
                                    return True
                for q in range(2, 4):
                    if inside(i, j) and inside(i+dx[q], j+dy[q]):
                        patt = Pattern([i, j], [i+dx[q], j+dy[q]], 3, "row", self.board)
                        patt.search_for_zeros()
                        if patt.zeros == 2:
                            if self.board[patt.prior_x, patt.prior_y] == " ":
                                self.board[patt.prior_x, patt.prior_y] = "0"
                                return True
                        else:
                            patt.search_for_xs()
                            if patt.xs == 2:
                                if self.board[patt.prior_x, patt.prior_y] == " ":
                                    self.board[patt.prior_x, patt.prior_y] = "X"
                                    return True
                for q in range(4, 8):
                    if inside(i, j) and inside(i + dx[q], j + dy[q]):
                        patt = Pattern([i, j], [i + dx[q], j + dy[q]], 3, "diag", self.board)
                        patt.search_for_zeros()
                        if patt.zeros == 2:
                            if self.board[patt.prior_x, patt.prior_y] == " ":
                                self.board[patt.prior_x, patt.prior_y] = "0"
                                return True
                        else:
                            patt.search_for_xs()
                            if patt.xs == 2:
                                if self.board[patt.prior_x, patt.prior_y] == " ":
                                    self.board[patt.prior_x, patt.prior_y] = "X"
                                    return True
        return False

    def fourth_best_move(self):
        for i in range(6):
            for j in range(6):
                dx = [1, -1, 0, 0, 1, -1, 1, -1]
                dy = [0, 0, 1, -1, 1, -1, -1, 1]
                for q in range(2):
                    if inside(i, j) and inside(i+dx[q], j+dy[q]):
                        patt = Pattern([i, j], [i+dx[q], j+dy[q]], 2, "col", self.board)
                        patt.search_for_zeros()
                        if patt.zeros == 1:
                            if self.board[patt.prior_x, patt.prior_y] == " ":
                                self.board[patt.prior_x, patt.prior_y] = "0"
                                return True
                        else:
                            patt.search_for_xs()
                            if patt.xs == 1:
                                if self.board[patt.prior_x, patt.prior_y] == " ":
                                    self.board[patt.prior_x, patt.prior_y] = "X"
                                    return True
                for q in range(2, 4):
                    if inside(i, j) and inside(i+dx[q], j+dy[q]):
                        patt = Pattern([i, j], [i+dx[q], j+dy[q]], 2, "row", self.board)
                        patt.search_for_zeros()
                        if patt.zeros == 1:
                            if self.board[patt.prior_x, patt.prior_y] == " ":
                                self.board[patt.prior_x, patt.prior_y] = "0"
                                return True
                        else:
                            patt.search_for_xs()
                            if patt.xs == 1:
                                if self.board[patt.prior_x, patt.prior_y] == " ":
                                    self.board[patt.prior_x, patt.prior_y] = "X"
                                    return True
                for q in range(4, 8):
                    if inside(i, j) and inside(i + dx[q], j + dy[q]):
                        patt = Pattern([i, j], [i + dx[q], j + dy[q]], 2, "diag", self.board)
                        patt.search_for_zeros()
                        if patt.zeros == 1:
                            if self.board[patt.prior_x, patt.prior_y] == " ":
                                self.board[patt.prior_x, patt.prior_y] = "0"
                                return True
                        else:
                            patt.search_for_xs()
                            if patt.xs == 1:
                                if self.board[patt.prior_x, patt.prior_y] == " ":
                                    self.board[patt.prior_x, patt.prior_y] = "X"
                                    return True
        return False

    def random_move(self):
        i = random.randint(0, 5)
        j = random.randint(0, 5)
        while self.board[i, j] != " ":
            i = random.randint(0, 5)
            j = random.randint(0, 5)
        self.board[i, j] = random.choice(["0", "X"])


