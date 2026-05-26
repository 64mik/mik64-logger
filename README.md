# mik64-logger

C++ logging library using the Singleton pattern. Supports multiple output destinations.

## Features

- Factory Pattern: Easy creation of writers through LoggerFactory.
- Singleton Pattern: Ensures a single logger instance for flexibility.
- Multiple Outputs: It supports console and file output simultaneously. You can also use both simultaneously.
- Timestamps: Adds timestamps to file logs in [HH:MM:SS] format at file output.
- File Rotation: Automatically creates new log files based on date (YYYY-MM-DD.log format).
- Thread-Safe: Uses mutexes and condition variables for thread safety.
- Asynchronous Logging: Tried to make producer-consumer pattern with a queue and background thread for non-blocking log operations.

## How to use

### As a submodule
```bash
git submodule add https://github.com/64mik/cpp-logger.git
```

```cmake
add_subdirectory(lib/cpp-logger)
target_link_libraries(your_project PRIVATE cpp-logger)
```

### Basic Setup
```cpp
//main.cpp
#include "mlog.h"
#include "loggerFactory.h"

int main(){
	// Create writers console (and/or) file
	mik64::Logger::getInstance().setWriters(mik64::LoggerFactory::getWriters({"file","console"}));
	MLOG_INFO_S << "This is an info message " << 1;
}
```

```cpp
#include "mlog.h"

void example(){
	// Log messages
	MLOG_INFO("This is an info message ");
	MLOG_WARNING_S << "This is a" << " warning message";
	MLOG_ERROR_S << 0.1 << " This is an error message";
}
```

### Macros

- `MLOG_INFO`: Logs at INFO level
- `MLOG_WARNING`: Logs at WARNING level
- `MLOG_ERROR`: Logs at ERROR level

- `MLOG_INFO_S`: Log stream at INFO level
- `MLOG_WARNING_S`: Log stream at WARNING level
- `MLOG_ERROR_S`: Log stream at ERROR level

### Log Output Format

- Console: `[LEVEL] line| function(): message`
- File: `[HH:MM:SS] [LEVEL] line| function(): message`

## Architecture

- Main thread enqueues log messages.
- Background thread dequeues and writes to all configured outputs.

## Building

This project uses C++17 and requires a C++ compiler

### Prerequisites

- C++17 compatible compiler
- Windows: MinGW-w64 or MSVC
- Cmake 3.15+

## Example Output

### Console
```
[INFO] 27| main(): This is an info message 
[WARN] 28| main(): This is a warning message
[ERR_] 29| main(): 0.1This is an error message
```

### File
```logs/2026-05-06.log
[20:20:56] [INFO] 27| main(): This is an info message 
[20:20:56] [WARN] 28| main(): This is a warning message
[20:20:56] [ERR_] 29| main(): 0.1This is an error message
```

## Performance

- Tested with 1,000,000 logs in ~603ms (enqueue/dequeue) on Windows 11, Intel i5-10210U (Release build)

## License

MIT License