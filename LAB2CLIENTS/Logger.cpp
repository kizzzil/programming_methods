#include <mutex>
#include <iostream>

using namespace std;

class Logger {
public:
    void log(const string& message) {
        lock_guard<mutex> lock(mutex);
        cout << message << endl;
    }
};