> Русская версия README доступна [здесь](README.ru.md)


# YtGrabber-TUI  

**Yt-Grabber-TUI** is the official fork of the upcoming project [**Yt-Grabber**](https://github.com/zheny-creator/YtGrabber), which in the future will be developed as a GUI application (Qt/Kirigami).  
Unlike the planned GUI version, **Yt-Grabber-TUI** provides a text-based user interface (TUI), allowing users to work with yt-dlp without learning its command-line arguments.  


## System Requirements for Linux

**OS:** 64-bit Linux distribution with glibc ≥ 2.31

**C++ Compiler:** g++ with C++11 support

**C++ Libraries:**

* Boost (filesystem, system, thread, process, property_tree for JSON)
* fmt
* spdlog

**External Utilities:**

* FFmpeg (for yt-dlp functionality)
* yt-dlp

## System Requirements for Windows

**OS:**
Windows 10 (64-bit) or later

**C++ Compiler:**

* MinGW-w64 g++ with C++11 support *(recommended v11 or newer)*
* MSVC (Visual Studio 2019 or newer)

**C++ Libraries:**

* **Boost 1.83** *(must be built from source; required modules: filesystem, system, thread, process, property_tree for JSON)*
* **fmt** (library for string formatting)
* **spdlog** (for structured logging output)

**External Utilities:**

* **FFmpeg** (required for yt-dlp functionality)
* **yt-dlp** (latest release from [https://github.com/yt-dlp/yt-dlp](https://github.com/yt-dlp/yt-dlp))

---

# Build

```Shell
make
```

  ## Dependency Installation
 **Debian / Ubuntu**

🔹 For runtime:
```shell
sudo apt install -y libboost-filesystem1.83.0 libboost-system1.83.0 libboost-thread1.83.0 libboost-program-options1.83.0 libfmt9 libspdlog1.12 ffmpeg yt-dlp
```

🔹 For building:
```shell
sudo apt install -y g++ make libboost-dev libfmt-dev libspdlog-dev
```

 **Fedora**

🔹 For runtime:
```shell
sudo dnf install -y boost boost-filesystem boost-system boost-thread boost-program-options fmt spdlog ffmpeg yt-dlp
```

🔹 For building:
```shell
sudo dnf install -y gcc-c++ make boost-devel fmt-devel spdlog-devel
```

 **Arch Linux**

🔹 For runtime:
```shell
sudo pacman -S --needed boost fmt spdlog ffmpeg yt-dlp
```

🔹 For building:
```shell
sudo pacman -S --needed base-devel make boost fmt spdlog
```
