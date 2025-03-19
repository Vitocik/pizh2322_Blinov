class Vehicle:
   """
   Класс для работы с транспортными средствами.
   """
   def __init__(self) -> None:
       """
       Инициализация объекта Vehicle.
       """
       self._speed: int = 0
       self.__engine_status: bool = False  
       self.model: str = "Неизвестно"  

   def start_engine(self) -> None:
       """
       Запуск двигателя.
       """
       self.__engine_status = True
       print(f"Двигатель {self.model} запущен.")

   def stop_engine(self) -> None:
       """
       Остановка двигателя.
       """
       self.__engine_status = False
       print(f"Двигатель {self.model} остановлен.")

   def drive(self) -> None:
       """
       Движение транспортного средства.
       """
       if self.__engine_status:
           print(f"Транспортное средство {self.model} движется со скоростью {self._speed} км/ч.")
       else:
           print("Двигатель выключен.")

   def __check_fuel(self) -> None:
       """
       Проверка уровня топлива.
       """
       print("Уровень топлива проверен.")

class WaterVehicle(Vehicle):
   """
   Класс для работы с водными транспортными средствами.
   """
   def __init__(self) -> None:
       """
       Инициализация объекта WaterVehicle.
       """
       super().__init__()
       self._buoyancy: str = "высокий"  
       self.__anchor_status: str = "поднят"  
       self.water_type: str = "соленая"  

   def sail(self) -> None:
       """
       Плавание судна.
       """
       if self._Vehicle__engine_status:
           print(f"Судно {self.model} плывет по {self.water_type} воде.")
           self.__lower_anchor() 
       else:
           print("Двигатель выключен.")

   def __lower_anchor(self) -> None:  
       """
       Опускание якоря.
       """
       self.__anchor_status = "опущен"
       print("Якорь опущен.")

class WheeledVehicle(Vehicle):
   """
   Класс для работы с колесными транспортными средствами.
   """
   def __init__(self) -> None:
       """
       Инициализация объекта WheeledVehicle.
       """
       super().__init__()
       self._wheel_count: int = 4
       self.__tire_pressure: int = 32
       self.license_plate: str = "ABC123"  

   def accelerate(self, speed: int) -> None:
       """
       Увеличение скорости.
       :param speed: Скорость.
       """
       self._speed = speed
       print(f"Скорость {self.model} увеличена до {self._speed} км/ч.")

   def __check_tires(self) -> None:
       """
       Проверка давления в шинах.
       """
       print(f"Давление в шинах: {self.__tire_pressure} psi.")

class Car(WheeledVehicle):
   """
   Класс для работы с автомобилями.
   """
   def __init__(self) -> None:
       """
       Инициализация объекта Car.
       """
       super().__init__()
       self._passenger_count: int = 5  
       self.__odometer: int = 0  
       self.color: str = "красная"  

   def honk(self) -> None:
       """
       Сигнал автомобиля.
       """
       print(f"{self.model} сигналит: Бип-бип!")

   def drive(self, distance: int) -> None:
       """
       Движение автомобиля.
       :param distance: Расстояние.
       """
       if self._Vehicle__engine_status:
           self.__odometer += distance
           print(f"{self.model} проехал {distance} км. Общий пробег: {self.__odometer} км.")
       else:
           print("Двигатель выключен.")

   def __update_odometer(self, distance: int) -> None: 
       """
       Обновление пробега.
       :param distance: Расстояние.
       """
       self.__odometer += distance
       print(f"Пробег обновлен: {self.__odometer} км.")