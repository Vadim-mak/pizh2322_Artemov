<h1> Лабораторная работа №4 </h1>
<h2>  Тема: Основы обектно-ориентированного программирования и проектирование UML-диаграмм </h2>
<h3>Выполнил:</h3>
Студент <u>2</u> курса группы <u>Пиж-б-о-23-2(2)</u>
Направление подготовки: <u>09.03.04 Программная инженерия</u>
Форма обучения: <u>Очная.</u>
<u>Артемов Вадим Сергеевич</u>

<h3>Задание 3:</h3>
<h4>Банковские вклады</h4>
<p>Банк предлагает ряд вкладов для физических лиц</p>
<p>- Срочный вклад: расчет прибыли осуществляется по формуле простых процентов</p>
<p>- Бонусный вклад: бонус начисляется в конце периода как % от прибыли, если вклад больше определенной суммы</p>
<p>- Вклад с капитализацией процентов</p>
<p>Реализуйте приложение, которое бы позволило подобрать клиенту вклад по заданным параметрам.</p>
<p>При выполнении задания необходимо построить UML-диаграмму классов приложения</p>

<h3>Задание 4:</h3>
<h4>Complex - комплексное число</h4>
<p>Прежде чем перейти к написанию кода:
  
Изучите предметную область объекта и доступные операции;

Для каждого поля и метода продумайте его область видимости, а также необходимость использования свойств.

При реализации класс должен содержать:

Специальные методы:

- __init__(self, ...) - инициализация с необходимыми параметрами;
 
- __str__(self) - представление объекта в удобном для человека виде;
 
- Специальные методы для возможности сложения, разности и прочих операций, которые класс должен поддерживать;
 
Методы класса:

- from_string(cls, str_value) - создает объект на основании строки str_value;
 
Поля, методы, свойства:

- Поля, необходимые для выбранного класса;
 
- Метод save(self, filename) - сохраняет объект в JSON-файл filename;
 
- Метод load(self, filename) - загружает объект из JSON-файла filename;
 
- Прочие методы (не менее 3-х) и свойства, выявленные на этапе изучения класса.
 
Реализуйте класс в отдельном модуле, а также создайте main.py, который бы тестировал все его возможности.

При выполнении задания необходимо построить UML-диаграмму классов приложения.</p>
