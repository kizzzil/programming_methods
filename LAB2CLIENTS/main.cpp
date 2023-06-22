#include <iostream>
#include "Office.cpp"

using namespace std;

main(){
    // Начало работы
    vector <int> res;
    Config config = Config();
    int n = config.getConfMap("AMOUNT_OF_OFFICES");
    for (int i=0; i < n; i++){
        Office office = Office();
        int tmp = office.simulateOffice();
        res.push_back(tmp);
    }

    for (int i= 0; i < n; i++){
        cout << res[i] << " "; 
    }
}