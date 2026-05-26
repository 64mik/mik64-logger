#include "file_writer.h"
#include <chrono>
#include <iostream>
namespace mik64 {
    FileWriter::FileWriter(const std::string& logDirectory){
        logDir_ = logDirectory;
        try {
            std::filesystem::create_directories(logDir_);
        } catch (const std::exception& e) {
            std::cerr << "Failed to create log directory: " << e.what() << std::endl;
        }
    }
    FileWriter::~FileWriter(){
        std::lock_guard<std::mutex> lock(file_mutex_);
        if (file_.is_open()) {
            file_.close();
        }
    }
    void FileWriter::write(const std::string& data) {
        auto now = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(now);
        if (in_time_t != last_t_) {
            std::tm t;
            localtime_s(&t, &in_time_t);
            char dateBuf[11];
            strftime(dateBuf, sizeof(dateBuf), "%Y-%m-%d", &t);
            std::string newDate(dateBuf);

            if (newDate != lastDate_) {
                if (file_.is_open()) file_.close();
                lastDate_ = newDate;
                currentFileName_ = lastDate_ + ".log";
                file_.open(logDir_ / currentFileName_, std::ios::app);
                if (!file_.is_open()) {
                    std::cerr << "Failed to open log file: " << (logDir_ / currentFileName_) << std::endl;
                    isFileOpen_ = false;
                    return;
                }
                isFileOpen_ = true;
            }
            strftime(timeBuf_, sizeof(timeBuf_), "[%H:%M:%S] ", &t);
            last_t_ = in_time_t;
        }
        if (file_.is_open() && isFileOpen_)
            file_ << timeBuf_ << data << '\n';
    }
}