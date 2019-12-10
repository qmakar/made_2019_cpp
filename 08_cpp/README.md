# made_2019_cpp

Написать свой контейнер Vector аналогичный std::vector, аллокатор и итератор произвольного доступа для него. Из поддерживаемых методов достаточно operator[], push_back, pop_back, empty, size, clear, begin, end, rbegin, rend, resize, reserve.

Чтобы тесты проходили, классы должны иметь такие имена:

```c++
template <class T>
class Allocator
{
};

template <class T>
class Iterator
{
};

template <class T, class Alloc = Allocator<T>>
class Vector
{
public:
    using iterator = Iterator<T>;

private:
    Alloc alloc_;
};
```

Интерфейс аллокатора и итератора смотрите в документации.

# Работа с проектом

Есть Makefile, с помощью которого можно собирать и запускать проект:

- **all** - сборка всего проекта
- **clean** - удаление собранных объектников и исполняемых файлов
- **test** - запуск и тестирование на нескольких примерах предложенного решения



