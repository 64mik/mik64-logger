#ifndef LOGGER_H
#define LOGGER_H
#include "i_writer.h"
#include <string>
#include <sstream>
#include <queue>
#include <condition_variable>
#include <thread>
#include <mutex>
#include <atomic>
#include <vector>
#include <memory>
namespace mik64{
    class Logger {
    public:
        enum class LogLevel {
            L_INFO,
            L_WARNING,
            L_ERROR
        };
        static Logger& getInstance();
        void log(LogLevel logLevel, const std::string& func_name, int line, const std::string& message);
        void setWriters(std::vector<std::shared_ptr<IWriter>> writerptr);
        void flush();
        class Wrapper{
            public:
                Wrapper(Logger::LogLevel logLevel, const char* func_name, int line = 0){
                    logBuffer << getInstance().getLogPrefix(logLevel, func_name, line);
                }
                ~Wrapper(){
                    getInstance().enQueue(logBuffer.str());
                }
                Wrapper(const Wrapper&) = delete;
                Wrapper& operator=(const Wrapper&) = delete;
                template<typename T>
                Wrapper& operator<<(const T& value){
                    logBuffer << value;
                    return *this;
                }
            private:
                std::ostringstream logBuffer;
        };    
    private:
        Logger();
        ~Logger();
        Logger(const Logger&) = delete;
        Logger& operator=(const Logger&) = delete;
        void enQueue(const std::string& str);
        void deQueue();
        std::string getLogPrefix(LogLevel logLevel, const std::string& func_name, int line);
        std::thread writer_;
        std::condition_variable cv_;
        std::mutex mtx_;
        std::queue<std::string> front_;
        std::atomic<bool> running_{true};
        std::atomic<size_t> pending_{0};
        bool is_ptr_changed_{false};
        std::vector<std::shared_ptr<IWriter>> writerptrs_;
    };
}
#endif // LOGGER_H