from complex import Complex

if __name__ == "__main__":
    try:
        # Создание объектов
        c1 = Complex(3, 4)
        c2 = Complex(1, 2)

        # Вывод объектов
        print("c1:", c1)  # Ожидаемый вывод: 3 + 4i
        print("c2:", c2)  # Ожидаемый вывод: 1 + 2i

        # Арифметические операции
        print("Сложение:", c1 + c2)  # Ожидаемый вывод: 4 + 6i
        print("Вычитание:", c1 - c2)  # Ожидаемый вывод: 2 + 2i
        print("Умножение:", c1 * c2)  # Ожидаемый вывод: -5 + 10i
        print("Деление:", c1 / c2)    # Ожидаемый вывод: 2.2 - 0.4i

        # Создание из строки
        c3 = Complex.from_string("5+6i")
        print("Из строки:", c3)  # Ожидаемый вывод: 5 + 6i

        # Проверка отрицательной мнимой части
        c4 = Complex.from_string("2-3i")
        print("Отрицательная мнимая часть:", c4)  # Ожидаемый вывод: 2 - 3i

        # Сохранение и загрузка
        c1.save("complex.json")
        c_loaded = Complex.load("complex.json")
        print("Загруженный объект:", c_loaded)  # Ожидаемый вывод: 3 + 4i

        # Тест ошибок
        # c_error = Complex.from_string("invalid")
        # zero_division = c1 / Complex(0, 0)

    except ValueError as e:
        print(f"Ошибка значения: {e}")
    except ZeroDivisionError as e:
        print(f"Ошибка деления: {e}")
    except Exception as e:
        print(f"Неожиданная ошибка: {e}")