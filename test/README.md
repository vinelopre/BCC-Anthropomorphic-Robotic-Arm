
# UNIT TESTING

This directory is intended for PlatformIO Test Runner and project tests.

Unit Testing is a software testing method by which individual units of
source code, sets of one or more MCU program modules together with associated
control data, usage procedures, and operating procedures, are tested to
determine whether they are fit for use. Unit testing finds problems early
in the development cycle.

# DEFAULT TEST FOLDER STRUCTURE

|--test
|  |
|  |--ARDUINO_MEGA_2560_R3
|  |  |--include
|  |  |--lib
|  |  |--test_mega
|  |  |  |
|  |  |  |--test_mega1
|  |  |  |  |--test_mega1.cpp
|  |  |  |
|  |  |  |--test_mega2
|  |  |  |  |--test_mega2.cpp
|  |
|  |--ARDUINO_NANO
|  |  |--include
|  |  |--lib
|  |  |--test_nano
|  |  |  |
|  |  |  |--test_nano1
|  |  |  |  |--test_nano1.cpp
|  |  |  |
|  |  |  |--test_nano2
|  |  |  |  |--test_nano2.cpp
|  |
|  |--ARDUINO_UNO_R3
|  |  |--include
|  |  |--lib
|  |  |--test_uno
|  |  |  |
|  |  |  |--test_uno1
|  |  |  |  |--test_uno1.cpp
|  |  |  |
|  |  |  |--test_uno2
|  |  |  |  |--test_uno2.cpp
|  |
|  |--README.md << THIS FILE

>[!warning]
> Test structure can be changed by modifying the `test_filter` configuration in the `platformio.ini` file.
> If you would like to identify a specific test to be performed, you must create and/or specify the **folder name** containing that test.

# CREATING TESTS

Creating tests using PlatformIO can be a difficult task if your environment is not properly set up.

This program uses the Unity framework for all of its tests.

Documentation on PlatformIO Unit Testing, including the Unity framework, can be found here:
- https://docs.platformio.org/en/latest/advanced/unit-testing/index.html


