#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <regex>
using namespace std;
//Реализовать простейший файловый менеджер с использованием ООП(классы,
//    наследование и так далее).
//    Файловый менеджер должен иметь такие возможности :
//■ показывать содержимое дисков;
//■ создавать папки / файлы;
//■ удалять папки / файлы;
//■ переименовывать папки / файлы;
//■ копировать / переносить папки / файлы;
//■ вычислять размер папки / файла;
//■ производить поиск по маске(с поиском по подпапкам) и так далее.
namespace fs = filesystem;

class FileManager
{
private:
    string path;

public:
    FileManager(const string& p) : path(p) {}

    void showContents()
    {
        for (auto& p : fs::directory_iterator(path))
        {
            cout << p.path().filename() << "\n";
        }
    }

    void createDirectory(const string& directoryName)
    {
        fs::create_directory(path + directoryName);
    }

    void createFile(const string& fileName)
    {
        ofstream file(path + fileName);
        file.close();
    }

    void deleteDirectory(const string& directoryName)
    {
        fs::remove_all(path + directoryName);
    }

    void deleteFile(const std::string& fileName)
    {
        fs::remove(path + fileName);
    }

    void rename(const string& oldName, const string& newName)
    {
        fs::rename(path + oldName, path + newName);
    }

    void copy(const string& source, const string& destination)
    {
        fs::path src = path + source;
        fs::path dst = path + destination;


        if (fs::is_directory(src) && !fs::is_directory(dst))
        {
            cout << "Ошибка: попытка копирования папки в файл\n";
            return;
        }

        fs::copy(src, dst, fs::copy_options::recursive);
    }


    void search(const string& mask)
    {
        try {
            if (!fs::exists(path) || !fs::is_directory(path)) {
                cout << "Ошибка: путь не существует или не является папкой.\n";
                return;
            }

            if (mask.empty()) {
                cout << "Ошибка: пустая строка маски.\n";
                return;
            }

            for (auto& p : fs::recursive_directory_iterator(path)) {
                if (fs::exists(p) && fs::is_regular_file(p)) {
                    string filename = p.path().filename().string();
                    if (filename.find(mask) != string::npos && filename == mask) {
                        cout << filename << "\n";
                        return;
                    }
                }
            }

            cout << "Файл с именем " << mask << " не найден.\n";
        }
        catch (const fs::filesystem_error& ex) {
            cout << "Ошибка: " << ex.what() << endl;
        }
    }


    void searchFolder(const string& directoryName) {
        if (!fs::exists(path) || !fs::is_directory(path)) {
            cout << "Ошибка: путь не существует или не является папкой.\n";
            return;
        }

        if (directoryName.empty()) {
            cout << "Ошибка: пустое имя папки.\n";
            return;
        }

        for (auto& p : fs::recursive_directory_iterator(path)) {
            if (fs::exists(p) && fs::is_directory(p)) {
                string folder = p.path().filename().string();
                if (folder == directoryName) {
                    cout << folder << "\n";
                    return;
                }
            }
        }

        cout << "Папка с именем " << directoryName << " не найдена.\n";
    }






    void size_file(const std::string& fileName)
    {
        cout << fs::file_size(path + fileName) << "\n";
    }
    void sizefo_lder(const std::string& fileName)
    {
        if (fs::is_directory(path + fileName))
        {
            uintmax_t total_size = 0;
            for (auto& p : fs::recursive_directory_iterator(path + fileName))
            {
                if (fs::is_regular_file(p))
                {
                    total_size += fs::file_size(p);
                }
            }
            cout << "Размер папки " << fileName << " составляет " << total_size << " байт.\n";
        }
        else
        {
            cout << "Это не папка, пожалуйста, укажите имя папки.\n";
        }
    }



};



int main()
{
    setlocale(LC_ALL, "ru");
    FileManager fm("F:\\");

    int choice;
    string fileName, directoryName, oldName, newName, source, destination, mask, total_size, directoryName1;

    cout << "1. Показать содержимое\n2. Создать папку\n3. Создать файл\n4. Удалить папку\n5. Удалить файл\n6. Переименовать\n7. Копировать\n8. Поиск файла\n9. Узнать размер файла\n10 Узнать размер папки\n11. Поиск папки\n12. Выход\n";

    do {
        cout << "Введите ваш выбор: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            fm.showContents();
            break;
        case 2:
            cout << "Введите имя папки: ";
            cin >> directoryName;
            fm.createDirectory(directoryName);
            break;
        case 3:
            cout << "Введите имя файла: ";
            cin >> fileName;
            fm.createFile(fileName);
            cout << endl;
            cout << "файл удален";
            break;
        case 4:
            cout << "Введите имя папки: ";
            cin >> directoryName;
            fm.deleteDirectory(directoryName);
            cout << endl;
            cout << "папка удалена";
            break;
        case 5:
            cout << "Введите имя файла: ";
            cin >> fileName;
            fm.deleteFile(fileName);
            break;
        case 6:
            cout << "Введите старое имя: ";
            cin >> oldName;
            cout << "Введите новое имя: ";
            cin >> newName;
            fm.rename(oldName, newName);
            break;
        case 7:
            cout << "Введите имя исходного файла/папки: ";
            cin >> source;
            cout << "Введите имя целевого файла/папки: ";
            cin >> destination;
            fm.copy(source, destination);
            break;

        case 8:
            cout << "Введите имя файла для поиска: ";
            cin >> mask;
            fm.search(mask);

            break;
        case 9:
            cout << "Введите имя файла: ";
            cin >> fileName;
            fm.size_file(fileName);
            break;
        case 10:
            cout << "Введите имя папки: ";
            cin >> total_size;
            fm.sizefo_lder(total_size);
            break;
        case 11:
            cout << "Введите имя папки для поиска:";
            cin >> directoryName1;
            fm.searchFolder(directoryName1);
            break;
        case 12:
            cout << "Выход...";
            break;
        default:
            cout << "Неверный выбор. Пожалуйста, попробуйте снова.";
            break;
        }

    } while (choice != 10);

    return 0;

}
