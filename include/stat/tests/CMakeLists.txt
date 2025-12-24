include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

add_executable(stat_tests
    probability/test_bayesian_posterior.cpp
)

target_link_libraries(stat_tests
    PRIVATE
        stat
        GTest::gtest
        GTest::gtest_main
)

target_compile_features(stat_tests PRIVATE cxx_std_20)

include(GoogleTest)
gtest_discover_tests(stat_tests)
