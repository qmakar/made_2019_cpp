# made_2019_cpp

Написать библиотеку-парсер строк состоящих из следующих токенов:

- строка
- число

Число состоит из символов от 0 до 9, строка - все остальные символы. Токены разделены пробелами, символами табуляции и первода строки.

Пользователь библиотеки должен иметь возможность зарегистрировать колбек-функцию вызываемую каждый раз, когда найден токен, функция получает токен. Должно быть возможно зарегистрировать свой обработчик под каждый тип токена. Также должны быть колбеки вызываемые перед началом парсинга и по его окончанию.

# Работа с проектом

Есть Makefile, с помощью которого можно собирать и запускать проект:

- **all** - сборка всего проекта
- **clean** - удаление собранных объектников и исполняемых файлов
- **test** - запуск и тестирование на нескольких примерах предложенного решения
- **run** - самостоятельный запуск программы



