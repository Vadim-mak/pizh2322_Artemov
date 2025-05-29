import json
from typing import List, Union, Iterator, Optional

class ComplexContainer:
    """
    Класс для работы с контейнером комплексных чисел.
    Поддерживает добавление, удаление, итерацию, сохранение и загрузку комплексных чисел.
    """
    def __init__(self, initial_data: Optional[List[complex]] = None) -> None:
        """
        Инициализация объекта ComplexContainer.
        :param initial_data: Начальный список комплексных чисел (опционально)
        """
        self._data: List[complex] = initial_data.copy() if initial_data else []

    def __str__(self) -> str:
        """
        Представление объекта в виде строки.
        :return: Строка с информацией о контейнере.
        """
        return f"ComplexContainer({[f'{c.real}{c.imag:+}i' for c in self._data]})"

    def __repr__(self) -> str:
        """
        Официальное строковое представление объекта.
        """
        return self.__str__()

    def __len__(self) -> int:
        """
        Возвращает количество элементов в контейнере.
        """
        return len(self._data)

    def __iter__(self) -> Iterator[complex]:
        """
        Возвращает итератор по элементам контейнера.
        """
        return iter(self._data)

    def __getitem__(self, index: int) -> complex:
        """
        Получение элемента по индексу.
        :param index: Индекс элемента.
        :return: Элемент контейнера.
        :raises IndexError: Если индекс вне диапазона.
        """
        try:
            return self._data[index]
        except IndexError:
            raise IndexError(f"Индекс {index} вне диапазона (0-{len(self._data)-1})")

    def add(self, value: Union[complex, float, int]) -> None:
        """
        Добавление числа в контейнер.
        :param value: Комплексное число или вещественное число (будет преобразовано в комплексное)
        :raises ValueError: Если передан нечисловой тип.
        """
        if isinstance(value, (complex, float, int)):
            self._data.append(complex(value))
        else:
            raise ValueError("Допускаются только числа (complex, float, int)")

    def remove(self, index: int) -> None:
        """
        Удаление элемента из контейнера по индексу.
        :param index: Индекс элемента.
        :raises IndexError: Если индекс вне диапазона.
        """
        if 0 <= index < len(self._data):
            del self._data[index]
        else:
            raise IndexError(f"Индекс {index} вне диапазона (0-{len(self._data)-1})")

    def clear(self) -> None:
        """
        Очистка контейнера.
        """
        self._data.clear()

    def save(self, filename: str) -> None:
        """
        Сохранение контейнера в JSON-файл.
        :param filename: Имя файла.
        :raises IOError: При ошибках работы с файлом.
        """
        try:
            with open(filename, 'w', encoding='utf-8') as file:
                json.dump([{'real': c.real, 'imag': c.imag} for c in self._data], file)
        except (IOError, OSError) as e:
            raise IOError(f"Ошибка при сохранении файла: {e}")

    def load(self, filename: str) -> None:
        """
        Загрузка контейнера из JSON-файла.
        :param filename: Имя файла.
        :raises IOError: При ошибках работы с файлом.
        :raises ValueError: При неверном формате данных.
        """
        try:
            with open(filename, 'r', encoding='utf-8') as file:
                data = json.load(file)
                self._data = [complex(c['real'], c['imag']) for c in data]
        except (IOError, OSError) as e:
            raise IOError(f"Ошибка при загрузке файла: {e}")
        except (KeyError, json.JSONDecodeError) as e:
            raise ValueError(f"Неверный формат данных в файле: {e}")

    def find(self, condition) -> List[complex]:
        """
        Поиск элементов по условию.
        :param condition: Функция-условие (принимает complex, возвращает bool)
        :return: Список найденных элементов.
        """
        return [c for c in self._data if condition(c)]