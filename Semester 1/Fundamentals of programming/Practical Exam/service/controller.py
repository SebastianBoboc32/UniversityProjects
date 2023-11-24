import random
import unittest
from src.domain.board import Board


class GameController:
    def __init__(self, repo, board):
        self.repo = repo
        self.board = board

    def add_symbol(self, x, y, val):
        self.board.add(x, y, val)

    def save_file(self):
        self.repo.save_file()

    def load_file(self):
        self.repo.load_file()

    def comp_random_move(self):
        x = random.randint(0, 5)
        y = random.randint(0, 5)
        while self.board.data[x][y] != " ":
            x = random.randint(0, 5)
            y = random.randint(0, 5)
        self.board.add(x, y, random.choice(["X", "0"]))
        """
        This function tries a random place on the board,
        if it's empty,then it will place a random symbol there
        else,it will randomly search for an empty position and
        will place there
        """


class TestCompPlayer(unittest.TestCase):
    def setUp(self) -> None:
        self.board = Board()

    def test_random_moves(self):
        for _ in range(5):
            okay = False
            while not okay:
                try:
                    x = random.randint(0, 5)
                    y = random.randint(0, 5)
                    self.board.add(x, y, random.choice(["0", "X"]))
                except ValueError:
                    pass
                else:
                    okay = True
        self.assertEqual(self.board.nr_of_symbols, 5)


if __name__ == "__main__":
    unittest.main()

