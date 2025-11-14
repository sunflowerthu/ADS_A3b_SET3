#include "ArrayGenerator.h"

class SortTester {
private:
    ArrayGenerator generator;

    // Insertion Sort для небольших массивов
    void insertionSort(std::vector<int>& arr, int left, int right) {
        for (int i = left + 1; i <= right; i++) {
            int key = arr[i];
            int j = i - 1;
            while (j >= left && arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
    }

    void heapify(std::vector<int>& arr, int heap_size, int i, int offset) {
        int largest = i;
        int left = 2 * (i - offset) + 1 + offset;
        int right = 2 * (i - offset) + 2 + offset;

        if (left < heap_size && arr[left] > arr[largest])
            largest = left;

        if (right < heap_size && arr[right] > arr[largest])
            largest = right;

        if (largest != i) {
            std::swap(arr[i], arr[largest]);
            heapify(arr, heap_size, largest, offset);
        }
    }

    // Heap Sort
    void heapSort(std::vector<int>& arr, int left, int right) {
        int n = right - left + 1;
        
        // Строим кучу (max-heap)
        for (int i = left + n/2 - 1; i >= left; i--) {
            heapify(arr, right + 1, i, left);
        }
        
        // Извлекаем элементы из кучи
        for (int i = right; i > left; i--) {
            std::swap(arr[left], arr[i]);
            heapify(arr, i, left, left);
        }
    }

    // Quick Sort со случайным опорным элементом
    int partition(std::vector<int>& arr, int left, int right) {
        // Случайный выбор опорного элемента
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dis(left, right);
        int pivotIndex = dis(gen);
        std::swap(arr[pivotIndex], arr[right]);
        
        int pivot = arr[right];
        int i = left - 1;
        
        for (int j = left; j < right; j++) {
            if (arr[j] <= pivot) {
                i++;
                std::swap(arr[i], arr[j]);
            }
        }
        std::swap(arr[i + 1], arr[right]);
        return i + 1;
    }

    // Introsort
    void introSort(std::vector<int>& arr, int left, int right, int depthLimit) {
        // Если элементов мало, используем Insertion Sort
        if (right - left < 16) {
            insertionSort(arr, left, right);
            return;
        }
        
        // Если глубина рекурсии превысила лимит, используем Heap Sort
        if (depthLimit == 0) {
            heapSort(arr, left, right);
            return;
        }
        
        // Иначе продолжаем Quick Sort
        int pi = partition(arr, left, right);
        introSort(arr, left, pi - 1, depthLimit - 1);
        introSort(arr, pi + 1, right, depthLimit - 1);
    }

public:
    SortTester() {}

    // Тестирование Introsort
    long long testHybridSort(const std::vector<int>& originalArray) {
        std::vector<int> arr = originalArray;
        auto start = std::chrono::high_resolution_clock::now();
        
        if (!arr.empty()) {
            int depthLimit = 2 * log2(arr.size());
            introSort(arr, 0, arr.size() - 1, depthLimit);
        }
        
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        return std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
    }
};
