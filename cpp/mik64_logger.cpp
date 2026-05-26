#include "mik64_logger.h"
#include <iostream>
namespace mik64 {
    void Logger::setWriters(std::vector<std::shared_ptr<IWriter>> writerptr){
        std::lock_guard<std::mutex> lock(mtx_);
        this->writerptrs_ = std::move(writerptr);
        is_ptr_changed_ = true;
    }
    Logger::Logger(){
        writer_ = std::thread(&Logger::deQueue, this);
    }
    Logger::~Logger() {    
        {
            std::lock_guard<std::mutex> lock(mtx_);
            running_ = false;
        }
        cv_.notify_all();
        if (writer_.joinable()) writer_.join();
    }
    Logger& Logger::getInstance() {
        static Logger instance;
        return instance;
    }
    void Logger::log(LogLevel logLevel, const std::string& func_name, int line, const std::string& message) {
        enQueue(getLogPrefix(logLevel, func_name, line) + message);
    }
    void Logger::flush() {
        std::unique_lock<std::mutex> lock(mtx_);
        cv_.notify_all();
        cv_.wait(lock, [this] { return (pending_.load(std::memory_order_acquire) == 0) || !running_; });
    }
    void Logger::enQueue(const std::string& data){
        std::lock_guard<std::mutex> lock(mtx_);
        bool fEmpty = front_.empty();
        pending_.fetch_add(1, std::memory_order_relaxed);
        front_.push(data);
        if (fEmpty) {
            cv_.notify_one();
        }
    }
    void Logger::deQueue() {
        std::string data;
        std::vector<std::shared_ptr<IWriter>> writers;
        std::queue<std::string> back;
        while (true) {
            {
                std::unique_lock<std::mutex> lock(mtx_);
                cv_.wait(lock, [this] { return !front_.empty() || !running_; });
                if (!running_ && front_.empty()) break;
                if(is_ptr_changed_) {
                    writers = writerptrs_;
                    is_ptr_changed_ = false;
                }
                std::swap(front_, back);
            }
            while(!back.empty()){
                data = std::move(back.front());
                back.pop();
                for(const auto& writer : writers){
                    if(writer)
                        writer->write(data);
                }
                size_t prev = pending_.fetch_sub(1, std::memory_order_acq_rel);
                if (prev == 1) {
                    cv_.notify_all();
                }
            }
        }
    }
    std::string Logger::getLogPrefix(LogLevel logLevel, const std::string& func_name, int line) {
        std::string prefix;
        switch (logLevel) {
            case LogLevel::L_INFO:
                prefix = "[INFO] ";
                break;
            case LogLevel::L_WARNING:
                prefix = "[WARN] ";
                break;
            case LogLevel::L_ERROR:
                prefix = "[ERR_] ";
                break;
            default:
                break;
        }
        if (line > 0) {
            prefix += std::to_string(line) + "| ";
        }
        prefix += func_name + "(): ";
        return prefix;
    }
}