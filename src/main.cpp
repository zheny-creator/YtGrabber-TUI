#include "yt-dlp.hpp" // for yt-dlp
#define DEBUG         // for debug

int main()
{
    string url, setting_set, setting_get;
    pt::ptree config;
    int choice;
    int quality;
    string enabled;
    int quality_video;
    fs::path path = bp::search_path("yt-dlp"); // for yt-dlp
    if (!fs::exists(path))                     // examination of the existence of yt-dlp
    {
        cout << "yt-dlp не найден" << endl; // if yt-dlp not found
        return 1;
    }
    settings_to_json json(config);     // for settings
    json.create_json_settings(config); // create json settings
    while (true)                       // menu
    {
        cout << "\t====Меню====" << endl;
        cout << "1. Скачать видео" << endl;
        cout << "2. Скачать аудио" << endl;
        cout << "3. Настройки" << endl;
        cout << "4. о программе" << endl;
        cout << "5. Выход" << endl;
        cout << "Выберите действие: ";
        cin >> choice; // choic
        cin.ignore();

        if (choice == 1) // download video
        {
            cout << "Введите ссылку на видео: ";
            getline(cin, url); // url
            auto q = config.get_child("quality");
            string enabled = q.get<string>("enabled", "false");
            int quality_video = q.get<int>("quality", 1080);
            if (enabled == "true")
            {
                quality = quality_video;
            }
            else if (enabled == "false")
            {
                cout << "Введите качество видео: ";
                cin >> quality; // quality
            }
            video video1(url, quality, setting_set); // for video
            video1.download(url, quality);           // download
        }
        if (choice == 2)
        {
            cout << "Введите ссылку на видео: ";
            getline(cin, url);   // url
            audio audio(url);    // for audio
            audio.download(url); // download
        }
        if (choice == 3)
        {
            while (true)
            {
                cout << "1. Качество видео" << endl;
                cout << "2. Расположение ffmpeg" << endl;
                cout << "3. Расположение yt-dlp" << endl;
                cout << "4. Превью видео" << endl;
                cout << "5. Выход" << endl;
                cout << "Выберите действие: ";
                cin >> choice; // choice
                cin.ignore();
                if (choice == 4)
                {
                    break;
                } // quality
                else if (choice == 1)
                {
                    while (true)
                    {
                        cout << "1. Включить" << endl;
                        cout << "2. Выключить" << endl;
                        cout << "3. Изменить качество видео" << endl;
                        cout << "4. Назад" << endl;
                        cout << "Выберите действие: "; // quality
                        cin >> choice;                 // choice
                        cin.ignore();
                        if (choice == 1)
                        {
                            if (config.get<string>("quality.enabled", "false") == "false")
                            {
                                config.put("quality.enabled", "true");
                                pt::write_json("config.json", config);
                                cout << "Качество видео включено" << endl;
                                continue;
                            } // enabled
                            else
                            {
                                cout << "Качество видео уже включено" << endl;
                                continue;
                            } // if video enabled
                        }
                        if (choice == 2)
                        {
                            if (config.get<string>("quality.enabled", "false") == "true")
                            {
                                config.put("quality.enabled", "false");
                                pt::write_json("config.json", config);
                                cout << "Качество видео выключено" << endl;
                                continue;
                            } // enabled
                            else
                            {
                                cout << "Качество видео уже выключено" << endl;
                                continue;
                            } // if video enabled
                        }
                        if (choice == 3)
                        {
                            if (config.get<string>("quality.enabled", "false") == "true")
                            {
                                cout << "Введите качество видео: ";
                                cin >> quality_video;
                                config.put("quality.quality", quality_video);
                                pt::write_json("config.json", config);
                                continue;
                            } // quality
                            else
                            {
                                if (config.get<string>("quality.enabled", "false") == "false")
                                {
                                    cout << "Качество видео выключено" << endl;
                                    continue;
                                }
                            }

                        } // quality
                    }
                }
                break;
            }
            if (choice == 4) // about
            {
                cout << "YtGrabber-TUI" << endl;
                cout << "Надстроками для yt-dlp" << endl;
                cout << "Автор: Женя Бородин" << endl;
                cout << "Верия: 1.0 Alpha 2" << endl;
            }
            if (choice == 5)
            {
                break;
            }
        }
    }
    return 0;
}