#ifndef MLOG_H
#define MLOG_H
#include "mik64_logger.h"
#include "logger_factory.h"
#define MLOG_INFO(msg) mik64::Logger::getInstance().log(mik64::Logger::LogLevel::L_INFO, __FUNCTION__, __LINE__, msg)
#define MLOG_WARNING(msg) mik64::Logger::getInstance().log(mik64::Logger::LogLevel::L_WARNING, __FUNCTION__, __LINE__, msg)
#define MLOG_ERROR(msg) mik64::Logger::getInstance().log(mik64::Logger::LogLevel::L_ERROR, __FUNCTION__, __LINE__, msg)
#define MLOG_INFO_S mik64::Logger::Wrapper(mik64::Logger::LogLevel::L_INFO, __FUNCTION__, __LINE__)
#define MLOG_WARNING_S mik64::Logger::Wrapper(mik64::Logger::LogLevel::L_WARNING, __FUNCTION__, __LINE__)
#define MLOG_ERROR_S mik64::Logger::Wrapper(mik64::Logger::LogLevel::L_ERROR, __FUNCTION__, __LINE__)
#define MLOG_SET_WRITERS(...) mik64::Logger::getInstance().setWriters(mik64::LoggerFactory::getWriters({__VA_ARGS__}))
#endif // MLOG_H