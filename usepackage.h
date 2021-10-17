//
// Created by Nikita on 01.10.2021.
//

#ifndef KVADRATKA_V2_USEPACKAGE_H
#define KVADRATKA_V2_USEPACKAGE_H
#define MAXPREC 1e-7

#include <stdio.h>
#include <complex.h>
#include <math.h>
#include <assert.h>
#include <stdbool.h>
#include <windows.h>

/*
 * Решение квадратного уравнения с вещественными коэффициентами вида ax^2+bx+c=0.
 * Допускаются комплекснозначные корни.
 */

/*
 * Примеры: a b c
 *
 * Вещ + Вещ: 1 -3 2
 *              1 2
 * Вещ кр 2: 1 -4 4
 *              2
 * b = 0, c ==
 */

//notTODO отредачить принт, чтобы оператор не печатал 0, если один из аргументов нулевой.
//completeTODO указатель в функциях нужно определить нулем
//completeTODO если коэфов мало, вывести ERROR: недостаточное количество коэфов
//completeTODO "сравнить" float с нулем: написать функцию сравнения двух флотов и определить разность, как некоторый
//      PREC, меньше которого число отождествляется с нулем
//completeTODO избавиться от n-строчных принтов
//completeTODO написать функцию распределения коэффициентов уравнения SolveEquation.
//      Она будет в зависимости от количества коэфф уравнения больше PREC кидать их в SolveLinEquation или SolveSqEquation
//completeTODO траблы с return: написать enum для NoRoots, OneRoot, ..., InfRoot и в функциях писать return enum.
//      таким образом решим проблему switch(): case Inf:;
//
//!unableTODO написать юнит тест в виде UnitTest.c и компилировать его по инициативе пользователя
//!      main теперь станет хабом для перехода либо в UnitTest.c либо в Kvadratka.c
//completeTODO 2 варианта реализации юнит тестирования (реализовать через структуру?):
//      1) обычная функция
//      2) отдельный файл .c:
//      2.1) запуск через #ifndef DEBUG #endif
//      2.2) запуск через if else в main
//!unableTODO main { Interface() } - определяем че хочет юзер
//TODO написать функцию принта в зависимости от enum
//notTODO если b=0, c=0, то выводится x = -0. Режет глаза. Исправить?
//notTODO ввод дробей возможен только в десятичном представлении. Исправить?

#endif KVADRATKA_V2_USEPACKAGE_H
