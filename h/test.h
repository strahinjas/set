#ifndef _TEST_H_
#define _TEST_H_

#include "set.h"
#include "performance_calculator.h"

#include <iostream>
#include <iomanip>
#include <cstdlib>

int randomize() { return rand() * (RAND_MAX + 1) + rand(); }

template<typename T> void test() {
	srand(1);
	int size[] = { 200, 500, 1000, 10000, 100000, 1000000 };
	cout << left << setw(15) << setfill(' ') << "Velicina";
	cout << left << setw(15) << setfill(' ') << "Formiranje";
	cout << left << setw(15) << setfill(' ') << "Umetanje";
	cout << left << setw(15) << setfill(' ') << "Brisanje";
	cout << left << setw(15) << setfill(' ') << "Pretraga";
	cout << left << setw(15) << setfill(' ') << "Razlika" << endl;
	for (int i = 0; i < 6; i++) {
		T x, a, b;
		PerformanceCalculator pc;
		double time = 0;
		cout << left << setw(15) << setfill(' ') << size[i];
		for (int k = 0; k < size[i]; k++) {
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
		cout << left << setw(15) << setfill(' ') << (time /= 3);
		time = 0;
		for (int j = 0; j < 3; j++) {
			int n = randomize();
			pc.start();
			try { a += n; }
			catch (Duplicate) {}
			pc.stop();
			time += pc.elapsedMillis();
		}
		cout << left << setw(15) << setfill(' ') << (time /= 3);
		time = 0;
		for (int j = 0; j < 3; j++) {
			int n = randomize();
			pc.start();
			try { a -= n; }
			catch (NotFound) {}
			pc.stop();
			time += pc.elapsedMillis();
		}
		cout << left << setw(15) << setfill(' ') << (time /= 3);
		time = 0;
		for (int j = 0; j < 3; j++) {
			int n = randomize();
			pc.start(); a.member(n); pc.stop();
			time += pc.elapsedMillis();
		}
		cout << left << setw(15) << setfill(' ') << (time /= 3);
		time = 0;
		for (int j = 0; j < 3; j++) {
			pc.start(); a - b; pc.stop();
			time += pc.elapsedMillis();
		}
		cout << left << setw(15) << setfill(' ') << (time /= 3) << endl;
	}
}

#endif