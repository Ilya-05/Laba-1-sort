#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <algorithm>

// Structure for storing the number of comparisons and permutations
struct SortResults {
    int comparisons;
    int swaps;
};

bool readArraysFromFile(const std::string& filename, int orderedArray[], int reversedArray[], int randomArray[], int size) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Mistake: the file could not be opened!" << std::endl;
        return false;
    }

    std::string line;

    // Read the sorted array
    if (std::getline(file, line)) {
        std::istringstream stream(line);
        int value;
        int count = 0;

        while (stream >> value) {
            if (stream.fail() || value < 0) {
                std::cerr << "Error: Invalid data in the file. All values must be positive integers." << std::endl;
                return false;
            }
            orderedArray[count++] = value;
            if (count > size) {
                std::cerr << "Error: Too many elements in the ordered array. Please provide exactly " << size << " positive integers." << std::endl;
                return false;
            }
        }

        if (count < size) {
            std::cerr << "Error: Not enough values in the ordered array. Please provide exactly " << size << " positive integers." << std::endl;
            return false;
        }
    }
    else {
        std::cerr << "Error: Could not read the ordered array from the file." << std::endl;
        return false;
    }

    // Read reverse array
    if (std::getline(file, line)) {
        std::istringstream stream(line);
        int value;
        int count = 0;

        while (stream >> value) {
            if (stream.fail() || value < 0) {
                std::cerr << "Error: Invalid data in the file. All values must be positive integers." << std::endl;
                return false;
            }
            reversedArray[count++] = value;
            if (count > size) {
                std::cerr << "Error: Too many elements in the reversed array. Please provide exactly " << size << " positive integers." << std::endl;
                return false;
            }
        }

        if (count < size) {
            std::cerr << "Error: Not enough values in the reversed array. Please provide exactly " << size << " positive integers." << std::endl;
            return false;
        }
    }
    else {
        std::cerr << "Error: Could not read the reversed array from the file." << std::endl;
        return false;
    }

    // Read a random array
    if (std::getline(file, line)) {
        std::istringstream stream(line);
        int value;
        int count = 0;

        while (stream >> value) {
            if (stream.fail() || value < 0) {
                std::cerr << "Error: Invalid data in the file. All values must be positive integers." << std::endl;
                return false;
            }
            randomArray[count++] = value;
            if (count > size) {
                std::cerr << "Error: Too many elements in the random array. Please provide exactly " << size << " positive integers." << std::endl;
                return false;
            }
        }

        if (count < size) {
            std::cerr << "Error: Not enough values in the random array. Please provide exactly " << size << " positive integers." << std::endl;
            return false;
        }
    }
    else {
        std::cerr << "Error: Could not read the random array from the file." << std::endl;
        return false;
    }

    file.close();
    return true;
}



// Simple sorting by inserts
SortResults insertionSort(int arr[], int n) {
    SortResults result = { 0, 0 };
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        result.comparisons++; // the first comparison to enter the loop
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
            result.comparisons++; // each comparison in the loop
            result.swaps++;
        }
        arr[j + 1] = key;
        result.swaps++;
    }
    return result;
}

// Bubble sorting
SortResults bubbleSort(int arr[], int n) {
    SortResults result = { 0, 0 };
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            result.comparisons++;
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                result.swaps++;
            }
        }
    }
    return result;
}

// Sorting by selection
SortResults selectionSort(int arr[], int n) {
    SortResults result = { 0, 0 };
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            result.comparisons++;
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            std::swap(arr[minIndex], arr[i]);
            result.swaps++;
        }
    }
    return result;
}

// Binary insertion sorting
SortResults binaryInsertionSort(int arr[], int n) {
    SortResults result = { 0, 0 };
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int left = 0, right = i - 1;

        // Searching for the insertion point using binary search
        while (left <= right) {
            int mid = left + (right - left) / 2;
            result.comparisons++;
            if (arr[mid] > key) {
                right = mid - 1;
            }
            else {
                left = mid + 1;
            }
        }

        // Shift elements to the right for insertion
        for (int j = i - 1; j >= left; j--) {
            arr[j + 1] = arr[j];
            result.swaps++;
        }
        arr[left] = key;
        result.swaps++;
    }
    return result;
}

// Shaker sorting
SortResults shakerSort(int arr[], int n) {
    SortResults result = { 0, 0 };
    bool swapped = true;
    int start = 0, end = n - 1;

    while (swapped) {
        swapped = false;
        // Direct passage
        for (int i = start; i < end; i++) {
            result.comparisons++;
            if (arr[i] > arr[i + 1]) {
                std::swap(arr[i], arr[i + 1]);
                result.swaps++;
                swapped = true;
            }
        }
        if (!swapped) break; // If nothing has been changed, exit
        swapped = false;
        end--;
        // Return passage
        for (int i = end - 1; i >= start; i--) {
            result.comparisons++;
            if (arr[i] > arr[i + 1]) {
                std::swap(arr[i], arr[i + 1]);
                result.swaps++;
                swapped = true;
            }
        }
        start++;
    }
    return result;
}

// Shell Sorting
SortResults shellSort(int arr[], int n) {
    SortResults result = { 0, 0 };
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
                result.swaps++;
                result.comparisons++;
            }
            arr[j] = temp;
            result.swaps++;
        }
    }
    return result;
}

// Pyramid sorting
void heapify(int arr[], int n, int i, SortResults& result) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    result.comparisons++;
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    result.comparisons++;
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        result.swaps++;
        heapify(arr, n, largest, result);
    }
}

SortResults heapSort(int arr[], int n) {
    SortResults result = { 0, 0 };

    // Building a heap (rearranging an array)
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i, result);
    }

    // Extracting items from the heap
    for (int i = n - 1; i > 0; i--) {
        std::swap(arr[0], arr[i]);
        result.swaps++;
        heapify(arr, i, 0, result);
    }
    return result;
}

/// Function for displaying the results table
void printResults(const std::vector<std::vector<SortResults>>& table) {
    std::cout << std::setw(20) << "Method/Array"
        << std::setw(30) << "Ordered"
        << std::setw(30) << "Reverse"
        << std::setw(30) << "Random"
        << std::endl;

    std::vector<std::string> methods = {
        "Insertion", "Exchange", "Selection", "Binary insertion", "Shaker", "Shell", "Pyramidal"
    };

    for (size_t i = 0; i < table.size(); ++i) {
        std::cout << std::setw(20) << methods[i];
        for (size_t j = 0; j < table[i].size(); ++j) {
            std::cout << std::setw(15) << "Comparisons: " << table[i][j].comparisons
                << std::setw(15) << "Permutations: " << table[i][j].swaps;
        }
        std::cout << std::endl;
    }
}

int main() {
    const int n = 200;
    int orderedArray[n], reversedArray[n], randomArray[n];

    // Reading arrays from a file
    if (!readArraysFromFile("arrays.txt", orderedArray, reversedArray, randomArray, n)) {
        return 1; // If an error occurred while reading the file, terminate the program
    }

    std::vector<std::vector<SortResults>> results(7, std::vector<SortResults>(3));

    // Performing sorting for all methods
    int tempArray[n];

    // Insert
    std::copy(orderedArray, orderedArray + n, tempArray);
    results[0][0] = insertionSort(tempArray, n);
    std::copy(reversedArray, reversedArray + n, tempArray);
    results[0][1] = insertionSort(tempArray, n);
    std::copy(randomArray, randomArray + n, tempArray);
    results[0][2] = insertionSort(tempArray, n);

    // Exchange
    std::copy(orderedArray, orderedArray + n, tempArray);
    results[1][0] = bubbleSort(tempArray, n);
    std::copy(reversedArray, reversedArray + n, tempArray);
    results[1][1] = bubbleSort(tempArray, n);
    std::copy(randomArray, randomArray + n, tempArray);
    results[1][2] = bubbleSort(tempArray, n);

    // Selection
    std::copy(orderedArray, orderedArray + n, tempArray);
    results[2][0] = selectionSort(tempArray, n);
    std::copy(reversedArray, reversedArray + n, tempArray);
    results[2][1] = selectionSort(tempArray, n);
    std::copy(randomArray, randomArray + n, tempArray);
    results[2][2] = selectionSort(tempArray, n);

    // Binary insertion
    std::copy(orderedArray, orderedArray + n, tempArray);
    results[3][0] = binaryInsertionSort(tempArray, n);
    std::copy(reversedArray, reversedArray + n, tempArray);
    results[3][1] = binaryInsertionSort(tempArray, n);
    std::copy(randomArray, randomArray + n, tempArray);
    results[3][2] = binaryInsertionSort(tempArray, n);

    // Shaker
    std::copy(orderedArray, orderedArray + n, tempArray);
    results[4][0] = shakerSort(tempArray, n);
    std::copy(reversedArray, reversedArray + n, tempArray);
    results[4][1] = shakerSort(tempArray, n);
    std::copy(randomArray, randomArray + n, tempArray);
    results[4][2] = shakerSort(tempArray, n);

    // Shell
    std::copy(orderedArray, orderedArray + n, tempArray);
    results[5][0] = shellSort(tempArray, n);
    std::copy(reversedArray, reversedArray + n, tempArray);
    results[5][1] = shellSort(tempArray, n);
    std::copy(randomArray, randomArray + n, tempArray);
    results[5][2] = shellSort(tempArray, n);

    // Pyramidal
    std::copy(orderedArray, orderedArray + n, tempArray);
    results[6][0] = heapSort(tempArray, n);
    std::copy(reversedArray, reversedArray + n, tempArray);
    results[6][1] = heapSort(tempArray, n);
    std::copy(randomArray, randomArray + n, tempArray);
    results[6][2] = heapSort(tempArray, n);

    // Table output
    printResults(results);

    return 0;
}