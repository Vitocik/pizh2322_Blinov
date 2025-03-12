import json

class Complex:
   """
   Класс для работы с комплексными числами.
   """
   def __init__(self, real: float, imag: float) -> None:
       """
       Инициализация объекта Complex.
       :param real: Действительная часть комплексного числа.
       :param imag: Мнимая часть комплексного числа.
       """
       self.real: float = real
       self.imag: float = imag
   
   def __str__(self) -> str:
       """
       Представление объекта в виде строки.
       :return: Строка с информацией о комплексном числе.
       """
       return f"{self.real} + {self.imag}i"
   
   def __add__(self, other: "Complex") -> "Complex":
       """
       Перегрузка оператора + для сложения комплексных чисел.
       :param other: Объект Complex.
       :return: Объект Complex.
       """
       return Complex(self.real + other.real, self.imag + other.imag)
   
   def __sub__(self, other: "Complex") -> "Complex":
       """
       Перегрузка оператора - для вычитания комплексных чисел.
       :param other: Объект Complex.
       :return: Объект Complex.
       """
       return Complex(self.real - other.real, self.imag - other.imag)
   
   def __mul__(self, other: "Complex") -> "Complex":
       """
       Перегрузка оператора * для умножения комплексных чисел.
       :param other: Объект Complex.
       :return: Объект Complex.
       """
       real: float = self.real * other.real - self.imag * other.imag
       imag: float = self.real * other.imag + self.imag * other.real
       return Complex(real, imag)
   
   def __truediv__(self, other: "Complex") -> "Complex":
       """
       Перегрузка оператора / для деления комплексных чисел.
       :param other: Объект Complex.
       :return: Объект Complex.
       """
       denom: float = other.real**2 + other.imag**2
       real: float = (self.real * other.real + self.imag * other.imag) / denom
       imag: float = (self.imag * other.real - self.real * other.imag) / denom
       return Complex(real, imag)
   
   @classmethod
   def from_string(cls, str_value: str) -> "Complex":
       """
       Создание объекта Complex из строки.
       :param str_value: Строка с комплексным числом.
       :return: Объект Complex.
       """
       real, imag = map(float, str_value.replace('i', '').split('+'))
       return cls(real, imag)
   
   def save(self, filename: str) -> None:
       """
       Сохранение комплексного числа в файл.
       :param filename: Имя файла.
       """
       with open(filename, 'w') as f:
           json.dump({'real': self.real, 'imag': self.imag}, f)
   
   @classmethod
   def load(cls, filename: str) -> "Complex":
       """
       Загрузка комплексного числа из файла.
       :param filename: Имя файла.
       :return: Объект Complex.
       """
       with open(filename, 'r') as f:
           data = json.load(f)
       return cls(data['real'], data['imag'])
