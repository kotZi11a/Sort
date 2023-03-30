#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <conio.h>
#include <algorithm>
#include <time.h> 

using namespace std;

vector<char> input_char(char end)
{
	int i;
	vector<char> char_array;
	char_array.clear();

	for (i = 0; i != -1; i++)
	{
		char sim = _getch();
		if (sim != end)
		{
			if (sim == '\b' && char_array.size() != 0)
			{
				cout << sim << ' ' << sim;
				char_array.pop_back();
			}
			if (sim == '-' || sim >= '0' && sim <= '9')
			{
				cout << sim;
				char_array.push_back(sim);
			}
		}
		else
		{
			if (end == '\r')
			{
				cout << endl;
			}
			else
			{
				cout << end;
			}
			i = -2;
		}
	}
	return char_array;
}

string str_check(vector<char> num)
{
	string number(num.begin(), num.end());
	int negat = number.find_first_of('-', 1);

	if (negat > 0)
		number = "";

	if (number != "0")
	{
		int p = number.find_first_not_of('0', 0);
		if (p != 1)
		{
			number = number.erase(0, p);
		}
	}
	return number;
}

bool correct_inp(string number)
{
	bool inp;
	int s = size(number);

	if (number == "" || s > 12)
	{
		cout << "Error. Write again: ";
		inp = 1;
	}
	else
	{
		inp = 0;
	}

	return inp;
}

double write_int(char end)
{
	int a = 0;
	int max_size = 12;
	bool inp = 1;

	while (inp)
	{
		vector<char> input_int = input_char(end);
		string number = str_check(input_int);
		inp = correct_inp(number);
		if (inp == 0)
		{
			a = stod(number);
		}
	}
	return a;
}

void fill_vector(vector<int>& array, int size)
{
	for (int i = 0; i < size; i++)
	{
		array[i] = rand() % 10000 - rand() % 10000;
	}
}

void reverse_sort(vector<int>& a)
{
	sort(a.begin(), a.end());
	reverse(a.begin(), a.end());
}

void enter_vector(vector<int>& array, int size)
{
	for (int i = 0; i < size; i++)
	{
		array[i] = write_int(' ');
	}
	cout << endl << endl;
}

void out_vector(vector<int>& a)
{
	if (a.size() <= 20)  // Если размер вектора <= 20 
	{
		cout << endl;
		for (int i = 0; i < a.size(); i++)
			cout << a[i] << ' ';
		cout << endl << endl;
	}
	else
	{
		cout << endl;
		for (int i = 0; i < 20; i++)
			cout << a[i] << ' ';
		cout << "..." << endl << endl;
	}
}

void sort_vector(vector<int>& a)
{
	for (int i = 0; i < a.size() - 1; i++)
	{
		int min = a[i];

		for (int n = i; n < a.size(); n++)
		{
			if (min > a[n])
			{
				min = a[n];
			}
			if (min != a[i])
			{
				a[n] = a[i];
				a[i] = min;
			}
		}
	}
}

void sort_vector2(vector<int>& a)
{
	for (int i = 0; i < a.size() - 1; i++)
	{
		int k;
		int min = a[i];

		for (int n = i; n < a.size(); n++)
		{
			k = i;
			if (min > a[n])
			{
				min = a[n];
				k = n;
			}
		}

		if (k != i)
		{
			a[k] = a[i];
			a[i] = min;
		}
	}
}

int main()
{
	bool begin = 1;
		while (begin)
		{
			int size_vec;
			double start, end;
			bool ent = 1;

			cout << "Enter size of vector: ";
			size_vec = write_int('\r');
			vector<int> array(size_vec);
			vector<int> sort_array;
			cout << "Write number to choice: keyboard input(1), auto fill(2), auto fill revers sort(3): ";

			while (ent)
			{
				int choice = write_int('\r');
				if (choice == 1)
				{
					cout << "You choice keyboard input. Write numbers separated by a space: " << endl;
					enter_vector(array, size_vec);
				}
				if (choice == 2)
				{
					fill_vector(array, size_vec);
					cout << "Vector: ";
					out_vector(array);
				}
				if (choice == 3)
				{
					fill_vector(array, size_vec);
					reverse_sort(array);
					cout << "Vector: ";
					out_vector(array);
				}
				if (choice != 1 && choice != 2 && choice != 3)
				{
					cout << "Error. Choice: keyboard input(1), auto fill(2), auto fill revers sort(3): ";
				}
				ent = (choice != 1 && choice != 2 && choice != 3);
			}

			sort_array = array;
			vector<int> sort_array2 = sort_array;
			start = (double)clock();
			sort(array.begin(), array.end());
			end = (double)clock();

			double t1 = end - start;
			cout << "Library Sorting vector: ";
			out_vector(array);
			start = (double)clock();

			sort_vector(sort_array);
			end = (double)clock();
			cout << "My function sort vector: ";
			out_vector(sort_array);
			double t = end - start;
			start = (double)clock();

			sort_vector2(sort_array);
			end = (double)clock();
			double t2 = end - start;
			cout << "My function sort vector2: ";
			out_vector(sort_array);

			if (t1 == 0)
			{
				cout << "Library Sorting Time <1ms" << endl;
			}
			else
			{
				cout << "Library Sorting Time = " << t1 << "ms" << endl;
			}
			if (t == 0)
			{
				cout << "Time my function sort <1ms" << endl;
			}
			else
			{
				cout << "Time my function sort = " << t << "ms" << endl;
			}
			if (t2 == 0)
			{
				cout << "Time my function sort2 <1ms" << endl;
			}
			else
			{
				cout << "Time my function sort2 = " << t2 << "ms" << endl;
			}

			cout << "Boost sort: " << t / t1 << endl << "Continue? (Y/N) ";
			char cont = 0;

			while (cont != 'y' && cont != 'n' && cont != 'Y' && cont != 'N')
			{
				cont = _getch();
			}
			cout << cont << endl;
			begin = (cont == 'y' || cont == 'Y');
		}
}