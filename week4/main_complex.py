from complex import Complex

if __name__ == "__main__":
    # Создание объектов
    c1 = Complex(3, 4)
    c2 = Complex(1, 2)

    # Вывод объектов
    print("c1:", c1)
    print("c2:", c2)

    # Арифметические операции
    print("Сложение:", c1 + c2)
    print("Вычитание:", c1 - c2)
    print("Умножение:", c1 * c2)
    print("Деление:", c1 / c2)

    # Создание из строки
    c3 = Complex.from_string("5+6i")
    print("Из строки:", c3)

    # Сохранение и загрузка
    c1.save("complex.json")
    c_loaded = Complex.load("complex.json")
    print("Загруженный объект:", c_loaded)

#Пример вывода:

# c1: 3 + 4i
# c2: 1 + 2i
# Сложение: 4 + 6i
# Вычитание: 2 + 2i
# Умножение: -5 + 10i
# Деление: 2.2 - 0.4i
# Из строки: 5 + 6i
# Загруженный объект: 3 + 4i