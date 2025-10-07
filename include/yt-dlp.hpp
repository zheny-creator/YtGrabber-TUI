#include <iostream> // for cout
#include <string>   // for string
#include "Settings.hpp"
#include "Log.hpp"                 // for log
#include <boost/process.hpp>       // for child
#include <boost/process/child.hpp> // for child
#include <boost/filesystem.hpp>    // for filesystem
#include <vector>
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
        string command;
        string path_ffmpeg;
        vector<string> args = {
            "-f", "bestvideo[height<=" + to_string(quality) + "]",
            url};
        if (config.get<string>("Custom Path to ffmpeg.enabled", "false") == "true")
        {
            path_ffmpeg = config.get<string>("Custom Path to ffmpeg.path", "ffmpeg");
            args.insert(args.begin(), "\"" + path_ffmpeg + "\"");
            args.insert(args.begin(), "--ffmpeg-location=");
        }
        if (config.get<string>("thumbnail.enabled", "false") == "true")
        {
            args.insert(args.begin(), "--embed-thumbnail");
        }
        cout << "Выполняется команда: yt-dlp ";
        for (const auto &a : args)
            cout << a << " ";
        cout << endl;
        bp::child c(bp::search_path("yt-dlp"), bp::args(args)); // Run yt-dlp
        c.wait();                                               // Wait for yt-dlp to finish
    }
};
class audio
{
private:
    string url; // url

public:
    audio(const string &url) : url(url) {} // Constructor

    // Function download audio
    void download(const string &url)
    {
        bp::child c(bp::search_path("yt-dlp"), bp::args({"-f", "bestaudio/best", url}));
        c.wait();
    }
};
