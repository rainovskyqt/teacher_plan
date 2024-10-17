cmake_minimum_required(VERSION 3.5)

project(teacher_plan VERSION 0.1.0.0 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt5 REQUIRED COMPONENTS Widgets LinguistTools Sql)
find_package(Qt5 REQUIRED COMPONENTS Widgets LinguistTools Sql)

set(TS_FILES i18/teacher_plan_ru_RU.ts)

set(PRJ_RESOURCES)
set(PRJ_DEFINES)
set(PRJ_SRCS)


file(GLOB_RECURSE PRJ_SRCS0 "src/*.h" "src/*.hpp" "src/*.cpp" "src/*.ui")
list(APPEND PRJ_SRCS ${PRJ_SRCS0})

add_executable(teacher_plan
    ${PROJECT_SOURCES}
    src/educationwork/montheducationwork.h src/educationwork/montheducationwork.cpp src/educationwork/montheducationwork.ui
    src/educationwork/weekeducationwork.h src/educationwork/weekeducationwork.cpp src/educationwork/weekeducationwork.ui
    src/educationwork/monthheader.h src/educationwork/monthheader.cpp src/educationwork/monthheader.ui
)


list(APPEND PRJ_RESOURCES
    "src/res.qrc"
    )

target_sources(${PROJECT_NAME} PRIVATE ${PRJ_SRCS} ${PRJ_UIS} ${PRJ_RESOURCES} ${QM_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/src)

qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})

target_link_libraries(teacher_plan
    PRIVATE
    Qt5::Widgets
    Qt5::Sql
)

set_target_properties(teacher_plan PROPERTIES
    ${BUNDLE_ID_OPTION}
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS teacher_plan
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

include(cmake/ASAN.cmake)


