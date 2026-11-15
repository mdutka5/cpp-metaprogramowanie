/*
 * Zadanie 3 — Odwracanie kolejności bajtów (konkretne)
 *
 * Opis:
 *   Pliki PNG i protokoły sieciowe zapisują liczby w kolejności big-endian
 *   (najstarszy bajt pierwszy), a procesory x86 i ARM trzymają je w little-endian.
 *   Po odczycie trzeba więc odwrócić kolejność bajtów: 0x12345678 -> 0x78563412.
 *   Sposób odwracania zależy od rozmiaru typu, a rozmiar jest znany przy kompilacji,
 *   więc wybierzesz go przez if constexpr (sizeof(T) == ...), jak w materiałach.
 *
 * Cel:
 *   Jeden szablon byteSwap<T> działa dla liczb bez znaku o rozmiarze 1, 2, 4 i 8 bajtów,
 *   a dla innych typów kompilator zgłasza czytelny błąd.
 *
 * Do zrobienia:
 *   a) Gałęzie if constexpr dla sizeof(T) == 1, 2 i 4.
 *   b) Gałąź dla sizeof(T) == 8: rozbij liczbę na dwie połówki po 4 bajty
 *      i użyj byteSwap dla każdej z nich.
 *   c) Dwa static_assert: na początku funkcji (tylko typy całkowite bez znaku)
 *      i w końcowej gałęzi else (nieobsługiwany rozmiar).
 *
 * Dopóki zadanie nie jest zrobione, kompilacja zatrzymuje się na static_assert.
 * Treść i oczekiwany wynik: zadania.md, zadanie 3.
 */
#include <cstdint>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <type_traits>

template <typename>
inline constexpr bool unsupportedSize = false;

template <typename T>
constexpr T byteSwap(T value)
{
    // TODO c: static_assert(std::is_integral_v<T> && std::is_unsigned_v<T>, "...");
    // TODO a: if constexpr (sizeof(T) == 1) ... else if constexpr (sizeof(T) == 2) ... == 4 ...
    // TODO b: else if constexpr (sizeof(T) == 8) ...
    // TODO c: else { static_assert(unsupportedSize<T>, "..."); }
    return value;
}

// ===== TESTY (nie zmieniaj) =====
static_assert(byteSwap(std::uint8_t{0xAB}) == 0xAB, "1 bajt: bez zmian");
static_assert(byteSwap(std::uint16_t{0x1234}) == 0x3412, "2 bajty: 0x1234 -> 0x3412");
static_assert(byteSwap(std::uint32_t{0x12345678}) == 0x78563412u, "4 bajty: 0x12345678 -> 0x78563412");
static_assert(byteSwap(std::uint32_t{0x000000FF}) == 0xFF000000u, "4 bajty: 0x000000FF -> 0xFF000000");
static_assert(byteSwap(std::uint64_t{0x0102030405060708}) == 0x0807060504030201u,
              "8 bajtow: 0x0102030405060708 -> 0x0807060504030201");
static_assert(byteSwap(byteSwap(std::uint32_t{0xDEADBEEF})) == 0xDEADBEEFu,
              "dwukrotne odwrocenie ma przywrocic liczbe");
static_assert(std::is_same_v<decltype(byteSwap(std::uint16_t{1})), std::uint16_t>,
              "wynik ma miec ten sam typ co argument");

template <typename T>
void show(const char *name, T value)
{
    const int digits = static_cast<int>(sizeof(T) * 2);
    std::cout << name << ": " << std::hex << std::setfill('0')
              << std::setw(digits) << +value << " -> "
              << std::setw(digits) << +byteSwap(value) << std::dec << "\n";
}

int main()
{
    show("uint8 ", std::uint8_t{0xAB});
    show("uint16", std::uint16_t{0x1234});
    show("uint32", std::uint32_t{0x12345678});
    show("uint64", std::uint64_t{0x0102030405060708});

    const unsigned char header[4] = {0x00, 0x00, 0x03, 0x20};
    std::uint32_t raw = 0;
    std::memcpy(&raw, header, sizeof(raw));
    std::cout << "szerokosc obrazka: " << byteSwap(raw) << "\n";

    return 0;
}
// ===== KONIEC TESTÓW =====
