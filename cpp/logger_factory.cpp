#include "logger_factory.h"
#include "file_writer.h"
#include "console_writer.h"
#include <set>
namespace mik64{
    std::vector<std::shared_ptr<IWriter>> LoggerFactory::getWriters(std::initializer_list<std::string> writerTypes){
        std::vector<std::shared_ptr<IWriter>> writers ={};
        std::set<std::string> seen;
        for(const auto& type : writerTypes) {
            if(seen.count(type)){
                continue;
            }
            seen.insert(type);
            if(type == "file") {
                writers.push_back(std::make_shared<FileWriter>());
            } 
            else if(type == "console") {
                writers.push_back(std::make_shared<ConsoleWriter>());
            }
        }
        return writers;
    }
}