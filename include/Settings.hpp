#include <iostream>                            // for cout
#include <string>                              // for string
#include "Log.hpp"                             // for log
#include <boost/process.hpp>                   // for child
#include <boost/filesystem.hpp>                // for filesystem
#include <boost/property_tree/ptree.hpp>       // for ptree
#include <boost/property_tree/json_parser.hpp> // for json_parser
#include <cstdlib>
#define DEBUG false                  // for debug
using namespace std;                 // for string
namespace fs = boost::filesystem;    // for filesystem
namespace bp = boost::process;       // for child
namespace pt = boost::property_tree; // for ptree

class settings_to_json
{
private:
    pt::ptree config;

public:
    settings_to_json(const pt::ptree &config) : config(config) {}

    void create_json_settings(pt::ptree &config)
    {
#if (DEBUG)
        cout << "Создание файла настроек..." << endl;
#endif
        fs::path config_dir;
        fs::path config_file;
#if defined(__linux__)
        const char *home = getenv("HOME");
        config_dir = fs::path(home) / ".config" / "yt-grabber-tui";
        try
        {
            fs::create_directories(config_dir);
        }
        catch (const fs::filesystem_error &e)
        {
            cerr << e.what() << "Ошибка создания директории" << std::endl;
        }
        config_file = config_dir / "config.json";
#elif defined(_WIN32)
#endif
        pt::ptree quality_video;
        quality_video.put("enabled", false);
        quality_video.put("quality", 1080);
        config.add_child("quality", quality_video);

        pt::ptree enabled_thumbnail;

        enabled_thumbnail.put("enabled", true);
        config.add_child("thumbnail", enabled_thumbnail);

        pt::ptree custom_path_ffmpeg;

        custom_path_ffmpeg.put("enabled", false);
        custom_path_ffmpeg.put("path", "You path to ffmpeg");
        config.add_child("Custom Path to ffmpeg", custom_path_ffmpeg);

        pt::ptree custom_path_yt_dlp;

        custom_path_yt_dlp.put("enabled", false);
        custom_path_yt_dlp.put("path", "You path to yt-dlp");
        config.add_child("Custom Path to yt-dlp", custom_path_yt_dlp);

        pt::ptree format_video;

        format_video.put("enabled", false);
        format_video.put("format", "mp4");
        config.add_child("format video", format_video);

        pt::ptree format_audio;

        format_audio.put("enabled", false);
        format_audio.put("format", "mp3");
        config.add_child("format audio", format_audio);

        pt::ptree quality_audio;

        quality_audio.put("enabled", false);
        quality_audio.put("quality", 128);
        config.add_child("quality audio", quality_audio);

        fs::path temp_file = config_dir / ("temp_config_" + std::to_string(getpid()) + ".json");
#if defined(_WIN32)
        temp_file = config_file.parent_path() / ("temp_config_" + std::to_string(GetCurrentProcessId()) + ".json");
#endif

        try
        {
            pt::write_json(temp_file.string(), config);
            fs::rename(temp_file, config_file);
#if (DEBUG)
            cout << "Файл настроек создан атомарно." << endl;
#endif
        }
        catch (const std::exception &e)
        {
            fs::remove(temp_file);
#if (DEBUG)
            cout << "Файл настроек уже существует или ошибка: " << e.what() << endl;
#endif
        }
    }

    void load_json_settings(pt::ptree &config)
    {
        fs::path config_file;
#if defined(__linux__)
        const char *home = getenv("HOME");
        config_file = fs::path(home) / ".config" / "yt-grabber-tui" / "config.json";
#endif
#if defined(__linux__)
        if (!fs::exists(config_file))
        {
            create_json_settings(config);
        }
        else
        {
#if (DEBUG)
            cout << "Загрузка настроек..." << endl;
#endif
        }
#elif defined(_WIN32)
        if (!fs::exists("config.json"))
        {
            create_json_settings(config);
        }
        else
        {
#if (DEBUG)
            cout << "Загрузка настроек..." << endl;
#endif
        }
#endif

#if defined(__linux__)
        try
        {
            pt::read_json(config_file.string(), config);
        }
        catch (const pt::json_parser::json_parser_error &e)
        {
            cerr << "Ошибка чтения файла настроек: " << e.what() << endl;
        }
#elif defined(_WIN32)
        try
        {
            pt::read_json("config.json", config);
        }
        catch (const pt::json_parser::json_parser_error &e)
        {
            cerr << "Ошибка чтения файла настроек: " << e.what() << endl;
        }
#endif
    }
};