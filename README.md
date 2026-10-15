# Лабораторная работа 3

Выполнил Матохин Артём, группа J3122, поток АиСД-3.1

## Запуск тестов

### Vector

```sh
gcc -I. tests/test_vector.c vector.c -o test_vector && ./test_vector
```

### LinkedList

```sh
gcc -I. tests/test_linked_list.c linked_list.c -o test_linked_list && ./test_linked_list
```

### k наиболее частых чисел

```sh
gcc -I. tests/test_top_k_frequent.c top_k_frequent.c vector.c -o test_top_k_frequent && ./test_top_k_frequent
```
