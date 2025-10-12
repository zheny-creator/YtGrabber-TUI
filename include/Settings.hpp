#include <iostream>                            // for cout
#include <string>                              // for string
#include "Log.hpp"                             // for log
#include <boost/process.hpp>                   // for child
#include <boost/filesystem.hpp>                // for filesystem
#include <boost/property_tree/ptree.hpp>       // for ptree
#include <boost/property_tree/json_parser.hpp> // for json_parser
#include <cstdlib>

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
        cout << "Создание файла настроек..." << endl;
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
        const char *home = std::getenv(L"LOCALAPPDATA");
        config_dir = fs::path(home) / "yt-grabber-tui";
        try
        {
            fs::create_directories(config_dir);
        }
        catch (const fs::filesystem_error &e)
        {
            cerr << e.what() << "Ошибка создания директории" << std::endl;
        }
        config_file = config_dir / "config.json";
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
#if defined(_WIN32)
        try
        {
            std::ofstream file(config_file.string()); // char-поток
            pt::write_json(file, config);
            file.close();
        }
        catch (const pt::json_parser::json_parser_error &e)
        {
            std::cerr << "Ошибка записи файла настроек: " << e.what() << std::endl;
        }
#else
        try
        {
            pt::write_json(config_file.string(), config);
        }
        catch (const pt::json_parser::json_parser_error &e)
        {
            std::cerr << "Ошибка записи файла настроек: " << e.what() << std::endl;
        }
#endif
    }

    void load_json_settings(pt::ptree &config)
    {
        fs::path config_file;

#if defined(_WIN32)
        const char *home = std::getenv("LOCALAPPDATA");
        if (!home)
        {
            std::cerr << "Не удалось получить LOCALAPPDATA" << std::endl;
            return;
        }
        config_file = fs::path(home) / "yt-grabber-tui" / "config.json";
#else
        const char *home = std::getenv("HOME");
        if (!home)
        {
            std::cerr << "Не удалось получить HOME" << std::endl;
            return;
        }
        config_file = fs::path(home) / ".config" / "yt-grabber-tui" / "config.json";
#endif

        // Если файла нет — создаём
        if (!fs::exists(config_file))
        {
            create_json_settings(config);
        }

        // Чтение
        try
        {
            std::ifstream file(config_file.string()); // char поток для Boost
            pt::read_json(file, config);
        }
        catch (const pt::json_parser::json_parser_error &e)
        {
            std::cerr << "Ошибка чтения файла настроек: " << e.what() << std::endl;
        }
    }

    void write_json_crossplatform(const fs::path &file_path, const pt::ptree &tree)
    {
        try
        {
#if defined(_WIN32)
            std::ofstream file(file_path.string()); // UTF-8 путь
#else
            std::ofstream file(file_path);
#endif
            if (!file)
            {
                std::cerr << "Не удалось открыть файл для записи: " << file_path << std::endl;
                return;
            }
            pt::write_json(file, tree);
            file.close();
        }
        catch (const pt::json_parser::json_parser_error &e)
        {
            std::cerr << "Ошибка записи файла: " << e.what() << std::endl;
        }
    }
};