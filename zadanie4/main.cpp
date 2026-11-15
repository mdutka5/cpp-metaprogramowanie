/*
 * Zadanie 4 — Robot sterowany napisami (praktyczne)
 *
 * Opis:
 *   switch działa tylko na liczbach całkowitych. Żeby sterować robotem poleceniami
 *   tekstowymi (forward, back, left, right, stop), zamieniamy napis na liczbę funkcją
 *   skrótu djb2. Etykiety case liczy kompilator dzięki literałowi "forward"_cmd
 *   (jak "start"_h w rozdziale „Switch po napisach”).
 *   Dwa różne napisy mogą mieć ten sam skrót (kolizja), np. "stop" i "stpO".
 *   Program musi to wykryć.
 *
 * Cel:
 *   Robot wykonuje polecenia wczytane z klawiatury, nieznane polecenia zgłasza,
 *   a napis kolidujący z poleceniem nie powoduje ruchu.
 *
 * Do zrobienia:
 *   a) Uzupełnij djb2: hash = 5381, potem dla każdego znaku hash = hash * 33 + znak.
 *   b) Uzupełnij literał operator""_cmd, który zwraca djb2 napisu.
 *   c) Uzupełnij execute: switch (djb2(command)) z etykietami case "forward"_cmd: itd.
 *   d) W każdej gałęzi case sprawdź jeszcze, czy command to naprawdę ten napis.
 *
 * Dopóki zadanie nie jest zrobione, kompilacja zatrzymuje się na static_assert.
 * Treść i oczekiwany wynik: zadania.md, zadanie 4.
 */
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <string>
#include <string_view>

// a) djb2: zacznij od 5381, dla każdego znaku c wykonaj hash = hash * 33 + c.
//    Znak zamień najpierw na liczbę 0..255: static_cast<unsigned char>(c).
//    Przepełnienie std::uint32_t jest tu dozwolone (liczby bez znaku zawijają się).
constexpr std::uint32_t djb2(std::string_view text)
{
    // TODO a
    (void)text;
    return 0;
}

// b) Literał "napis"_cmd ma zwracać djb2 tego napisu.
constexpr std::uint32_t operator""_cmd(const char *text, std::size_t length)
{
    // TODO b
    (void)text;
    (void)length;
    return 0;
}

struct Robot
{
    int x = 0;
    int y = 0;
};

enum class Result
{
    Moved,
    Stopped,
    Unknown
};

// c) forward: y + 1, back: y - 1, left: x - 1, right: x + 1, stop: Result::Stopped.
// d) W każdej gałęzi case porównaj też command z oczekiwanym napisem (command == "forward"),
//    a gdy się nie zgadza, potraktuj polecenie jako nieznane.
constexpr Result execute(Robot &robot, std::string_view command)
{
    // TODO c, d
    (void)robot;
    (void)command;
    return Result::Unknown;
}

// ===== TESTY (nie zmieniaj) =====
static_assert(djb2("") == 5381u, "djb2 pustego napisu to 5381");
static_assert(djb2("a") == 5381u * 33u + 'a', "djb2(\"a\") = 5381 * 33 + 'a'");
static_assert(djb2("ab") == (5381u * 33u + 'a') * 33u + 'b', "djb2(\"ab\") liczone znak po znaku");
static_assert("forward"_cmd == djb2("forward"), "literal _cmd ma zwracac djb2 napisu");
static_assert(djb2("stop") == djb2("stpO"), "stop i stpO maja ten sam skrot (kolizja)");

constexpr Robot runScript()
{
    Robot robot;
    execute(robot, "forward");
    execute(robot, "forward");
    execute(robot, "left");
    execute(robot, "back");
    execute(robot, "right");
    execute(robot, "right");
    return robot;
}
static_assert(runScript().x == 1 && runScript().y == 1, "po skrypcie robot powinien stac na (1, 1)");

constexpr bool stopStops()
{
    Robot robot;
    return execute(robot, "stop") == Result::Stopped;
}
static_assert(stopStops(), "stop ma zwracac Result::Stopped");

constexpr bool unknownDoesNothing()
{
    Robot robot;
    return execute(robot, "jump") == Result::Unknown && robot.x == 0 && robot.y == 0;
}
static_assert(unknownDoesNothing(), "nieznane polecenie nie rusza robota");

constexpr bool collisionIsUnknown()
{
    Robot robot;
    return execute(robot, "stpO") == Result::Unknown && execute(robot, "legS") == Result::Unknown &&
           robot.x == 0 && robot.y == 0;
}
static_assert(collisionIsUnknown(), "napis z tym samym skrotem co polecenie to nadal nieznane polecenie");

int main()
{
    Robot robot;
    std::string command;
    while (std::cin >> command)
    {
        const Result result = execute(robot, command);
        if (result == Result::Stopped)
            break;
        if (result == Result::Unknown)
            std::cout << "nieznane polecenie: " << command << "\n";
    }
    std::cout << "pozycja: (" << robot.x << ", " << robot.y << ")\n";
    return 0;
}
// ===== KONIEC TESTÓW =====
