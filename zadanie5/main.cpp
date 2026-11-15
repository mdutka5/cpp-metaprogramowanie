/*
 * Zadanie 5 — Budzik z literałem "07:30"_hm (praktyczne)
 *
 * Opis:
 *   Godziny zapisujemy w kodzie literałem, np. "07:30"_hm. Błędna godzina wpisana
 *   w kod ("25:00"_hm) ma być błędem kompilacji. Ten sam parser obsługuje godziny
 *   wpisane przez użytkownika, a wtedy błąd jest wyjątkiem, który program łapie.
 *   Program pokazuje, ile minut zostało do budzika.
 *
 * Cel:
 *   Jedna funkcja parseTime działa przy kompilacji i po uruchomieniu.
 *   W C++20 literał _hm jest consteval, budzik jest constinit, a program liczy,
 *   ile razy parseTime wykonała się dopiero po uruchomieniu.
 *
 * Do zrobienia (C++17):
 *   a) digitValue: znak '0'..'9' -> liczba 0..9, inny znak -> wyjątek.
 *   b) parseTime: "HH:MM" -> Time, z kontrolą formatu i zakresu (wyjątki).
 *   c) toMinutes i minutesUntil: minuty od północy i minuty do podanej godziny.
 *   d) literał operator""_hm zwracający parseTime(...).
 * Do zrobienia (C++20, kompilacja z -std=c++20 lub -DCMAKE_CXX_STANDARD=20):
 *   e) literał oznacz consteval, a wakeUpTime oznacz constinit.
 *   f) w parseTime zwiększaj runtimeParseCount, tylko gdy funkcja działa po uruchomieniu.
 *
 * Dopóki zadanie nie jest zrobione, kompilacja zatrzymuje się na static_assert.
 * Treść i oczekiwany wynik: zadania.md, zadanie 5.
 */
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <string_view>
#if __cplusplus >= 202002L
#include <type_traits>
#endif

struct Time
{
    int hour;
    int minute;
};

#if __cplusplus >= 202002L
// f) Liczba wywołań parseTime wykonanych dopiero po uruchomieniu programu.
inline int runtimeParseCount = 0;
#endif

// a) '0'..'9' -> 0..9. Każdy inny znak: throw std::invalid_argument("niepoprawna cyfra").
constexpr int digitValue(char c)
{
    // TODO a
    (void)c;
    return 0;
}

// b) "HH:MM" -> Time. Sprawdzaj w tej kolejności:
//    1. długość 5 i ':' na pozycji 2, inaczej throw std::invalid_argument("oczekiwano formatu HH:MM");
//    2. cyfry na pozostałych pozycjach (digitValue);
//    3. godzina 0..23 i minuta 0..59, inaczej throw std::invalid_argument("godzina lub minuta poza zakresem").
// f) (C++20) jeśli !std::is_constant_evaluated(), zwiększ runtimeParseCount.
constexpr Time parseTime(std::string_view text)
{
    // TODO b
    // TODO f (C++20)
    (void)text;
    return Time{0, 0};
}

// c) Liczba minut od północy, np. 07:30 -> 450.
constexpr int toMinutes(Time t)
{
    // TODO c
    (void)t;
    return 0;
}

// c) Ile minut od godziny from do najbliższej godziny to (także przez północ). Wynik 0..1439.
//    Wskazówka: doba ma 1440 minut, przyda się % 1440.
constexpr int minutesUntil(Time from, Time to)
{
    // TODO c
    (void)from;
    (void)to;
    return 0;
}

// d) Literał "HH:MM"_hm ma zwracać parseTime(std::string_view{text, length}).
// e) W C++20 ten sam literał ma być consteval (zamiast constexpr).
#if __cplusplus >= 202002L
constexpr Time operator""_hm(const char *text, std::size_t length) // TODO e: consteval
{
    // TODO d
    (void)text;
    (void)length;
    return Time{0, 0};
}
#else
constexpr Time operator""_hm(const char *text, std::size_t length)
{
    // TODO d
    (void)text;
    (void)length;
    return Time{0, 0};
}
#endif

// e) Godzina budzika: zmienna globalna, którą program zmienia po uruchomieniu.
#if __cplusplus >= 202002L
Time wakeUpTime = "07:30"_hm; // TODO e: dodaj constinit
#else
Time wakeUpTime = "07:30"_hm;
#endif

// ===== TESTY (nie zmieniaj) =====
static_assert(digitValue('0') == 0 && digitValue('7') == 7 && digitValue('9') == 9, "cyfry 0..9");
static_assert(parseTime("07:30").hour == 7 && parseTime("07:30").minute == 30, "07:30 -> 7 h 30 min");
static_assert(parseTime("23:59").hour == 23 && parseTime("23:59").minute == 59, "23:59 -> 23 h 59 min");
static_assert(toMinutes("07:30"_hm) == 450, "07:30 to 450 minut od polnocy");
static_assert(toMinutes("00:00"_hm) == 0, "00:00 to 0 minut od polnocy");
static_assert(minutesUntil("22:00"_hm, "23:30"_hm) == 90, "z 22:00 do 23:30 jest 90 minut");
static_assert(minutesUntil("23:00"_hm, "01:30"_hm) == 150, "z 23:00 do 01:30 jest 150 minut (przez polnoc)");
static_assert(minutesUntil("07:30"_hm, "07:30"_hm) == 0, "ta sama godzina: 0 minut");

int failures = 0;

void expectInvalid(std::string_view text)
{
    try
    {
        parseTime(text);
        std::cout << "FAIL: " << text << " powinno zostac odrzucone\n";
        ++failures;
    }
    catch (const std::invalid_argument &)
    {
    }
}

void printTime(Time t)
{
    std::cout << std::setfill('0') << std::setw(2) << t.hour << ':' << std::setw(2) << t.minute;
}

int main()
{
    expectInvalid("7:30");
    expectInvalid("07-30");
    expectInvalid("ab:cd");
    expectInvalid("24:00");
    expectInvalid("12:60");
    std::cout << (failures == 0 ? "walidacja: OK" : "walidacja: FAIL") << "\n";

    std::cout << "budzik: ";
    printTime(wakeUpTime);
    std::cout << "\n";

    wakeUpTime = "06:45"_hm;
    std::cout << "budzik po zmianie: ";
    printTime(wakeUpTime);
    std::cout << "\n";

    std::string input;
    while (std::cin >> input)
    {
        try
        {
            const Time now = parseTime(input);
            printTime(now);
            std::cout << " -> do budzika " << minutesUntil(now, wakeUpTime) << " min\n";
        }
        catch (const std::invalid_argument &error)
        {
            std::cout << input << ": blad: " << error.what() << "\n";
        }
    }

#if __cplusplus >= 202002L
    std::cout << "parsowania w runtime: " << runtimeParseCount << "\n";
#endif

    return failures == 0 ? 0 : 1;
}
// ===== KONIEC TESTÓW =====
