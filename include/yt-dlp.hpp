#include <iostream> // for cout
#include <string>   // for string
#include "Settings.hpp"
#include "Log.hpp"                 // for log
#include <boost/process.hpp>       // for child
#include <boost/process/child.hpp> // for child
#include <boost/filesystem.hpp>    // for filesystem
using namespace std;               // for string
namespace fs = boost::filesystem;  // for filesystem
namespace bp = boost::process;     // for child

class video // Class video
{
private:              // Private members
    string url;       // url
    int quality;      // quality
    string subtitles; // subtitles

public: // Public members
        // Constructor
    video(const string &url, int &quality, string &subtitles) : url(url), quality(quality), subtitles(subtitles) {}

    void download(const string &url, int &quality) // Function download
    {
        bp::child c(bp::search_path("yt-dlp"), bp::args({"-f", "bestvideo[height<=" + to_string(quality) + "]", url})); // Run yt-dlp
        c.wait();                                                                                                       // Wait for yt-dlp to finish
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
