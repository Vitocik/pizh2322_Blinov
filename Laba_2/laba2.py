from typing import List

class ArrayBase:
   """
   Абстрактный базовый класс для работы с массивами.
   Позволяет хранить, сортировать, изменять и анализировать числовые массивы.
   """
   def __init__(self, size: int = 0):
       """
       Инициализация массива заданного размера.
       :param size: Размер массива, по умолчанию 0.
       """
       self._size = size
       self._data = [0] * size
   
   def __call__(self):
       """
       Вызываемый метод для возврата массива.
       :return: Список элементов массива.
       """
       return self._data
   
   def input_data(self, values: List[int]):
       """
       Заполняет массив переданными значениями (ограничение по размеру).
       :param values: Список значений для массива.
       """
       self._data = values[:self._size]
   
   def output_data(self):
       """
       Возвращает текущий массив.
       :return: Список элементов массива.
       """
       return self._data
   
   def min_max(self):
       """
       Определяет минимальное и максимальное значение в массиве.
       :return: Кортеж (минимальный элемент, максимальный элемент).
       """
       return min(self._data), max(self._data)
   
   def sort_array(self):
       """
       Сортирует массив по возрастанию.
       """
       self._data.sort()
   
   def sum_elements(self):
       """
       Возвращает сумму всех элементов массива.
       :return: Сумма элементов массива.
       """
       return sum(self._data)
   
   def __str__(self):
       """
       Преобразует массив в строку для удобного вывода.
       :return: Строковое представление массива.
       """
       return str(self._data)

class TArray(ArrayBase):
   """
   Класс для работы с одномерным массивом, расширяющий функциональность ArrayBase.
   """
   def __init__(self, size: int = 0, values: List[int] = None):
       """
       Инициализация одномерного массива с возможностью начальной инициализации данными.
       :param size: Размер массива.
       :param values: Начальный список значений.
       """
       super().__init__(size)
       if values:
           self.input_data(values)
   
   def __add__(self, value: int):
       """
       Перегрузка оператора + для добавления элемента в массив.
       :param value: Значение, которое добавляется в конец массива.
       :return: Объект TArray с обновленным массивом.
       """
       self._data.append(value)
       self._size += 1
       return self
   
   def __mul__(self, num: int):
       """
       Перегрузка оператора * для умножения каждого элемента массива на заданное число.
       :param num: Число, на которое умножаются элементы массива.
       :return: Объект TArray с обновленным массивом.
       """
       self._data = [x * num for x in self._data]
       return self
   
   def __call__(self):
       """
       Вызываемый метод, возвращает строку с данными массива.
       :return: Строковое представление массива.
       """
       return f"Массив: {self._data}"

# Пример использования
arr = TArray(5, [1, 2, 3, 4, 5])
print(arr())  # Вызываемый метод
arr + 6
print(arr.output_data())  # [1, 2, 3, 4, 5, 6]
arr * 2
print(arr.output_data())  # [2, 4, 6, 8, 10, 12]
