#include <iostream> 
#include <vector> 
#include <thread> 
#include "FileSearchLib.h" // Підключення статичної бібліотеки "FileSearchLib.h" з функцією пошуку файлу

// Функція для пошуку файлу за ім'ям у кореневому каталозі з багатопотоковим підходом
void SearchFileInRoot(const std::string& rootDir, const std::string& filename, bool& found)
{
    if (found) // Якщо файл знайдено в іншому потоці, вийти з функції
        return;

    std::string filePath = SearchFileInDirectory(rootDir, filename); // Виклик функції пошуку з статичної бібліотеки
    if (!filePath.empty()) // Якщо файл знайдено
    {
        found = true; // Позначити, що файл знайдено, щоб інші потоки зупинилися
        std::cout << "File found: " << filePath << std::endl; // Вивести повний шлях до знайденого файлу
    }
}

int main()
{
    const std::string rootDirectory = "/"; // Кореневий каталог для пошуку файлу (або "C:\" для Win)
    const std::string filenameToSearch = "Sometext.txt"; // Ім'я файлу, яке потрібно знайти
    const int maxThreads = 8; // Максимальна кількість потоків для одночасного виконання пошуку

    bool fileFound = false; // Змінна, що вказує, чи файл був знайдений
    std::vector<std::thread> searchThreads; // Вектор для зберігання об'єктів потоків

    // Запускаємо декілька потоків для пошуку файлу у кореневому каталозі
    for (int i = 0; i < maxThreads; ++i)
    {
        // Створюємо новий потік, передаючи йому аргументи для пошуку
        searchThreads.emplace_back(SearchFileInRoot, rootDirectory, filenameToSearch, std::ref(fileFound));
    }

    // Очікуємо завершення всіх потоків
    for (auto& thread : searchThreads)
    {
        thread.join();
    }

    // Після завершення потоків перевіряємо, чи файл був знайдений
    if (!fileFound)
    {
        std::cout << "File not found in the root directory." << std::endl;
    }

    return 0; // Повертаємо 0, щоб позначити успішне виконання програми
}
