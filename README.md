# YtGrabber-TUI  

## 🇷🇺 Описание (Russian)  

**Yt-Grabber-TUI** — это официальное ответвление предполагаемого проекта [**Yt-Grabber**](https://github.com/zheny-creator/YtGrabber), который в будущем будет реализован в виде GUI-приложения (Qt/Kirigami).  
В отличие от основной версии, **Yt-Grabber-TUI** предоставляет текстовый интерфейс (TUI), позволяющий работать с yt-dlp без необходимости изучать его команды.

## Системные требования

ОС: Windows 8 x64 или выше

Компилятор C++: g++

Стандарт языка: C++11

Библиотеки C++:

Boost (filesystem, system, thread, process)

fmt

spdlog (для логирования)

nlohmann/json (json.hpp)

Внешние утилиты: yt-dlp (актуальная версия)


# Сборка
```Shell
g++ -fdiagnostics-color=always -g -Iinclude src/main.cpp -o main -lboost_system -lboost_filesystem -lpthread -lfmt
```

---

## 🇬🇧 Description (English)  

**Yt-Grabber-TUI** is the official fork of the upcoming project [**Yt-Grabber**](https://github.com/zheny-creator/YtGrabber), which in the future will be developed as a GUI application (Qt/Kirigami).  
Unlike the planned GUI version, **Yt-Grabber-TUI** provides a text-based user interface (TUI), allowing users to work with yt-dlp without learning its command-line arguments.  


## System Requirements

OS: Windows 8 x64 or higher

C++ Compiler: g++

Language Standard: C++11

C++ Libraries:

Boost (filesystem, system, thread, process)

fmt

spdlog (for logging)

nlohmann/json (json.hpp)

External Tools: yt-dlp (latest version)



# Build

```Shell
g++ -fdiagnostics-color=always -g -Iinclude src/main.cpp -o main -lboost_system -lboost_filesystem -lpthread -lfmt
```
