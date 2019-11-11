#include <ctime>
#include <string>
#include <vector>
#include <functional>
#include <cfloat>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <iomanip>

using namespace std;

const int MOD = 1e9 + 7;
const int ITERATIONS_NUM = 2e7;
//const double CLOCKS_PER_MS = CLOCKS_PER_SEC / 1e6;
const int FILLED_IN_BAR_LENGTH = 42;

template<typename T>
double measureDelta(T a, T b, T c) {
	clock_t start = clock();

	for (int i = 1; i < ITERATIONS_NUM; i++) {
		a = b;
		b = c;
		c = a;
		a = b;
		b = c;
		c = a;
	}

	clock_t end = clock();
	double t = (end * 1. - start * 1.) / CLOCKS_PER_SEC;

	return t;
}

template<typename T>
double measureAddition(T a, T b, T c) {
	clock_t start = clock();

	for (int i = 1; i < ITERATIONS_NUM; i++) {
		a = b + c;
		b = c + a;
		c = a + b;
		a = b + c;
		b = c + a;
		c = a + b;
	}

	clock_t end = clock();
	double t = (end * 1. - start * 1.) / CLOCKS_PER_SEC;

	return t;
}

template<typename T>
double measureSubstraction(T a, T b, T c) {
	clock_t start = clock();
	
	for (int i = 1; i < ITERATIONS_NUM; i++) {
		a = b - c;
		b = c - a;
		c = a - b;
		a = b - c;
		b = c - a;
		c = a - b;
	}

	clock_t end = clock();
	double t = (end * 1. - start * 1.) / CLOCKS_PER_SEC;

	return t;
}

template<typename T>
double measureMultiplication(T a, T b, T c) {
	clock_t start = clock();

	for (int i = 1; i < ITERATIONS_NUM; i++) {
		a = b * c;
		b = c * a;
		c = a * b;
		a = b * c;
		b = c * a;
		c = a * b;
	}

	clock_t end = clock();
	double t = (end * 1. - start * 1.) / CLOCKS_PER_SEC;

	return t;
}

template<typename T>
double measureDivision(T a, T b, T c) {
	clock_t start = clock();

	for (int i = 1; i < ITERATIONS_NUM; i++) {
		a = b / c;
		b = c / a;
		c = a / b;
		a = b / c;
		b = c / a;
		c = a / b;
	}

	clock_t end = clock();
	double t = (end * 1. - start * 1.) / CLOCKS_PER_SEC;

	return t;
}

int getBarCompletion(double curSpeed, double maxSpeed) {
	return ceil(min(1., curSpeed / maxSpeed) * FILLED_IN_BAR_LENGTH);
}

string getProgressBar(int fullLength, int completion, char filler = '#') {
	return string(completion, filler) + string(fullLength - completion, ' ');
}

void printTitle() {
	string filledBar = getProgressBar(FILLED_IN_BAR_LENGTH, FILLED_IN_BAR_LENGTH);
	cout << "  operation  |      type     |       op / sec      |    %    |  " << filledBar << "  |" << '\n';
}

void printSeparator() {
	int rowLen = 109;
	cout << getProgressBar(rowLen, rowLen, '-') << '\n';
}

void printRow(string operation, string type, double opPerSec, int barCompletion, int speedPercentage) {
	char perSec[13];
	snprintf(perSec, 13, "%.6e", opPerSec);
	cout << setw(7) << operation << setw(7) << "|"
		<< setw(12) << type << setw(4) << "|"
		<< setw(17) << perSec << setw(5) << "|"
		<< setw(6) << speedPercentage << setw(4) << "|"
		<< setw(2 + FILLED_IN_BAR_LENGTH)
		<< getProgressBar(FILLED_IN_BAR_LENGTH, barCompletion)
		<< setw(3) << "|" << '\n';
}

void runBenchmark(bool displayResult = true) {
	vector<double> result;

	char g = 1, h = 1, i = 1;
	result.push_back(measureDelta<char>(g, h, i));
	result.push_back(measureAddition<char>(g, h, i));
	result.push_back(measureSubstraction<char>(g, h, i));
	result.push_back(measureMultiplication<char>(g, h, i));
	result.push_back(measureDivision<char>(g, h, i));

	int a = 1, b = 1, c = 1;
	result.push_back(measureDelta<int>(a, b, c));
	result.push_back(measureAddition<int>(a, b, c));
	result.push_back(measureSubstraction<int>(a, b, c));
	result.push_back(measureMultiplication<int>(a, b, c));
	result.push_back(measureDivision<int>(a, b, c));

	long long d = 1, e = 1, f = 1;
	result.push_back(measureDelta<long long>(d, e, f));
	result.push_back(measureAddition<long long>(d, e, f));
	result.push_back(measureSubstraction<long long>(d, e, f));
	result.push_back(measureMultiplication<long long>(d, e, f));
	result.push_back(measureDivision<long long>(d, e, f));

	float j = 1, k = 1, l = 1;
	result.push_back(measureDelta<float>(j, k, l));
	result.push_back(measureAddition<float>(j, k, l));
	result.push_back(measureSubstraction<float>(j, k, l));
	result.push_back(measureMultiplication<float>(j, k, l));
	result.push_back(measureDivision<float>(j, k, l));

	double m = 1, n = 1, o = 1;
	result.push_back(measureDelta<double>(m, n, o));
	result.push_back(measureAddition<double>(m, n, o));
	result.push_back(measureSubstraction<double>(m, n, o));
	result.push_back(measureMultiplication<double>(m, n, o));
	result.push_back(measureDivision<double>(m, n, o));

	string operations[5] = { "=", "+", "-", "*", "/" };
	string types[5] = { "char", "int", "long long", "float", "double" };

	vector<double> speed;
	double standart = 0;
	int idx = 0;

	for (int i = 0; i < 25; i++) {
		if (i % 5 != 0) {
			double pureTime = result[i] - result[(i / 5) * 5];
			double opPerSec = ITERATIONS_NUM / pureTime;

			speed.push_back(opPerSec);
			if (opPerSec > standart) {
				standart = opPerSec;
				idx = i;
			}
		}
		else speed.push_back(0);
	}

	if (displayResult) {
		printTitle();
		printSeparator();
	}

	for (int i = 0; i < 25; i++) {
		if (i % 5 != 0) {
			if (displayResult) {
				printRow(operations[i % 5], types[i / 5], speed[i],
					getBarCompletion(speed[i], standart), (speed[i] / standart) * 100);
			}
		}
	}

	if (displayResult) {
		printSeparator();
	}
}

int main()
{
	runBenchmark();
	system("pause>>void");
    return 0;
}
