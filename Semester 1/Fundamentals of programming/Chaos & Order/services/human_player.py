class HumanPlayer:
    def __init__(self, board):
        self.board = board

    def make_a_move(self, symbol, x_coord, y_coord):
        if self.board[x_coord, y_coord] is not " ":
            raise ValueError("Can't place there")
        self.board[[x_coord, y_coord]] = symbol


