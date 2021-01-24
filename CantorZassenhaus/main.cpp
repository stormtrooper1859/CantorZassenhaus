#include <iostream>

#include <cstdlib>
#include <iostream>
#include <vector>
#include <cstdint>

#include "mpirxx.h"

#include "Polynomial.h"
#include "CantorZassenhaus.h"


using namespace std;


int check_perf() {
    Polynomial p1 = Polynomial("x^12+x^11+2x^9+2x^8+2x^6+1x^5+2x^4+2x^3");

    auto rez = factor(p1, 3);
    for (auto p : rez) {
        cout << p.second << " " << p.first << "\n";
    }

    return 0;
}


// prof - 60sec
int check_perf1() {
    Polynomial p1 = Polynomial("x^144+793x^143+145x^142+733x^141+392x^140+671x^139+459x^138+886x^137+118x^136+510x^135+737x^134+345x^133+955x^132+12x^131+695x^130+185x^129+479x^128+435x^127+881x^126+958x^125+64x^124+472x^123+677x^122+206x^121+211x^120+846x^119+343x^118+422x^117+647x^116+962x^115+972x^114+803x^113+98x^112+40x^111+450x^110+386x^109+862x^108+17x^107+647x^106+110x^105+450x^104+386x^103+276x^102+426x^101+988x^100+365x^99+314x^98+447x^97+709x^96+830x^95+426x^94+405x^93+434x^92+649x^91+794x^90+149x^89+840x^88+325x^87+187x^86+40x^85+939x^84+385x^83+463x^82+324x^81+414x^80+45x^79+666x^78+624x^77+245x^76+660x^75+140x^74+761x^73+983x^72+867x^71+323x^70+923x^69+181x^68+132x^67+744x^66+475x^65+579x^64+235x^63+131x^62+259x^61+238x^60+955x^59+694x^58+971x^57+640x^56+115x^55+40x^54+378x^53+487x^52+342x^51+808x^50+690x^49+239x^48+402x^47+614x^46+529x^45+150x^44+904x^43+827x^42+356x^41+783x^40+229x^39+251x^38+426x^37+839x^36+875x^35+267x^34+628x^33+810x^32+950x^31+254x^30+236x^29+100x^28+880x^27+161x^26+259x^25+954x^24+450x^23+778x^22+194x^21+789x^20+284x^19+549x^18+949x^17+142x^16+600x^15+208x^14+940x^13+940x^12+83x^11+545x^10+908x^9+772x^8+636x^7+878x^6+458x^5+98x^4+593x^3+492x^2+711x+72");

    auto rez = factor(p1, 991);
    // auto rez = factor(p1, 994813);
    for (auto p : rez) {
        cout << p.second << " " << p.first << "\n";
    }

    return 0;
}


// prof - 303 sec; 579946 - created and destroyed polynomials
int check_perf2() {
    Polynomial p1 = Polynomial("x^312+x^217+x^46+1");

    auto rez = factor(p1, 994813);
    for (auto p : rez) {
        cout << p.second << " " << p.first << "\n";
    }

    return 0;
}



int main2() {
    std::string poly_string, module_string;

    std::getline(std::cin, poly_string);
    std::getline(std::cin, module_string);

    Polynomial p1 = Polynomial(poly_string);

    auto rez = factor(p1, mpz_class(module_string));
    for (auto p : rez) {
        cout << p.second << " " << p.first << "\n";
    }

    return 0;
}

int main() {
    wtf = 0;
    //check_perf();
    check_perf1();
    //check_perf2();
    //main2()
    cout << "wtf " << wtf << "\n";
}