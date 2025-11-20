#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

struct Gracz {
    std::string imie;
    int proby;
};


int poziom_trudnosci() {
    int poziom;
    int zakres;

    std::cout << "Wybierz poziom trudnosci:\n";
    std::cout << "1. Latwy (1 do 50)\n";
    std::cout << "2. Sredni (1 do 100)\n";
    std::cout << "3. Trudny (1 do 250)\n";
    std::cout << "Twoj wybor: ";
    std::cin >> poziom;

    switch (poziom) {
    case 1:
        zakres = 50;
        std::cout << "Wybrano poziom LATWY.\n";
        break;
    case 2:
        zakres = 100;
        std::cout << "Wybrano poziom SREDNI.\n";
        break;
    case 3:
        zakres = 250;
        std::cout << "Wybrano poziom TRUDNY.\n";
        break;
    }

    return zakres;
}

void zapiszWynik(const std::string & imie, int proby) {
    std::ofstream plik("top5.txt", std::ios::app); // dopisuje na końcu
    if (plik.is_open()) {
        plik << imie << " " << proby << "\n";
        plik.close();
    }
    else {
        std::cout << "Cos jest not yes\n";
    }
}

void wyswietlTop5() {
    std::ifstream plik("top5.txt");
    std::vector<Gracz> gracze;

   
    if (plik.is_open()) {
        Gracz g;
        while (plik >> g.imie >> g.proby) {
            gracze.push_back(g);
        }
        plik.close();
    }
    else {
        std::cout << "Brak danych. Zagraj, aby utworzyc liste TOP5.\n";
        return;
    }

    if (gracze.empty()) {
        std::cout << "Brak wynikow do wyswietlenia.\n";
        return;
    }

    //Sortowanie wynikow rosnaco
    std::sort(gracze.begin(), gracze.end(), [](const Gracz& a, const Gracz& b) {
        return a.proby < b.proby;
        });
 

    std::cout << "\n=== TOP 5 GRACZY ===\n";
    for (size_t i = 0; i < gracze.size() && i < 5; ++i) {
        std::cout << i + 1 << ". " << gracze[i].imie << " - " << gracze[i].proby << " prob\n";
    }
    std::cout << "=====================\n\n";

    std::cout << "\nNacisnij ENTER, aby wrocic do menu...";
    std::cin.ignore();
    std::cin.get();
}


void gra() {
    int zakres = poziom_trudnosci();  // funkcja zwraca zakres
    int wylosowana = rand() % zakres + 1;
    int strzal, proby = 0;

    std::cout << "Zgadnij liczbe od 1 do " << zakres << "\n";

    do {
        std::cout << "Twoj strzal: ";
        std::cin >> strzal;
        proby++;

        if (strzal > wylosowana)
            std::cout << "Za duza liczba! Proba nr: " << proby << "\n";
        else if (strzal < wylosowana)
            std::cout << "Za mala liczba! Proba nr: " << proby << "\n";
        else
            std::cout << "Zgadles liczbe " << wylosowana
            << " w: " << proby << " probach!\n";
    } while (strzal != wylosowana);

    // Po wygranej zapisz wynik
    std::string imie;
    std::cout << "Podaj swoje imie, aby zapisac wynik: ";
    std::cin >> imie;

    zapiszWynik(imie, proby);
    std::cout << "Wynik zapisany!\n";

    std::cout << "\nNacisnij ENTER, aby wrocic do menu...";
    std::cin.ignore();
    std::cin.get();
}



int main() {
    srand(static_cast<unsigned int>(time(0)));

    int opcja;
    do{

    std::cout << "=====================================\n";
    std::cout << "=          Guess Number!            =\n";
    std::cout << "=====================================\n";
    std::cout << "=          1 - Zagraj w gre         =\n";
    std::cout << "=          2 - Sprawdz TOP5         =\n";
    std::cout << "=          3 - Zamknij              =\n";
    std::cout << "=====================================\n\n";

    std::cout << "Wybierz numer, aby kontynuowac: ";
    std::cin >> opcja;


    switch (opcja) {
    case 1: {

        gra();
        break;
    }

    case 2:

        wyswietlTop5();
        break;

    case 3:
        std::cout << "Koniec gry. \n";
        break;

    default:
        std::cout << "Nieznana opcja.\n";
    }
} while (opcja != 3);

    return 0;
}