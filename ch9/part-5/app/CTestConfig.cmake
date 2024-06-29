set(CTEST_PROJECT_NAME minimal-cmake)
set(CTEST_NIGHTLY_START_TIME 01:00:00 UTC)
set(SITE "minimal-cmake")

if(CMAKE_VERSION VERSION_GREATER 3.14)
  set(CTEST_SUBMIT_URL https://my.cdash.org/submit.php?project=minimal-cmake)
else()
  set(CTEST_DROP_METHOD "https")
  set(CTEST_DROP_SITE "my.cdash.org")
  set(CTEST_DROP_LOCATION "/submit.php?project=minimal-cmake")
endif()

set(CTEST_DROP_SITE_CDASH TRUE)
