### Overview
# SchedulerApplication

A desktop-based task scheduling and management system built with **C++**, **Qt Widgets**, and **SQLite**.  
The application allows users to create, manage, and organize tasks through a modern graphical user interface developed using Qt Creator.


## Features

- Add, update, and delete tasks
- Organize tasks by:
  - Todo
  - In Progress
  - Done
- Graphical desktop interface using Qt Widgets
- Multi-page navigation using `QStackedWidget`
- SQLite database integration for persistent storage
- Task scheduling with date and time management
- Object-oriented architecture
- Modular project structure



## Tech Stack

- **C++**
- **Qt 6 (Qt Widgets)**
- **SQLite**
- **Visual Studio**
- **Qt Creator**



# Project Structure

```
SchedulerApplication/
│
├── app/                      # Application entry point
│   └── main.cpp
│
├── include/                  # Header files
│
├── src/                      # Source files
│
├── ui/                       # Qt Designer UI files
│
├── scheduler.db              # SQLite database
│
├── SchedulerApplication.sln  # Visual Studio solution
├── SchedulerApplication.vcxproj
├── SchedulerApplication.qtvscr
│
├── README.md
└── .gitignore
```


# Application Architecture

## Core Components

### Scheduler
Handles task management operations including:
- Adding tasks
- Updating tasks
- Viewing tasks

### Task
Represents a single task containing:
- Title/Message
- Status
- Date
- Time

### Qt UI Layer
Built using Qt Widgets and Qt Designer:
- Navigation buttons
- Multiple pages using `QStackedWidget`
- Interactive forms and task views

### Database Layer
SQLite database used for:
- Persistent task storage
- Loading saved tasks
- Updating task records



# GUI Overview

The application now includes a complete **Qt-based graphical interface** instead of a console-only workflow.

## UI Features
- Multiple pages/screens
- Task management interface
- Responsive Qt layouts
- Modern desktop application workflow



# Build Instructions

## Requirements

Install:
- Qt 6+
- Visual Studio 2022
- Qt Visual Studio Tools
- MSVC Compiler



# Running with Visual Studio

1. Clone the repository:


git clone https://github.com/ShanzayGit/SchedulerApplication.git

2. Open:

SchedulerApplication.sln


3. Configure Qt Version in Visual Studio

4. Build the solution:


Ctrl + Shift + B


5. Run the project:


Ctrl + F5

# Running with Qt Creator

1. Open Qt Creator
2. Open the project/solution
3. Configure the Qt kit
4. Build and run


# Database

The project uses an SQLite database:

scheduler.db

Database stores:
- Task title
- Status
- Date
- Time



# Current Functionality

- Create tasks
- Update task 
- View tasks
- Persistent storage with SQLite
- GUI-based interaction


# Future Improvements

- Dark mode support
- Notifications/reminders
- Calendar integration
- Search and filtering
- Recurring tasks
- Drag-and-drop task management
- Improved UI styling
- Charts/productivity analytics


# Learning Outcomes

This project demonstrates:
- Object-Oriented Programming in C++
- Qt GUI development
- Event-driven programming
- SQLite database integration
- Desktop application architecture
- Modular project organization


# Author

## Shanzay Malik

Software Engineering Student  
Passionate about:
- C++
- Qt Development
- Desktop Applications
- Software Design
- UI Development

