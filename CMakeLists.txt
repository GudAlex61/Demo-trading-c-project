cmake_minimum_required(VERSION 3.16)
project(CryptoTrader)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Main dependencies
find_package(OpenSSL REQUIRED)
find_package(SQLite3 REQUIRED)
find_package(CURL REQUIRED)
find_package(nlohmann_json 3.9.1 REQUIRED)
find_package(Qt6 COMPONENTS Widgets REQUIRED)

# Project sources
set(SOURCES
    src/main.cpp
    src/MakingAPosition.cpp
    src/api.cpp
    src/frontend.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${SQLite3_INCLUDE_DIRS}
    ${CURL_INCLUDE_DIRS}
    ${OPENSSL_INCLUDE_DIR}
    ${Qt6_INCLUDE_DIRS}
)

# Linking
target_link_libraries(${PROJECT_NAME} PRIVATE
    SQLite::SQLite3
    OpenSSL::SSL
    OpenSSL::Crypto
    CURL::libcurl
    nlohmann_json::nlohmann_json
    Qt6::Widgets 
    pthread
)
