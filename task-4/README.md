## Задача 4
Написать парсер аргументов командной строки на языке С (через getopt и
getopt_long).

Программа принимает опции ```-m -c -s -t```, а также
```--elbrus=[1c+, 2c+, 2c3, 4c, 8c, 16c]``` и любое количество строк не-опций (без символов - и
-- перед ними).

Нужно парсить их в любых комбинациях, например:
```prg -tm -s --elbrus=16c file0 --elbrus=2c3 file1```<br>(Пример вывода): ```Options are correct: t, m, c, elbrus=16c, elbrus=2c3, non-options:
file0, file1.```

```prg -tm -x --elbrus=16c file0```<br>
(Пример вывода): ```Options are incorrect.```

Доп. задание - вывод некорректной опции на экран

#### Сборка (находясь в директории задания):
```bash
make clean && make
```

Запуск реализации через getopt():

> [!WARNING]
> Поскольку в short.bin используется getopt(), он может обрабатывать только короткии опции

```bash
./build/short.bin -m file1 -cs -t file2
```

Запуск реализации через getopt_long():

> [!NOTE]
> long.bin использует getopt_long(), поэтому он может обрабатывать все опции

```bash
./build/long.bin -m file1 --elbrus=16c -cs -t file2
```
