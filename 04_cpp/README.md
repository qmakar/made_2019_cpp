# made_2019_cpp

Нужно написать класс-матрицу, тип элементов int. В конструкторе задается количество рядов и строк. Поддерживаются оперции: получить количество строк(rows)/столбцов(columns), получить конкретный элемент, умножить на число(*=), сравнение на равенство/неравенство. В случае ошибки выхода за границы бросать исключение:

```c++
throw std::out_of_range("")
```

Пример:

```c++
const size_t rows = 5;
const size_t cols = 3;

Matrix m(rows, cols);

assert(m.getRows() == 5);
assert(m.getColumns() == 3);

m[1][2] = 5; // строка 1, колонка 2
double x = m[4][1];

m *= 3; // умножение на число

Matrix m1(rows, cols);

if (m1 == m)
{
}
```

##### Подсказка

Чтобы реализовать семантику [][] понадобится прокси-класс. Оператор матрицы возращает другой класс, в котором тоже используется оператор [] и уже этот класс возвращает значение.



# Работа с проектом

Есть Makefile, с помощью которого можно собирать и запускать проект:

- **all** - сборка всего проекта
- **clean** - удаление собранных объектников и исполняемых файлов
- **test** - запуск и тестирование на нескольких примерах предложенного решения


