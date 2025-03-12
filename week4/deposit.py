# Программирование на языке высокого уровня (Python).
# Задание № 3.
#
# Выполнил: Блинов В.А.
# Группа: ПИЖ-б-о-23-2
# E-mail: viktor70797@gmail.com

from typing import Tuple, Dict


class TimeDeposit:
    """
    Класс для работы с вкладом на определенный срок.
    """

    def __init__(self, name: str, interest_rate: float, period_limit: Tuple[int, int], sum_limit: Tuple[float, float]) -> None:
        """
        Инициализация объекта TimeDeposit.
        :param name: Наименование вклада.
        :param interest_rate: Процентная ставка.
        :param period_limit: Ограничения по сроку вклада (кортеж из двух значений: минимальный и максимальный срок).
        :param sum_limit: Ограничения по сумме вклада (кортеж из двух значений: минимальная и максимальная сумма).
        """
        self.name: str = name
        self._interest_rate: float = interest_rate
        self._period_limit: Tuple[int, int] = period_limit
        self._sum_limit: Tuple[float, float] = sum_limit
        self._check_self()

    def __str__(self) -> str:
        """
        Представление объекта в виде строки.
        :return: Строка с информацией о вкладе.
        """
        return (f"Наименование:       {self.name}\n"
                f"Валюта:             {self.currency}\n"
                f"Процентная ставка:  {self._interest_rate}\n"
                f"Срок (мес.):        {self._period_limit}\n"
                f"Сумма:              {self._sum_limit}")

    @property
    def currency(self) -> str:
        """
        Валюта вклада.
        :return: Строка с валютой вклада.
        """
        return "руб."

    def _check_self(self) -> None:
        """
        Проверка корректности данных вклада.
        """
        assert 0 < self._interest_rate <= 100, "Неверно указан процент по вкладу!"
        assert 1 <= self._period_limit[0] < self._period_limit[1], "Неверно указаны ограничения по сроку вклада!"
        assert 0 < self._sum_limit[0] <= self._sum_limit[1], "Неверно указаны ограничения по сумме вклада!"

    def _check_user_params(self, initial_sum: float, period: int) -> None:
        """
        Проверка корректности данных пользователя.
        :param initial_sum: Начальная сумма вклада.
        :param period: Срок вклада.
        """
        assert self._sum_limit[0] <= initial_sum < self._sum_limit[1], "Условия вклада не соблюдены!"
        assert self._period_limit[0] <= period < self._period_limit[1], "Условия вклада не соблюдены!"

    def get_profit(self, initial_sum: float, period: int) -> float:
        """
        Расчет прибыли по вкладу.
        :param initial_sum: Начальная сумма вклада.
        :param period: Срок вклада.
        :return: Прибыль по вкладу.
        """
        self._check_user_params(initial_sum, period)
        return initial_sum * self._interest_rate / 100 * period / 12

    def get_sum(self, initial_sum: float, period: int) -> float:
        """
        Расчет общей суммы по вкладу.
        :param initial_sum: Начальная сумма вклада.
        :param period: Срок вклада.
        :return: Общая сумма по вкладу.
        """
        return initial_sum + self.get_profit(initial_sum, period)


class BonusTimeDeposit(TimeDeposit):
    """
    Класс для работы с бонусным вкладом на определенный срок.
    """

    def __init__(self, name: str, interest_rate: float, period_limit: Tuple[int, int], sum_limit: Tuple[float, float],
                 bonus: Dict[str, float]) -> None:
        """
        Инициализация объекта BonusTimeDeposit.
        :param name: Наименование вклада.
        :param interest_rate: Процентная ставка.
        :param period_limit: Ограничения по сроку вклада (кортеж из двух значений: минимальный и максимальный срок).
        :param sum_limit: Ограничения по сумме вклада (кортеж из двух значений: минимальная и максимальная сумма).
        :param bonus: Бонус (словарь с ключами 'percent' и 'sum').
        """
        self._bonus: Dict[str, float] = bonus
        super().__init__(name, interest_rate, period_limit, sum_limit)

    def __str__(self) -> str:
        """
        Представление объекта в виде строки.
        :return: Строка с информацией о бонусном вкладе.
        """
        return (super().__str__() + "\n"
                f"Бонус (%):          {self._bonus['percent']}\n"
                f"Бонус (мин. сумма): {self._bonus['sum']}")

    def _check_self(self) -> None:
        """
        Проверка корректности данных бонусного вклада.
        """
        super()._check_self()
        assert 'percent' in self._bonus and 'sum' in self._bonus, "Некорректные данные бонуса!"
        assert 0 <= self._bonus['percent'] <= 100, "Процент бонуса должен быть в пределах 0-100!"
        assert self._bonus['sum'] > 0, "Минимальная сумма для бонуса должна быть больше 0!"

    def get_profit(self, initial_sum: float, period: int) -> float:
        """
        Расчет прибыли по бонусному вкладу.
        :param initial_sum: Начальная сумма вклада.
        :param period: Срок вклада.
        :return: Прибыль по бонусному вкладу.
        """
        profit: float = super().get_profit(initial_sum, period)
        if initial_sum >= self._bonus['sum']:
            profit += profit * self._bonus['percent'] / 100
        return profit


class CompoundTimeDeposit(TimeDeposit):
    """
    Класс для работы с вкладом на определенный срок с капитализацией процентов.
    """

    def __str__(self) -> str:
        """
        Представление объекта в виде строки.
        :return: Строка с информацией о вкладе с капитализацией процентов.
        """
        return super().__str__() + "\nКапитализация %   : Да"

    def get_profit(self, initial_sum: float, period: int) -> float:
        """
        Расчет прибыли по вкладу с капитализацией процентов.
        :param initial_sum: Начальная сумма вклада.
        :param period: Срок вклада.
        :return: Прибыль по вкладу с капитализацией процентов.
        """
        self._check_user_params(initial_sum, period)
        return initial_sum * ((1 + self._interest_rate / 100 / 12) ** period - 1)


deposits_data: Dict[str, float | Tuple[int, int] | Tuple[float, float]] = {
    "interest_rate": 5,
    "period_limit": (6, 18),
    "sum_limit": (1000, 100000)
}

deposits: list[TimeDeposit] = [
    TimeDeposit("Сохраняй", **deposits_data), 
    BonusTimeDeposit("Бонусный 2", **deposits_data, bonus={"percent": 5, "sum": 2000}),
    CompoundTimeDeposit("С капитализацией", **deposits_data)
]


