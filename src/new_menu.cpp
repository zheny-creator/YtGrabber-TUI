#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <string>
#include <vector>
#include <iostream>

using namespace ftxui;
using namespace std;

int main()
{

    auto button = Button("Скачать видео", []
                         { cout << "Тест"; });
    auto button_2 = Button("Скачать аудио", []
                           { cout << "Тест 2"; });
    auto screen = ScreenInteractive::TerminalOutput();

    auto container = Container::Vertical({button, button_2});

    auto renderer = Renderer(container, [&]
                             { return vbox({button->Render() | center,
                                            button_2->Render() | center}) |
                                      border; });

    screen.Loop(renderer);
}