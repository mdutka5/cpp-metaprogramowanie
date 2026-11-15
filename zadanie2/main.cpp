/*
 * Zadanie 2 — NWD i NWW w czasie kompilacji (najprostsze)
 *
 * Opis:
 *   Największy wspólny dzielnik liczymy algorytmem Euklidesa:
 *   NWD(a, 0) = a, a dla b != 0: NWD(a, b) = NWD(b, a % b).
 *   Najmniejsza wspólna wielokrotność: NWW(a, b) = a / NWD(a, b) * b.
 *   Obie funkcje są constexpr, więc ten sam kod liczy przy kompilacji
 *   (testy, rozmiar tablicy) i po uruchomieniu (liczby z klawiatury).
 *
 * Cel:
 *   Wszystkie testy static_assert przechodzą, a program liczy NWD i NWW
 *   także dla liczb wpisanych z klawiatury.
 *
 * Do zrobienia:
 *   a) Uzupełnij funkcję constexpr nwd(a, b).
 *   b) Uzupełnij funkcję constexpr nww(a, b), korzystając z nwd.
 *
 * Dopóki zadanie nie jest zrobione, kompilacja zatrzymuje się na static_assert.
 * Treść i oczekiwany wynik: zadania.md, zadanie 2.
 */
#include <array>
#include <iostream>

// a) NWD(a, 0) = a, a dla b != 0: NWD(a, b) = NWD(b, a % b).
//    Możesz użyć rekurencji albo pętli while (b != 0).
constexpr unsigned nwd(unsigned a, unsigned b)
{
    // TODO a
    (void)a;
    (void)b;
    return 0;
}

// b) NWW(a, b) = a / NWD(a, b) * b. Najpierw dzielimy, żeby nie przekroczyć zakresu.
//    Zakładamy, że a i b są dodatnie.
constexpr unsigned nww(unsigned a, unsigned b)
{
    // TODO b
    (void)a;
    (void)b;
    return 0;
}

// ===== TESTY (nie zmieniaj) =====
static_assert(nwd(12, 18) == 6, "NWD(12, 18) = 6");
static_assert(nwd(17, 5) == 1, "NWD(17, 5) = 1");
static_assert(nwd(7, 0) == 7, "NWD(7, 0) = 7");
static_assert(nwd(0, 9) == 9, "NWD(0, 9) = 9");
static_assert(nwd(1071, 462) == 21, "NWD(1071, 462) = 21");
static_assert(nww(4, 6) == 12, "NWW(4, 6) = 12");
static_assert(nww(21, 6) == 42, "NWW(21, 6) = 42");
static_assert(nww(7, 7) == 7, "NWW(7, 7) = 7");
static_assert(nww(65536, 65536) == 65536, "NWW(65536, 65536) = 65536 (najpierw dzielenie, potem mnozenie)");

int main()
{
    std::array<int, nww(4, 6)> schedule{};
    std::cout << "nwd(1071, 462) = " << nwd(1071, 462) << "\n";
    std::cout << "schedule.size() = " << schedule.size() << "\n";

    unsigned a = 0, b = 0;
    std::cin >> a >> b;
    std::cout << "nwd = " << nwd(a, b) << ", nww = " << nww(a, b) << "\n";

    return 0;
}
// ===== KONIEC TESTÓW =====
