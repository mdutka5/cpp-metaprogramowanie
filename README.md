# Metaprogramowanie w C++ — zadania

Pięć zadań na zajęcia z metaprogramowania, od najprostszych do praktycznych:

| Nr | Poziom | Temat |
|---|---|---|
| 1 | najprostsze | funkcja `constexpr` jako szerokość pól bitowych i rozmiar `std::bitset` |
| 2 | najprostsze | NWD i NWW jako funkcje `constexpr` (`nwd`, `nww`) |
| 3 | konkretne | odwracanie kolejności bajtów z `if constexpr` |
| 4 | praktyczne | robot sterowany przez `switch` po napisach z literałem `_cmd` |
| 5 | praktyczne | budzik z literałem `"07:30"_hm`: `consteval`, `constinit`, `std::is_constant_evaluated` |

Treść zadań, oczekiwane wyniki i instrukcje kompilacji są w pliku [zadania.md](zadania.md).

Każdy katalog `zadanie1`–`zadanie5` zawiera projekt CMake i plik `main.cpp`:

- na górze pliku jest opis zadania: cel i lista kroków;
- miejsca do uzupełnienia są oznaczone `TODO`;
- testy `static_assert` zatrzymują kompilację, dopóki zadanie nie jest zrobione poprawnie.

Zadania 1–4 wymagają C++17. Zadanie 5 ma część C++17 i część C++20 (`-DCMAKE_CXX_STANDARD=20`).
