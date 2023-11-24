class A8Exception(Exception):

    def __init__(self, msg):
        self._msg = msg

    def __str__(self):
        return self._msg


class A8ValidationException(A8Exception):
    def __init__(self, error_list):
        self._errors = error_list

    def __str__(self):
        result = ' '
        for err in self._errors:
            result += err
            result += '\n'

        return result
