#include <iostream>
#include <vector>
#include <time.h>
#include <thread>
#include <chrono>
#include <mutex>
#include <Windows.h> 

using namespace std;

mutex mtx;

auto handle = GetStdHandle(STD_OUTPUT_HANDLE);

// устанавливает курсор в консоли на указанную позицию
void set_cursor(int x, int y)
{
    SetConsoleCursorPosition(handle, { static_cast<SHORT>(x), static_cast<SHORT>(y) });
}

void render_progress_bar(int x, int y, int width, double progress, char fill_symbol)
{
    int fill_w = static_cast<int>(width * progress);
    int empty_w = width - fill_w;

    set_cursor(x, y);

	cout << "Sorting progress [";

    for (int i = 0; i < fill_w; ++i)
        std::cout << fill_symbol;

    for (int i = 0; i < empty_w; ++i)
        std::cout << " ";

	cout << "]" << "\n";
}

void odd(vector<int>& vec){
	int n = vec.size();
	for (size_t j = 0; j + 1 < n; j += 2) {
		if (vec[j] > vec[j + 1]) {
			mtx.lock();
			swap(vec[j], vec[j + 1]);
			mtx.unlock();
		}
	}
}

void even(vector<int>& vec){
	int n = vec.size();
	for (size_t j = 1; j + 1 < n; j += 2) {
		if (vec[j] > vec[j + 1]) {
			mtx.lock();
			swap(vec[j], vec[j + 1]);
			mtx.unlock();
		}
	}
}

void ParallelOddEvenSorting(vector<int>& vec) {
	int n = vec.size();
	int width = 35;
	int k = n > width ? n / width : width / n;
	
	for (size_t i = 0; i < n; i++){
		if (i % k == 0 || i == n - 1){
			render_progress_bar(0, 0, width, (1.0 * i / (n - 1)), '*');
		}
		if (i % 2 == 0){
			// odd(vec, n);
			thread(odd, ref(vec)).join();
		}
		else{
			// even(vec, n);
			thread(even, ref(vec)).join();
		}
	}
}

void oddEvenSorting(vector<int>& vec) {
	int n = vec.size();
	int width = 35;
	int k = n > width ? n / width : width / n;
	for (size_t i = 0; i < n; i++) {
		if (i % k == 0 || i == n - 1){
			render_progress_bar(0, 2, width, (1.0 * i / (n - 1)),'*');
		}
		for (size_t j = (i % 2) ? 0 : 1; j + 1 < n; j += 2) {
			if (vec[j] > vec[j + 1]) {
				swap(vec[j], vec[j + 1]);
			}
		}
	}
}


void intiliazation(vector<int>& vec,vector<int>& pvec, int n){
	// Для разнообразныхэлементов
	srand(time(NULL));

	for (int i = 0; i < n; i++)
	{
		int k = rand();
		vec.push_back(k);
		pvec.push_back(k);
	}
}

void printVector(vector<int> vec){
	for (int i = 0; i < vec.size(); i++)
	{
		cout << vec[i] << "\n";
	}
}

void printEL(){
	for (int i = 0; i < 100; i++){
		cout << "elem" << "\n";
	}
}

const int n = 10000;

int main()
{	
	vector<int> vec; 
	vector<int> pvec;
	intiliazation(vec,pvec, n);
	system ("cls");

	clock_t begin = clock();
	ParallelOddEvenSorting(pvec);
    clock_t end = clock();
    printf("Sorting time is %f for %d elements - Parallel method\n", (double)(end - begin) / CLOCKS_PER_SEC, n);

	begin = clock();
	oddEvenSorting(vec);
    end = clock();
	printf("Sorting time is %f for %d elements - Sequential method\n", (double)(end - begin) / CLOCKS_PER_SEC, n);
}