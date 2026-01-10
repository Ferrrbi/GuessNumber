#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

// Struktura przechowująca dane gracza
struct Gracz {
    std::string imie;
    int proby;
    std::string poziom;
};

//Funkcja czyszcząca ekran konsoli Windows i Linux
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

//Funkcja sprawdzająca, czy użytkownik wpisał liczbę
bool czyLiczba(int& x) {
    if (!(std::cin >> x)) {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        return false;
    }
    return true;
}

//Funkcja wyboru poziomu trudności
int poziom_trudnosci(std::string & poziom_nazwa) {
    int poziom;
    int zakres;

    std::cout << "Wybierz poziom trudnosci:\n";
    std::cout << "1. Latwy (1 do 50)\n";
    std::cout << "2. Sredni (1 do 100)\n";
    std::cout << "3. Trudny (1 do 250)\n";
    std::cout << "Twoj wybor: ";
    while (!czyLiczba(poziom)) {
        std::cout << "Twoj wybor: ";
    }

    switch (poziom) {
    case 1:
        zakres = 50;
        std::cout << "Wybrano poziom LATWY.\n";
        poziom_nazwa = "Latwy";
        break;
    case 2:
        zakres = 100;
        std::cout << "Wybrano poziom SREDNI.\n";
        poziom_nazwa = "Sredni";
        break;
    case 3:
        zakres = 250;
        std::cout << "Wybrano poziom TRUDNY.\n";
        poziom_nazwa = "Trudny";
        break;
    }

    return zakres;
}

//Funkcja zapisująca wynik gracza do pliku top5.txt na koniec
void zapiszWynik(const std::string & imie, int proby, const std::string & poziom) {
    std::ofstream plik("top5.txt", std::ios::app); 
    if (plik.is_open()) {
        plik << imie << " " << proby << " " << poziom << "\n";
        plik.close();
    }
    else {
        std::cout << "Cos jest not yes\n";
    }
}

// Funkcja wyświetlająca ranking TOP5, max 5 wyników posortowanych rosnąco
void wyswietlTop5() {
    std::ifstream plik("top5.txt");
    std::vector<Gracz> gracze;

    if (plik.is_open()) {
        Gracz g;
        while (plik >> g.imie >> g.proby >> g.poziom) {
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
        std::cout << i + 1 << ". " << gracze[i].imie << " - " << gracze[i].proby << " prob" << " | " << gracze[i].poziom << "\n";
    }
    std::cout << "=====================\n\n";

    std::cout << "\nNacisnij ENTER, aby wrocic do menu...";
    std::cin.ignore();
    std::cin.get();
    clearScreen();
}


void gra() {
    std::string poziom;
    int zakres = poziom_trudnosci(poziom);  
    int wylosowana = rand() % zakres + 1;                 //+1 żeby było od 1 a nie od 0
    int strzal, proby = 0;

    std::cout << "Zgadnij liczbe od 1 do " << zakres << "\n\n";

    do {
        std::cout << "Proba nr: " << proby + 1 << " Twoj strzal: ";
        while (!czyLiczba(strzal)) {
            std::cout << "Proba nr: " << proby + 1 << " Twoj strzal: ";
        }
        proby++;

        if (strzal > wylosowana)
            std::cout << "Za duza liczba! Proba nr: " << proby << "\n\n";
        else if (strzal < wylosowana)
            std::cout << "Za mala liczba! Proba nr: " << proby << "\n\n";
        else
            std::cout << "Zgadles liczbe " << wylosowana
            << " w: " << proby << " probach!\n\n";
    } while (strzal != wylosowana);

    // Po wygranej zapisz wynik
    std::string imie;
    std::cout << "Podaj swoje imie, aby zapisac wynik: ";
    std::cin >> imie;

    zapiszWynik(imie, proby, poziom);
    std::cout << "Wynik zapisany!\n";

    std::cout << "\nNacisnij ENTER, aby wrocic do menu...";
    std::cin.ignore();
    std::cin.get();
    clearScreen();
}





int main() {
    srand(static_cast<unsigned int>(time(0)));                    // Na podstawie czasu za każdym razem "losuje" inną liczbę
    int opcja;
    
    do{
        clearScreen();

    std::cout << "=====================================\n";
    std::cout << "=          Guess Number!            =\n";
    std::cout << "=====================================\n";
    std::cout << "=          1 - Zagraj w gre         =\n";

    if (std::ifstream("top5.txt").good()) {                       // Opcja TOP5 widoczna tylko jeśli plik istnieje
        std::cout << "=          2 - Sprawdz TOP5         =\n";
    }
    std::cout << "=          3 - Zamknij              =\n";
    std::cout << "=====================================\n\n";
    std::cout << "Wybierz numer, aby kontynuowac: ";
    

    while (!czyLiczba(opcja)) {
        std::cout << "Wybierz numer, aby kontynuowac: ";
    }


    switch (opcja) {
    case 1: {

        clearScreen();
        gra();
        break;
    }

    case 2:

        if (!std::ifstream("top5.txt").good()) {
            clearScreen();
            std::cout << "Opcja TOP5 jest jeszcze zablokowana!\n";
            std::cin.ignore();
            std::cin.get();
            break;
        }
        clearScreen();
        wyswietlTop5();
        break;

    case 3:
        clearScreen();
        std::cout << "Koniec gry. \n";
        break;

        default:
            clearScreen();
            std::cout << "Nieznana opcja.\n";
            std::cout << "Nacisnij ENTER...";
            std::cin.ignore();
            std::cin.get();
    }
} while (opcja != 3);

    return 0;
}
