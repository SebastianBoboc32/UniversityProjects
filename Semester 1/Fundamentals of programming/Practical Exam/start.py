from src.domain.board import Board
from src.repo.repo import TextFileRepo
from src.service.controller import GameController
from src.ui.ui import UserInterface


if __name__ == "__main__":
    board = Board()
    repo = TextFileRepo("archive.txt", board)
    controller = GameController(repo, board)
    ui = UserInterface(board, repo, controller)
    ui.welcome()
    ui.game()
