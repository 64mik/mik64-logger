#ifndef LOGGER_FACTORY_H
#define LOGGER_FACTORY_H
#include "file_writer.h"
#include "console_writer.h"
#include <vector>
#include <memory>
namespace mik64::LoggerFactory {
    std::vector<std::shared_ptr<IWriter>> getWriters(std::initializer_list<std::string> writerTypes);
}
#endif // LOGGER_FACTORY_H