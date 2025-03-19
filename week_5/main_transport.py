# main.py

from transport import WaterVehicle, WheeledVehicle, Car

def main():
# Тестирование WaterVehicle
    print("=== Тестирование WaterVehicle ===")
    boat = WaterVehicle()
    boat.model = "Лодка"
    boat.water_type = "пресной"
    boat.start_engine()
    boat.sail()
    boat.stop_engine()
    print()

    # Тестирование WheeledVehicle
    print("=== Тестирование WheeledVehicle ===")
    truck = WheeledVehicle()
    truck.model = "Грузовик"
    truck.license_plate = "XYZ789"
    truck.start_engine()
    truck.accelerate(80)
    truck.drive()
    truck.stop_engine()
    print()

    # Тестирование Car
    print("=== Тестирование Car ===")
    car = Car()
    car.model = "Toyota"
    car.color = "синий"
    car.start_engine()
    car.accelerate(60)
    car.drive(150)
    car.drive(200)
    car.honk()
    car.stop_engine()
    print()

if __name__ == "__main__":
    main()

# Вывод программы:

# === Тестирование WaterVehicle ===
# Двигатель Лодка запущен.
# Судно Лодка плывет по пресной воде.
# Якорь опущен.
# Двигатель Лодка остановлен.
#
# === Тестирование WheeledVehicle ===
# Двигатель Грузовик запущен.
# Скорость Грузовик увеличена до 80 км/ч.
# Транспортное средство Грузовик движется со скоростью 80 км/ч.
# Двигатель Грузовик остановлен.
#
# === Тестирование Car ===
# Двигатель Toyota запущен.
# Скорость Toyota увеличена до 60 км/ч.
# Toyota проехал 150 км. Общий пробег: 150 км.
# Toyota проехал 200 км. Общий пробег: 350 км.
# Toyota сигналит: Бип-бип!
# Двигатель Toyota остановлен.