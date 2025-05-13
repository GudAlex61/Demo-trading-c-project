cmake_minimum_required(VERSION 3.10)

project(DemoTrading LANGUAGES CXX)

# Настройка для Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Поиск необходимых пакетов
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)
find_package(CURL REQUIRED)
find_package(SQLite3 REQUIRED)

# Включаем директории
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/demo-trading
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Добавляем исходные файлы
set(SOURCES
    demo-trading/main.cpp
    src/api.cpp
    src/sql.cpp
    src/MakingAPosition.cpp
    demo-trading/login.cpp
    demo-trading/authorization.cpp
    demo-trading/registration.cpp
)

# Добавляем заголовочные файлы
set(HEADERS
    include/api.h
    include/sql.h
    include/MakingAPosition.h
    demo-trading/login.h
    demo-trading/authorization.h
    demo-trading/registration.h
)

# Добавляем UI-формы
set(FORMS
    demo-trading/login.ui
    demo-trading/authorization.ui
    demo-trading/registration.ui
)

# Создаем исполняемый файл
add_executable(DemoTrading
    ${SOURCES}
    ${HEADERS}
    ${FORMS}
)

# Подключаем зависимости
target_link_libraries(DemoTrading PRIVATE
    Qt6::Core
    Qt6::Widgets
    ${CURL_LIBRARIES}
    SQLite::SQLite3
)

# Устанавливаем стандарт C++
set_target_properties(DemoTrading PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)
