﻿#include <iostream>

#include "mpirxx.h"

/*
int main()
{
	mpz_class a, b, c;
	a = 1234;
	b = "99999999999999999999999999999999999999978";
	c = a + b;
	std::cout << c << "\n";
	return 0;
}
*/
// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"



#include <cstdlib>
#include <iostream>
#include <vector>
#include <cstdint>

#include "Polynomial.h"
#include "CantorZassenhaus.h"


using namespace std;

int main4() {

	std::vector<int64_t> v1({ 2, 1, 3, 1 });
	std::vector<int64_t> v2({ 4, 1, 2 });

	Polynomial p1 = Polynomial();
	p1.coeff = v1;
	Polynomial p2 = Polynomial();
	p2.coeff = v2;


    cout << "p1: " << p1 << "\n";


	Polynomial p3 = mul(p1, p2, 5);

	for (auto t : p3.coeff) {
		cout << t << " ";
	}
	cout << "\n";

	cout << p1 << "\n";
	cout << p2.to_string("y") << "\n";
	cout << p3 << "\n";

    Polynomial p4 = add(p1, p2);

	cout << p4 << "\n";

	return 0;
}



int main3() {
	using namespace std;

	vector<int> v1 = { 1, 3, 6 };
	vector<int> v2 = { 1, 2, 6 };

	bool rez = v1 == v2;

	cout << rez << "\n";

    return 0;
}

int main5() {
    Polynomial p1 = Polynomial({ 1, 0, 1, 0, 0, 2 });
    Polynomial p2 = Polynomial({ 1, 1 });

    cout << p1 << "\n";
    cout << p2 << "\n";

    Polynomial p3 = div(p1, p2, 3);

    cout << p3 << "\n";

    return 0;
}

int main6() {
    Polynomial p1 = Polynomial({ 2, 1, 2, 2, 2, 0, 0, 2 });
    Polynomial p2 = Polynomial({ 2, 0, 1, 1 });

    cout << p1 << "\n";
    cout << p2 << "\n";

    Polynomial p3 = div(p1, p2, 3);

    cout << p3 << "\n";

    return 0;
}

int main() {

    for (size_t i = 0; i < 10; i++)
    {
        Polynomial poly = get_random_polynomial(5, 3);
        cout << poly << "\n";
    }

    return 0;
}