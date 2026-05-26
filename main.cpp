#include <iostream>
#include "mlog.h"
#include "logger_factory.h"
#include <chrono>
#include <memory>
void hello(){
    MLOG_INFO("Hello, Logger");
}
void test(int count){
    auto start = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < count; ++i) {
        if(i % 2 == 0) {
            MLOG_WARNING_S<<"This "<< 2 << 5<<"is a warning log message."<< 8;
        } else {
            hello();
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> diff = end - start;
    std::cout << count << " logs enqueue time: " << diff.count() << " ms" << std::endl;
    auto file_end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> file_diff = file_end - start;
    std::cout << count << " logs file write time: " << file_diff.count() << " ms" << std::endl;
}
int main() {
    mik64::Logger::getInstance().setWriters(mik64::LoggerFactory::getWriters({"file"}));
    MLOG_INFO("This is an info message ");
    MLOG_WARNING_S << "This is a" << " warning message";
    MLOG_ERROR_S << 0.1 << "This is an error message";
    test(1000000);
    return 0;
}