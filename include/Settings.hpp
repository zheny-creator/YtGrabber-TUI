#include <iostream>                            // for cout
#include <string>                              // for string
#include "Log.hpp"                             // for log
#include <boost/process.hpp>                   // for child
#include <boost/process/child.hpp>             // for child
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
        const char *home = getenv("HOME");
        fs::path config_dir = fs::path(home) / ".config" / "YtGrabber-TUI";
        fs::create_directories(config_dir);
        fs::path config_file = config_dir / "config.json";

        pt::ptree quality_video;

        quality_video.put("enabled", false);
        quality_video.put("quality", 1080);
        config.add_child("quality", quality_video);

        pt::ptree enabled_thumbnail;

        enabled_thumbnail.put("enabled", true);
        config.add_child("thumbnail", enabled_thumbnail);

        pt::ptree custom_path_ffmpeg;

        custom_path_ffmpeg.add("enabled", false);
        custom_path_ffmpeg.add("path", "You path to ffmpeg");
        config.add_child("Custom Path to ffmpeg", custom_path_ffmpeg);

        pt::ptree custom_path_yt_dlp;

        custom_path_yt_dlp.add("enabled", false);
        custom_path_yt_dlp.add("path", "You path to yt-dlp");
        config.add_child("Custom Path to yt-dlp", custom_path_yt_dlp);

        pt::write_json(config_file.string(), config);
    }

    void load_json_settings(pt::ptree &config)
    {

        const char *home = std::getenv("HOME");
        fs::path config_dir = fs::path(home) / ".config" / "YtGrabber-TUI" / "config.json";

        if (!fs::exists(config_dir))
        {
            create_json_settings(config);
        }
        if (fs::exists(config_dir))
        {
            cout << "Загрузка настроек..." << endl;
            pt::read_json(config_dir.string(), config);
        }
        else
        {
            create_json_settings(config);
        }
    }
};