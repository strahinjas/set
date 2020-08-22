#ifndef _BENCHMARK_H_
#define _BENCHMARK_H_

#include <vector>
#include <cstdlib>
#include <iomanip>
#include <iostream>

#include "set.h"
#include "exceptions.h"
#include "performance_calculator.h"

int randomize() { return rand() * (RAND_MAX + 1) + rand(); }

template<typename T>
void benchmark()
{
	srand(1);
	std::vector<int> sizes = { 200, 500, 1000, 10000, 100000, 1000000 };

	constexpr int WIDTH = 15;
	constexpr int COUNT = 3;

	std::cout << std::left << std::setw(WIDTH) << std::setfill(' ') << "Velicina";
	std::cout << std::left << std::setw(WIDTH) << std::setfill(' ') << "Formiranje";
	std::cout << std::left << std::setw(WIDTH) << std::setfill(' ') << "Umetanje";
	std::cout << std::left << std::setw(WIDTH) << std::setfill(' ') << "Brisanje";
	std::cout << std::left << std::setw(WIDTH) << std::setfill(' ') << "Pretraga";
	std::cout << std::left << std::setw(WIDTH) << std::setfill(' ') << "Razlika";
	std::cout << "\n";

	for (const int& size : sizes)
	{
		T x, a, b;
		PerformanceCalculator pc;
		double time = 0;

		std::cout << std::left << std::setw(WIDTH) << std::setfill(' ') << size;

		for (int k = 0; k < size; k++)
		{
			int n = randomize(), m = randomize();
			pc.start();

			try { x += n; }
			catch (Duplicate) {}
			try { a += n; }
			catch (Duplicate) {}
			try { b += m; }
			catch (Duplicate) {}

			pc.stop();
			time += pc.elapsedMillis();
		}

		std::cout << std::left << std::setw(WIDTH) << std::setfill(' ') << (time /= COUNT);

		time = 0;
		for (int j = 0; j < COUNT; j++)
		{
			int n = randomize();
			pc.start();

			try { a += n; }
			catch (Duplicate) {}

			pc.stop();
			time += pc.elapsedMillis();
		}

		std::cout << std::left << std::setw(WIDTH) << std::setfill(' ') << (time /= COUNT);

		time = 0;
		for (int j = 0; j < COUNT; j++)
		{
			int n = randomize();
			pc.start();

			try { a -= n; }
			catch (NotFound) {}

			pc.stop();
			time += pc.elapsedMillis();
		}

		std::cout << std::left << std::setw(WIDTH) << std::setfill(' ') << (time /= COUNT);

		time = 0;
		for (int j = 0; j < COUNT; j++)
		{
			int n = randomize();
			pc.start();
			a.member(n);
			pc.stop();
			time += pc.elapsedMillis();
		}

		std::cout << std::left << std::setw(WIDTH) << std::setfill(' ') << (time /= COUNT);

		time = 0;
		for (int j = 0; j < COUNT; j++)
		{
			pc.start();
			a - b;
			pc.stop();
			time += pc.elapsedMillis();
		}

		std::cout << std::left << std::setw(WIDTH) << std::setfill(' ') << (time /= COUNT) << "\n";
	}
}

#endif