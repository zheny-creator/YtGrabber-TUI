#include "yt-dlp.hpp" // for yt-dlp
#define DEBUG         // for debug

int main()
{
    string url, setting_set, setting_get;
    int choice;
    int quality;
    fs::path path = bp::search_path("yt-dlp"); // for yt-dlp
    if (!fs::exists(path))                     // examination of the existence of yt-dlp
    {
        cout << "yt-dlp не найден" << endl; // if yt-dlp not found
        return 1;
    }

    while (true) // menu
    {
        cout << "\t====Меню====" << endl;
        cout << "1. Скачать видео" << endl;
        cout << "2. Скачать аудио" << endl;
        cout << "3. Настройки" << endl;
        cout << "4. о программе" << endl;
        cout << "5. Выход" << endl;
        cout << "Выберите действие: ";
        cin >> choice;   // choice
        cin.ignore();    // for cin
        if (choice == 1) // download video
        {
            cout << "Введите ссылку на видео: ";
            getline(cin, url); // url
            cout << "Введите качество видео: ";
            cin >> quality;                          // quality
            video video1(url, quality, setting_set); // for video
            video1.download(url);                    // download

            cout << "В разработке" << endl;
        }
        if (choice == 2)
        {
            cout << "В разработке" << endl;
        }
        if (choice == 3)
        {
            cout << "В разработке" << endl;
        }
        if (choice == 4) // about
        {
            cout << "YtGrabber-TUI" << endl;
            cout << "Надстроками для yt-dlp" << endl;
            cout << "Автор: Женя Бородин" << endl;
            cout << "Верия: 1.0 Alpha 1" << endl;
        }
        if (choice == 5)
        {
            break;
        }
    }
    return 0;
}
