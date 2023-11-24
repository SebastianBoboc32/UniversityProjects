class UserInterface:
    def __init__(self, board, repo, service):
        self._board = board
        self._repo = repo
        self._service = service
        self.active_player = "bot"

    def welcome(self):
        print(str(self._board))
        print("1.New game")
        print("2.Load game")
        print("Select an action")
        token = int(input())
        if token == 2:
            self._repo.load_file()

    def game(self):
        while True:
            if self.active_player == "bot":
                self._service.comp_random_move()
                stop = self._board.check_chaos()
                if stop:
                    print(str(self._board))
                    print("Chaos wins")
                    return
                else:
                    stop = self._board.check_order()
                    if stop:
                        print(str(self._board))
                        print("Order wins")
                        return
                self.active_player = "human"
            elif self.active_player == "human":
                print(str(self._board))
                print("Choose an action")
                print("1.Make a move")
                print("2.Save")
                print("3.Load most recent save")
                print("0.Exit")
                token = int(input())
                if token == 1:
                    print(str(self._board))
                    okay = False
                    while not okay:
                        try:
                            x = int(input("Select x coord: "))
                            y = int(input("Select y coord: "))
                            symbol = input("Symbol")
                            self._board.add(x, y, symbol)
                        except ValueError:
                            print("Illegal move,try again")
                        else:
                            okay = True
                elif token == 2:
                    self._repo.save_file()
                elif token == 3:
                    self._repo.load_file()
                elif token == 0:
                    return
                stop = self._board.check_chaos()
                if stop:
                    print(str(self._board))
                    print("Chaos wins")
                    return
                else:
                    stop = self._board.check_order()
                    if stop:
                        print(str(self._board))
                        print("Order wins")
                        return
                self.active_player = "bot"


