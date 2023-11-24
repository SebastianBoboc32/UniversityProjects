from src.domain.domain import Expense
import copy
from src.repositories.memory_repo import MemoryRepo


class ServiceException(Exception):
    def __init__(self, message):
        self.__message = message

    @property
    def message(self):
        return self.__message


class ExpenseService:

    def __init__(self, repository):
        self._repo = repository
        self.operations = 0
        self._archive = []
        self._archive.append(copy.deepcopy(self._repo.get_all()))

    def add(self, expense: Expense):
        self._repo.add(expense)
        self._archive.append(copy.deepcopy(self._repo.get_all()))
        self.operations += 1

    def return_all(self):
        return self._repo.get_all()

    def filter(self, min_amount):
        if type(min_amount) != int:
            raise TypeError("This parameter must be a string")
        self._repo._data = list(filter(lambda x: x.amount > min_amount, copy.deepcopy(self._repo._data)))
        self.operations += 1
        self._archive.append(copy.deepcopy(self._repo.get_all()))

    def undo(self):
        if self.operations == 0:
            raise ValueError("Nothing to undo")

        self.operations -= 1
        self._repo.change_data(copy.deepcopy(self._archive[len(self._archive)-2]))
        _ = self._archive.pop()


def test_services():
    repository = MemoryRepo()
    service = ExpenseService(repository)
    service.operations += 1
    try:
        service.undo()
    except ServiceException:
        assert True

    try:
        service.filter("min_amount")
    except ServiceException:
        assert True


if __name__ == "__main__":
    test_services()
