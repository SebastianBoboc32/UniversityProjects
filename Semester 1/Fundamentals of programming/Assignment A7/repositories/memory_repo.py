import copy

from src.domain.domain import Expense
import random


class RepoException(Exception):
    def __init__(self, message):
        self.__message = message

    @property
    def message(self):
        return self.__message


class MemoryRepo(object):

    def __init__(self):
        self._data = []

    def add(self, expense: Expense):
        if expense in self._data:
            raise ValueError("Expense already added")
        self._data.append(expense)

    def get_all(self):
        return self._data

    def change_data(self, new_lst):
        self._data = copy.deepcopy(new_lst)

    def add_rand(self):
        types = ["misc", "food", "tax", "utility", "hobbies", "gas"]
        expense = Expense(random.randint(1, 32), random.randint(100, 1001), random.choice(types))
        self._data.append(expense)


def test_memory_repo():

    mem_repo = MemoryRepo()
    assert len(mem_repo.get_all()) == 0

    mem_repo.add(Expense(1, 100, "bills"))

    lst = mem_repo.get_all()[0]
    assert str(lst) == "1,100,bills"

    expense = Expense(31, 200, "meds")

    try:
        mem_repo.add(expense)
    except RepoException:
        assert True

    try:
        mem_repo.add(lst)
    except RepoException:
        assert True


if __name__ == "__main__":
    test_memory_repo()
