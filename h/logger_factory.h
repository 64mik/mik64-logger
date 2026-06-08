#ifndef LOGGER_FACTORY_H
#define LOGGER_FACTORY_H
#include <vector>
#include <memory>
#include "i_writer.h"
namespace mik64::LoggerFactory {
    std::vector<std::shared_ptr<IWriter>> getWriters(std::initializer_list<std::string> writerTypes);
}
#endif // LOGGER_FACTORY_H