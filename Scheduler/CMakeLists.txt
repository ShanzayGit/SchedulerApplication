cmake_minimum_required(VERSION 3.19)
project(Scheduler LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(Scheduler
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    addtaskspage.h addtaskspage.cpp addtaskspage.ui
    updatetaskspage.h updatetaskspage.cpp updatetaskspage.ui
    viewtaskspage.h viewtaskspage.cpp viewtaskspage.ui
    viewallpage.h viewallpage.cpp viewallpage.ui
    viewtodaypage.h viewtodaypage.cpp viewtodaypage.ui
    viewtodopage.h viewtodopage.cpp viewtodopage.ui
    viewinprogresspage.h viewinprogresspage.cpp viewinprogresspage.ui
    viewdonepage.h viewdonepage.cpp viewdonepage.ui
    viewspecificpage.h viewspecificpage.cpp viewspecificpage.ui
    updatemessagepage.h updatemessagepage.cpp updatemessagepage.ui
    updatedatepage.h updatedatepage.cpp updatedatepage.ui
    updatetimepage.h updatetimepage.cpp updatetimepage.ui
    updatestatuspage.h updatestatuspage.cpp updatestatuspage.ui
    homepage.h homepage.cpp homepage.ui
    updatehome.h updatehome.cpp updatehome.ui
    viewhome.h viewhome.cpp viewhome.ui
)

target_link_libraries(Scheduler
    PRIVATE
        Qt::Core
        Qt::Widgets
)

install(TARGETS Scheduler
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET Scheduler
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
