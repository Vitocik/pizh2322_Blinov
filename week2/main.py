from abc import ABC, abstractmethod

class ArrayBase(ABC):
   """Абстрактный базовый класс для массивов."""
   @abstractmethod
   def add_element(self, value):
       """
       Метод для добавления элемента в массив.
       :param value: Значение для добавления.
       """
       pass

   @abstractmethod
   def sort(self):
       """Метод для сортировки массива."""
       pass

   @abstractmethod
   def find_min_max(self):
       """
       Метод для поиска минимального и максимального элемента.
       :return: Кортеж с минимальным и максимальным элементами.
       """
       pass

class TArray(ArrayBase):
   """Класс для работы с одномерным массивом."""
   def __init__(self, elements=None):
       """
       Инициализация одномерного массива.
       :param elements: Список значений для ввода.
       """
       self._elements = elements if elements is not None else []
   
   def add_element(self, value):
       """
       Метод для добавления элемента в массив.
       :param value: Значение для добавления.
       """
       self._elements.append(value)
   
   def __str__(self):
       """
       Метод для преобразования массива в строку.
       :return: Строка с данными массива.
       """
       return str(self._elements)
   
   def __call__(self):
       """
       Вызываемый метод, который возвращает сумму элементов массива.
       :return: Сумма элементов.
       """
       return sum(self._elements)
   
   def find_min_max(self):
       """
       Метод для поиска минимального и максимального элемента.
       :return: Кортеж с минимальным и максимальным элементами.
       """
       if not self._elements:
           return None, None
       return min(self._elements), max(self._elements)
   
   def sort(self):
       """Метод для сортировки массива."""
       self._elements.sort()
   
   def __add__(self, value):
       """
       Перегрузка оператора + для добавления элемента.
       :param value: Значение для добавления.
       :return: Объект TArray.
       """
       if isinstance(value, (int, float)):
           return TArray(self._elements + [value])
       raise TypeError("Неподдерживаемый тип для добавления")
   
   def __mul__(self, number):
       """
       Перегрузка оператора * для умножения элементов массива на число.
       :param number: Число для умножения.
       :return: Объект TArray.
       """
       if isinstance(number, (int, float)):
           return TArray([x * number for x in self._elements])
       raise TypeError("Умножение поддерживает только значения int или float")
   
   def sum_elements(self):
       """
       Метод для поиска суммы элементов массива.
       :return: Сумма элементов.
       """
       return sum(self._elements)

# Композиция
class ArrayHandler:
   """Класс для обработки массива."""
   def __init__(self, array: TArray):
       """
       Инициализация объекта ArrayHandler.
       :param array: Объект TArray.
       """
       self.array = array
   
   def process(self):
       """
       Метод для сортировки массива и поиска минимального и максимального элемента.
       :return: Кортеж с минимальным и максимальным элементами.
       """
       self.array.sort()
       return self.array.find_min_max()

# Пример использования
arr = TArray([3, 1, 4, 1, 5, 9])
print("Исходный массив:", arr)
arr.sort()
print("Отсортированный массив:", arr)
print("Минимальный и максимальный элемент:", arr.find_min_max())
print("Сумма элементов:", arr())
arr2 = arr + 7
print("После добавления 7:", arr2)
arr3 = arr * 2
print("После умножения на 2:", arr3)
