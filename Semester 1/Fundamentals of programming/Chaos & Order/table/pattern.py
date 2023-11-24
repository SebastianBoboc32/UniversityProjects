class Pattern:
    def __init__(self, start, end, size, shape, board):
        self.xs = 0
        self.zeros = 0
        self.size = size
        self.start = start
        self.end = end
        self.shape = shape
        self.board = board
        self.prior_y = 0
        self.prior_x = 0
        if self.start[0] > self.end[0] or self.start[1] > self.end[1]:
            self.start, self.end = self.end, self.start

    def search_for_xs(self):
        if self.shape == "row":
            pointer = self.start
            while pointer[0] <= self.end[0] and pointer[1] <= self.end[1]:
                if self.board[pointer[0]][pointer[1]] == "X":
                    self.xs += 1
                elif self.board[pointer[0]][pointer[1]] == " ":
                    self.prior_x, self.prior_y = pointer[0], pointer[1]
                pointer[0] += 1

        elif self.shape == "col":
            pointer = self.start
            while pointer[0] <= self.end[0] and pointer[1] <= self.end[1]:
                if self.board[pointer[0]][pointer[1]] == "X":
                    self.xs += 1
                elif self.board[pointer[0]][pointer[1]] == " ":
                    self.prior_x, self.prior_y = pointer[0], pointer[1]
            pointer[1] += 1

        elif self.shape == "diag":
            if self.end[1]-self.start[1] == self.end[0]-self.start[0]:
                pointer = self.start
                while pointer[0] <= self.end[0] and pointer[1] <= self.end[1]:
                    if self.board[pointer[0]][pointer[1]] == "X":
                        self.xs += 1
                    elif self.board[pointer[0]][pointer[1]] == " ":
                        self.prior_x, self.prior_y = pointer[0], pointer[1]
                pointer[0] += 1
                pointer[1] += 1
            else:
                pointer = self.start
                while pointer[0] >= self.end[0] and pointer[1] <= self.end[1]:
                    if self.board[pointer[0]][pointer[1]] == "X":
                        self.xs += 1
                    elif self.board[pointer[0]][pointer[1]] == " ":
                        self.prior_x, self.prior_y = pointer[0], pointer[1]
                    pointer[0] -= 1
                    pointer[1] += 1

    def search_for_zeros(self):
        if self.shape == "row":
            pointer = self.start
            while pointer[0] <= self.end[0] and pointer[1] <= self.end[1]:
                if self.board[pointer[0]][pointer[1]] == "0":
                    self.zeros += 1
                elif self.board[pointer[0]][pointer[1]] == " ":
                    self.prior_x, self.prior_y = pointer[0], pointer[1]
                pointer[0] += 1

        elif self.shape == "col":
            pointer = self.start
            while pointer[0] <= self.end[0] and pointer[1] <= self.end[1]:
                if self.board[pointer[0]][pointer[1]] == "0":
                    self.zeros += 1
                elif self.board[pointer[0]][pointer[1]] == " ":
                    self.prior_x, self.prior_y = pointer[0], pointer[1]
                pointer[1] += 1

        elif self.shape == "diag":
            if self.end[1] - self.start[1] == self.end[0] - self.start[0]:
                pointer = self.start
                while pointer[0] <= self.end[0] and pointer[1] <= self.end[1]:
                    if self.board[pointer[0]][pointer[1]] == "0":
                        self.zeros += 1
                    elif self.board[pointer[0]][pointer[1]] == " ":
                        self.prior_x, self.prior_y = pointer[0], pointer[1]
                pointer[0] += 1
                pointer[1] += 1
            else:
                pointer = self.start
                while pointer[0] >= self.end[0] and pointer[1] <= self.end[1]:
                    if self.board[pointer[0]][pointer[1]] == "0":
                        self.zeros += 1
                    elif self.board[pointer[0]][pointer[1]] == " ":
                        self.prior_x, self.prior_y = pointer[0], pointer[1]
                    pointer[0] -= 1
                    pointer[1] += 1
