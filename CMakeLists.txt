cmake_minimum_required(VERSION 3.10)
project(maolansndio VERSION 0.0.1 DESCRIPTION "SNDIO backend for Maolan library")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
include(GNUInstallDirs)

file(GLOB SRCS src/*.cpp src/audio/*.cpp src/midi/*.cpp)
file(GLOB HEADERS maolan/audio/sndio/*.hpp)
install(FILES ${HEADERS} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/maolan/audio/sndio)
set(MY_HEADERS ${MY_HEADEARS} ${HEADERS})
file(GLOB HEADERS maolan/midi/sndio/*.hpp)
install(FILES ${HEADERS} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/maolan/midi/sndio)
set(MY_HEADERS ${MY_HEADEARS} ${HEADERS})

enable_testing()
add_custom_target(build-tests)

find_package(PkgConfig REQUIRED)

pkg_check_modules(NLOHMANN REQUIRED nlohmann_json)
set(MY_INCLUDE_DIRS ${MY_INCLUDE_DIRS} ${NLOHMANN_INCLUDE_DIRS})
set(MY_LIBRARY_DIRS ${MY_LIBRARY_DIRS} ${NLOHMANN_LIBRARY_DIRS})
set(MY_LIBRARIES ${MY_LIBRARIES} ${NLOHMANN_LIBRARIES})

pkg_check_modules(MAOLAN REQUIRED libmaolan)
set(MY_INCLUDE_DIRS ${MY_INCLUDE_DIRS} ${MAOLAN_INCLUDE_DIRS})
set(MY_LIBRARY_DIRS ${MY_LIBRARY_DIRS} ${MAOLAN_LIBRARY_DIRS})
set(MY_LIBRARIES ${MY_LIBRARIES} ${MAOLAN_LIBRARIES})

pkg_check_modules(SNDIO REQUIRED sndio)
set(MY_INCLUDE_DIRS ${MY_INCLUDE_DIRS} ${SNDIO_INCLUDE_DIRS})
set(MY_LIBRARY_DIRS ${MY_LIBRARY_DIRS} ${SNDIO_LIBRARY_DIRS})
set(MY_LIBRARIES ${MY_LIBRARIES} ${SNDIO_LIBRARIES})

add_executable(test-load EXCLUDE_FROM_ALL tests/load.cpp)
target_link_directories(test-load PUBLIC ${MAOLAN_LIBRARY_DIRS})
target_link_libraries(test-load ${MAOLAN_LIBRARIES})
add_dependencies(build-tests test-load)

configure_file(libmaolansndio.pc.in libmaolansndio.pc @ONLY)
if (PKG_CONFIG_INSTALL_PATH)
    install(FILES ${PROJECT_BINARY_DIR}/libmaolansndio.pc DESTINATION ${CMAKE_INSTALL_PREFIX}${PKG_CONFIG_INSTALL_PATH})
elseif (BSD)
    install(FILES ${PROJECT_BINARY_DIR}/libmaolansndio.pc DESTINATION ${CMAKE_INSTALL_PREFIX}/libdata/pkgconfig)
else()
    install(FILES ${PROJECT_BINARY_DIR}/libmaolansndio.pc DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/pkgconfig)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_INSTALL_PREFIX}/include ${MY_INCLUDE_DIRS})
link_directories(${CMAKE_INSTALL_PREFIX}/lib ${MY_LIBRARY_DIRS})
add_compile_options(-Wall -Werror)

add_library(maolansndio SHARED ${SRCS} ${MY_HEADERS})
add_dependencies(build-tests maolansndio)
target_link_libraries(maolansndio ${MY_LIBRARIES})
install(TARGETS maolansndio LIBRARY DESTINATION lib)
