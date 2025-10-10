# YtGrabber-TUI  

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
