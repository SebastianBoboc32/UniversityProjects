import random
import unittest
from src.domain.board import Board


class Position:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    @property
    def dx(self):
        dx = []
        if (self.x, self.y) in [(0, 0), (0, 18), (18, 0), (18, 18)]:
            dx = [9, -9, 0, 0]
        elif (self.x, self.y) in [(3, 3), (3, 15), (15, 3), (15, 15)]:
            dx = [6, -6, 0, 0]
        elif (self.x, self.y) in [(6, 6), (6, 12), (12, 6), (12, 12), (6, 9), (9, 6), (12, 9), (9, 12)]:
            dx = [3, -3, 0, 0]
        elif (self.x, self.y) in [(3, 9), (9, 3), (15, 9), (9, 15)]:
            dx = [3, -3, 6, -6, 0, 0, 0, 0]
        elif (self.x, self.y) in [(0, 9), (9, 0), (18, 9), (9, 18)]:
            dx = [3, -3, 9, -9, 0, 0, 0, 0]
        return dx

    @property
    def dy(self):
        dy = []
        if (self.x, self.y) in [(0, 0), (0, 18), (18, 0), (18, 18)]:
            dy = [0, 0, 9, -9]
        elif (self.x, self.y) in [(3, 3), (3, 15), (15, 3), (15, 15)]:
            dy = [0, 0, 6, -6]
        elif (self.x, self.y) in [(6, 6), (6, 12), (12, 6), (12, 12), (6, 9), (9, 6), (12, 9), (9, 12)]:
            dy = [0, 0, 3, -3]
        elif (self.x, self.y) in [(3, 9), (9, 3), (15, 9), (9, 15)]:
            dy = [0, 0, 0, 0, 3, -3, 6, -6]
        elif (self.x, self.y) in [(0, 9), (9, 0), (18, 9), (9, 18)]:
            dy = [0, 0, 0, 0, 3, -3, 9, -9]
        return dy


class ComputerPlayer:
    def __init__(self, board):
        self._board = board
        self._symbol = "@"
        self.pieces = 9
        self.unused_pieces = 9
        self.made_mill = False
        self.blocked_mill = False
        self.can_move = True
        self.acive_mill = False

    def inside(self, x, y):
        if x not in range(0, 19):
            return False
        return y in range(0, 19)

    @property
    def board(self):
        return self._board

    @property
    def symbol(self):
        return self._symbol

    def first_move(self):
        x, y = random.choice(self._board.playable_positions)
        self._board.table[x][y] = self._symbol

    def try_to_make_a_mill(self):
        for itt in self._board.playable_positions:
            if self._board.table[itt[0]][itt[1]] == self._symbol:
                current_pos = Position(itt[0], itt[1])
                for dirr in range(len(current_pos.dx)):
                    new_x = itt[0] + current_pos.dx[dirr]
                    new_y = itt[1] + current_pos.dy[dirr]
                    if self.inside(new_x, new_y) and (new_x, new_y) in self._board.playable_positions and \
                        self._board.table[new_x][new_y] == "*":
                        curr_pos = Position(new_x, new_y)
                        near_symbols = []
                        for direction in range(len(curr_pos.dx)):
                            x_new = new_x + curr_pos.dx[direction]
                            y_new = new_y + curr_pos.dy[direction]
                            if self.inside(x_new, y_new) and (x_new, y_new) in self._board.playable_positions and \
                                self._board.table[x_new][y_new] == self._symbol and (x_new, y_new) != (itt[0], itt[1]) and \
                                    (x_new == itt[0] or y_new == itt[1]):
                                near_symbols.append((x_new, y_new))
                                new_pos = Position(x_new, y_new)
                                for dir in range(len(new_pos.dx)):
                                    new_xx = x_new + new_pos.dx[dir]
                                    new_yy = y_new + new_pos.dy[dir]
                                    if (new_xx, new_yy) in self._board.playable_positions and self._board.table[new_xx][new_yy] == self._symbol \
                                    and (new_xx, new_yy) not in [(itt[0], itt[1]), (x_new, y_new)] and (new_xx == x_new or new_yy == y_new):
                                        near_symbols.append((new_xx, new_yy))
                                        if len(near_symbols) > 1:
                                            self.board.make_move(itt[0], itt[1], new_x, new_y, self._symbol)
                                            self.made_mill = True
                                            return
                        if len(near_symbols) > 1:
                            self.board.make_move(itt[0], itt[1], new_x, new_y)
                            self.made_mill = True
                            return

    def try_to_block_a_mill(self):
        for itt in self._board.playable_positions:
            if self._board.table[itt[0]][itt[1]] == self._symbol:
                current_pos = Position(itt[0], itt[1])
                for dirr in range(len(current_pos.dx)):
                    new_x = itt[0] + current_pos.dx[dirr]
                    new_y = itt[1] + current_pos.dy[dirr]
                    if self.inside(new_x, new_y) and (new_x, new_y) in self._board.playable_positions and \
                        self._board.table[new_x][new_y] == "*":
                        curr_pos = Position(new_x, new_y)
                        near_symbols = []
                        for direction in range(len(curr_pos.dx)):
                            x_new = new_x + curr_pos.dx[direction]
                            y_new = new_y + curr_pos.dy[direction]
                            if self.inside(x_new, y_new) and (x_new, y_new) in self._board.playable_positions and \
                                self._board.table[x_new][y_new] == "#" and (x_new, y_new) != (itt[0], itt[1]) and \
                                    (x_new == itt[0] or y_new == itt[1]):
                                near_symbols.append((x_new, y_new))
                                new_pos = Position(x_new, y_new)
                                for dir in range(len(new_pos.dx)):
                                    new_xx = x_new + new_pos.dx[dir]
                                    new_yy = y_new + new_pos.dy[dir]
                                    if (new_xx, new_yy) in self._board.playable_positions and self._board.table[new_xx][
                                        new_yy] == "#" \
                                            and (new_xx, new_yy) not in [(itt[0], itt[1]), (x_new, y_new)] and (
                                            new_xx == x_new or new_yy == y_new):
                                        near_symbols.append((new_xx, new_yy))
                                        if len(near_symbols) > 1:
                                            self.board.make_move(itt[0], itt[1], new_x, new_y)
                                            self.made_mill = True
                                            return
                        if len(near_symbols) > 1:
                            self.board.make_move(itt[0], itt[1], new_x, new_y, self._symbol)
                            self.blocked_mill = True
                            return

    def random_move_in_pregame(self):
        for itt in self._board.playable_positions:
            if self._board.table[itt[0]][itt[1]] == self._symbol:
                current_pos = Position(itt[0], itt[1])
                for direction in range(len(current_pos.dx)):
                    new_x = itt[0] + current_pos.dx[direction]
                    new_y = itt[1] + current_pos.dy[direction]
                    if self.inside(new_x, new_y) and (new_x, new_y) in self._board.playable_positions and \
                        self._board.table[new_x][new_y] == "*":
                        self._board.add_a_piece(new_x, new_y, self._symbol)
                        self.unused_pieces -= 1
                        return
        for itt in self._board.playable_positions:
            if self._board.table[itt[0]][itt[1]] == "*":
                self._board.add_a_piece(itt[0], itt[1], self._symbol)
                self.unused_pieces -= 1
                return

    def take_out_human_piece(self):
        for itt in self._board.playable_positions:
            if self._board.table[itt[0]][itt[1]] == "#":
                self._board.table[itt[0]][itt[1]] = "*"
                return

    def try_to_make_a_mill_in_pregame(self):
        for itt in self._board.playable_positions:
            if self._board.table[itt[0]][itt[1]] == "*":
                current_position = Position(itt[0], itt[1])
                near_symbols = []
                for dirr in range(len(current_position.dx)):
                    new_x = itt[0] + current_position.dx[dirr]
                    new_y = itt[1] + current_position.dy[dirr]
                    if (new_x, new_y) in self._board.playable_positions and self._board.table[new_x][new_y] == self._symbol \
                        and (new_x == itt[0] or new_y == itt[1]):
                        near_symbols.append((new_x, new_y))
                        new_position = Position(new_x, new_y)
                        for dir in range(len(new_position.dx)):
                            x_new = new_x + new_position.dx[dir]
                            y_new = new_y + new_position.dy[dir]
                            if (x_new, y_new) in self._board.playable_positions and self._board.table[x_new][
                                y_new] == self._symbol \
                                    and ((x_new, y_new) != (itt[0], itt[1])) and (x_new == itt[0] or y_new == itt[1]):
                                near_symbols.append((x_new, y_new))
                                if len(near_symbols) > 1:
                                    self._board.add_a_piece(itt[0], itt[1], self._symbol)
                                    self.blocked_mill = True
                                    self.unused_pieces -= 1
                                    return
                if len(near_symbols) > 1:
                    self._board.add_a_piece(itt[0], itt[1], self._symbol)
                    self.made_mill = True
                    self.unused_pieces -= 1
                    return

    def try_to_block_a_mill_in_pregame(self):
        for itt in self._board.playable_positions:
            if self._board.table[itt[0]][itt[1]] == "*":
                current_position = Position(itt[0], itt[1])
                near_symbols = []
                for dirr in range(len(current_position.dx)):
                    new_x = itt[0] + current_position.dx[dirr]
                    new_y = itt[1] + current_position.dy[dirr]
                    if (new_x, new_y) in self._board.playable_positions and self._board.table[new_x][new_y] == "#" \
                        and (new_x == itt[0] or new_y == itt[1]):
                        near_symbols.append((new_x, new_y))
                        new_position = Position(new_x, new_y)
                        for dir in range(len(new_position.dx)):
                            x_new = new_x + new_position.dx[dir]
                            y_new = new_y + new_position.dy[dir]
                            if(x_new, y_new) in self._board.playable_positions and self._board.table[x_new][y_new] == "#" \
                                and ((x_new, y_new) != (itt[0], itt[1])) and (x_new == itt[0] or y_new == itt[1]):
                                near_symbols.append((x_new, y_new))
                                if len(near_symbols) > 1:
                                    self._board.add_a_piece(itt[0], itt[1], self._symbol)
                                    self.blocked_mill = True
                                    self.unused_pieces -= 1
                                    return
                    if len(near_symbols) > 1:
                        self._board.add_a_piece(itt[0], itt[1], self._symbol)
                        self.blocked_mill = True
                        self.unused_pieces -= 1
                        return

    def random_move(self):
        for itt in self._board.playable_positions:
            if self._board.table[itt[0]][itt[1]] == self._symbol:
                current_pos = Position(itt[0], itt[1])
                for direction in range(len(current_pos.dx)):
                    new_x = itt[0] + current_pos.dx[direction]
                    new_y = itt[1] + current_pos.dy[direction]
                    if self.inside(new_x, new_y) and (new_x, new_y) in self._board.playable_positions and \
                        self._board.table[new_x][new_y] == "*":
                        self._board.make_move(new_x, new_y, itt[0], itt[1], self._symbol)
                        return
        for itt in self._board.playable_positions:
            if self._board.table[itt[0]][itt[1]] == "*":
                return
        self.can_move = False


class TestComputerPlayer(unittest.TestCase):
    def setUp(self) -> None:
        board = Board()
        self._board = board
        computer_player = ComputerPlayer(board)
        self._computer_player = computer_player

    def test_try_to_block_a_mill_in_pregame(self):
        self._board.table[0][0] = "#"
        self._board.table[0][18] = "#"
        self._computer_player.try_to_block_a_mill_in_pregame()
        self.assertEqual(self._board.table[0][9], "@")

    def test_try_to_make_a_mill_in_pregame(self):
        self._board.table[0][0] = "@"
        self._board.table[0][18] = "@"
        self._board.table[0][9] = "*"
        self._computer_player.try_to_make_a_mill_in_pregame()
        self.assertEqual(self._board.table[0][9], "@")

    def test_try_to_block_a_mill(self):
        self._board.table[0][9] = "#"
        self._board.table[0][18] = "#"
        self._board.table[9][0] = "@"
        print(str(self._board))
        self._computer_player.try_to_block_a_mill()
        self.assertEqual(self._computer_player.blocked_mill, False)

    def test_try_to_make_a_mill(self):
        self._board.table[0][0] = "@"
        self._board.table[0][18] = "@"
        self._board.table[0][9] = "*"
        self._board.table[3][9] = "@"
        self._computer_player.try_to_make_a_mill()
        self.assertEqual(self._computer_player.made_mill, False)


if __name__ == "__main__":
    unittest.main()


