# YtGrabber-TUI  

## 🇷🇺 Описание (Russian)  

**Yt-Grabber-TUI** — это официальное ответвление предполагаемого проекта [**Yt-Grabber**](https://github.com/zheny-creator/YtGrabber), который в будущем будет реализован в виде GUI-приложения (Qt/Kirigami).  
В отличие от основной версии, **Yt-Grabber-TUI** предоставляет текстовый интерфейс (TUI), позволяющий работать с yt-dlp без необходимости изучать его команды.

## Системные требования

**ОС:** 64-битный дистрибутив Linux с glibc ≥ 2.31  

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

**OS:** 64-bit Linux distribution with glibc ≥ 2.31

**C++ Compiler:** g++ with C++11 support

**C++ Libraries:**

* Boost (filesystem, system, thread, process, property_tree for JSON)
* fmt
* spdlog

**External Utilities:**

* FFmpeg (for yt-dlp functionality)
* yt-dlp

# Build

```Shell
make
```
