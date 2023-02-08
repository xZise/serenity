set(TEST_SOURCES
    TestBasicTokenizer.cpp
    TestBasicParser.cpp
    TestBasicInterpreter.cpp
)

foreach(source IN LISTS TEST_SOURCES)
    serenity_test("${source}" LibBASIC LIBS LibBASIC)
endforeach()
