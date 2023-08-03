#include <iostream> // Підключення бібліотек
#include <string> 
#include <filesystem> 

namespace fs = std::filesystem; // Створення псевдоніма "fs" для зручного доступу до простору імен "std::filesystem"

// Функція для пошуку файлу за ім'ям у певному каталозі
std::string SearchFileInDirectory(const std::string& directory, const std::string& filename)
{
    for (const auto& entry : fs::directory_iterator(directory)) // Перебирання всіх файлів та каталогів у заданому "directory"
    {
        if (entry.is_regular_file() && entry.path().filename().string() == filename) // Перевірка, чи поточний об'єкт - звичайний файл і його ім'я збігається з заданим "filename"
        {
            return entry.path().string(); // Повернення повного шляху до знайденого файлу
        }
    }
    return ""; // Повернення порожнього рядка, якщо файл не знайдено
}
