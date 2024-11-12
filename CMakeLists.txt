cmake_minimum_required(VERSION 3.5)
project(cedilla)


set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMakeModules)

option(CEDILLA_CODE_COVERAGE "Enable code coverage" OFF)

if (CEDILLA_CODE_COVERAGE)
    include(CodeCoverage)
    include(CodeCoverage)
endif ()

find_package(Boost)
find_package(PythonInterp 3 REQUIRED)

if (NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/ucd/ucd.all.flat.xml)
    message("Fetching unicode data")
    file(DOWNLOAD "ftp://ftp.unicode.org/Public/10.0.0/ucdxml/ucd.all.flat.zip" ${CMAKE_CURRENT_SOURCE_DIR}/ucd/ucd.all.flat.zip)
    execute_process(COMMAND ${CMAKE_COMMAND} -E tar xvf ucd.all.flat.zip WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/ucd)
endif ()
if (NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/ucd/NormalizationTest.txt)
    message("Fetching unicode tests")
    file(DOWNLOAD "ftp://ftp.unicode.org/Public/10.0.0/ucd/NormalizationTest.txt" ${CMAKE_CURRENT_SOURCE_DIR}/ucd/NormalizationTest.txt)
endif ()

# Define paths
set(VENV_DIR ${CMAKE_BINARY_DIR}/venv)
set(REQUIREMENTS_FILE ${CMAKE_BINARY_DIR}/requirements.txt)

if(WIN32)
    set(VENV_PYTHON ${VENV_DIR}/Scripts/python.exe)
    set(VENV_PIP ${VENV_DIR}/Scripts/pip.exe)
else()
    set(VENV_PYTHON ${VENV_DIR}/bin/python)
    set(VENV_PIP ${VENV_DIR}/bin/pip)
endif()

# Content of requirements.txt
file(WRITE ${REQUIREMENTS_FILE} "lxml\npystache\n")

# Custom command to set up the virtual environment and install packages
# Custom command to set up the virtual environment and install packages
add_custom_command(
        OUTPUT ${VENV_PYTHON}  # This ensures the venv only gets created once
        COMMAND ${PYTHON_EXECUTABLE} -m venv ${VENV_DIR}  # Create virtual environment
        COMMAND ${VENV_PIP} install -r ${REQUIREMENTS_FILE}  # Install packages
        COMMENT "Setting up virtual environment"
        DEPENDS ${REQUIREMENTS_FILE}
)

# Command to generate normalization data using the virtual environment
add_custom_command(
        OUTPUT ${CMAKE_BINARY_DIR}/generated/normalization_data.cpp
        COMMAND ${VENV_PYTHON} ${PROJECT_SOURCE_DIR}/gen_normalization_table.py
        DEPENDS
        ${PROJECT_SOURCE_DIR}/gen_normalization_table.py
        ${PROJECT_SOURCE_DIR}/tpl/normalization_data.cpp.tpl
        ${PROJECT_SOURCE_DIR}/ucd/ucd.all.flat.xml
        ${VENV_PYTHON}  # Ensure venv setup is run first
        COMMENT "Generating normalization data"
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
)

# Add a target to run the generation command
add_custom_target(generate_normalization_data ALL
        DEPENDS ${CMAKE_BINARY_DIR}/generated/normalization_data.cpp
)

add_library(cedilla STATIC
        gen_normalization_table.py
        tpl/normalization_data.cpp.tpl
        ${CMAKE_BINARY_DIR}/generated/normalization_data.cpp
        include/cedilla/normalization.hpp
        include/cedilla/detail/hangul.hpp
        include/cedilla/detail/normalization_view.hpp
        include/cedilla/detail/unicode_base_view.hpp
        third_party/text_view-range-v3/src/error_status.cpp
)
target_link_libraries(cedilla)
target_compile_features(cedilla PUBLIC cxx_std_17)

target_include_directories(cedilla PUBLIC
        ${Boost_INCLUDE_DIRS}
        include
        ${CMAKE_BINARY_DIR}/generated/include
        third_party/range-v3/include
        third_party/text_view-range-v3/include
)

add_subdirectory(tests)
