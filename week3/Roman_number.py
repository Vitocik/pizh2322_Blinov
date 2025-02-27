class Roman:
    """
    Класс для работы с римскими числами.
    Поддерживает преобразование римских чисел в арабские и обратно,
    а также арифметические операции: сложение, вычитание, умножение и деление.
    """
    
    ROMAN_TO_INT: dict[str, int] = {'I': 1, 'V': 5, 'X': 10, 'L': 50, 'C': 100, 'D': 500, 'M': 1000}
    INT_TO_ROMAN: list[tuple[int, str]] = [
        (1000, 'M'), (900, 'CM'), (500, 'D'), (400, 'CD'),
        (100, 'C'), (90, 'XC'), (50, 'L'), (40, 'XL'),
        (10, 'X'), (9, 'IX'), (5, 'V'), (4, 'IV'), (1, 'I')
    ]
    
    def __init__(self, value: str | int) -> None:
        """
        Инициализация объекта Roman.
        :param value: Римское число (str) или арабское число (int).
        :raises ValueError: Если передан недопустимый тип данных.
        """
        if isinstance(value, str):
            self.value: int = self.roman_to_int(value)
        elif isinstance(value, int):
            self.value: int = value
        else:
            raise ValueError("Недопустимый тип. Используйте str (римское число) или int.")
    
    @staticmethod
    def roman_to_int(roman: str) -> int:
        """
        Преобразует римское число в арабское.
        :param roman: Строка с римским числом.
        :return: Целое число.
        """
        total: int = 0
        prev_value: int = 0
        for char in reversed(roman):
            current_value: int = Roman.ROMAN_TO_INT[char]
            if current_value < prev_value:
                total -= current_value
            else:
                total += current_value
            prev_value = current_value
        return total
    
    @staticmethod
    def int_to_roman(number: int) -> str:
        """
        Преобразует арабское число в римское.
        :param number: Целое число.
        :return: Строка с римским числом.
        """
        result: str = ""
        for value, symbol in Roman.INT_TO_ROMAN:
            while number >= value:
                result += symbol
                number -= value
        return result
    
    def __add__(self, other: "Roman") -> "Roman":
        """
        Сложение двух римских чисел.
        :param other: Объект Roman.
        :return: Новый объект Roman.
        """
        return Roman(self.value + other.value)
    
    def __sub__(self, other: "Roman") -> "Roman":
        """
        Вычитание двух римских чисел.
        :param other: Объект Roman.
        :raises ValueError: Если результат меньше или равен нулю.
        :return: Новый объект Roman.
        """
        result: int = self.value - other.value
        if result <= 0:
            raise ValueError("Результат не является допустимым римским числом.")
        return Roman(result)
    
    def __mul__(self, other: "Roman") -> "Roman":
        """
        Умножение двух римских чисел.
        :param other: Объект Roman.
        :return: Новый объект Roman.
        """
        return Roman(self.value * other.value)
    
    def __truediv__(self, other: "Roman") -> "Roman":
        """
        Деление двух римских чисел (целочисленное деление).
        :param other: Объект Roman.
        :raises ZeroDivisionError: Если делитель равен нулю.
        :raises ValueError: Если результат равен нулю.
        :return: Новый объект Roman.
        """
        if other.value == 0:
            raise ZeroDivisionError("Деление на ноль недопустимо.")
        result: int = self.value // other.value
        if result == 0:
            raise ValueError("Результат не является допустимым римским числом.")
        return Roman(result)
    
    def __str__(self) -> str:
        """
        Представление объекта в виде строки (римское число).
        :return: Строка с римским числом.
        """
        return self.int_to_roman(self.value)


# Пример использования
num1 = Roman("X")
num2 = Roman("V")
result_add = num1 + num2
result_sub = num1 - num2
result_mul = num1 * num2
result_div = num1 / num2

print(f"{num1} + {num2} = {result_add} ({result_add.value})")  # X + V = XV (15)
print(f"{num1} - {num2} = {result_sub} ({result_sub.value})")  # X - V = V (5)
print(f"{num1} * {num2} = {result_mul} ({result_mul.value})")  # X * V = L (50)
print(f"{num1} / {num2} = {result_div} ({result_div.value})")  # X / V = II (2)