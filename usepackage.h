//
// Created by Nikita on 01.10.2021.
//

/*
 * Решение квадратного уравнения с вещественными коэффициентами вида ax^2+bx+c=0.
 * Допускаются комплекснозначные корни.
 */

#ifndef KVADRATKA_V2_USEPACKAGE_H
#define KVADRATKA_V2_USEPACKAGE_H

#define MAXPREC 1e-7

#include <stdio.h>
#include <complex.h>
#include <math.h>
#include <assert.h>
#include <stdbool.h>
#include <windows.h>

//! Для работы с return
enum RootCount
{
    InfRoot = -1,
    NoRoot,
    OneRoot,
    TwoRoots,
    ComplexRoots
};

//! Хаб, в котором происходит перераспределение коэффициентов в SolveLinear или SolveSquare
void SolveEq (double, double, double);

//! Солвер линейного уравнения вида b*y+c=0
enum RootCount SolveLinear (double, double, double complex * x1);

//! Солвер квадратного уравнения вида a*y^2+b*y+c=0
enum RootCount SolveSquare (double, double, double, double complex * x1, double complex * x2);

//! Сравнение double с нулем
bool cmpDouble (double, double);

//! AKA kvadratka.c: главная функция программы, на вход берет коэффициенты и выводит ответ
void kvadratka (void);

//! AKA UnitTest.c: Юнит-тестирование
void UnitTest (void);

#endif KVADRATKA_V2_USEPACKAGE_H
