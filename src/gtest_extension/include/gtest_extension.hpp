
#ifndef GTEST_EXTENSION_HPP
#define GTEST_EXTENSION_HPP

#include <filesystem>
#include <gmock/gmock.h>

using namespace testing;
namespace fs = std::filesystem;

class GTestExtension : public ::testing::Test {
protected:
    static inline fs::path    testExecutablePath;
    static inline fs::path    testExecutableDirPath;
    static inline fs::path    testOutputDirPath;
    static inline std::string testSuiteName;
    std::string               testFullName;

public:
    static void  SetUpTestSuite();
    static void  TearDownTestSuite();
    virtual void SetUp() override;
    virtual void TearDown() override;

    static void initTestSuiteName();
    static void initTestSuitePaths();
    void        initTestFullName();
    std::string prepareCommandWithArguments(fs::path executable, const std::vector<std::string> &args);
};

#endif  // GTEST_EXTENSION_HPP
