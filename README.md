> Русская версия README доступна [здесь](README.ru.md)


# YtGrabber-TUI  

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

  ## Dependency Installation
 **Debian / Ubuntu**

🔹 For runtime:
```shell
sudo apt install -y libboost-filesystem libboost-system libboost-thread libboost-program-options libfmt10 libspdlog1 ffmpeg yt-dlp
```

🔹 For building:
```shell
sudo apt install -y g++ cmake libboost-dev libfmt-dev libspdlog-dev
```

 **Fedora**

🔹 For runtime:
```shell
sudo dnf install -y boost boost-filesystem boost-system boost-thread boost-program-options fmt spdlog ffmpeg yt-dlp
```

🔹 For building:
```shell
sudo dnf install -y gcc-c++ cmake boost-devel fmt-devel spdlog-devel
```

 **Arch Linux**

🔹 For runtime:
```shell
sudo pacman -S --needed boost fmt spdlog ffmpeg yt-dlp
```

🔹 For building:
```shell
sudo pacman -S --needed base-devel cmake boost fmt spdlog
```
