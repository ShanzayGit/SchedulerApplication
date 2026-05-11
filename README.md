## SchedulerApplication

## Overview
SchedulerApplication is a C++ project that manages tasks by date and time. It allows users to add, update, and display tasks, supporting features such as viewing today's tasks, in-progress tasks, and completed tasks. The project demonstrates object-oriented design with classes for Scheduler, Task, Date, MyTime, and a custom MyString implementation.

## Folder Structure
- **include/** → Header files (Date.h, MyTime.h, Task.h, Scheduler.h, MyString.h)
- **src/** → Source files (.cpp implementations)
- **app/** → Entry point (main.cpp)
- **SchedulerApplication.sln** → Visual Studio solution
- **SchedulerApplication.vcxproj** → Visual Studio project file
- **README.md** → Project documentation


### Build Instructions

## Windows (Visual Studio)
- Open SchedulerApplication.sln in Visual Studio.
- Build the solution (Ctrl+Shift+B).
- Run the project (Ctrl+F5).

## Linux/Mac (g++)
```
g++ src/*.cpp app/main.cpp -I include -o scheduler
./scheduler
```
## Usage
- After building, run the executable to start the application. Example usage:
- Add tasks with specific dates, times and status(Todo/InProgress/Done).
- Display today's tasks.
- View tasks marked as Todo, InProgress or Done.

## Sample Output
Today's Tasks:
1. Today's scheduled task is : Team meeting
   Status for today's task : Todo
   Time of Today's Task : 02:00:00 PM

2. Today's scheduled task is : Team Dinner
   Status for today's task : Todo
   Time of Today's Task : 08:00:00 PM

## Features
- Task management by date and time.
- Update task message, status, date, and time.
- Display tasks filtered by status.
- Custom string class implementation (MyString).

## Future Improvements
- Add persistence (save/load tasks to file).
- Implement recurring tasks.
- Enhance UI with a graphical interface.

## Project Structure
- src/ → implementation files
- include/ → header files
  
## Architecture
- Scheduler: manages task operations
- Task: represents a single task
- Date/Time: utility classes
  
## Technologies
- C++
- OOP
  
  
