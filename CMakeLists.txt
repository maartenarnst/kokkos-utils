cmake_minimum_required(VERSION 3.23)

#---- Read the version file.
file(READ version.json VERSION_JSON)

string(JSON KOKKOS_UTILS_VERSION GET "${VERSION_JSON}" "kokkos-utils" "value")

string(JSON Doxygen_REQUIRED_VERSION GET "${VERSION_JSON}" dependencies doxygen    value)
string(JSON GTest_REQUIRED_VERSION   GET "${VERSION_JSON}" dependencies googletest value)
string(JSON Kokkos_REQUIRED_VERSION  GET "${VERSION_JSON}" dependencies kokkos     value)

#---- Define the project. It uses C++ only.
project(
    kokkos-utils
    VERSION ${KOKKOS_UTILS_VERSION}
    LANGUAGES CXX
)

#---- Options.
option(KokkosUtils_ENABLE_TESTS "Enable testing" ON)
option(KokkosUtils_ENABLE_DOC   "Enable documentation" ON)

#---- Global property that helps us keep track of files that will automatically be added
#     to our Doxygen documentation.
define_property(GLOBAL PROPERTY KokkosUtils_FILES_FOR_DOC
    BRIEF_DOCS "Files that will be added to the Doxygen documentation."
)

#---- Find Kokkos.
#
# Currently, we require the Kokkos::kokkoscore target. Other targets will be added as needed.
if(NOT TARGET Kokkos::kokkoscore)
    find_package(
        Kokkos
        ${Kokkos_REQUIRED_VERSION}
        CONFIG
        REQUIRED
    )
#else()
    #if(NOT Kokkos_VERSION VERSION_GREATER_EQUAL Kokkos_REQUIRED_VERSION)
    #    message(FATAL_ERROR "Kokkos version should be at least ${Kokkos_REQUIRED_VERSION}.")
    #endif()
endif()

#---- Find Google Test.
#
# Currently, we require the GTest::gtest_main target. Other targets will be added as needed.
if(NOT TARGET GTest::gtest_main)
    find_package(
        GTest
        ${GTest_REQUIRED_VERSION}
        CONFIG
        REQUIRED
    )
#else()
    #if(NOT GTest_VERSION VERSION_GREATER_EQUAL GTest_REQUIRED_VERSION)
    #    message(FATAL_ERROR "Google Test version should be at least ${GTest_REQUIRED_VERSION}.")
    #endif()
endif()

#---- Build the Kokkos::utils library.
add_library(KokkosUtils INTERFACE)
add_library(Kokkos::utils ALIAS KokkosUtils)

target_sources(
    KokkosUtils
    INTERFACE
        include/kokkos-utils/concepts/View.hpp
)

target_include_directories(
    KokkosUtils
    INTERFACE
        "include/"
)

target_compile_features(
    KokkosUtils
    INTERFACE
        cxx_std_20
)

target_compile_definitions(
    KokkosUtils
    INTERFACE
        KOKKOS_IMPL_PUBLIC_INCLUDE
)

#---- Testing.
if(KokkosUtils_ENABLE_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

#---- Documentation.
if(KokkosUtils_ENABLE_DOC)
    add_subdirectory(docs)
endif()
