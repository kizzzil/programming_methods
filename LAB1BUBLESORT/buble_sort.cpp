#include <iostream>
#include <vector>
#include <time.h>
#include <thread>
#include <chrono>


using namespace std;

void oddEvenSorting(vector<int>& vec) {
	int n = vec.size();
	for (size_t i = 0; i < n; i++) {
		// if (i % 1000 == 0){
		// 	cout << "I'm alive" << "\n";
		// }
		for (size_t j = (i % 2) ? 0 : 1; j + 1 < n; j += 2) {
			if (vec[j] > vec[j + 1]) {
				swap(vec[j], vec[j + 1]);
			}
		}
	}
}

void intiliazation(vector<int>& vec, int n){
	// srand(time(NULL));

	for (int i = 0; i < n; i++)
	{
		vec.push_back(rand());
	}
}

void printVector(vector<int> vec){
	for (int i = 0; i < vec.size(); i++)
	{
		cout << vec[i] << "\n";
	}
}

const int n = 50000;

int main()
{	
	vector<int> vec; 
	intiliazation(vec, n);

	clock_t begin = clock();
	oddEvenSorting(vec);
    clock_t end = clock();
    printf("Sort time %f for %d elements", (double)(end - begin) / CLOCKS_PER_SEC, n);
}