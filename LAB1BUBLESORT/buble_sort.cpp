#include <iostream>
#include <vector>

using namespace std;

void oddEvenSorting(vector<int>& vec) {
	int n = vec.size();
	for (size_t i = 0; i < n; i++) {
		for (size_t j = (i % 2) ? 0 : 1; j + 1 < n; j += 2) {
			if (vec[j] > vec[j + 1]) {
				swap(vec[j], vec[j + 1]);
			}
		}
	}
}

int main()
{

	int n = 100;

	// srand(time(NULL));

	vector<int> a; 

	for (int i = 0; i < n; i++)
	{
		a.push_back(rand());
	}

	oddEvenSorting(a);

	for (int i = 0; i < n; i++)
	{
		cout << a[i] << "\n";
	}
	
}