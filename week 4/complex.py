import json

class Complex:
    """
    Класс для работы с комплексными числами.
    Поддерживает основные арифметические операции и сериализацию.
    """
    def __init__(self, real: float, imag: float) -> None:
        """
        Инициализация объекта Complex.
        :param real: Действительная часть комплексного числа.
        :param imag: Мнимая часть комплексного числа.
        """
        self.real: float = real
        self.imag: float = imag
    
    def __str__(self) -> str:
        """
        Представление объекта в виде строки.
        :return: Строка с информацией о комплексном числе.
        """
        if self.imag >= 0:
            return f"{self.real} + {self.imag}i"
        else:
            return f"{self.real} - {-self.imag}i"
    
    def __add__(self, other: "Complex") -> "Complex":
        """
        Перегрузка оператора + для сложения комплексных чисел.
        :param other: Объект Complex.
        :return: Объект Complex.
        """
        return Complex(self.real + other.real, self.imag + other.imag)
    
    def __sub__(self, other: "Complex") -> "Complex":
        """
        Перегрузка оператора - для вычитания комплексных чисел.
        :param other: Объект Complex.
        :return: Объект Complex.
        """
        return Complex(self.real - other.real, self.imag - other.imag)
    
    def __mul__(self, other: "Complex") -> "Complex":
        """
        Перегрузка оператора * для умножения комплексных чисел.
        :param other: Объект Complex.
        :return: Объект Complex.
        """
        real: float = self.real * other.real - self.imag * other.imag
        imag: float = self.real * other.imag + self.imag * other.real
        return Complex(real, imag)
    
    def __truediv__(self, other: "Complex") -> "Complex":
        """
        Перегрузка оператора / для деления комплексных чисел.
        :param other: Объект Complex.
        :raises ZeroDivisionError: Если модуль делителя равен нулю.
        :return: Объект Complex.
        """
        denom: float = other.real**2 + other.imag**2
        if denom == 0:
            raise ZeroDivisionError("Деление на нулевое комплексное число")
        real: float = (self.real * other.real + self.imag * other.imag) / denom
        imag: float = (self.imag * other.real - self.real * other.imag) / denom
        return Complex(real, imag)
    
    @classmethod
    def from_string(cls, str_value: str) -> "Complex":
        """
        Создание объекта Complex из строки.
        Поддерживает форматы: "a+bi", "a-bi", "a" (только действительная часть).
        :param str_value: Строка с комплексным числом.
        :return: Объект Complex.
        :raises ValueError: Если строка имеет неверный формат.
        """
        str_value = str_value.replace(' ', '')
        if 'i' not in str_value:
            return cls(float(str_value), 0.0)
        
        parts = str_value.replace('-', '+-').split('+')
        parts = [p for p in parts if p != '']
        
        if len(parts) == 1:
            if 'i' in parts[0]:
                imag = parts[0].replace('i', '')
                return cls(0.0, float(imag))
            else:
                return cls(float(parts[0]), 0.0)
        
        real_part = parts[0]
        imag_part = parts[1].replace('i', '')
        
        return cls(float(real_part), float(imag_part))
    
    def save(self, filename: str) -> None:
        """
        Сохранение комплексного числа в файл в формате JSON.
        :param filename: Имя файла.
        """
        with open(filename, 'w') as f:
            json.dump({'real': self.real, 'imag': self.imag}, f)
    
    @classmethod
    def load(cls, filename: str) -> "Complex":
        """
        Загрузка комплексного числа из файла.
        :param filename: Имя файла.
        :return: Объект Complex.
        :raises FileNotFoundError: Если файл не существует.
        """
        with open(filename, 'r') as f:
            data = json.load(f)
        return cls(data['real'], data['imag'])


# Пример использования
if __name__ == "__main__":
    c1 = Complex(3, 4)
    c2 = Complex(1, -2)
    
    print(f"c1 = {c1}")  # 3 + 4i
    print(f"c2 = {c2}")  # 1 - 2i
    
    print(f"Сумма: {c1 + c2}")  # 4 + 2i
    print(f"Разность: {c1 - c2}")  # 2 + 6i
    print(f"Произведение: {c1 * c2}")  # 11 - 2i
    print(f"Частное: {c1 / c2}")  # -1 + 2i
    
    # Тест сериализации
    c1.save("complex.json")
    c3 = Complex.load("complex.json")
    print(f"Загруженное число: {c3}")  # 3 + 4i
    
    # Тест создания из строки
    c4 = Complex.from_string("2-3i")
    print(f"Из строки: {c4}")  # 2 - 3i
    
    try:
        c5 = Complex.from_string("invalid")
    except ValueError as e:
        print(f"Ошибка: {e}")
    
    try:
        bad_division = c1 / Complex(0, 0)
    except ZeroDivisionError as e:
        print(f"Ошибка: {e}")