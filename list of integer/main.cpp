
#include <iostream>
#include <fstream>
#include <string>
#include <limits>

#include "DSA.h"

int main()
{
    // STRINGS (names)
    RawDynamicArray<std::string> names;

    std::ifstream nameFile("names.txt");

    // Check whether the file opened successfully
    if (!nameFile.is_open())
    {
        std::cout << "Error: Cannot open names.txt\n";
        return 1;
    }

    std::string line;

    while (std::getline(nameFile, line))
    {
        if (!line.empty())
        {
            names.pushBack(line);
        }
    }

    if (nameFile.bad())
    {
        std::cout << "Error: Failed to read names.txt\n";
        return 1;
    }

    nameFile.close();

    std::cout << "=== Names (before sorting) ===\n";
    names.print("\n");

    names.sort();

    std::cout << "\n=== Names (after sorting) ===\n";
    names.print("\n");

    std::string nameToFind;

    std::cout << "\nEnter a name to search for: ";
    std::getline(std::cin, nameToFind);

    int nameIndex = names.sequentialSearch(nameToFind);

    if (nameIndex != -1)
    {
        std::cout << "Found \"" << nameToFind << "\" at index " << nameIndex << ".\n";
    }

    else
    {
        std::cout << "\"" << nameToFind << "\" was NOT found.\n";
    }

    // INTEGERS (numbers)
    RawDynamicArray<int> numbers;

    std::ifstream numberFile("numbers.txt");

    if (!numberFile.is_open())
    {
        std::cout << "Error: Cannot open numbers.txt\n";
        return 1;
    }

    int number;

    while (numberFile >> number)
    {
        numbers.pushBack(number);
    }

    if (!numberFile.eof())
    {
        std::cout << "Error: Invalid data in numbers.txt\n";
        return 1;
    }

    numberFile.close();

    std::cout << "\n=== Numbers (before sorting) ===\n";
    numbers.print(" ");

    numbers.sort();

    std::cout << "\n=== Numbers (after sorting) ===\n";
    numbers.print(" ");

    int numberToFind;

    std::cout << "\nEnter an integer to search for: ";

    while (!(std::cin >> numberToFind))
    {
        if (std::cin.eof())
        {
            std::cout << "\nInput ended.\n";
            return 1;
        }

        std::cin.clear();

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "Invalid input. Enter an integer: ";
    }

    int numberIndex = numbers.sequentialSearch(numberToFind);

    if (numberIndex != -1)
    {
        std::cout << "Found " << numberToFind << " at index " << numberIndex << ".\n";
    }

    else
    {
        std::cout << numberToFind << " was NOT found.\n";
    }

    return 0;
}
