#include <iostream>
#include <vector>
#include <time.h>
#include <thread>
#include <chrono>
#include <mutex>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

mutex mtx;

// Считывание данных из конфигурациоонного файла
int getNumberOfElemetsFromConfig(){
	int n;
	ifstream configFile("config.txt");
	string line;
	getline(configFile, line);
	istringstream ss(line);
	string tmp;
	while(ss >> tmp){
		try {
            int value = std::stoi(tmp);
            n = value;
            break;
        } catch (const std::exception& e) {
        }
	}
	configFile.close();
	return n;
}

// Функция сортировки пузырьком
void oddEvenSorting(vector<int>& vec) {
	int n = vec.size();

	for (int i = 0; i < n; i++) {
		// Сама сортировка 
		for (int j = (i % 2) ? 0 : 1; j + 1 < n; j += 2) {
			if (vec[j] > vec[j + 1]) {
				swap(vec[j], vec[j + 1]);
			}
		}
	}
}

vector<int> merge(const vector<int>& v1, const vector<int>& v2) {

    vector<int> result(v1.size() + v2.size());

    int i = 0, j = 0;
    while (i < v1.size() && j < v2.size()) {
        if (v1[i] < v2[j]) {
            result.push_back(v1[i]);
            i++;
        } else {
            result.push_back(v2[j]);
            j++;
        }
    }
    while (i < v1.size()) {
        result.push_back(v1[i]);
        i++;
    }
    while (j < v2.size()) {
        result.push_back(v2[j]);
        j++;
    }
    return result;
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
		threads.push_back(move(thread(oddEvenSorting, ref(elemVector[i]))));
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
	// thread(oddEvenSorting, ref(vec), 2).join();
	cout << "Even and odd arrays have been sorted\n";
	vec = merge(elemVector[0], elemVector[1]);
	cout << "Parallel method sorted the array\n";
}


// Функция заполнения векторов случайными велечинами
void intiliazation(vector<int>& vec, vector<int>& pvec, int n){
	// Для разнообразныхэлементов
	srand(time(NULL));

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
	oddEvenSorting(vec);
    clock_t end = clock();
	time = (double) end - begin;
}

int main()
{	
	// Количество элементов 

	const int n = getNumberOfElemetsFromConfig();

	vector<int> vec; 
	vector<int> pvec;
	// Заполнение вектором случайными данными
	intiliazation(vec,pvec, n);
	// Время выполнения 
	double time1 = 0;
	double time2 = 0;

	// Запуск тредов с Параллельной реализацией и Последовательной реализацией
	thread thread1(runParallel, ref(pvec), ref(time1));
	thread thread2(runSequential, ref(vec), ref(time2));

	// Ожидание выволнения прцессов в треде
	system("cls");
	printf("Please wait...\n");
	thread1.join();
	thread2.join();

	// Вывод результатов работы
	printf("Sorting time is %f for %d elements - Parallel method\n", time1 / CLOCKS_PER_SEC, n);
	printf("Sorting time is %f for %d elements - Sequential method\n", time2 / CLOCKS_PER_SEC, n);
}