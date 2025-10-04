#include <iostream>                            // for cout
#include <string>                              // for string
#include "json.hpp"                            // for json
#include "Log.hpp"                             // for log
#include <boost/process.hpp>                   // for child
#include <boost/process/child.hpp>             // for child
#include <boost/filesystem.hpp>                // for filesystem
#include <boost/property_tree/ptree.hpp>       // for ptree
#include <boost/property_tree/json_parser.hpp> // for json_parser

using json = nlohmann::json;         // for json
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

    void create_json_settings()
    {
        if (fs::exists("config.json"))
        {
            cout << "Загрузка настроек..." << endl;
            pt::read_json("config.json", config);
        }
        else
        {
            cout << "Создание файла настроек..." << endl;
            pt::ptree quality_video;

            quality_video.put("enabled", false);
            quality_video.put("quality", "1080");
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

            pt::write_json("config.json", config);
        }
    }
};