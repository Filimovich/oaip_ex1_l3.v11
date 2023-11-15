#include <iostream>
#include <iomanip>
#include <cmath>

// TODO: прототипировать функции и перенести их логику под main

using namespace std;

void input_error(void) //? Ошибка ввода: чистим ввод, игнорим все до конца строки
{
	cout << "Input data type error. Try again." << endl;
	cin.clear();
	cin.ignore(1000, '\n');
}

int divByZero_error(double num1, double num2) //? Проверка на ноль в знаменателе (Мы не поймаем эту ошибку, так как нуль этой функции в комплексной плоскости)
{
	if ((pow(M_E, (num1 - num2)) + num1 / 2) == 0) {
		cout << "Divide by zero error. Try again." << endl;
		return (1);
	}
	return (0);
}

int negativeSqrt_error(double num1, double num2)
{
	if ((num1 + num2) < 0){
		cout << "Trying to get sqrt of negative value. Try again." << endl;
		return (1);
	}
	return (0);
}

int doubleOverflow_error(double digit) //? Проверка на NaN или inf в результате вычислений (переполнение double)
{
	if (isnan(digit) || isinf(digit)) {
		cout << "Overflow error. Try again." << endl;
		return (1);
	}
	return (0);
}

void inputOutOfRange_error() //? Проверка на переполнение double при вводе данных
{
	cout << "Out of range error. Try again." << endl;
	cin.clear();
	cin.ignore(1000, '\n');
}

//! Следующая функция совсем не простая. Не смог сделать адекватную верификацию
//! через условные операторы и/или циклы. Ввод типа: 123abc, считался нормальным

double digit_input()
{
	double digit;
	while(1) {
		string str;
		size_t pos{}; // Тип данных беззнакового целого. Нужен для возврата длины строки
		cin >> str;
		try { //Начинаем отлов ошибки ввода
			digit = stod(str, &pos); // Парс строки в double и помещаем в pos длину полученной строки
			if (cin && pos == str.size()) //Если число ЧИСЕЛ в строке совпадет с ее длиной => все гуд
				break;
			else {
				input_error();
			}
		}
		catch (invalid_argument const&) { //Если stod не сможет спарсить строку (const& не обязателен. Избавляет от ошибки -Werror: catching polymorphic type)
			input_error();
		}
		catch (out_of_range const&) {
			inputOutOfRange_error();
		}
	}

	return (digit);
}

int main()
{
	float x;
	float y;
	float z;
	float b;

	do {
		do {
			cout << "Enter variable x: " << endl;
			x = digit_input();
			cout << "Enter variable y: " << endl;
			y = digit_input();
		} while (divByZero_error(x, y) || negativeSqrt_error(x, y));

		cout << "Enter variable z: " << endl;
		z = digit_input();

		b = pow(y, cbrt(fabs(x))) + pow(cos(y), 3) * // Часть до дроби
				(fabs(x - y) * (1 + pow(sin(z), 2) / sqrt(x + y))) / // Числитель
				(pow(M_E, (x - y)) + x / 2); // Знаменатель
	
	} while (doubleOverflow_error(b));

	cout << "The answer is: " << fixed << setprecision(4) << b;
	
	return (0);
}
