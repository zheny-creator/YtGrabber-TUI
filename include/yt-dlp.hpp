#include <iostream>
#include <string>
#include "json.hpp"
#include <cstdlib>
#include "Log.hpp"
#include <boost/process.hpp>
#include <boost/process/child.hpp>
#include <boost/filesystem.hpp>

using json = nlohmann::json;
using namespace std;
namespace fs = boost::filesystem;
namespace bp = boost::process;

class video
{
private:
    string url;
    int quality;
    string subtitles;

public:
    video(const string &url, int &quality, string &subtitles) : url(url), quality(quality), subtitles(subtitles) {}

    void download(const string &url)
    {
        bp::child c(bp::search_path("yt-dlp"), bp::args({url}));
        c.wait();
    }
};
