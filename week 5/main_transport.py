# main.py

from transport import WaterVehicle, WheeledVehicle, Car

def main():
    # Тестирование WaterVehicle
    print("=== Тестирование WaterVehicle ===")
    boat = WaterVehicle("Лодка", "пресной")
    boat.start_engine()
    boat.sail()
    boat.stop_engine()
    print()

    # Тестирование WheeledVehicle
    print("=== Тестирование WheeledVehicle ===")
    truck = WheeledVehicle("Грузовик", "XYZ789")
    truck.start_engine()
    truck.accelerate(80)
    truck.drive()
    truck.stop_engine()
    print()

    # Тестирование Car
    print("=== Тестирование Car ===")
    car = Car("Toyota", "синий")
    car.start_engine()
    car.accelerate(60)
    car.drive(150)
    car.drive(200)
    car.honk()
    car.stop_engine()
    print()

if __name__ == "__main__":
    main()