// #include <mutex>
// #include <iostream>

// using namespace std;

// class Logger {
// private:
//     std::mutex mtx;

// public:
//     void log(const std::string& message) {
//         std::lock_guard<std::mutex> lock(mtx);
//         std::cout << message << std::endl;
//     }
// };
#include <mutex>
#include <iostream>

using namespace std;

class Logger {
private:
    mutex& mtx;
public:
    Logger(std::mutex& mutex) : mtx(mutex) {}
    void log(const string& message) {
        lock_guard<mutex> lock(mtx);
        cout << message << endl;
    }
};