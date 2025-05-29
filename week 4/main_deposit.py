# Программирование на языке высокого уровня (Python).
# Задание № 3.
#
# Выполнил: Артемов В.С.
# Группа: ПИЖ-б-о-23-2
# E-mail: avs10353@mail.ru

from deposit import deposits

def main():
    print("Добро пожаловать в систему подбора вкладов!")

    while True:
        print("\n-----")
        print("Нажмите 1, чтобы подобрать вклад, или любую другую клавишу для выхода.")

        answer = input("Ваш выбор: ").strip()
        if answer != "1":
            break

        try:
            # Ввод данных с проверкой
            while True:
                try:
                    initial_sum = float(input("1/2: Введите начальную сумму вклада: "))
                    if initial_sum <= 0:
                        print("Сумма должна быть положительной. Попробуйте снова.")
                        continue
                    break
                except ValueError:
                    print("Ошибка: введите числовое значение.")

            while True:
                try:
                    period = int(input("2/2: Введите срок вклада (мес.): "))
                    if period <= 0:
                        print("Срок должен быть положительным. Попробуйте снова.")
                        continue
                    break
                except ValueError:
                    print("Ошибка: введите целое число.")

            # Поиск подходящих вкладов
            matched_deposits = []
            for deposit in deposits:
                try:
                    deposit._check_user_params(initial_sum, period)
                    matched_deposits.append(deposit)
                except AssertionError:
                    continue

            # Вывод результатов
            if matched_deposits:
                print("\n{0:<20} | {1:<15} | {2:<15}".format(
                    "Вклад", "Прибыль", "Итоговая сумма"
                ))
                for deposit in matched_deposits:
                    print("{0:<20} | {1:>10,.2f} {3:4} | {2:>10,.2f} {3:4}".format(
                        deposit.name,
                        deposit.get_profit(initial_sum, period),
                        deposit.get_sum(initial_sum, period),
                        deposit.currency))
            else:
                print("\nК сожалению, нет подходящих вкладов для указанных условий.")

        except Exception as e:
            print(f"\nПроизошла ошибка: {e}")

    print("\nСпасибо, что воспользовались услугами нашего банка! До свидания!")

if __name__ == "__main__":
    main()