from src.domain.board import Board
from src.human_move.human_move import HumanPlayer
from src.computer_move.computer_move import ComputerPlayer
import time


class UserInterface:
    def __init__(self, board, computer_player, human_player):
        self.board = board
        self.computer_player = computer_player
        self.human_player = human_player
        self.game_over = False
        self.current_player = None

    @staticmethod
    def print_instructions():
        print("\n\n")
        print("INSTRUCTIONS:")
        print("TYPE THE COORDINATES FOR YOUR DESIRED MOVES")
        print("e.g. x: 0 and y: 9 selects the cell of coordinates 0 and 9 ")
        print("HOW TO PLAY:")
        print("The basic aim of Nine Mens Morris is to make mills \n"
              "- vertical or horizontal lines of three in a row. Every time this is achieved an opponent's piece is "
              "removed,\n"
              " , the overall objective being to reduce the number of opponent's pieces to less than three")
        print("\n\n")

    def pre_game(self):
        self.current_player = self.human_player
        while self.human_player.unused_pieces > 0 or self.computer_player.unused_pieces > 0:
            print("Remaining player pieces: " + str(self.human_player.unused_pieces))
            print("Remaining computer pieces: " + str(self.computer_player.unused_pieces))
            if self.current_player == self.human_player:
                self.current_player = self.computer_player
                print(str(self.board))
                print("Add a piece")
                print("Select the position of the piece")
                okay = False
                while not okay:
                    try:
                        x_coord = int(input("x: "))
                        y_coord = int(input("y: "))
                        self.human_player.add_a_piece(x_coord, y_coord)
                    except ValueError:
                        print("Couldn't make the move")
                        print("Try again")
                    else:
                        okay = True
                print(str(self.board))
                if self.board.mill == self.human_player.symbol and not human_player.active_mill:
                    print("Take out a piece from the computer player")
                    okay = False
                    while not okay:
                        try:
                            x = int(input("x: "))
                            y = int(input("y: "))
                            self.human_player.take_out_computer_piece(x, y)
                            human_player.active_mill = True
                            self.computer_player.pieces -= 1
                        except ValueError:
                            print("Couldn't take out that piece")
                            print("Try again")
                        else:
                            okay = True
                else:
                    human_player.active_mill = False
            elif self.current_player == self.computer_player:
                self.current_player = self.human_player
                self.computer_player.made_mill = False
                self.computer_player.blocked_mill = False
                self.computer_player.try_to_block_a_mill_in_pregame()
                if not self.computer_player.blocked_mill:
                    self.computer_player.try_to_make_a_mill_in_pregame()
                    if not self.computer_player.made_mill:
                        self.computer_player.random_move_in_pregame()
                if self.board.mill == self.computer_player.symbol and not computer_player.active_mill:
                    self.computer_player.take_out_human_piece()
                    self.human_player.pieces -= 1
                    computer_player.active_mill = True
                else:
                    computer_player.active_mill = False

    def game(self):
        beginning = time.perf_counter()
        self.current_player = self.human_player
        while self.human_player.pieces > 2 or self.computer_player.pieces > 2:
            if self.current_player == self.human_player:
                self.human_player.search_for_moves()
                if not self.human_player.can_move:
                    print("Computer wins!")
                    return
                self.current_player = self.computer_player
                print(str(self.board))
                print("Move a piece")
                okay = False
                while not okay:
                    try:
                        print("Select the position to move from")
                        x_coord = int(input("x: "))
                        y_coord = int(input("y: "))
                        print("Select the position to move to")
                        x_new = int(input("x: "))
                        y_new = int(input("y: "))
                        self.human_player.make_a_move(x_new, y_new, x_coord, y_coord)
                    except ValueError:
                        print("Couldn't make the move")
                        print("Try again")
                    else:
                        okay = True
                print(str(self.board))
                if self.board.mill == self.human_player.symbol and not human_player.active_mill:
                    print("Take out a piece from the computer player")

                    okay = False
                    while not okay:
                        try:
                            x = int(input("x: "))
                            y = int(input("y: "))
                            self.human_player.take_out_computer_piece(x, y)
                            self.computer_player.pieces -= 1
                            human_player.active_mill = True
                        except ValueError:
                            print("Couldn't take out that piece,try again")
                        else:
                            okay = True
                else:
                    human_player.active_mill = False
            elif self.current_player == self.computer_player:
                self.current_player = self.human_player
                self.computer_player.made_mill = False
                self.computer_player.blocked_mill = False
                self.computer_player.try_to_block_a_mill()
                if not self.computer_player.blocked_mill:
                    self.computer_player.try_to_make_a_mill()
                    if not self.computer_player.made_mill:
                        self.computer_player.random_move()
                if self.board.mill == self.computer_player.symbol and not computer_player.active_mill:
                    self.computer_player.take_out_human_piece()
                    self.human_player.pieces = self.human_player.pieces - 1
                    computer_player.active_mill = True
                else:
                    computer_player.active_mill = False
                if not self.computer_player.can_move:
                    print("You win!")
                    return
            current_time = time.perf_counter()
            if current_time-beginning > 300:
                print("It's a tie")
                return
        if self.human_player.pieces == 2:
            print("Computer wins!")
        else:
            print("You win!")


if __name__ == "__main__":
    board = Board()
    computer_player = ComputerPlayer(board)
    human_player = HumanPlayer(board)
    ui = UserInterface(board, computer_player, human_player)
    ui.print_instructions()
    ui.pre_game()
    ui.game()
