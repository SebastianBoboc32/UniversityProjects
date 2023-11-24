class TextFileRepo:
    def __init__(self, file_name, board):
        self.data = []
        self._file_name = file_name
        self.board = board

    def save_file(self):
        fout = open(self._file_name, "wt")
        self.data = self.board.get_all()
        for i in range(6):
            for j in range(6):
                if self.data[i][j] in ["0", "X"]:
                    fout.write(self.data[i][j])
                else:
                    fout.write(".")
            fout.write("\n")
        fout.close()

    def load_file(self):
        fin = open(self._file_name, "rt")
        lines = fin.readlines()
        i = 0
        all_lines = []
        for line in lines:
            current_line = line.strip()
            all_lines.append(line)
        fin.close()
        for i in range(6):
            for j in range(6):
                if all_lines[i][j] in ["0", "X"]:
                    self.board.ovr(i, j, all_lines[i][j])
                else:
                    self.board.ovr(i, j, " ")

"""
if __name__ == "__main__":
    board = Board()
    repo = TextFileRepo("test_repo.txt", board)
    for _ in range(5):
        okay = False
        while not okay:
            try:
                x = random.randint(0, 5)
                y = random.randint(0, 5)
                repo.board.add(x, y, "0")
            except ValueError:
                pass
            else:
                okay = True

    print(str(repo.board))
    repo.save_file()
    for _ in range(5):
        okay = False
        while not okay:
            try:
                x = random.randint(0, 5)
                y = random.randint(0, 5)
                repo.board.add(x, y, "0")
            except ValueError:
                pass
            else:
                okay = True
    repo.load_file()
    print(str(repo.board))
"""


