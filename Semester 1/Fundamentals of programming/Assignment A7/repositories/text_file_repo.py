from src.repositories.memory_repo import *


class TextFileRepo(MemoryRepo):

    def __init__(self, file_name):
        super(TextFileRepo, self).__init__()
        self._file_name = file_name
        self._load_file()

    def _load_file(self):
        fin = open(self._file_name, "rt")
        lines = fin.readlines()
        fin.close()
        for line in lines:
            current_line = line.split(",")
            expense = Expense(int(current_line[0].strip()), int(current_line[1].strip()), current_line[2].strip())
            super().add(expense)

    def _save_file(self):
        fout = open(self._file_name, "wt")
        for obj in self.get_all():
            fout.write(str(obj))
            fout.write('\n')
        fout.close()

    def add(self, expense: Expense):
        super().add(expense)
        self._save_file()


def test_textfile_repo():

    text_repo = TextFileRepo("test_exp.txt")
    assert len(text_repo.get_all()) == 0

    text_repo.add(Expense(1, 100, "bills"))

    lst = text_repo.get_all()[0]
    assert str(lst) == "1,100,bills"

    expense = Expense(31, 200, "meds")

    try:
        text_repo.add(expense)
    except RepoException:
        assert True

    try:
        text_repo.add(lst)
    except RepoException:
        assert True


if __name__ == "__main__":
    test_textfile_repo()
