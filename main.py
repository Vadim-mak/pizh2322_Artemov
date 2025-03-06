import math

class Point3D:
    """  
    Класс для представления точки в 3D-пространстве.  
    """

    def __init__(self, x=0, y=0, z=0):
        """  
        Инициализация точки в 3D-пространстве.  

        :param x: Координата x (по умолчанию 0)  
        :param y: Координата y (по умолчанию 0)  
        :param z: Координата z (по умолчанию 0)  
        """
        self.x = x
        self.y = y
        self.z = z

    def __repr__(self):
        """  
        Возвращает строковое представление точки.  

        :return: Строка вида "(x, y, z)"  
        """
        return f'({self.x}, {self.y}, {self.z})'


class Vector3D:
    """  
    Класс для работы с векторами в 3D-пространстве.  
    """

    def __init__(self, x=0, y=0, z=0):
        """  
        Инициализация вектора с координатами (x, y, z).  

        :param x: Координата x (по умолчанию 0)  
        :param y: Координата y (по умолчанию 0)  
        :param z: Координата z (по умолчанию 0)  
        """
        self._point = Point3D(x, y, z)  # Композиция

    def __repr__(self):
        """  
        Возвращает строковое представление вектора.  

        :return: Строка вида "Vector3D(x, y, z)"  
        """
        return f'Vector3D{self._point}'

    def display(self):
        """  
        Выводит вектор в консоль.  
        """
        print(f'Vector: {self._point}')

    def read(self):
        """  
        Читает координаты вектора с клавиатуры.  
        """
        self._point.x = float(input("Введите x: "))
        self._point.y = float(input("Введите y: "))
        self._point.z = float(input("Введите z: "))

    def __add__(self, other):
        """  
        Складывает два вектора.  

        :param other: Второй вектор  
        :return: Новый вектор, равный сумме текущего и переданного  
        """
        if not isinstance(other, Vector3D):
            raise TypeError("Сложение возможно только с другим вектором")
        return Vector3D(self._point.x + other._point.x,
                        self._point.y + other._point.y,
                        self._point.z + other._point.z)

    def __sub__(self, other):
        """  
        Вычитает два вектора.  

        :param other: Второй вектор  
        :return: Новый вектор, равный разности текущего и переданного  
        """
        if not isinstance(other, Vector3D):
            raise TypeError("Вычитание возможно только с другим вектором")
        return Vector3D(self._point.x - other._point.x,
                        self._point.y - other._point.y,
                        self._point.z - other._point.z)

    def __mul__(self, other):
        """  
        Умножает вектор на число или вычисляет скалярное произведение.  

        :param other: Число (умножение на скаляр) или вектор (скалярное произведение)  
        :return: Вектор (если умножение на число) или число (если скалярное произведение)  
        """
        if isinstance(other, (int, float)):
            return Vector3D(self._point.x * other,
                            self._point.y * other,
                            self._point.z * other)
        elif isinstance(other, Vector3D):
            return (self._point.x * other._point.x +
                    self._point.y * other._point.y +
                    self._point.z * other._point.z)  # Скалярное произведение
        else:
            raise TypeError("Неподдерживаемая операция умножения")

    def __matmul__(self, other):
        """  
        Вычисляет векторное произведение двух векторов.  

        :param other: Второй вектор  
        :return: Новый вектор – результат векторного произведения  
        """
        if not isinstance(other, Vector3D):
            raise TypeError("Векторное произведение возможно только с другим вектором")
        return Vector3D(self._point.y * other._point.z - self._point.z * other._point.y,
                        self._point.z * other._point.x - self._point.x * other._point.z,
                        self._point.x * other._point.y - self._point.y * other._point.x)

    def __call__(self):
        """  
        Вычисляет длину вектора.  

        :return: Длина вектора (float)  
        """
        return math.sqrt(self._point.x**2 + self._point.y**2 + self._point.z**2)


# Пример использования
v1 = Vector3D(3, 4, 5)
v2 = Vector3D(1, 2, 3)

print("v1:", v1)
print("v2:", v2)

v3 = v1 + v2
print("Сложение v1 + v2:", v3)

v4 = v1 - v2
print("Вычитание v1 - v2:", v4)

scalar_product = v1 * v2
print("Скалярное произведение v1 * v2:", scalar_product)

vector_product = v1 @ v2
print("Векторное произведение v1 @ v2:", vector_product)

scaled_vector = v1 * 2
print("Умножение v1 на скаляр 2:", scaled_vector)

length_v1 = v1()
print("Длина вектора v1:", length_v1)
