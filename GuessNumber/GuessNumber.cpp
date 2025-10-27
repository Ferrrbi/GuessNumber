// GuessNumber.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>

void test() {
    std::cout << "Test";
}


int main()
{
    int opcja;


    std::cout << "=====================================\n";
    std::cout << "=          Guess Number!            =\n";
    std::cout << "=====================================\n";
    std::cout << "=          1 - Zagraj w gre         =\n";
    std::cout << "=          2 - Sprawdz TOP5         =\n";
    std::cout << "=          3 - Zamknij              =\n";
    std::cout << "=====================================\n\n\n\n";



    std::cout << "Wybierz numer, aby kontynuowac: ";
    std::cin >> opcja;

    switch (opcja) {
    case 1:
        test();           // wywołanie funkcji wewnątrz case
        break;
    case 2:
        test();        
        break;
    case 3:
        test();        
        break;
    default:
        std::cout << "Nieznana opcja.";
    }
    return 0;
}

// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln
