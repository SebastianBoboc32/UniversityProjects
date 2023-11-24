from src.domain.domain import Expense
from src.repositories.memory_repo import MemoryRepo, RepoException
import pickle


class BinaryFileRepo(MemoryRepo):

    def __init__(self, file_name="expenses.bin"):
        super(BinaryFileRepo, self).__init__()
        self._file_name = file_name
        self._load_file()

    def _load_file(self):
        fin = open(self._file_name, "rb")
        obj = pickle.load(fin)
        for expense in obj:
            super().add(expense)
        fin.close()

    def add(self, expense: Expense):
        super().add(expense)
        self._save_file()

    def _save_file(self):
        fout = open(self._file_name, "wb")
        pickle.dump(self.get_all(), fout)
        fout.close()

    def add_random(self):
        super().add_rand()
        self._save_file()


def test_bin_repo():
    bin_repo = BinaryFileRepo("test_exp.bin")
    assert len(bin_repo.get_all()) == 1
    bin_repo.add(Expense(12, 500, "food"))
    expense = bin_repo.get_all()[0]
    assert str(expense) == "12,500,food"

    try:
        bin_repo.add(expense)
    except RepoException:
        assert True
