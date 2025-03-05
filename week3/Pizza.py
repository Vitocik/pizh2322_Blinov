from typing import List

class Pizza:
    """
    Класс для работы с пиццей.
    Поддерживает создание пиццы с заданными параметрами и выполнение операций по приготовлению.
    """
   
    def __init__(self, name: str, dough: str, sauce: str, toppings: List[str], price: int) -> None:
        """
        Инициализация объекта Pizza.
        :param name: Название пиццы.
        :param dough: Тесто.
        :param sauce: Соус.
        :param toppings: Список топпингов.
        :param price: Цена пиццы.
        """
        self.name = name
        self.dough = dough
        self.sauce = sauce
        self.toppings = toppings
        self.price = price
   
    def __str__(self) -> str:
        """
        Представление объекта в виде строки.
        :return: Строка с информацией о пицце.
        """
        return f"{self.name}: {self.dough}, {self.sauce}, {', '.join(self.toppings)}, {self.price} руб."
   
    def prepare(self) -> str:
        """
        Подготовка пиццы.
        :return: Строка с описанием процесса подготовки.
        """
        return f"Готовим {self.name}: замешиваем {self.dough}, добавляем {self.sauce}, кладем {', '.join(self.toppings)}."
   
    def bake(self) -> str:
        """
        Выпекание пиццы.
        :return: Строка с описанием процесса выпекания.
        """
        return f"Выпекаем {self.name}."
   
    def cut(self) -> str:
        """
        Нарезка пиццы.
        :return: Строка с описанием процесса нарезки.
        """
        return f"Нарезаем {self.name}."
   
    def pack(self) -> str:
        """
        Упаковка пиццы.
        :return: Строка с описанием процесса упаковки.
        """
        return f"Упаковываем {self.name}."

class PepperoniPizza(Pizza):
    """
    Класс для работы с пиццей Пепперони.
    """
    def __init__(self) -> None:
        super().__init__("Пепперони", "среднее тесто", "томатный соус", ["пепперони", "сыр"], 500)

class BBQPizza(Pizza):
    """
    Класс для работы с пиццей Барбекю.
    """
    def __init__(self) -> None:
        super().__init__("Барбекю", "толстое тесто", "BBQ соус", ["курица", "лук", "сыр"], 600)

class SeafoodPizza(Pizza):
    """
    Класс для работы с пиццей Дары Моря.
    """
    def __init__(self) -> None:
        super().__init__("Дары Моря", "тонкое тесто", "сливочный соус", ["креветки", "мидии", "сыр"], 700)

class Order:
    """
    Класс для работы с заказом.
    Поддерживает добавление пицц в заказ, расчет общей стоимости и обработку заказа.
    """
    order_counter: int = 0

    def __init__(self) -> None:
        """
        Инициализация объекта Order.
        """
        self.ordered_pizzas: List[Pizza] = []
        Order.order_counter += 1
        self.order_id: int = Order.order_counter
   
    def __str__(self) -> str:
        """
        Представление объекта в виде строки.
        :return: Строка с информацией о заказе.
        """
        return f"Заказ #{self.order_id}: {', '.join(pizza.name for pizza in self.ordered_pizzas)}"
   
    def add_pizza(self, pizza: Pizza) -> None:
        """
        Добавление пиццы в заказ.
        :param pizza: Объект Pizza.
        """
        self.ordered_pizzas.append(pizza)
   
    def calculate_total(self) -> int:
        """
        Расчет общей стоимости заказа.
        :return: Общая стоимость заказа.
        """
        return sum(pizza.price for pizza in self.ordered_pizzas)
   
    def process_order(self) -> None:
        """
        Обработка заказа.
        """
        print(f"\nОбработка {self}")
        for pizza in self.ordered_pizzas:
            print(pizza.prepare())
            print(pizza.bake())
            print(pizza.cut())
            print(pizza.pack())
        print(f"\nИтоговая стоимость: {self.calculate_total()} руб.")
        print("Заказ выполнен!")

class Terminal:
    """
    Класс для работы с терминалом заказа пиццы.
    Поддерживает отображение меню, обработку ввода пользователя и прием оплаты.
    """
    def __init__(self) -> None:
        """
        Инициализация объекта Terminal.
        """
        self.menu: List[Pizza] = [PepperoniPizza(), BBQPizza(), SeafoodPizza()]
        self.order: Order = None
        self.display_menu: bool = True
   
    def __str__(self) -> str:
        """
        Представление объекта в виде строки.
        :return: Строка с информацией о терминале.
        """
        return "Терминал для заказа пиццы"

    def show_menu(self) -> None:
        """
        Отображение меню.
        """
        print("Меню:")
        for i, pizza in enumerate(self.menu, 1):
            print(f"{i}. {pizza}")

    def process_input(self) -> Order:
    """
    Обработка ввода пользователя.
    :return: Объект Order.
    """
    self.order = Order()  # Создаем новый заказ
    while True:  # Бесконечный цикл для выбора пицц
        self.show_menu()  # Показываем меню
        choice = input("Выберите пиццу (или '0' для завершения заказа): ")  # Запрашиваем выбор пользователя
        if choice == "0":  # Если пользователь ввел '0', завершаем выбор
            break
        if choice.isdigit() and 1 <= int(choice) <= len(self.menu):  # Проверяем корректность выбора
            self.order.add_pizza(self.menu[int(choice) - 1])  # Добавляем выбранную пиццу в заказ
            print(f"{self.menu[int(choice) - 1].name} добавлена в заказ.")  # Сообщаем о добавлении
        else:
            print("Некорректный выбор.")  # Сообщаем об ошибке, если выбор некорректен
    return self.order  # Возвращаем сформированный заказ

    def accept_payment(self) -> None:
        """
        Прием оплаты.
        """
        if self.order:
            print(f"Принята оплата на сумму {self.order.calculate_total()} руб.")

# Запуск терминала
terminal = Terminal()
order = terminal.process_input()
order.process_order()
terminal.accept_payment()
