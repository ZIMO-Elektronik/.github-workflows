include(GoogleTest)

file(GLOB_RECURSE SRC *.cpp)
add_executable(.github-workflowsTests ${SRC})

sanitize(address,undefined)

target_common_warnings(.github-workflowsTests PRIVATE)

cpmaddpackage(
  NAME
  googletest
  GITHUB_REPOSITORY
  "google/googletest"
  GIT_TAG
  main
  SYSTEM
  YES
  OPTIONS
  "INSTALL_GTEST OFF")

target_link_libraries(.github-workflowsTests
                      PRIVATE .github-workflows GTest::gtest_main GTest::gmock)

gtest_discover_tests(.github-workflowsTests)
