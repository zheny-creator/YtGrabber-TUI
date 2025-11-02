#include <iostream> // for cout
#include <string>   // for string
#include "Settings.hpp"
#include <boost/process.hpp>    // for child
#include <boost/filesystem.hpp> // for filesystem
#include <vector>
#include <new>
using namespace std;              // for string
namespace fs = boost::filesystem; // for filesystem
namespace bp = boost::process;    // for child

class video // Class video
{
private:              // Private members
    string url;       // url
    int quality;      // quality
    string subtitles; // subtitles
    pt::ptree config; // config

public: // Public members
        // Constructor
    video(const string &url, int &quality, string &subtitles, const pt::ptree &config) : url(url), quality(quality), subtitles(subtitles), config(config) {}

    void download(const string &url, int &quality, const pt::ptree &config) // Function download
    {
        string path_ffmpeg;
        string yt_dlp_path = bp::search_path("yt-dlp").string();
        vector<string> args; // Vector of arguments
        string video_format = config.get<string>("format video.format", "mp4");
        string sub_lang = config.get<string>("subtitles.language", "en");
        string bestaudio = "bestaudio";
        string bestaudio_quality = config.get<string>("quality_audio_for_video.quality", "128");
        if (config.get<string>("quality_audio_for_video.enabled", "false") == "true")
        {
            bestaudio = "bestaudio[abr<= " + bestaudio_quality + "]";
        }
        try
        {
            args = {
                "-f", "\""
                      "bestvideo[height<=" +
                          to_string(quality) + "]" + "+" + "bestaudio"
                                                           "\"",
                url};
        }
        catch (const bad_alloc &e)
        {
            cerr << e.what() << "Ошибка выделения памяти" << endl;
        }
        if (config.get<string>("Custom Path to ffmpeg.enabled", "false") == "true")
        {
            if (!fs::exists(config.get<string>("Custom Path to ffmpeg.path", "ffmpeg")))
            {
                cerr << "Путь к ffmpeg указан неверно!" << endl;
                return;
            }
            else if (fs::is_directory(config.get<string>("Custom Path to ffmpeg.path", "ffmpeg")))
            {
                cerr << "Это путь к папке!" << endl;
            }

            else if (fs::exists(config.get<string>("Custom Path to ffmpeg.path", "ffmpeg")))
            {
                path_ffmpeg = config.get<string>("Custom Path to ffmpeg.path", "ffmpeg");
                args.insert(args.begin(), "--ffmpeg-location=\"" + path_ffmpeg + "\"");
            }
        }
        if (config.get<string>("thumbnail.enabled", "false") == "true")
        {
            args.insert(args.begin(), "--embed-thumbnail");
        }
        if (config.get<string>("Custom Path to yt-dlp.enabled", "false") == "true")
        {
            if (!fs::exists(config.get<string>("Custom Path to yt-dlp.path", "yt-dlp")))
            {
                cerr << "Путь к yt-dlp указан неверно!" << endl;
                return;
            }
            else if (fs::is_directory(config.get<string>("Custom Path to yt-dlp.path", "yt-dlp")))
            {
                cerr << "Это путь к папке!" << endl;
                return;
            }
            else if (fs::exists(config.get<string>("Custom Path to yt-dlp.path", "yt-dlp")))
            {
                yt_dlp_path = config.get<string>("Custom Path to yt-dlp.path", "yt-dlp");
            }
        }
        if (config.get<string>("format video.enabled", "false") == "true")
        {

            args.insert(args.begin(), video_format);
            args.insert(args.begin(), "--merge-output-format");
        }
        if (config.get<string>("subtitles.enabled", "false") == "true")
        {
            if (config.get<string>("subtitles.auto", "false") == "false")
            {
                sub_lang = config.get<string>("subtitles.language", "en");
                args.insert(args.begin(), sub_lang);
                args.insert(args.begin(), "--sub-lang ");
                args.insert(args.begin(), "--embed-subs ");
                args.insert(args.begin(), "--write-subs ");
            }
            else if (config.get<string>("subtitles.enabled", "false") == "true")
            {
                sub_lang = config.get<string>("subtitles.language", "en");
                args.insert(args.begin(), sub_lang);
                args.insert(args.begin(), "--sub-lang ");
                args.insert(args.begin(), " --write-auto-subs ");
            }
        }
        cout << "Выполняется команда: yt-dlp ";
        for (const auto &a : args)
            cout << a << " ";
        cout << endl;
        try
        {
            bp::child c(yt_dlp_path, bp::args(args)); // Run yt-dlp
            c.wait();                                 // Wait for yt-dlp to finish
        }
        catch (const bp::process_error &e)
        {
            cerr << e.what() << "Ошибка запуска процесса!" << endl; // Handle process error
        }
    }
};
class audio
{
private:
    string url;       // url
    int quality;      // quality
    string subtitles; // subtitles
    pt::ptree config; // config

public:
    audio(const string &url, int &quality, string &subtitles, const pt::ptree &config) : url(url), quality(quality), subtitles(subtitles), config(config) {}

    // Function download audio
    void download(const string &url, int &quality, const pt::ptree &config)
    {
        vector<string> args; // Vector of arguments
        string path_ffmpeg;
        string yt_dlp_path = bp::search_path("yt-dlp").string();
        string audio_format;
        string sub_lang;
        if (quality > 256)
        {
            try
            {
                args = {
                    "-f", "bestaudio/best",
                    url};
            }
            catch (const bad_alloc &e)
            {
                cerr << e.what() << "Ошибка выделения памяти" << endl;
            }
        }
        else
        {
            try
            {
                args = {
                    "-f", "bestaudio[abr>=" + to_string(quality) + "]",
                    url};
            }
            catch (const bad_alloc &e)
            {
                cerr << e.what() << "Ошибка выделения памяти" << endl;
            }
        }
        if (config.get<string>("format audio.enabled", "false") == "true")
        {
            audio_format = config.get<string>("format audio.format", "mp3");
            args.push_back(audio_format);
            args.push_back("--audio-format");
            args.push_back("-x");
        }
        if (config.get<string>("Custom Path to ffmpeg.enabled", "false") == "true")
        {
            if (!fs::exists(config.get<string>("Custom Path to ffmpeg.path", "ffmpeg")))
            {
                cerr << "Путь к ffmpeg указан неверно!" << endl;
                return;
            }
            else if (fs::is_directory(config.get<string>("Custom Path to ffmpeg.path", "ffmpeg")))
            {
                cerr << "Это путь к папке!" << endl;
            }

            else if (fs::exists(config.get<string>("Custom Path to ffmpeg.path", "ffmpeg")))
            {
                path_ffmpeg = config.get<string>("Custom Path to ffmpeg.path", "ffmpeg");
                args.insert(args.begin(), "--ffmpeg-location=\"" + path_ffmpeg + "\"");
            }
        }
        if (config.get<string>("Custom Path to yt-dlp.enabled", "false") == "true")
        {
            if (!fs::exists(config.get<string>("Custom Path to yt-dlp.path", "yt-dlp")))
            {
                cerr << "Путь к yt-dlp указан неверно!" << endl;
                return;
            }
            else if (fs::is_directory(config.get<string>("Custom Path to yt-dlp.path", "yt-dlp")))
            {
                cerr << "Это путь к папке!" << endl;
                return;
            }
            else if (fs::exists(config.get<string>("Custom Path to yt-dlp.path", "yt-dlp")))
            {
                yt_dlp_path = config.get<string>("Custom Path to yt-dlp.path", "yt-dlp");
            }
        }
        cout << "Выполняется команда: yt-dlp ";
        for (const auto &a : args)
            cout << a << " ";
        cout << endl;
        try
        {
            bp::child c(yt_dlp_path, bp::args(args)); // Run yt-dlp
            c.wait();                                 // Wait for yt-dlp to finish
        }
        catch (const bp::process_error &e)
        {
            cerr << e.what() << "Ошибка запуска процесса!" << endl; // Handle process error
        }
    }
};