cmake_minimum_required(VERSION 3.16)

project(MatamStory VERSION 1.0 LANGUAGES CXX)

add_executable(MatamStory
    main.cpp
    MatamStory.cpp
    Utilities.cpp
    Players/Player.cpp
    Players/Job.cpp
    Players/Character.cpp
    Events/Event.cpp
    Events/Monster.cpp
)

target_compile_features(MatamStory PRIVATE cxx_std_17)
set_target_properties(MatamStory PROPERTIES
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)
target_include_directories(MatamStory PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/Players
    ${CMAKE_CURRENT_SOURCE_DIR}/Events
)
if(MSVC)
    target_compile_options(MatamStory PRIVATE /W4)
else()
    target_compile_options(MatamStory PRIVATE -Wall -Werror -pedantic-errors)
endif()

include(CTest)
if(BUILD_TESTING)
    find_package(Python3 COMPONENTS Interpreter REQUIRED)
    foreach(case_number RANGE 1 3)
        if(case_number EQUAL 1)
            set(expected_exit 0)
        else()
            set(expected_exit 1)
        endif()
        add_test(
            NAME example_${case_number}
            COMMAND ${Python3_EXECUTABLE}
                ${CMAKE_CURRENT_SOURCE_DIR}/scripts/check_fixture.py
                $<TARGET_FILE:MatamStory>
                ${CMAKE_CURRENT_SOURCE_DIR}/tests/test${case_number}.events
                ${CMAKE_CURRENT_SOURCE_DIR}/tests/test${case_number}.players
                ${CMAKE_CURRENT_SOURCE_DIR}/tests/test${case_number}.expected
                ${expected_exit}
        )
    endforeach()
endif()
