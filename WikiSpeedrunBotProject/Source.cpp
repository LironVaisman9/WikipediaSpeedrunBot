#include <iostream>
#include <thread>

int main() {
    unsigned int cores = std::thread::hardware_concurrency();
    std::cout << "Amount of threads: " << cores << std::endl;
    return 0;
}
