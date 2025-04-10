#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>

// Структура для хранения статистики о файле
struct FileStats {
    std::string filename;  // Имя файла
    int lines = 0;         // Количество строк
    int words = 0;         // Количество слов
    int bytes = 0;         // Размер в байтах
    int chars = 0;         // Количество символов
};

// Функция для вывода статистики в соответствии с запрошенными опциями
void printStats(const FileStats& stats, bool showLines, bool showWords, bool showBytes, bool showChars) {
    bool first = true;  // Флаг для управления пробелами между значениями

    // Вывод количества строк, если запрошено
    if (showLines) {
        std::cout << stats.lines;
        first = false;
    }

    // Вывод количества слов, если запрошено
    if (showWords) {
        if (!first) std::cout << " ";
        std::cout << stats.words;
        first = false;
    }

    if (showBytes) {
        if (!first) std::cout << " ";
        std::cout << stats.bytes;
        first = false;
    }

    if (showChars) {
        if (!first) std::cout << " ";
        std::cout << stats.chars;
        first = false;
    }

    // Вывод имени файла и перевода строки
    std::cout << " " << stats.filename << std::endl;
}

// Функция для вывода содержимого файла на экран
void printFileContent(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка: невозможно открыть файл '" << filename << "'" << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << std::endl;
    }
    file.close();
}

// Функция для подсчета статистики файла
FileStats countFileStats(const std::string& filename) {
    FileStats stats;
    stats.filename = filename;

    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Ошибка: невозможно открыть файл '" << filename << "'" << std::endl;
        return stats;
    }

    char c;
    bool inWord = false;  // Флаг, указывающий, что мы внутри слова

    // Определение размера файла в байтах
    file.seekg(0, std::ios::end);
    stats.bytes = file.tellg();
    file.seekg(0, std::ios::beg);


    while (file.get(c)) {
        stats.chars++;

        // Если встретился символ новой строки
        if (c == '\n') {
            stats.lines++;
            if (inWord) {
                stats.words++;
                inWord = false;
            }
        }
        // Если встретился пробельный символ
        else if (std::isspace(static_cast<unsigned char>(c))) {
            if (inWord) {
                stats.words++;
                inWord = false;
            }
        }
        // Если это символ слова
        else {
            inWord = true;
        }
    }

    // Учет последнего слова, если файл не заканчивается пробелом
    if (inWord) {
        stats.words++;
    }

    // Учет последней строки, если файл не заканчивается символом новой строки
    if (stats.chars > 0 && file.peek() == EOF && c != '\n') {
        stats.lines++;
    }

    file.close();
    return stats;
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Russian");

    // Обработка случая, когда передано только имя программы и имя файла без опций
    if (argc == 2 && argv[1][0] != '-') {
        printFileContent(argv[1]);
        return 0;
    }

    std::vector<std::string> filenames;  // Список имен файлов для обработки
    bool showLines = false;
    bool showWords = false; 
    bool showBytes = false;
    bool showChars = false;   

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        // Обработка длинных опций (--option)
        if (arg == "--lines" || arg == "-l") {
            showLines = true;
        }
        else if (arg == "--words" || arg == "-w") {
            showWords = true;
        }
        else if (arg == "--bytes" || arg == "-c") {
            showBytes = true;
        }
        else if (arg == "--chars" || arg == "-m") {
            showChars = true;
        }
        // Обработка комбинированных коротких опций (-lwm)
        else if (arg.size() > 1 && arg[0] == '-' && arg[1] != '-') {
            for (size_t j = 1; j < arg.size(); ++j) {
                switch (arg[j]) {
                case 'l': showLines = true; break;
                case 'w': showWords = true; break;
                case 'c': showBytes = true; break;
                case 'm': showChars = true; break;
                default:
                    std::cerr << "Ошибка: неизвестная опция '" << arg[j] << "'" << std::endl;
                    return 1;
                }
            }
        }
        // Если аргумент не является опцией, считаем его именем файла
        else if (arg[0] != '-') {
            filenames.push_back(arg);
        }
        else {
            std::cerr << "Ошибка: неизвестная опция '" << arg << "'" << std::endl;
            return 1;
        }
    }

    // Проверка, что указано хотя бы одно имя файла
    if (filenames.empty()) {
        std::cerr << "Ошибка: не указано имя файла" << std::endl;
        return 1;
    }

    // Обработка каждого файла
    for (const auto& filename : filenames) {
        // Если указаны какие-либо опции, выводим статистику
        if (showLines || showWords || showBytes || showChars) {
            FileStats stats = countFileStats(filename);
            printStats(stats, showLines, showWords, showBytes, showChars);
        }
        // Иначе выводим содержимое файла
        else {
            printFileContent(filename);
        }
    }

    return 0;
}