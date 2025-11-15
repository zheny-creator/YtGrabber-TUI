#include "yt-dlp.hpp" // for yt-dlp
#define DEBUG true    // for debug
#include <regex>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
using namespace ftxui;

int main()
{
    setlocale(LC_ALL, "ru_RU.UTF-8");
    string url, setting_set, setting_get, path_ffmpeg, path_yt_dlp, format_audio, format_video, subtitles_language, dowload_dir; // strings for url, settings, path
    pt::ptree config;                                                                                                            // for json
    int choice = 0;                                                                                                              // for choice
    int quality = 0;                                                                                                             // for quality
    int quality_audio = 0;                                                                                                       // for quality_video
    int choice_menu_settings = 0;                                                                                                // for choice_menu_settings
    int choice_menu_quality = 0;                                                                                                 // for choice_menu_quality
    int choice_menu_ffmpeg = 0;                                                                                                  // for choice_menu_ffmpeg
    int choice_menu_yt_dlp = 0;                                                                                                  // for choice_menu_yt_dlp
    int choice_menu_preview = 0;                                                                                                 // for choice_menu_preview
    int choice_menu_format_audio = 0;                                                                                            // for choice _menu_format_audio
    int menu_experemental = 0;                                                                                                   // for menu_experemental
    int menu_quality_video = 0;
    string enabled;             // for enabled
    int menu_quality_audio = 0; // for menu_quality
    int quality_video = 0;      // for quality_video
    int subtitles_menu = 0;     // for subtitles
    int menu_quality_audio_for_video = 0;
    int quality_audio_for_video = 0;
    int menu_dowload_dir = 0;
    fs::path path_to_ytdlp = bp::environment::find_executable("yt-dlp");  // for yt-dlp
    fs::path path_to_ffmpeg = bp::environment::find_executable("ffmpeg"); // for ffmpeg
    fs::path path_to_javascript_engine = bp::environment::find_executable("nodejs");
    if (!fs::exists(path_to_ytdlp)) // examination of the existence of yt-dlp
    {
        cout << "yt-dlp не найден" << endl; // if yt-dlp not found
        return 1;
    }
    if (!fs::exists(path_to_ffmpeg))
    {
        cout << "ffmpeg не найден" << endl; // if ffmpeg not found
        return 1;
    } // examination of the existence of ffmpeg
    if (!fs::exists(path_to_javascript_engine))
    {
        cout << "nodejs не найден" << endl;
    }
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
    if (config.get<string>("New experemental menu.enabled", "false") == "true")
    {
        vector<string> menu_experemental = {"1. Скачать видео", "2. Скачать аудио", "3. Настройки", "4. О программе", "5. Выход", "6. Экспериментальные функции"};
        auto screen = ScreenInteractive::TerminalOutput();
        auto menu = Menu(&menu_experemental, &choice);
        auto renderer = Renderer(menu, [&]
                                 { return vbox({
                                              text("Меню") | bold | center,
                                              separator(),
                                              menu->Render(),
                                          }) |
                                          border | center; });
        screen.Loop(renderer);
    }
    else
    {
        while (true) // menu
        {
            cout << "\t====Меню====" << endl;
            cout << "1. Скачать видео" << endl;
            cout << "2. Скачать аудио" << endl;
            cout << "3. Настройки" << endl;
            cout << "4. О программе" << endl;
            cout << "5. Выход" << endl;
            cout << "Выберите действие: ";
            cin >> choice; // choice
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
                if (config.get<string>("quality audio.enabled", "false") == "true")
                {
                    quality_audio = config.get<int>("quality audio.quality", 128);
                }
                else
                {
                    cout << "Введите качество аудио: ";
                    cin >> quality_audio;
                    if (cin.fail())
                    {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Ошибка ввода! Введите число.\n";
                        continue;
                    }
                }
                if (url.empty())
                {
                    cout << "Ссылка не введена" << endl;
                    continue;
                }
                audio audio(url, quality_audio, setting_set, config); // for audio
                audio.download(url, quality_audio, config);           // download
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
                    cout << "6. Формат видео" << endl;
                    cout << "7. Формат аудио" << endl;
                    cout << "8. Субтитры" << endl;
                    cout << "9. Качество аудио для видео" << endl;
                    cout << "10. Путь по умолчанию для скачивания видео" << endl;
                    cout << "11. Выход" << endl;
                    cout << "12. Экспериментальные настройки" << endl;
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
                    if (choice_menu_settings == 11)
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
                            cin.ignore();
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
                                    getline(cin, path_yt_dlp);
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
                    if (choice_menu_settings == 7)
                    {
                        while (true)
                        {
                            cout << "1. Включить" << endl;
                            cout << "2. Выключить" << endl;
                            cout << "3. Изменить формат аудио" << endl;
                            cout << "4. Назад" << endl;
                            cout << "Выберите действие: ";
                            cin >> choice_menu_format_audio;
                            cin.ignore();
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
                    if (choice_menu_settings == 5)
                    {
                        while (true)
                        {
                            cout << "1. Включить" << endl;
                            cout << "2. Выключить" << endl;
                            cout << "3. Качество" << endl;
                            cout << "4. Назад" << endl;
                            cout << "Выберите действие: ";
                            cin >> menu_quality_audio;
                            cin.ignore();
                            if (menu_quality_audio == 1)
                            {
                                if (config.get<string>("quality audio.enabled", "false") == "false")
                                {
                                    try
                                    {
                                        config.put("quality audio.enabled", "true");
                                        cout << "Качество аудио включено" << endl;
                                    }
                                    catch (const pt::json_parser::json_parser_error &e)
                                    {
                                        cout << e.what() << "Ошибка записи файла настроек" << endl;
                                    }
                                }
                                else if (config.get<string>("quality audio.enabled", "false") == "true")
                                {
                                    cout << "Качество аудио уже включено" << endl;
                                }
                            }
                            if (menu_quality_audio == 2)
                            {
                                if (config.get<string>("quality audio.enabled", "false") == "true")
                                {
                                    try
                                    {
                                        config.put("quality audio.enabled", "false");
                                        cout << "Качество аудио выключено" << endl;
                                    }
                                    catch (const pt::json_parser::json_parser_error &e)
                                    {
                                        cout << e.what() << "Ошибка записи файла настроек" << endl;
                                    }
                                }
                                else if (config.get<string>("quality audio.enabled", "false") == "false")
                                {
                                    cout << "Качество аудио уже выключено" << endl;
                                }
                            }
                            if (menu_quality_audio == 3)
                            {
                                if (config.get<string>("quality audio.enabled", "false") == "true")
                                {
                                    cout << "Введите качество аудио: ";
                                    cin >> quality_audio;
                                    config.put("quality audio.quality", quality_audio);
                                    try
                                    {
                                        pt::write_json(config_file.string(), config);
                                    }
                                    catch (const pt::json_parser::json_parser_error &e)
                                    {
                                        cout << e.what() << "Ошибка записи файла настроек" << endl;
                                    }
                                }
                            }
                            if (menu_quality_audio == 4)
                            {
                                break;
                            }
                        }
                    }
                    if (choice_menu_settings == 6)
                    {
                        while (true)
                        {
                            cout << "1. Включить" << endl;
                            cout << "2. Выключить" << endl;
                            cout << "3. Формат видео" << endl;
                            cout << "4. Назад" << endl;
                            cout << "Выберите действие: ";
                            cin >> menu_quality_video;
                            cin.ignore();
                            if (menu_quality_video == 1)
                            {
                                if (config.get<string>("format video.enabled", "false") == "false")
                                {
                                    config.put("format video.enabled", "true");
                                    try
                                    {
                                        pt::write_json(config_file.string(), config);
                                        cout << "Качество видео включено" << endl;
                                    }
                                    catch (const pt::json_parser::json_parser_error &e)
                                    {
                                        cout << e.what() << "Ошибка записи файла настроек" << endl;
                                    }
                                }
                                else if (config.get<string>("format video.enabled", "false") == "true")
                                {
                                    cout << "Качество видео уже включено" << endl;
                                }
                            }
                            if (menu_quality_video == 2)
                            {
                                if (config.get<string>("format video.enabled", "false") == "true")
                                {
                                    config.put("format video.enabled", "false");
                                    try
                                    {
                                        pt::write_json(config_file.string(), config);
                                        cout << "Качество видео выключено" << endl;
                                    }
                                    catch (const pt::json_parser::json_parser_error &e)
                                    {
                                        cout << e.what() << "Ошибка записи файла настроек" << endl;
                                    }
                                }
                                else if (config.get<string>("format video.enabled", "false") == "false")
                                {
                                    cout << "Качество видео уже выключено" << endl;
                                }
                            }
                            if (menu_quality_video == 3)
                            {
                                if (config.get<string>("format video.enabled", "false") == "true")
                                {
                                    cout << "Введите формат видео: ";
                                    cin >> format_video;
                                    config.put("format video.format", format_video);
                                    try
                                    {
                                        pt::write_json(config_file.string(), config);
                                    }
                                    catch (const pt::json_parser::json_parser_error &e)
                                    {
                                        cout << e.what() << "Ошибка записи файла настроек" << endl;
                                    }
                                }
                            }
                            if (menu_quality_video == 4)
                            {
                                break;
                            }
                        }
                    }
                    if (choice_menu_settings == 8)
                    {
                        while (true)
                        {
                            cout << "1. Включить" << endl;
                            cout << "2. Выключить" << endl;
                            cout << "3. Язык субтитров" << endl;
                            cout << "4. Включить/Отключить автоматические субтитры" << endl;
                            cout << "5. Назад" << endl;
                            cout << "Выберите действие: ";
                            cin >> subtitles_menu;
                            cin.ignore();
                            if (subtitles_menu == 1)
                            {
                                if (config.get<string>("subtitles.enabled", "false") == "false")
                                {
                                    config.put("subtitles.enabled", "true");
                                    try
                                    {
                                        pt::write_json(config_file.string(), config);
                                        cout << "Субтитры включены" << endl;
                                    }
                                    catch (const pt::json_parser::json_parser_error &e)
                                    {
                                        cout << e.what() << "Ошибка записи файла настроек" << endl;
                                    }
                                }
                                else if (config.get<string>("subtitles.enabled", "false") == "true")
                                {
                                    cout << "Субтитры уже включены" << endl;
                                }
                            }
                            if (subtitles_menu == 2)
                            {
                                if (config.get<string>("subtitles.enabled", "false") == "true")
                                {
                                    config.put("subtitles.enabled", "false");
                                    try
                                    {
                                        pt::write_json(config_file.string(), config);
                                        cout << "Субтитры выключены" << endl;
                                    }
                                    catch (const pt::json_parser::json_parser_error &e)
                                    {

                                        cout << e.what() << "Ошибка записи файла настроек" << endl;
                                    }
                                }
                                else if (config.get<string>("subtitles.enabled", "false") == "false")
                                {
                                    cout << "Субтитры уже выключены" << endl;
                                }
                            }
                            if (subtitles_menu == 3)
                            {
                                if (config.get<string>("subtitles.enabled", "false") == "true")
                                {
                                    cout << "Введите язык субтитров: ";
                                    cin >> subtitles_language;
                                    config.put("subtitles.language", subtitles_language);
                                    try
                                    {
                                        pt::write_json(config_file.string(), config);
                                    }
                                    catch (const pt::json_parser::json_parser_error &e)
                                    {
                                        cout << e.what() << "Ошибка записи файла настроек" << endl;
                                    }
                                }
                            }
                            if (subtitles_menu == 5)
                            {
                                break;
                            }
                            if (subtitles_menu == 4)
                            {
                                if (config.get<string>("subtitles.auto", "false") == "true")
                                {
                                    config.put("subtitles.auto", "false");
                                }
                                else if (config.get<string>("subtitles.auto", "false") == "false")
                                {
                                    config.put("subtitles.auto", "true");
                                }
                                try
                                {
                                    pt::write_json(config_file.string(), config);
                                }
                                catch (const pt::json_parser::json_parser_error &e)
                                {
                                    cout << e.what() << "Ошибка записи файла настроек" << endl;
                                }
                            }
                        }
                    }
                    if (choice_menu_settings == 9)
                    {
                        while (true)
                        {
                            cout << "1. Включить" << endl;
                            cout << "2. Выключить" << endl;
                            cout << "3. Качество" << endl;
                            cout << "4. Назад" << endl;
                            cout << "Выберите действие: ";
                            cin >> menu_quality_audio_for_video;
                            cin.ignore();
                            if (menu_quality_audio_for_video == 1)
                            {
                                if (config.get<string>("quality audio for video") == "false")
                                {
                                    config.put("quality audio for video", "true");
                                    try
                                    {
                                        pt::write_json(config_file.string(), config);
                                        cout << "Качество включено" << endl;
                                    }
                                    catch (const pt::json_parser::json_parser_error &e)
                                    {
                                        cout << e.what() << "Ошибка записи файла настроек" << endl;
                                    }
                                }
                                else if (config.get<string>("quality audio for video", "false") == "true")
                                {
                                    cout << "Качество уже включено" << endl;
                                }
                            }
                            if (menu_quality_audio_for_video == 2)
                            {
                                if (config.get<string>("quality audio for video", "false") == "true")
                                {
                                    config.put("quality audio for video", "false");
                                    try
                                    {
                                        pt::write_json(config_file.string(), config);
                                        cout << "Качество выключено" << endl;
                                    }
                                    catch (const pt::json_parser::json_parser_error &e)
                                    {
                                        cout << e.what() << "Ошибка записи файла настроек" << endl;
                                    }
                                }
                                else if (config.get<string>("quality audio for video", "false") == "false")
                                {
                                    cout << "Качество уже выключено" << endl;
                                }
                            }
                            if (menu_quality_audio_for_video == 3)
                            {
                                if (config.get<string>("quality audio for video", "false") == "true")
                                {
                                    cout << "Введите качество: ";
                                    cin >> quality_audio_for_video;
                                    config.put("quality audio for video", quality_audio_for_video);
                                    try
                                    {
                                        pt::write_json(config_file.string(), config);
                                    }
                                    catch (const pt::json_parser::json_parser_error &e)
                                    {
                                        cout << e.what() << "Ошибка записи файла настроек" << endl;
                                    }
                                }
                            }
                            if (menu_quality_audio_for_video == 4)
                            {
                                break;
                            }
                        }
                    }
                    if (choice_menu_settings == 12)
                    {
                        if (config.get<string>("experemental settings.enabled", "false") == "true")
                        {
                            while (true)
                            {
                                cout << "1. Новое меню" << endl;
                                cout << "2. Назад" << endl;
                                cout << "Выберите действие: ";
                                cin >> menu_experemental;
                                cin.ignore();
                                if (menu_experemental == 1)
                                {
                                    cout << "Новое меню будет доступно с 1.1 Alpha 2" << endl;
                                }
                                if (menu_experemental == 2)
                                {
                                    break;
                                }
                            }
                        }
                        else if (config.get<string>("experemental settings.enabled", "false") == "false")
                        {
                            cout << "Включите экпериментальные настройки в config.json" << endl;
                        }
                    }
                    if (choice_menu_settings == 10)
                    {
                        while (true)
                        {
                            cout << "1. Включить" << endl;
                            cout << "2. Выключить" << endl;
                            cout << "3. Изменить путь" << endl;
                            cout << "4. Назад" << endl;
                            cout << "Выберите действие: ";
                            cin >> menu_dowload_dir;
                            if (menu_dowload_dir == 1)
                            {
                                if (config.get<string>("path to download video.enabled", "false") == "false")
                                {
                                    config.put("path to download video.enabled", "true");
                                    try
                                    {
                                        pt::write_json(config_file.string(), config);
                                        cout << "Путь включен" << endl;
                                    }
                                    catch (const pt::json_parser::json_parser_error &e)
                                    {
                                        cout << e.what() << "Ошибка записи файла настроек" << endl;
                                    }
                                }
                                else if (config.get<string>("path to download video.enabled", "false") == "true")
                                {
                                    if (config.get<string>("path to download video.enabled", "false") == "true")
                                    {
                                        cout << "Путь уже включен" << endl;
                                    }
                                }
                            }
                            if (menu_dowload_dir == 2)
                            {
                                if (config.get<string>("path to download video.enabled", "false") == "true")
                                {
                                    config.put("path to download video.enabled", "false");
                                    try
                                    {
                                        pt::write_json(config_file.string(), config);
                                        cout << "Путь выключен" << endl;
                                    }
                                    catch (const pt::json_parser::json_parser_error &e)
                                    {
                                        cout << e.what() << "Ошибка записи файла настроек" << endl;
                                    }
                                }
                                else if (config.get<string>("path to download video.enabled", "false") == "false")
                                {
                                    if (config.get<string>("path to download video.enabled", "false") == "false")
                                    {
                                        cout << "Путь уже выключен" << endl;
                                    }
                                }
                            }
                            if (menu_dowload_dir == 3)
                            {
                                if (config.get<string>("path to download video.enabled", "false") == "true")
                                {
                                    cout << "Введите путь: ";
                                    cin >> dowload_dir;
                                    config.put("path to download video.path", dowload_dir);
                                    try
                                    {
                                        pt::write_json(config_file.string(), config);
                                    }
                                    catch (const pt::json_parser::json_parser_error &e)
                                    {
                                        cout << e.what() << "Ошибка записи файла настроек" << endl;
                                    }
                                }
                            }
                            if (menu_dowload_dir == 4)
                            {
                                break;
                            }
                        }
                    }
                }
            }
            if (choice == 4) // about
            {
                cout << "YtGrabber-TUI" << endl;
                cout << "TUI надстрока над yt-dlp" << endl;
                cout << "Версия: 1.1 Alpha 2" << endl;
                cout << "Кодовое имя: Axolotl" << endl;
            }
            if (choice == 5)
            {
                break;
            }
        }
    }
}
