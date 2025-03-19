import json
from typing import List

class ComplexContainer:
   """
   Класс для работы с контейнером комплексных чисел.
   """
   def __init__(self) -> None:
       """
       Инициализация объекта ComplexContainer.
       """
       self._data: List[complex] = []

   def __str__(self) -> str:
       """
       Представление объекта в виде строки.
       :return: Строка с информацией о контейнере.
       """
       return str(self._data)

   def __getitem__(self, index: int) -> complex:
       """
       Получение элемента по индексу.
       :param index: Индекс элемента.
       :return: Элемент контейнера.
       """
       return self._data[index]

   def add(self, value: complex) -> None:
       """
       Добавление комплексного числа в контейнер.
       :param value: Комплексное число.
       """
       if isinstance(value, complex):
           self._data.append(value)
       else:
           raise ValueError("Допускаются только комплексные числа")

   def remove(self, index: int) -> None:
       """
       Удаление элемента из контейнера по индексу.
       :param index: Индекс элемента.
       """
       if 0 <= index < len(self._data):
           del self._data[index]
       else:
           raise IndexError("Индекс вне диапазона")

   def save(self, filename: str) -> None:
       """
       Сохранение контейнера в файл.
       :param filename: Имя файла.
       """
       with open(filename, 'w') as file:
           json.dump([{'real': c.real, 'imag': c.imag} for c in self._data], file)

   def load(self, filename: str) -> None:
       """
       Загрузка контейнера из файла.
       :param filename: Имя файла.
       """
       with open(filename, 'r') as file:
           self._data = [complex(c['real'], c['imag']) for c in json.load(file)]
