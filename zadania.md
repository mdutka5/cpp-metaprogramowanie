# Metaprogramowanie w C++: zadania

Zadania opierają się na materiale „Metaprogramowanie C++”. Każde odwołuje się do konkretnych rozdziałów, podanych w tabeli. Zaczynamy od prostych funkcji `constexpr`, a kończymy na `consteval` i `constinit`.

| Nr | Poziom | Temat | Katalog | Rozdziały materiału |
|---|---|---|---|---|
| 1 | najprostsze | funkcja `constexpr` w miejscach wymagających stałej | `zadanie1` | Funkcje constexpr, static_assert, Inne użycia wyrażeń constexpr |
| 2 | najprostsze | NWD i NWW jako funkcje `constexpr` | `zadanie2` | Funkcje constexpr, static_assert |
| 3 | konkretne | `if constexpr` zależne od rozmiaru typu | `zadanie3` | If constexpr, static_assert |
| 4 | praktyczne | `switch` po napisach, literał użytkownika | `zadanie4` | Switch po napisach, Literały constexpr |
| 5 | praktyczne | `consteval`, `constinit`, wykrywanie czasu kompilacji | `zadanie5` | Literały constexpr, Funkcje consteval, Zmienne constinit, If consteval |

## Jak pracować

1. Otwórz `zadanieN/main.cpp`. Na górze pliku jest krótki opis zadania: co trzeba osiągnąć i co zrobić.
2. Uzupełnij miejsca oznaczone `TODO`, w kolejności liter a), b), c)…
3. Skompiluj. W każdym pliku są **testy `static_assert`**: dopóki zadanie nie jest zrobione, kompilacja zatrzyma się na nich z komunikatem, co jest nie tak.
4. Uruchom program i porównaj wynik z sekcją „Po uruchomieniu”.

Części od `===== TESTY` do `===== KONIEC TESTÓW` nie zmieniaj.

## Jak kompilować i uruchamiać

**CMake** (w katalogu zadania):

```bash
cd zadanie1
cmake -S . -B build
cmake --build build
./build/zadanie1
```

**g++ / clang++:**

```bash
g++ -std=c++17 -Wall -Wextra zadanie1/main.cpp -o zadanie1/program
./zadanie1/program
```

**Visual Studio** (Developer Command Prompt): `cl /std:c++17 /EHsc /utf-8 zadanie1\main.cpp`.

Dane wejściowe można wpisać z klawiatury, zakończyć przez Ctrl+D (Linux, macOS) lub Ctrl+Z i Enter (Windows), albo podać od razu: `echo "15 11 2026" | ./build/zadanie1`.

**Wersja C++.** Materiał używa C++23 (`import std;`, `std::print`), ale zadania celowo korzystają ze zwykłych `#include` i `std::cout`, żeby działały także na starszych kompilatorach:

- zadania 1–4 wymagają tylko **C++17** (GCC ≥ 8, Clang ≥ 7, MSVC 2019);
- zadanie 5 ma część C++17 i część **C++20**. Część C++20 wymaga GCC ≥ 10, Clang ≥ 12 lub MSVC 2019 16.10, a buduje się ją przez `cmake -S . -B build20 -DCMAKE_CXX_STANDARD=20` albo flagę `-std=c++20`.

---

## Zadanie 1: data w czterech bajtach (najprostsze)

Rejestrator zapisuje miliony dat, więc każda ma zajmować jak najmniej pamięci. Dzień (1–31), miesiąc (1–12) i rok (0–4095) zapiszemy w **polach bitowych**: `unsigned day : 5;` oznacza pole zajmujące tylko 5 bitów. Szerokość pola musi być stałą znaną przy kompilacji. Zamiast liczyć ją ręcznie, wywołamy funkcję `constexpr`, tak jak `kwadrat(2)` w rozdziale *Inne użycia wyrażeń constexpr*.

**Do zrobienia w `zadanie1/main.cpp`:**

a) Uzupełnij `constexpr int bitsNeeded(unsigned value)`. Zwraca najmniejszą liczbę bitów, w której mieści się `value`, a dla `0` zwraca `1`. W pętli przesuwaj `value` o jeden bit w prawo (`value >>= 1`), aż spadnie do zera, i licz obroty pętli. Pętla `do { ... } while (value > 0);` od razu obsłuży zero.

| `value` | 0 | 1 | 2 | 7 | 8 | 31 | 4095 | 4096 |
|---|---|---|---|---|---|---|---|---|
| wynik | 1 | 1 | 2 | 3 | 4 | 5 | 12 | 13 |

b) W strukturze `PackedDate` zamień szerokości pól `1` na `bitsNeeded(31)`, `bitsNeeded(12)` i `bitsNeeded(4095)`. Zrób najpierw punkt a), bo pole o szerokości 0 jest błędem. Ostrzeżenia o obcinaniu wartości (*truncation*) znikną po wykonaniu tego punktu.

**Po uruchomieniu** dla wejścia `15 11 2026`:

```text
flags.size() = 10
sizeof(PackedDate) = 4
data: 15.11.2026
rok 2026 potrzebuje 11 bitow
```

---

## Zadanie 2: NWD i NWW w czasie kompilacji (najprostsze)

Największy wspólny dzielnik (NWD) liczymy **algorytmem Euklidesa**: `NWD(a, 0) = a`, a dla `b ≠ 0` mamy `NWD(a, b) = NWD(b, a % b)`. Najmniejsza wspólna wielokrotność (NWW) to `NWW(a, b) = a / NWD(a, b) * b`.

Obie funkcje są `constexpr`, więc ten sam kod liczy przy kompilacji (testy `static_assert`, rozmiar `std::array`) i po uruchomieniu programu (liczby z klawiatury). Opisuje to rozdział *Funkcje constexpr*.

**Do zrobienia w `zadanie2/main.cpp`:**

a) Uzupełnij `constexpr unsigned nwd(unsigned a, unsigned b)` według algorytmu Euklidesa. Możesz użyć rekurencji (`return nwd(b, a % b);`) albo pętli `while (b != 0)`.

b) Uzupełnij `constexpr unsigned nww(unsigned a, unsigned b)`, korzystając z `nwd`. Najpierw dziel, potem mnóż (`a / nwd(a, b) * b`). Iloczyn `a * b` mógłby przekroczyć zakres `unsigned`, co sprawdza test `nww(65536, 65536)`. Zakładamy, że `a` i `b` są dodatnie.

**Po uruchomieniu** dla wejścia `84 120`:

```text
nwd(1071, 462) = 21
schedule.size() = 12
nwd = 12, nww = 840
```

---

## Zadanie 3: odwracanie kolejności bajtów (konkretne)

Pliki PNG i protokoły sieciowe zapisują liczby w kolejności **big-endian**: najstarszy bajt jest pierwszy. Procesory x86 i ARM trzymają liczby w **little-endian**: najmłodszy bajt jest pierwszy. Po odczycie liczby z pliku trzeba więc odwrócić kolejność jej bajtów:

### Co to big/little-edian: 
https://dev.to/amanprasad/understanding-endianness-little-endian-vs-big-endian-31e

```text
0x1234     -> 0x3412
0x12345678 -> 0x78563412
```

Sposób odwracania zależy od rozmiaru typu. Rozmiar (`sizeof(T)`) jest znany przy kompilacji, więc właściwy kod wybierzesz przez `if constexpr`, jak w przykładzie `print` z rozdziału *If constexpr*. Kompilator wygeneruje dla każdego typu tylko jedną gałąź.

**Do zrobienia w `zadanie3/main.cpp`** (w szablonie `byteSwap<T>`):

a) Gałęzie `if constexpr` dla trzech rozmiarów (`>>` i `<<` to przesunięcia bitowe, `&` to AND, `|` to OR):

| `sizeof(T)` | wynik |
|---|---|
| 1 | `value` (jeden bajt, nie ma czego zamieniać) |
| 2 | `static_cast<T>((value >> 8) \| (value << 8))` |
| 4 | `((value >> 24) & 0xFF) \| ((value >> 8) & 0xFF00) \| ((value << 8) & 0xFF0000) \| (value << 24)`, rzutowane na `T` |

b) Gałąź dla `sizeof(T) == 8`. Rozbij liczbę na dwie połówki:

- `low = static_cast<std::uint32_t>(value)`,
- `high = static_cast<std::uint32_t>(value >> 32)`.

Odwróć każdą z nich **tym samym szablonem** `byteSwap` i zamień je miejscami: wynik to `(static_cast<T>(byteSwap(low)) << 32) | byteSwap(high)`.

c) Dwa `static_assert`:

- na początku funkcji: `T` musi być typem całkowitym bez znaku (`std::is_integral_v<T> && std::is_unsigned_v<T>`), z komunikatem `"byteSwap: tylko typy calkowite bez znaku"`;
- w końcowej gałęzi `else`: `static_assert(unsupportedSize<T>, "byteSwap: nieobslugiwany rozmiar typu");`.

Pomocnicza stała `unsupportedSize<T>` jest już w pliku. Zwykłe `static_assert(false, ...)` starsze kompilatory zgłaszają jako błąd nawet wtedy, gdy ta gałąź nie jest wybrana.

**Po uruchomieniu:**

```text
uint8 : ab -> ab
uint16: 1234 -> 3412
uint32: 12345678 -> 78563412
uint64: 0102030405060708 -> 0807060504030201
szerokosc obrazka: 800
```

---

## Zadanie 4: robot sterowany napisami (praktyczne)

`switch` w C++ działa tylko na liczbach całkowitych. W rozdziale *Switch po napisach* napis jest zamieniany na liczbę funkcją skrótu FNV-1a, a etykiety `case` liczy kompilator dzięki literałowi `"start"_h`. Tu użyjesz innej funkcji skrótu, **djb2**, do sterowania robotem.

Funkcja skrótu zamienia dowolny napis na liczbę 32-bitową, więc **dwa różne napisy mogą dostać ten sam skrót**. To jest **kolizja**. Dla djb2 tak jest np. z `"stop"` i `"stpO"`, a także z `"left"` i `"legS"`. Program musi takie przypadki odróżnić.

**Do zrobienia w `zadanie4/main.cpp`:**

a) `constexpr std::uint32_t djb2(std::string_view text)`: zacznij od `hash = 5381`. Dla każdego znaku `c` wykonaj `hash = hash * 33 + static_cast<unsigned char>(c)`. Przepełnienie `std::uint32_t` jest dozwolone, bo liczby bez znaku zawijają się modulo 2³².

b) Operator literałowy `constexpr std::uint32_t operator""_cmd(const char* text, std::size_t length)`, który zwraca `djb2(std::string_view{text, length})`. Nazwa literału użytkownika musi zaczynać się od `_`.

c) Funkcja `constexpr Result execute(Robot& robot, std::string_view command)` z instrukcją `switch (djb2(command))` i etykietami `case "forward"_cmd:` itd.:

| polecenie | działanie | wynik |
|---|---|---|
| `forward` | `y + 1` | `Result::Moved` |
| `back` | `y - 1` | `Result::Moved` |
| `left` | `x - 1` | `Result::Moved` |
| `right` | `x + 1` | `Result::Moved` |
| `stop` | — | `Result::Stopped` |
| inne | robot stoi | `Result::Unknown` |

d) **Ochrona przed kolizją.** W każdej gałęzi `case` sprawdź jeszcze, czy `command` to naprawdę ten napis (`if (command == "forward")`). Jeśli nie, wyjdź ze `switch` (`break`) i zwróć `Result::Unknown`.

**Po uruchomieniu** dla wejścia `forward forward left back jump stpO right stop forward`:

```text
nieznane polecenie: jump
nieznane polecenie: stpO
pozycja: (0, 1)
```

Ostatnie `forward` nie jest wykonane, bo wcześniej było `stop`.

---

## Zadanie 5: budzik z literałem `"07:30"_hm` (praktyczne)

Godziny zapisujemy w kodzie literałem, np. `"07:30"_hm`. Chcemy, żeby **literówka w godzinie wpisanej w kod**, np. `"25:00"_hm`, była błędem kompilacji. Ta sama funkcja parsująca ma też obsługiwać godziny wpisane przez użytkownika. Wtedy błąd ma być wyjątkiem, który program łapie i zgłasza.

Kluczowa obserwacja: instrukcja `throw` może stać w funkcji `constexpr`. Jeśli jednak zostanie **wykonana podczas kompilacji**, wyrażenie przestaje być stałe i kompilacja się nie udaje. Po uruchomieniu ta sama instrukcja `throw` jest zwykłym wyjątkiem.

### Część C++17

**Do zrobienia w `zadanie5/main.cpp`:**

a) `constexpr int digitValue(char c)`: znak `'0'`–`'9'` zamień na `0`–`9` (`c - '0'`). Dla innego znaku `throw std::invalid_argument("niepoprawna cyfra")`.

b) `constexpr Time parseTime(std::string_view text)` zamienia `"HH:MM"` na `Time{hour, minute}`. Sprawdzaj w tej kolejności:

1. długość 5 i `':'` na pozycji 2, inaczej `throw std::invalid_argument("oczekiwano formatu HH:MM")`;
2. cyfry na pozostałych pozycjach, przez `digitValue`;
3. godzina `0–23` i minuta `0–59`, inaczej `throw std::invalid_argument("godzina lub minuta poza zakresem")`.

c) `constexpr int toMinutes(Time t)` zwraca liczbę minut od północy (`07:30` → `450`). `constexpr int minutesUntil(Time from, Time to)` zwraca liczbę minut od `from` do najbliższego `to`, także przez północ (`23:00` → `01:30` = `150`). Doba ma 1440 minut, więc przyda się `% 1440`.

d) Operator literałowy `operator""_hm(const char* text, std::size_t length)`, który zwraca `parseTime(std::string_view{text, length})`. Uzupełnij go w obu gałęziach `#if`.

### Część C++20

Kompiluj z `-std=c++20` lub `-DCMAKE_CXX_STANDARD=20`. Uzupełniasz tylko kod w gałęziach `#if __cplusplus >= 202002L`.

e) Literał `_hm` oznacz **`consteval`** zamiast `constexpr`. Zmienną `wakeUpTime` oznacz **`constinit`**.

f) W `parseTime`, wewnątrz bloku `#if __cplusplus >= 202002L`, zwiększaj `runtimeParseCount` tylko wtedy, gdy funkcja działa po uruchomieniu: `if (!std::is_constant_evaluated()) ++runtimeParseCount;`.

Uwaga: zwykłe `if`, nie `if constexpr`. Warunek `if constexpr (std::is_constant_evaluated())` jest liczony przy kompilacji, więc zawsze wychodzi `true`.

**Po uruchomieniu** dla wejścia `22:15 07:30 7:30 24:00`:

```text
walidacja: OK
budzik: 07:30
budzik po zmianie: 06:45
22:15 -> do budzika 510 min
07:30 -> do budzika 1395 min
7:30: blad: oczekiwano formatu HH:MM
24:00: blad: godzina lub minuta poza zakresem
parsowania w runtime: 9
```

Ostatnia linia pojawia się tylko w C++20.
