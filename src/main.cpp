#include "include/yt-dlp-settings.hpp"
#define DEBUG

int main()
{
    string url, setting_set, setting_get;
    int choice;
    while (true)
    {
        cout << "\t====Меню====" << endl;
        cout << "1. Скачать видео" << endl;
        cout << "2. Скачать аудио" << endl;
        cout << "3. Настройки" << endl;
        cout << "4. о программе" << endl;
        cout << "5. Выход" << endl;
        cin >> choice;
        cin.ignore();
        if (choice == 1)
        {
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
        }
        if (choice == 5)
        {
            break;
        }
    }
    return 0;
}
