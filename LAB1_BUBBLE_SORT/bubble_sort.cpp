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

// Отрисовка progress bar'a  (Работает неидеальано, но со своей задачей справляется)
void render_progress_bar(int x, int y, int width, double progress, char fill_symbol)
{
	// Колличество пустных полей и полей с симоволом 
    int fill_w = static_cast<int>(width * progress);
    int empty_w = width - fill_w;

	// Установка курсора в конкретную область
    SetConsoleCursorPosition(handle, { static_cast<SHORT>(x), static_cast<SHORT>(y) });

	// Ограничение вывода в консоль
	mtx.lock();
	cout << "Sorting progress [";

    for (int i = 0; i < fill_w; ++i)
        std::cout << fill_symbol;

    for (int i = 0; i < empty_w; ++i)
        std::cout << " ";

	cout << "]" << "\n";
	mtx.unlock();
}

// Функция сортировки пузырьком
void oddEvenSorting(vector<int>& vec, int y) {
	int n = vec.size();

	// Данные для работы progress bar'a 
	// width - длина progress bar'a 
	// checkpoint - момент, в которые нам нужно обновлять progress bar
	int width = 35;
	int checkpoint = n > width ? n / width : width / n;

	for (int i = 0; i < n; i++) {
		// Отрисовка progress bar'a
		if (i % checkpoint == 0 || i == n - 1){
			render_progress_bar(0, y, width, (1.0 * i / (n - 1)),'*');
		}
		// Сама сортировка 
		for (int j = (i % 2) ? 0 : 1; j + 1 < n; j += 2) {
			if (vec[j] > vec[j + 1]) {
				swap(vec[j], vec[j + 1]);
			}
		}
	}
}


// Функция параллельной сортировки пузырьком
void ParallelOddEvenSorting(vector<int>& vec) {
	// Колличество тредов
	int thK = 2;
	int n = vec.size();

	// Аналогично коду в oddEvenSorting
	int width = 35;
	int k = n > width ? n / width : width / n;

	// Вектора для параллеливания 
	vector<vector<int>> elemVector;
	vector<thread> threads;
	
	// Создание и заполнение массива чётных и нечётных
	for (int i = 0; i < thK; i++){
		vector<int> a;
		elemVector.push_back(a);
	}

	for (int i = 0; i < n; i++){
		elemVector[i%thK].push_back(vec[i]);
	}

	// Создание и помещение тредов для удобной работы
	for (size_t i = 0; i < thK; i++){
		threads.push_back(move(thread(oddEvenSorting, ref(elemVector[i]), i)));
	}

	// Присоединение тредов, для того чтобы ждать их
	for (int i = 0; i < threads.size(); i++){
		threads[i].join();
	}
	
	// Возвращение отсортированных чётных и нечётных векторов
	for (int i = 0; i < n; i++){
		if (i % 2 == 0){
			vec[i] = elemVector[0][i/2];
		}
		else{
			vec[i] = elemVector[0][i/2];
		}
	}

	// Последний проход по вектору для полной сортировки пришедших данных
	thread(oddEvenSorting, ref(vec), 2).join();

}


// Функция заполнения векторов случайными велечинами
void intiliazation(vector<int>& vec, vector<int>& pvec, int n){
	// Для разнообразныхэлементов
	// srand(time(NULL));

	for (int i = 0; i < n; i++)
	{
		int k = rand();
		vec.push_back(k);
		pvec.push_back(k);
	}
}

// Функция вывода вектор
void printVector(vector<int> vec){
	for (int i = 0; i < vec.size(); i++)
	{
		cout << vec[i] << "\n";
	}
}

// Функция запуска Параллельной реализации 
void runParallel(vector<int>& vec, double& time){
	clock_t begin = clock();
	ParallelOddEvenSorting(vec);
    clock_t end = clock();
	time = (double) end - begin;
}

// Функция запуска Последовательной реализации 
void  runSequential(vector<int>& vec, double& time){
	clock_t begin = clock();
	oddEvenSorting(vec, 3);
    clock_t end = clock();
	time = (double) end - begin;
}



int main()
{	
	// Коллличество элементов 
	const int n = 50000;

	vector<int> vec; 
	vector<int> pvec;
	// Заполнение вектором случайными данными
	intiliazation(vec,pvec, n);
	// Очистка консоли
	system ("cls");

	// Время выполнения 
	double time1 = 0;
	double time2 = 0;

	// Запуск тредов с Параллельной реализацией и Последовательной реализацией
	thread thread1(runParallel, ref(pvec), ref(time1));
	thread thread2(runSequential, ref(vec), ref(time2));

	// Ожидание выволнения прцессов в треде
	thread1.join();
	thread2.join();

	// Вывод результатов работы
	printf("Sorting time is %f for %d elements - Parallel method\n", time1 / CLOCKS_PER_SEC, n);
	printf("Sorting time is %f for %d elements - Sequential method\n", time2 / CLOCKS_PER_SEC, n);
}