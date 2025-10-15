#include "yt-dlp.hpp" // for yt-dlp
#define DEBUG false   // for debug

int main()
{
    setlocale(LC_ALL, "ru_RU.UTF-8");
    string url, setting_set, setting_get, path_ffmpeg, path_yt_dlp, format_audio; // strings for url, settings, path
    pt::ptree config;                                                             // for json
    int choice;                                                                   // for choice
    int quality;                                                                  // for quality
    int choice_menu_settings;                                                     // for choice_menu_settings
    int choice_menu_quality;                                                      // for choice_menu_quality
    int choice_menu_ffmpeg;                                                       // for choice_menu_ffmpeg
    int choice_menu_yt_dlp;                                                       // for choice_menu_yt_dlp
    int choice_menu_preview;                                                      // for choice_menu_preview
    int choice_menu_format_audio;                                                 // for choice _menu_format_audio
    string enabled;                                                               // for enabled
    int quality_video;                                                            // for quality_video
    fs::path path_to_ytdlp = bp::search_path("yt-dlp");                           // for yt-dlp
    fs::path path_to_ffmpeg = bp::search_path("ffmpeg");                          // for ffmpeg
    if (!fs::exists(path_to_ytdlp))                                               // examination of the existence of yt-dlp
    {
        cout << "yt-dlp не найден" << endl; // if yt-dlp not found
        return 1;
    }
    if (!fs::exists(path_to_ffmpeg))
    {
        cout << "ffmpeg не найден" << endl; // if ffmpeg not found
        return 1;
    } // examination of the existence of ffmpeg
    fs::path config_dir;                    // for config_dir
    fs::path config_file;                   // for config_file
#if defined(__linux__)                      // if linux
    const char *home = std::getenv("HOME"); // for home
    if (!home)                              // if home not found
    {
        std::cerr << "Профиль пользователя не был найден!" << std::endl; // if home not found
        return 1;                                                        // exit
    }
    config_dir = fs::path(home) / ".config" / "yt-grabber-tui"; // config_dir
    config_file = config_dir / "config.json";                   // config_file

#elif defined(_WIN32) // if windows
    config_file = "config.json"; // config_file
#endif
    settings_to_json json(config);
    json.load_json_settings(config);
    while (true) // menu
    {
        cout << "\t====Меню====" << endl;
        cout << "1. Скачать видео" << endl;
        cout << "2. Скачать аудио" << endl;
        cout << "3. Настройки" << endl;
        cout << "4. О программе" << endl;
        cout << "5. Выход" << endl;
        cout << "Выберите действие: ";
        cin >> choice; // choic
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка ввода! Введите число.\n";
            continue;
        }
        cin.ignore();

        if (choice == 1) // download video
        {
            cout << "Введите ссылку на видео: ";
            getline(cin, url); // url
            if (url.empty())
            {
                cout << "Ссылка не введена" << endl;
                continue;
            }
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
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Ошибка ввода! Введите число.\n";
                    continue;
                }
            }
            video video1(url, quality, setting_set, config); // for video
            video1.download(url, quality, config);           // download
        }
        if (choice == 2)
        {
            cout << "Введите ссылку на видео: ";
            getline(cin, url); // url
            if (url.empty())
            {
                cout << "Ссылка не введена" << endl;
                continue;
            }
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
                cout << "5. Качество аудио" << endl;
                cout << "6. формат видео" << endl;
                cout << "7. формат аудио" << endl;
                cout << "8. Выход" << endl;
                cout << "Выберите действие: ";
                cin >> choice_menu_settings; // choice
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Ошибка ввода! Введите число.\n";
                    continue;
                }
                cin.ignore();
                if (choice_menu_settings == 8)
                {
                    break;
                } // quality
                else if (choice_menu_settings == 1)
                {
                    while (true)
                    {
                        cout << "1. Включить" << endl;
                        cout << "2. Выключить" << endl;
                        cout << "3. Изменить качество видео" << endl;
                        cout << "4. Назад" << endl;
                        cout << "Выберите действие: "; // quality
                        cin >> choice_menu_quality;    // choice
                        if (cin.fail())
                        {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Ошибка ввода! Введите число.\n";
                            continue;
                        }
                        cin.ignore();
                        if (choice_menu_quality == 1)
                        {
                            if (config.get<string>("quality.enabled", "false") == "false")
                            {
                                config.put("quality.enabled", "true");
                                try
                                {
                                    pt::write_json(config_file.string(), config);
                                }
                                catch (const pt::json_parser::json_parser_error &e)
                                {
                                    cout << e.what() << "Ошибка записи файла настроек" << endl;
                                }
                                cout << "Качество видео включено" << endl;
                                continue;
                            } // enabled
                            else
                            {
                                cout << "Качество видео уже включено" << endl;
                                continue;
                            } // if video enabled
                        }
                        if (choice_menu_quality == 2)
                        {
                            if (config.get<string>("quality.enabled", "false") == "true")
                            {
                                config.put("quality.enabled", "false");
                                try
                                {
                                    pt::write_json(config_file.string(), config);
                                }
                                catch (const pt::json_parser::json_parser_error &e)
                                {
                                    cout << e.what() << "Ошибка записи файла настроек" << endl;
                                }
                                cout << "Качество видео выключено" << endl;
                                continue;
                            } // enabled
                            else
                            {
                                cout << "Качество видео уже выключено" << endl;
                                continue;
                            } // if video enabled
                        }
                        if (choice_menu_quality == 3)
                        {
                            if (config.get<string>("quality.enabled", "false") == "true")
                            {
                                cout << "Введите качество видео: ";
                                cin >> quality_video;
                                config.put("quality.quality", quality_video);
                                try
                                {
                                    pt::write_json(config_file.string(), config);
                                }
                                catch (const pt::json_parser::json_parser_error &e)
                                {
                                    cout << e.what() << "Ошибка записи файла настроек" << endl;
                                }
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
                        if (choice_menu_quality == 4)
                        {
                            break;
                        }
                    }
                }
                else if (choice_menu_settings == 2)
                {
                    while (true)
                    {
                        cout << "1. Включить" << endl;
                        cout << "2. Выключить" << endl;
                        cout << "3. Изменить путь" << endl;
                        cout << "4. Назад" << endl;
                        cout << "Выберите действие: "; // ffmpeg
                        cin >> choice_menu_ffmpeg;     // choice
                        cin.ignore();
                        if (cin.fail())
                        {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Ошибка ввода! Введите число.\n";
                            continue;
                        }
                        if (choice_menu_ffmpeg == 1)
                        {
                            if (config.get<string>("Custom Path to ffmpeg.enabled", "false") == "false")
                            {
                                config.put("Custom Path to ffmpeg.enabled", "true");
                                try
                                {
                                    pt::write_json(config_file.string(), config);
                                }
                                catch (const pt::json_parser::json_parser_error &e)
                                {
                                    cout << e.what() << "Ошибка записи файла настроек" << endl;
                                }
                                cout << "Путь к ffmpeg включен" << endl;
                                continue;
                            } // enabled
                            else if (config.get<string>("Custom Path to ffmpeg.enabled", "false") == "true")
                            {
                                cout << "Путь к ffmpeg уже включен" << endl;
                            }
                        }
                        else if (choice_menu_ffmpeg == 2)
                        {
                            if (config.get<string>("Custom Path to ffmpeg.enabled", "false") == "true")
                            {
                                config.put("Custom Path to ffmpeg.enabled", "false");
                                try
                                {
                                    pt::write_json(config_file.string(), config);
                                }
                                catch (const pt::json_parser::json_parser_error &e)
                                {
                                    cout << e.what() << "Ошибка записи файла настроек" << endl;
                                }
                                cout << "Путь к ffmpeg выключен" << endl;
                                continue;
                            } // enabled
                            else if (config.get<string>("Custom Path to ffmpeg.enabled", "false") == "false")
                            {
                                cout << "Путь к ffmpeg уже выключен" << endl;
                            }
                        }
                        else if (choice_menu_ffmpeg == 3)
                        {
                            if (config.get<string>("Custom Path to ffmpeg.enabled", "false") == "true")
                            {
                                cout << "Введите путь к ffmpeg: ";
                                cin >> path_ffmpeg;
                                config.put("Custom Path to ffmpeg.path", path_ffmpeg);
                                try
                                {
                                    pt::write_json(config_file.string(), config);
                                }
                                catch (const pt::json_parser::json_parser_error &e)
                                {
                                    cout << e.what() << "Ошибка записи файла настроек" << endl;
                                }
                                continue;
                            } // path

                            else
                            {
                                if (config.get<string>("Custom Path to ffmpeg.enabled", "false") == "false")
                                {
                                    cout << "Путь к ffmpeg выключен" << endl;
                                    continue;
                                }
                            }
                        }
                        else if (choice_menu_ffmpeg == 4)
                        {
                            break;
                        }
                    }
                }
                if (choice_menu_settings == 4)
                {
                    while (true)
                    {
                        cout << "1. Включить" << endl;
                        cout << "2. Выключить" << endl;
                        cout << "3. Назад" << endl;
                        cout << "Выберите действие: "; // preview
                        cin >> choice_menu_preview;    // choice
                        if (cin.fail())
                        {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Ошибка ввода! Введите число.\n";
                            continue;
                        }
                        cin.ignore();
                        if (choice_menu_preview == 1)
                        {
                            if (config.get<string>("thumbnail.enabled", "false") == "false")
                            {
                                config.put("thumbnail.enabled", "true");
                                try
                                {
                                    pt::write_json(config_file.string(), config);
                                }
                                catch (const pt::json_parser::json_parser_error &e)
                                {
                                    cout << e.what() << "Ошибка записи файла настроек" << endl;
                                }
                                cout << "Предпросмотр включен" << endl;
                            }
                            else
                            {
                                cout << "Предпросмотр уже включен" << endl;
                            }
                        }
                        if (choice_menu_preview == 2)
                        {
                            if (config.get<string>("thumbnail.enabled", "false") == "true")
                            {
                                config.put("thumbnail.enabled", "false");
                                try
                                {
                                    pt::write_json(config_file.string(), config);
                                }
                                catch (const pt::json_parser::json_parser_error &e)
                                {
                                    cout << e.what() << "Ошибка записи файла настроек" << endl;
                                }
                                cout << "Предпросмотр выключен" << endl;
                            }
                            else
                            {
                                cout << "Предпросмотр уже выключен" << endl;
                            }
                        }
                        if (choice_menu_preview == 3)
                        {
                            break;
                            ;
                        }
                    }
                }
                if (choice_menu_settings == 3)
                {
                    while (true)
                    {
                        cout << "1. Включить" << endl;
                        cout << "2. Выключить" << endl;
                        cout << "3. Изменить путь" << endl;
                        cout << "4. Назад" << endl;
                        cout << "Выберите действие: ";
                        cin >> choice_menu_yt_dlp;
                        if (cin.fail())
                        {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Ошибка ввода! Введите число.\n";
                            continue;
                        }
                        if (choice_menu_yt_dlp == 1)
                        {
                            if (config.get<string>("Custom Path to yt-dlp.enabled", "false") == "false")
                            {
                                config.put("Custom Path to yt-dlp.enabled", "true");
                                try
                                {
                                    pt::write_json(config_file.string(), config);
                                }
                                catch (const pt::json_parser::json_parser_error &e)
                                {
                                    cout << e.what() << "Ошибка записи файла настроек" << endl;
                                }
                                cout << "Путь к yt-dlp включен" << endl;
                                continue;
                            }
                            else if (config.get<string>("Custom Path to yt-dlp.enabled", "false") == "true")
                            {
                                cout << "Путь к yt-dlp уже включен" << endl;
                            }
                        }
                        if (choice_menu_yt_dlp == 2)
                        {
                            if (config.get<string>("Custom Path to yt-dlp.enabled", "false") == "true")
                            {
                                config.put("Custom Path to yt-dlp.enabled", "false");
                                try
                                {
                                    pt::write_json(config_file.string(), config);
                                }
                                catch (const pt::json_parser::json_parser_error &e)
                                {
                                    cout << e.what() << "Ошибка записи файла настроек" << endl;
                                }
                                cout << "Путь к yt-dlp выключен" << endl;
                                continue;
                            }
                            else if (config.get<string>("Custom Path to yt-dlp.enabled", "false") == "false")
                            {
                                if (config.get<string>("Custom Path to yt-dlp.enabled", "false") == "false")
                                {
                                    cout << "Путь к yt-dlp уже выключен" << endl;
                                }
                            }
                        }
                        if (choice_menu_yt_dlp == 3)
                        {
                            if (config.get<string>("Custom Path to yt-dlp.enabled", "false") == "true")
                            {
                                cout << "Введите путь к yt-dlp: ";
                                cin >> path_yt_dlp;
                                config.put("Custom Path to yt-dlp.path", path_yt_dlp);
                                try
                                {
                                    pt::write_json(config_file.string(), config);
                                }
                                catch (const pt::json_parser::json_parser_error &e)
                                {
                                    cout << e.what() << "Ошибка записи файла настроек" << endl;
                                }
                                continue;
                            }
                            else if (config.get<string>("Custom Path to yt-dlp.enabled", "false") == "false")
                            {
                                cout << "Путь к yt-dlp выключен" << endl;
                            }
                        }
                        if (choice_menu_yt_dlp == 4)
                        {
                            break;
                        }
                    }
                }
                else if (choice_menu_settings == 5)
                {
                    while (true)
                    {
                        cout << "1. Включить" << endl;
                        cout << "2. Выключить" << endl;
                        cout << "3. Изменить путь" << endl;
                        cout << "4. Назад" << endl;
                        if (choice_menu_format_audio == 1)
                        {
                            if (config.get<string>("format audio.enabled", "false") == "false")
                            {
                                try
                                {
                                    config.put("format audio.enabled", "true");
                                    cout << "Формат аудио включен" << endl;
                                }
                                catch (const pt::json_parser::json_parser_error &e)
                                {
                                    cout << e.what() << "Ошибка записи файла настроек" << endl;
                                }
                            }
                            if (config.get<string>("format audio.enabled", "false") == "true")
                            {
                                cout << "Формат аудио уже включен" << endl;
                            }
                        } // TODO: add audio format
                        if (choice_menu_format_audio == 2)
                        {
                            if (config.get<string>("format audio.enabled", "false") == "true")
                            {
                                try
                                {
                                    config.put("format audio.enabled", "false");
                                    cout << "Формат аудио выключен" << endl;
                                }
                                catch (const pt::json_parser::json_parser_error &e)
                                {
                                    cout << e.what() << "Ошибка записи файла настроек" << endl;
                                }
                            }
                            if (config.get<string>("format audio.enabled", "false") == "false")
                            {
                                cout << "Формат аудио уже выключен" << endl;
                            }
                        }
                        if (choice_menu_format_audio == 3)
                        {
                            if (config.get<string>("format audio.enabled", "false") == "true")
                            {
                                cout << "Введите формат аудио: ";
                                cin >> format_audio;
                                config.put("format audio.format", format_audio);
                                try
                                {
                                    pt::write_json(config_file.string(), config);
                                    cout << "Формат аудио изменен" << endl;
                                }
                                catch (const pt::json_parser::json_parser_error &e)
                                {
                                    cout << e.what() << "Ошибка записи файла настроек" << endl;
                                }
                            }
                        }
                        if (choice_menu_format_audio == 4)
                        {
                            break;
                        }
                    }
                }
            }
            if (choice == 4) // about
            {
                cout << "YtGrabber-TUI" << endl;
                cout << "TUI надстрока над yt-dlp" << endl;
                cout << "Автор: Женя Бородин" << endl;
                cout << "Версия: 1.1 Alpha 1" << endl;
            }
            if (choice == 5)
            {
                break;
            }
        }
    }