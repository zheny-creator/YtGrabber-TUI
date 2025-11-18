> Русская версия README доступна [здесь](README.ru.md)


# YtGrabber-TUI  

**Yt-Grabber-TUI** is the official fork of the upcoming project [**Yt-Grabber**](https://github.com/zheny-creator/YtGrabber), which in the future will be developed as a GUI application (Qt/Kirigami).  
Unlike the planned GUI version, **Yt-Grabber-TUI** provides a text-based user interface (TUI), allowing users to work with yt-dlp without learning its command-line arguments.  


## System Requirements for Linux

**OS:** 64-bit Linux distribution with glibc ≥ 2.35

**C++ Compiler:** g++ with C++17 support

**C++ Libraries:**

* Boost (filesystem, system, thread, process, property_tree for JSON)
* fmt

**External Utilities:**

* FFmpeg (for yt-dlp functionality)
* yt-dlp

# Build

```Shell
make
```
