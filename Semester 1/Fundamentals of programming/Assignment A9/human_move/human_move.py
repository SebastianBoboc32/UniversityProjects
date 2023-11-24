from src.computer_move.computer_move import Position
from src.domain.board import Board
import unittest


class HumanPlayer:
    def __init__(self, board):
        self._board = board
        self._symbol = "#"
        self._pieces = 9
        self.unused_pieces = 9
        self.can_move = True
        self.active_mill = False

    @property
    def symbol(self):
        return self._symbol

    @property
    def pieces(self):
        return self._pieces

    @pieces.setter
    def pieces(self, new_number):
        self._pieces = new_number

    def search_for_moves(self):
        for itt in self._board.playable_positions:
            if self._board.table[itt[0]][itt[1]] == self._symbol:
                current_position = Position(itt[0], itt[1])
                for sz in range(len(current_position.dx)):
                    xx = itt[0] + current_position.dx[sz]
                    yy = itt[1] + current_position.dy[sz]
                    if (xx, yy) in self._board.playable_positions:
                        if self._board.table[xx][yy] == "*":
                            return
        self.can_move = False

    def add_a_piece(self, x_coord, y_coord):
        if x_coord not in range(0, 19):
            raise ValueError("Number too big or too small")
        if y_coord not in range(0, 19):
            raise ValueError("Number too big or too small")
        if self._board.table[x_coord][y_coord] != "*":
            raise ValueError("Can't move there")
        if (x_coord, y_coord) not in self._board.playable_positions:
            raise ValueError("Can't move there")
        self._board.add_a_piece(x_coord, y_coord, self._symbol)
        self.unused_pieces -= 1

    def make_a_move(self, new_x, new_y, old_x, old_y):
        if new_x not in range(0, 19):
            raise ValueError("Number too big or too small")
        if new_y not in range(0, 19):
            raise ValueError("Number too big or too small")
        if old_x not in range(0, 19):
            raise ValueError("Number too big or too small")
        if old_y not in range(0, 19):
            raise ValueError("Number too big or too small")
        if (old_x, old_y) not in self._board.playable_positions:
            raise ValueError("Invalid position")
        if (new_x, new_y) not in self._board.playable_positions:
            raise ValueError("Invalid position")
        if self._board.table[old_x][old_y] in ["@", "*"]:
            raise ValueError("Invalid move")
        if self._board.table[new_x][new_y] in ["@", "#"]:
            raise ValueError("Invalid move")
        initial_position = Position(old_x, old_y)
        found = False
        for itt in range(len(initial_position.dx)):
            vrf_x = old_x + initial_position.dx[itt]
            vrf_y = old_y + initial_position.dy[itt]
            if (new_x, new_y) == (vrf_x, vrf_y):
                found = True
        if not found:
            raise ValueError("Invalid move")
        self._board.make_move(new_x, new_y, old_x, old_y, self._symbol)

    def take_out_computer_piece(self, x_coord, y_coord):
        if x_coord not in range(0, 19):
            raise ValueError("Number too big or too small")
        if y_coord not in range(0, 19):
            raise ValueError("Number too big or too small")
        if (x_coord, y_coord) not in self._board.playable_positions:
            raise ValueError("Invalid position")
        if self._board.table[x_coord][y_coord] != "@":
            raise ValueError("Computer piece not found")
        self._board.table[x_coord][y_coord] = "*"


class TestHumanPlayer(unittest.TestCase):
    def setUp(self) -> None:
        board = Board()
        player = HumanPlayer(board)
        self.player = player

    def test_add_a_piece(self):
        self.player.add_a_piece(0, 0)
        with self.assertRaises(ValueError):
            self.player.add_a_piece(0, 0)
        with self.assertRaises(ValueError):
            self.player.add_a_piece(7, 7)

    def test_make_a_move(self):
        self.player.add_a_piece(0, 0)
        self.player.make_a_move(0, 9, 0, 0)
        with self.assertRaises(ValueError):
            self.player.make_a_move(6, 6, 0, 0)
        with self.assertRaises(ValueError):
            self.player.make_a_move(18, 18, 8, 9)

    def test_take_out_computer_piece(self):
        self.player.add_a_piece(0, 0)
        with self.assertRaises(ValueError):
            self.player.take_out_computer_piece(6, 6)
        with self.assertRaises(ValueError):
            self.player.take_out_computer_piece(0, 0)
        with self.assertRaises(ValueError):
            self.player.take_out_computer_piece(7, 9)


if __name__ == "__main__":
    unittest.main()
