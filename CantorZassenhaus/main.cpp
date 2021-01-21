#include <iostream>

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

/*
int main()
{
    mpz_t a, b;
    size_t nob;
    mpz_init(a); mpz_init(b);  //initialization 
    mpz_set_str(b, "61754454545545454545454", 10); //large things work in strings in this world 
    nob = mpz_sizeinbase(b, 2); //find how many bits are there in the binary 
    std::cout << nob << "\n";
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
#include "Utils.h"


using namespace std;

/*
int main4() {

	std::vector<int64_t> v1({ 2, 1, 3, 1 });
	std::vector<int64_t> v2({ 4, 1, 2 });

	Polynomial p1 = Polynomial(v1);
	Polynomial p2 = Polynomial(v2);


    cout << "p1: " << p1 << "\n";


	Polynomial p3 = Polynomial::mul(p1, p2, 5);

	//for (auto t : p3.coeff) {
//		cout << t << " ";
//	}
	cout << "\n";

	cout << p1 << "\n";
	cout << p2.to_string("y") << "\n";
	cout << p3 << "\n";

    Polynomial p4 = Polynomial::add(p1, p2);

	cout << p4 << "\n";

	return 0;
}

int main6() {
    Polynomial p1 = Polynomial({ 2, 1, 2, 2, 2, 0, 0, 0 });
    Polynomial p2 = Polynomial({ 2, 0, 1, 1 });

    cout << p1 << "\n";
    cout << p2 << "\n";

    auto p3div = Polynomial::div(p1, p2, 3);

    cout << p3div.first << "\n";
    cout << p3div.second << "\n";

    return 0;
}
*/

int main7() {

    for (size_t i = 0; i < 10; i++)
    {
        Polynomial poly = Polynomial::get_random_polynomial(5, 3);
        cout << poly << "\n";
    }

    return 0;
}

int main8() {
    string s = "3x^5+x^4+2x^3+4x^2+2x+2";
    auto r = split_by(s, "+");

    for (auto ss : r) {
        cout << ss << "\n";
    }

    return 0;
}

int main9() {
    auto p = parse_polynomial("3x^5+1x^4+2x^3+4x^2+2x^1+2x^0");

    cout << p << "\n";

    return 0;
}

int main10() {
    Polynomial p1 = parse_polynomial("2x^7+1x^6+2x^5+2x^4+2x^3+2x^0");
    Polynomial p2 = parse_polynomial("2x^3+1x^1+1x^0");

    auto p3div = Polynomial::div(p1, p2, 3);

    std::string result = "x^4+2x^3+2x^2+x+2";

    cout << p3div << "\n";
    cout << result << "\n";

    return 0;
}

int main11() {
    Polynomial p1 = parse_polynomial("2x^7+1x^6+2x^5+2x^4+2x^3+2x^0");
    Polynomial p2 = parse_polynomial("1x^5+1x^3+2x^0");

    auto p3div = gcd(p1, p2, 3);

    std::string result = "x^4+2x^3+2x^2+x+2";

    cout << p3div << "\n";
    cout << result << "\n";

    return 0;
}

/*
check copy
int main12() {
    Polynomial p1 = parse_polynomial("2x^7+1x^6+2x^5+2x^4+2x^3+2x^0");
    Polynomial p2 = p1;
    p1.coeff[0] += 1;

    cout << p1 << "\n";
    cout << p2 << "\n";

    return 0;
}
*/

int main13() {
    Polynomial p1 = parse_polynomial("1x^12+1x^11+2x^9+2x^8+2x^6+1x^5+2x^4+2x^3");
    /*auto p2 = p1.diff(3);
    auto p3 = gcd(p1, p2, 3);
    cout << p1 << "\n";
    cout << p2 << "\n";
    cout << p3 << "\n";
    cout << Polynomial::div(p1, p2, 3).first << "\n";*/

    auto rez = square_free_decomposition(p1, 3);
    for (auto p : rez) {
        cout << p.second << " " << p.first << "\n";
    }

    return 0;
}

int main15() {
    Polynomial p1 = parse_polynomial("1x^1");
    Polynomial p2 = parse_polynomial("1x^5+1x^4+1x^3+2x^1+2x^0");

    auto rez1 = Polynomial::div(p1, p2, 3);
    auto rez2 = Polynomial::mod(p1, p2, 3);
    cout << rez1 << "\n";
    cout << rez2 << "\n";

    return 0;
}


int main16() {
    Polynomial p1 = parse_polynomial("1x^5+1x^4+1x^3+2x^1+2x^0");
    Polynomial h1 = parse_polynomial("1x^1");
    auto h = powmod(h1, 3, p1, 3);

    cout << h1 << "\n";
    cout << h << "\n";

    return 0;
}

int main17() {
    Polynomial p1 = parse_polynomial("1x^5+1x^4+1x^3+2x^1+2x^0");
    Polynomial p2 = parse_polynomial("1x^2+2x^1");
    auto r = gcd(p2, p1, 3);
    cout << r << "\n";

    return 0;
}

int main18() {
    Polynomial p1 = parse_polynomial("1x^5+1x^4+1x^3+2x^1+2x^0");

    auto rez = distinct_degree_factorization(p1, 3);
    for (auto p : rez) {
        cout << p.second << " " << p.first << "\n";
    }

    return 0;
}

int main19() {
    Polynomial p1 = parse_polynomial("1x^4+1x^3+1x^1+2x^0");

    auto rez = equal_degree_factorization(p1, 2, 3);
    for (auto p : rez) {
        cout << p << "\n";
    }

    return 0;
}

int main20() {
    Polynomial p1 = parse_polynomial("1x^12+1x^11+2x^9+2x^8+2x^6+1x^5+2x^4+2x^3");

    auto rez = factor(p1, 3);
    for (auto p : rez) {
        cout << p.second << " " << p.first << "\n";
    }

    return 0;
}

int main21() {
    Polynomial p1 = parse_polynomial("1x^2+1x^0");

    auto rez = distinct_degree_factorization(p1, 3);
    for (auto p : rez) {
        cout << p.second << " " << p.first << "\n";
    }

    return 0;
}

int main22() {
    Polynomial p1 = parse_polynomial("1x^2+1x^0");
    Polynomial p2 = parse_polynomial("1x^0");

    auto rez1 = Polynomial::div(p2, p1, 3);
    auto rez2 = Polynomial::mod(p2, p1, 3);
    cout << rez1 << "\n";
    cout << rez2 << "\n";

    return 0;
}

int main23() {
    Polynomial p1 = parse_polynomial("1x^12+1x^11+2x^9+2x^8+2x^6+1x^5+2x^4+2x^3");

    auto rez = factor(p1, 3);
    for (auto p : rez) {
        cout << p.second << " " << p.first << "\n";
    }

    return 0;
}

// need profiling
int main24() {
    Polynomial p1 = parse_polynomial("1x^24+10x^23+32x^22+28x^21+13x^20+13x^19+17x^18+12x^17+29x^16+16x^15+13x^14+30x^13+31x^12+31x^11+2x^10+15x^9+5x^8+15x^7+3x^6+10x^5+18x^4+4x^3+6x^2+36x^1+19x^0");

    auto rez = factor(p1, 37);
    for (auto p : rez) {
        cout << p.second << " " << p.first << "\n";
    }

    return 0;
}

int main25() {
    Polynomial p1 = parse_polynomial("1x^11+1x^10+1x^9+1x^8+1x^6+1x^5+1x^0");

    auto rez = factor(p1, 2);
    for (auto p : rez) {
        cout << p.second << " " << p.first << "\n";
    }

    return 0;
}

int main26() {
    Polynomial p1 = parse_polynomial("1x^14+1x^10+1x^9+1x^8+1x^7+1x^6+1x^3+1x^2+1x^0");

    auto rez = factor(p1, 2);
    for (auto p : rez) {
        cout << p.second << " " << p.first << "\n";
    }

    return 0;
}

int main27() {
    // Polynomial p1 = parse_polynomial("1x^18+1x^17+1x^13+1x^12+1x^9+1x^7+1x^6+1x^5+1x^4+1x^3+1x^2+1x^1+1x^0");
    Polynomial p1 = parse_polynomial("1x^63+1x^0");

    auto rez = factor(p1, 2);
    for (auto p : rez) {
        cout << p.second << " " << p.first << "\n";
    }

    return 0;
}

// prof - 60sec
int main() {
    wtf = 1;

    Polynomial p1 = parse_polynomial("1x^144+793x^143+145x^142+733x^141+392x^140+671x^139+459x^138+886x^137+118x^136+510x^135+737x^134+345x^133+955x^132+12x^131+695x^130+185x^129+479x^128+435x^127+881x^126+958x^125+64x^124+472x^123+677x^122+206x^121+211x^120+846x^119+343x^118+422x^117+647x^116+962x^115+972x^114+803x^113+98x^112+40x^111+450x^110+386x^109+862x^108+17x^107+647x^106+110x^105+450x^104+386x^103+276x^102+426x^101+988x^100+365x^99+314x^98+447x^97+709x^96+830x^95+426x^94+405x^93+434x^92+649x^91+794x^90+149x^89+840x^88+325x^87+187x^86+40x^85+939x^84+385x^83+463x^82+324x^81+414x^80+45x^79+666x^78+624x^77+245x^76+660x^75+140x^74+761x^73+983x^72+867x^71+323x^70+923x^69+181x^68+132x^67+744x^66+475x^65+579x^64+235x^63+131x^62+259x^61+238x^60+955x^59+694x^58+971x^57+640x^56+115x^55+40x^54+378x^53+487x^52+342x^51+808x^50+690x^49+239x^48+402x^47+614x^46+529x^45+150x^44+904x^43+827x^42+356x^41+783x^40+229x^39+251x^38+426x^37+839x^36+875x^35+267x^34+628x^33+810x^32+950x^31+254x^30+236x^29+100x^28+880x^27+161x^26+259x^25+954x^24+450x^23+778x^22+194x^21+789x^20+284x^19+549x^18+949x^17+142x^16+600x^15+208x^14+940x^13+940x^12+83x^11+545x^10+908x^9+772x^8+636x^7+878x^6+458x^5+98x^4+593x^3+492x^2+711x^1+72x^0");

    auto rez = factor(p1, 991);
    for (auto p : rez) {
        cout << p.second << " " << p.first << "\n";
    }

    cout << "num of poly " << wtf << "\n";

    return 0;
}

int main29()
{
    mpz_class a, b, c;
    a = -1234;
    b = 46;
    c = a % b;
    std::cout << c << "\n";
    return 0;
}




int main31() {
    vector<mpz_class> v({ mpz_class(0),mpz_class(3) ,mpz_class(7) });
    Polynomial p1(v);

    cout << p1 << "\n";

    //p1.coeff[0] += 1;
    v[0] += 1;

    cout << p1 << "\n";


    return 0;
}



// prof - 303 sec; 579946 - created and destroyed polynomial
int main32() {
    wtf = 1;

    Polynomial p1 = parse_polynomial("1x^312+1x^217+1x^46+1x^0");

    auto rez = factor(p1, 994813);
    for (auto p : rez) {
        cout << p.second << " " << p.first << "\n";
    }

    cout << "num of poly " << wtf << "\n";

    return 0;
}


//Polynomial p1 = Polynomial({ 1, 4, 6, 3 });
//Polynomial p2 = Polynomial({ 6, 3, 2, 1 });
//Polynomial p1 = Polynomial({ 2, 1, 2, 2, 2, 0, 0, 2 });
//Polynomial p2 = Polynomial({ 2, 0, 1, 1 });

