#include "list_set.h"
#include "bst_set.h"
#include "test.h"

#include <string>
#include <fstream>

int main() {
	cout << "Dvostruko ulancana lista:\n\n";
	test<ListSet>();
	cout << "\nBinarno stablo pretrazivanja:\n\n";
	test<BSTSet>();

	BSTSet s;
	cout << "\nIzaberite jednu od opcija:\n";
	cout << "1. Unos elemenata u skup\n";
	cout << "2. Ispis sadrzaja skupa\n";
	cout << "3. Brisanje elementa iz skupa\n";
	cout << "4. Brisanje elemenata skupa u zadatom opsegu\n";
	cout << "5. Kardinalni broj skupa\n";
	cout << "6. Razlika skupova\n";
	cout << "7. Izlaz iz programa\n\n";
	while (true) {
		cout << "Redni broj instrukcije? ";
		int choice; cin >> choice;
		cout << endl;
		try {
			switch (choice) {
			case 1:
				cout << "Izaberite nacin unosa:\n";
				cout << "0. Standardni ulaz\n";
				cout << "1. Datoteka\n";
				cout << "Vas izbor? "; cin >> choice; cout << endl;
				if (choice) {
					cout << "Ime datoteke? ";
					string name; cin >> name;
					ifstream dat;
					dat.open(name);
					if (!dat.is_open()) throw Error();
					int n; dat >> n;
					for (int i = 0; i < n; i++) {
						int k; dat >> k;
						try { s += k; }
						catch (Duplicate) { cout << "Greska: Broj " << k << " vec pripada skupu!\n"; }
					}
					dat.close();
					break;
				}
				else {
					cout << "Broj elemenata? ";
					int n; cin >> n;
					cout << "Elementi? ";
					for (int i = 0; i < n; i++) {
						int k; cin >> k;
						try { s += k; }
						catch (Duplicate) { cout << "Greska: Broj " << k << " vec pripada skupu!\n"; }
					}
					break;
				}
			case 2: cout << s; break;
			case 3:
				cout << "Element koji zelite da obrisete? ";
				int k; cin >> k;
				try { s -= k; }
				catch (NotFound) { cout << "\nGreska: Broj " << k << " se ne nalazi u skupu!\n"; }
				break;
			case 4:
				cout << "Granice opsega? ";
				int min, max; cin >> min >> max;
				s.removeInterval(min, max);
				break;
			case 5:
				if (!card(s)) cout << "Skup je prazan!";
				else cout << "Broj elemenata u skupu: " << card(s);
				break;
			case 6: {
				BSTSet x;
				cout << "Broj elemenata drugog skupa? ";
				int n; cin >> n;
				cout << "Elementi? ";
				for (int i = 0; i < n; i++) {
					int k; cin >> k;
					x += k;
				}
				cout << "\nRezultujuci skup: " << (s = s - x);
				break;
			}
			case 7: exit(0);
			default: cout << "Ne postoji instrukcija pod datim brojem!";
			}
			cout << endl << endl;
		}
		catch (bad_alloc) { cout << "\nGreska: Neuspesna alokacija memorije!\n\n"; }
		catch (exception& e) { cout << e.what(); }
	}
}