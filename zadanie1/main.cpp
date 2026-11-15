/*
 * Zadanie 1 — Data w czterech bajtach (najprostsze)
 *
 * Opis:
 *   Rejestrator zapisuje miliony dat, więc każda ma zajmować jak najmniej pamięci.
 *   Dzień (1–31), miesiąc (1–12) i rok (0–4095) zapiszemy w polach bitowych.
 *   Liczbę bitów każdego pola policzy funkcja constexpr, a nie programista.
 *
 * Cel:
 *   Wszystkie testy static_assert przechodzą, a PackedDate zajmuje 4 bajty
 *   zamiast 12 (trzy zwykłe pola unsigned).
 *
 * Do zrobienia:
 *   a) Uzupełnij funkcję bitsNeeded(value): ile bitów potrzeba, żeby zapisać value.
 *   b) W PackedDate zamień szerokości pól "1" na wywołania bitsNeeded(...).
 *
 * Dopóki zadanie nie jest zrobione, kompilacja zatrzymuje się na static_assert.
 * Treść i oczekiwany wynik: zadania.md, zadanie 1.
 */
#include <bitset>
#include <iostream>

// a) Najmniejsza liczba bitów, w której zmieści się value. Dla value == 0 wynik to 1.
//    Wskazówka: w pętli przesuwaj value o jeden bit w prawo (value >>= 1), aż spadnie do zera,
//    i licz obroty pętli. Pętla do-while od razu obsłuży value == 0.
constexpr int bitsNeeded(unsigned value)
{
    // TODO a
    (void)value;
    return 0;
}

// b) Szerokość każdego pola ma wynikać z bitsNeeded(...) dla jego największej wartości:
//    dzień 31, miesiąc 12, rok 4095. Zrób najpierw punkt a), bo pole o szerokości 0 to błąd.
struct PackedDate
{
    unsigned day : 1;   // TODO b: zamień 1 na bitsNeeded(31)
    unsigned month : 1; // TODO b: zamień 1 na bitsNeeded(12)
    unsigned year : 1;  // TODO b: zamień 1 na bitsNeeded(4095)
};

// ===== TESTY (nie zmieniaj) =====
static_assert(bitsNeeded(0) == 1, "bitsNeeded(0) powinno dac 1");
static_assert(bitsNeeded(1) == 1, "bitsNeeded(1) powinno dac 1");
static_assert(bitsNeeded(2) == 2, "bitsNeeded(2) powinno dac 2");
static_assert(bitsNeeded(7) == 3, "bitsNeeded(7) powinno dac 3");
static_assert(bitsNeeded(8) == 4, "bitsNeeded(8) powinno dac 4");
static_assert(bitsNeeded(31) == 5, "bitsNeeded(31) powinno dac 5");
static_assert(bitsNeeded(4095) == 12, "bitsNeeded(4095) powinno dac 12");
static_assert(bitsNeeded(4096) == 13, "bitsNeeded(4096) powinno dac 13");

constexpr bool storesLargestDate()
{
    PackedDate date{};
    date.day = 31;
    date.month = 12;
    date.year = 4095;
    return date.day == 31 && date.month == 12 && date.year == 4095;
}
static_assert(storesLargestDate(), "PackedDate musi pomiescic date 31.12.4095");
static_assert(sizeof(PackedDate) == 4, "PackedDate powinna zajmowac 4 bajty");

int main()
{
    std::bitset<bitsNeeded(1000)> flags;
    std::cout << "flags.size() = " << flags.size() << "\n";
    std::cout << "sizeof(PackedDate) = " << sizeof(PackedDate) << "\n";

    unsigned day = 0, month = 0, year = 0;
    std::cin >> day >> month >> year;

    PackedDate date{};
    date.day = day;
    date.month = month;
    date.year = year;
    std::cout << "data: " << date.day << '.' << date.month << '.' << date.year << "\n";

    std::cout << "rok " << year << " potrzebuje " << bitsNeeded(year) << " bitow\n";

    return 0;
}
// ===== KONIEC TESTÓW =====
