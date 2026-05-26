#ifndef CONSOLE_WRITER_H
#define CONSOLE_WRITER_H
#include "i_writer.h"
namespace mik64{
    class ConsoleWriter : public IWriter {
    public:
        ConsoleWriter();
        ~ConsoleWriter();
        void write(const std::string& data) override;
    private:
        void setColor(int color, int backColor);
        //gotoxy?
        //좌표 버퍼에 좌표를 미리 설정해놓고 출력 종류에 따라 알아서 goto?
        //추후 수정
        enum location{
            L_INFO,
            L_WARNNING,
            L_ERROR,
            MAX
        };
        int xyBuffer[location::MAX] = {2,1,0};
    };
}
#endif //CONSOLE_LOGGER_H