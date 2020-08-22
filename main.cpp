#include <string>
#include <fstream>

#include "list_set.h"
#include "bst_set.h"
#include "benchmark.h"

template<typename T>
int manipulate()
{
	T set;
	int choice;

	while (true)
	{
		std::cout << "Izaberite jednu od opcija:\n";
		std::cout << "1. Unos elemenata u skup\n";
		std::cout << "2. Ispis sadrzaja skupa\n";
		std::cout << "3. Brisanje elementa iz skupa\n";
		std::cout << "4. Brisanje elemenata skupa u zadatom opsegu\n";
		std::cout << "5. Kardinalni broj skupa\n";
		std::cout << "6. Razlika skupova\n";
		std::cout << "7. Povratak u glavni meni\n";
		std::cout << "8. Izlaz iz programa\n\n";

		std::cout << "Vas izbor? ";

		std::cin >> choice;

		std::cout << "\n";

		try
		{
			switch (choice)
			{
			case 1:
				std::cout << "Izaberite nacin unosa:\n";
				std::cout << "0. Standardni ulaz\n";
				std::cout << "1. Datoteka\n";

				std::cout << "Vas izbor? ";

				std::cin >> choice;
				
				std::cout << "\n";

				if (choice)
				{
					std::cout << "Ime datoteke? ";

					std::string name; std::cin >> name;
					std::ifstream file;

					file.open(name);

					if (!file.is_open()) throw Error();

					int n; file >> n;

					for (int i = 0; i < n; i++)
					{
						int k; file >> k;
						try
						{
							set += k;
						}
						catch (Duplicate)
						{
							std::cout << "Greska: Broj " << k << " vec pripada skupu!\n";
						}
					}

					file.close();
					break;
				}
				else
				{
					std::cout << "Broj elemenata? ";

					int n;
					std::cin >> n;

					std::cout << "Elementi? ";
					for (int i = 0; i < n; i++)
					{
						int k; std::cin >> k;
						try
						{
							set += k;
						}
						catch (Duplicate)
						{
							std::cout << "Greska: Broj " << k << " vec pripada skupu!\n";
						}
					}
					break;
				}
			case 2:
				std::cout << set;
				break;
			case 3:
				std::cout << "Element koji zelite da obrisete? ";
				int k; std::cin >> k;
				try
				{
					set -= k;
				}
				catch (NotFound)
				{
					std::cout << "\nGreska: Broj " << k << " se ne nalazi u skupu!\n";
				}
				break;
			case 4:
				std::cout << "Granice opsega? ";

				int min, max;
				std::cin >> min >> max;

				set.removeInterval(min, max);
				break;
			case 5:
				if (!set.size()) std::cout << "Skup je prazan!";
				else std::cout << "Broj elemenata u skupu: " << set.size();
				break;
			case 6:
			{
				T other;

				std::cout << "Broj elemenata drugog skupa? ";

				int n;
				std::cin >> n;

				std::cout << "Elementi? ";
				for (int i = 0; i < n; i++)
				{
					int k; std::cin >> k;
					other += k;
				}

				std::cout << "\nSkup dobijen razlikom: " << (set = set - other);
				break;
			}
			case 7:
				return 0;
			case 8:
				return 1;
			default:
				std::cout << "Uneli ste vrednost koja nije podrzana, pokusajte ponovo.";
			}

			std::cout << "\n\n";
		}
		catch (std::bad_alloc)
		{
			std::cout << "\nGreska: Neuspesna alokacija memorije!\n\n";
		}
		catch (std::exception& e)
		{
			std::cout << e.what();
		}
	}
}

int main()
{
	int choice;

	while (true)
	{
		std::cout << "Izaberite zeljenu implementaciju skupa:\n";
		std::cout << "1. Dvostruko ulancana lista\n";
		std::cout << "2. Binarno stablo pretrazivanja\n";
		std::cout << "3. Poredjenje performansi\n";
		std::cout << "4. Izlaz iz programa\n\n";
		std::cout << "Vas izbor? ";

		std::cin >> choice;

		std::cout << "\n";

		switch (choice)
		{
		case 1:
		{
			if (manipulate<ListSet>()) return 0;
			break;
		}
		case 2:
		{
			if (manipulate<BSTSet>()) return 0;
			break;
		}
		case 3:
			std::cout << "Dvostruko ulancana lista:\n\n";
			benchmark<ListSet>();

			std::cout << "\nBinarno stablo pretrazivanja:\n\n";
			benchmark<BSTSet>();

			break;
		case 4:
			return 0;
		default:
			std::cout << "Uneli ste vrednost koja nije podrzana, pokusajte ponovo.";
		}

		std::cout << "\n\n";
	}
}