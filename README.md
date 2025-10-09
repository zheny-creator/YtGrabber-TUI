# YtGrabber-TUI  

## 🇷🇺 Описание (Russian)  

**Yt-Grabber-TUI** — это официальное ответвление предполагаемого проекта [**Yt-Grabber**](https://github.com/zheny-creator/YtGrabber), который в будущем будет реализован в виде GUI-приложения (Qt/Kirigami).  
В отличие от основной версии, **Yt-Grabber-TUI** предоставляет текстовый интерфейс (TUI), позволяющий работать с yt-dlp без необходимости изучать его команды.

## Системные требования

### Windows

ОС: Windows 8 x64 или выше

Компилятор C++: g++

Стандарт языка: C++11

Библиотеки C++ для сборки проекта:

Boost (filesystem, system, thread, process)

fmt

spdlog (для логирования)

nlohmann/json (json.hpp)

Внешние утилиты: yt-dlp (актуальная версия)

### Linux

**ОС:** 64-битный дистрибутив Linux с glibc ≥ 2.31  
*(например: Ubuntu 20.04+, Debian 11+, Fedora 32+)*

**Компилятор C++:** g++ с поддержкой C++11  

**Библиотеки C++:**
- Boost (filesystem, system, thread, process, property_tree для JSON)
- fmt
- spdlog

**Внешние утилиты:**
- FFmpeg (для работы с yt-dlp)
- yt-dlp

# Сборка
```Shell
make
```

---

## 🇬🇧 Description (English)  

**Yt-Grabber-TUI** is the official fork of the upcoming project [**Yt-Grabber**](https://github.com/zheny-creator/YtGrabber), which in the future will be developed as a GUI application (Qt/Kirigami).  
Unlike the planned GUI version, **Yt-Grabber-TUI** provides a text-based user interface (TUI), allowing users to work with yt-dlp without learning its command-line arguments.  


## System Requirements

OS: Windows 8 x64 or higher

C++ Compiler: g++

Language Standard: C++11

C++ Libraries for build project:

Boost (filesystem, system, thread, process)

fmt

spdlog (for logging)

nlohmann/json (json.hpp)

External Tools: yt-dlp (latest version)



# Build

```Shell
make
```
