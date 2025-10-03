#include "yt-dlp.hpp"
#define DEBUG

int main()
{
    string url, setting_set, setting_get;
    int choice;
    int quality;
    fs::path path = bp::search_path("yt-dlp");
    if (!fs::exists(path))
    {
        cout << "yt-dlp не найден" << endl;
        return 1;
    }

    while (true)
    {
        cout << "\t====Меню====" << endl;
        cout << "1. Скачать видео" << endl;
        cout << "2. Скачать аудио" << endl;
        cout << "3. Настройки" << endl;
        cout << "4. о программе" << endl;
        cout << "5. Выход" << endl;
        cout << "Выберите действие: ";
        cin >> choice;
        cin.ignore();
        if (choice == 1)
        {
            cout << "Введите ссылку на видео: ";
            getline(cin, url);
            cout << "Введите качество видео: ";
            cin >> quality;
            video video1(url, quality, setting_set);
            video1.download(url);

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
        if (choice == 4)
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
