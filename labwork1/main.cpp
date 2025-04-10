#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>

// ��������� ��� �������� ���������� � �����
struct FileStats {
    std::string filename;  // ��� �����
    int lines = 0;         // ���������� �����
    int words = 0;         // ���������� ����
    int bytes = 0;         // ������ � ������
    int chars = 0;         // ���������� ��������
};

// ������� ��� ������ ���������� � ������������ � ������������ �������
void printStats(const FileStats& stats, bool showLines, bool showWords, bool showBytes, bool showChars) {
    bool first = true;  // ���� ��� ���������� ��������� ����� ����������

    // ����� ���������� �����, ���� ���������
    if (showLines) {
        std::cout << stats.lines;
        first = false;
    }

    // ����� ���������� ����, ���� ���������
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

    // ����� ����� ����� � �������� ������
    std::cout << " " << stats.filename << std::endl;
}

// ������� ��� ������ ����������� ����� �� �����
void printFileContent(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "������: ���������� ������� ���� '" << filename << "'" << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << std::endl;
    }
    file.close();
}

// ������� ��� �������� ���������� �����
FileStats countFileStats(const std::string& filename) {
    FileStats stats;
    stats.filename = filename;

    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "������: ���������� ������� ���� '" << filename << "'" << std::endl;
        return stats;
    }

    char c;
    bool inWord = false;  // ����, �����������, ��� �� ������ �����

    // ����������� ������� ����� � ������
    file.seekg(0, std::ios::end);
    stats.bytes = file.tellg();
    file.seekg(0, std::ios::beg);


    while (file.get(c)) {
        stats.chars++;

        // ���� ���������� ������ ����� ������
        if (c == '\n') {
            stats.lines++;
            if (inWord) {
                stats.words++;
                inWord = false;
            }
        }
        // ���� ���������� ���������� ������
        else if (std::isspace(static_cast<unsigned char>(c))) {
            if (inWord) {
                stats.words++;
                inWord = false;
            }
        }
        // ���� ��� ������ �����
        else {
            inWord = true;
        }
    }

    // ���� ���������� �����, ���� ���� �� ������������� ��������
    if (inWord) {
        stats.words++;
    }

    // ���� ��������� ������, ���� ���� �� ������������� �������� ����� ������
    if (stats.chars > 0 && file.peek() == EOF && c != '\n') {
        stats.lines++;
    }

    file.close();
    return stats;
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Russian");

    // ��������� ������, ����� �������� ������ ��� ��������� � ��� ����� ��� �����
    if (argc == 2 && argv[1][0] != '-') {
        printFileContent(argv[1]);
        return 0;
    }

    std::vector<std::string> filenames;  // ������ ���� ������ ��� ���������
    bool showLines = false;
    bool showWords = false; 
    bool showBytes = false;
    bool showChars = false;   

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        // ��������� ������� ����� (--option)
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
        // ��������� ��������������� �������� ����� (-lwm)
        else if (arg.size() > 1 && arg[0] == '-' && arg[1] != '-') {
            for (size_t j = 1; j < arg.size(); ++j) {
                switch (arg[j]) {
                case 'l': showLines = true; break;
                case 'w': showWords = true; break;
                case 'c': showBytes = true; break;
                case 'm': showChars = true; break;
                default:
                    std::cerr << "������: ����������� ����� '" << arg[j] << "'" << std::endl;
                    return 1;
                }
            }
        }
        // ���� �������� �� �������� ������, ������� ��� ������ �����
        else if (arg[0] != '-') {
            filenames.push_back(arg);
        }
        else {
            std::cerr << "������: ����������� ����� '" << arg << "'" << std::endl;
            return 1;
        }
    }

    // ��������, ��� ������� ���� �� ���� ��� �����
    if (filenames.empty()) {
        std::cerr << "������: �� ������� ��� �����" << std::endl;
        return 1;
    }

    // ��������� ������� �����
    for (const auto& filename : filenames) {
        // ���� ������� �����-���� �����, ������� ����������
        if (showLines || showWords || showBytes || showChars) {
            FileStats stats = countFileStats(filename);
            printStats(stats, showLines, showWords, showBytes, showChars);
        }
        // ����� ������� ���������� �����
        else {
            printFileContent(filename);
        }
    }

    return 0;
}