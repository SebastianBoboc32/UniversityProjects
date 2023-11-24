from services.human_player import HumanPlayer
from services.computer_player import ComputerPlayer
from table.board import Board


class UserInterface:
    def __init__(self, board, human_player, computer_player):
        self.board = board
        self.human_player = human_player
        self.computer_player = computer_player
        self.current_player = human_player
        self.game_over = False

    @staticmethod
    def welcome_message():
        print("Make a move by writing: x_coord y_coord symbol")
        print("For example 3 3 X")

    def first_move(self):
        self.computer_player.random_move()

    def game(self):
        while True:
            if self.current_player == self.human_player:
                print("Make a move")
                okay = False
                while not okay:
                    try:
                        x_coord, y_coord, symbol = input().split()
                        x_coord, y_coord = int(x_coord), int(y_coord)
                        self.human_player.make_a_move(symbol, x_coord, y_coord)
                    except ValueError:
                        print("Illegal move,try again")
                    else:
                        okay = True
                if self.board.check_order():
                    self.game_over = True
                    print("Computer won!")
                    return
                elif self.board.check_chaos():
                    self.game_over = True
                    print("You win!")
                    return
                self.current_player = self.computer_player
            elif self.computer_player == self.current_player:
                if not self.current_player.try_to_win():
                    if not self.current_player.second_best_move():
                        if not self.current_player.third_best_move():
                            if not self.current_player.fourth_best_move():
                                self.current_player.random_move()
                if self.board.check_order():
                    self.game_over = True
                    print("Computer won!")
                    return
                elif self.board.check_chaos():
                    self.game_over = True
                    print("You win!")
                    return
                self.current_player = self.human_player
            print(str(self.board))


if __name__ == "__main__":
    board = Board()
    human_player = HumanPlayer(board)
    computer_player = ComputerPlayer(board)
    ui = UserInterface(board, human_player, computer_player)
    ui.welcome_message()
    ui.first_move()
    ui.game()







