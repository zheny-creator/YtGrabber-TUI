# YtGrabber-TUI  

**Yt-Grabber-TUI** — это официальное ответвление предполагаемого проекта [**Yt-Grabber**](https://github.com/zheny-creator/YtGrabber), который в будущем будет реализован в виде GUI-приложения (Qt/Kirigami).  
В отличие от основной версии, **Yt-Grabber-TUI** предоставляет текстовый интерфейс (TUI), позволяющий работать с yt-dlp без необходимости изучать его команды.

## Системные требования для Linux

**ОС:** 64-битный дистрибутив Linux с glibc ≥ 2.31  

**Компилятор C++:** g++ с поддержкой C++11  

**Библиотеки C++:**
- Boost (filesystem, system, thread, process, property_tree для JSON)
- fmt
- spdlog

**Внешние утилиты:**
- FFmpeg (для работы с yt-dlp)
- yt-dlp

## Системные требования для Windows

**ОС:**
Windows 10 (64-разрядная) или новее

**Компилятор C++:**

* MinGW-w64 g++ с поддержкой C++11 *(рекомендуется версия 11 или новее)*
* MSVC (Visual Studio 2019 или новее)

**Библиотеки C++:**

* **Boost 1.83** *(должна быть собрана из исходников; требуемые модули: filesystem, system, thread, process, property_tree для JSON)*
* **fmt** (библиотека для форматирования строк)
* **spdlog** (для структурированного логирования)

**Внешние утилиты:**

* **FFmpeg** (необходим для работы функциональности yt-dlp)
* **yt-dlp** (последняя версия с [https://github.com/yt-dlp/yt-dlp](https://github.com/yt-dlp/yt-dlp)

---


# Сборка
```Shell
make
```

## Установка зависимостей
 **Debian / Ubuntu**

🔹 Для запуска:
```shell
sudo apt install -y libboost-filesystem1.83.0 libboost-system1.83.0 libboost-thread1.83.0 libboost-program-options1.83.0 libfmt9 libspdlog1.12 ffmpeg yt-dlp
```
🔹 Для сборки:
```shell
sudo apt install -y g++ make libboost-dev libfmt-dev libspdlog-dev
```

 **Fedora**

🔹 Для запуска:
```shell
sudo dnf install -y boost boost-filesystem boost-system boost-thread boost-program-options fmt spdlog ffmpeg yt-dlp
```

🔹 Для сборки:
```shell
sudo dnf install -y gcc-c++ make boost-devel fmt-devel spdlog-devel
```

  **Arch Linux**

🔹 Для запуска:
```shell
sudo pacman -S --needed boost fmt spdlog ffmpeg yt-dlp
```

🔹 Для сборки:
```shell
sudo pacman -S --needed base-devel make boost fmt spdlog
```

