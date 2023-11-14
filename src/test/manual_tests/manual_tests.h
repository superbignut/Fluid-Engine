#ifndef BIG_MANUAL_TESTS_H_
#define BIG_MANUAL_TESTS_H_

#include "array_accessor1.h"
#include "array_accessor2.h"
#include "array_accessor3.h"
#include <cnpy.h>
#include <pystring.h>
#include <gtest/gtest.h>
#include <fstream>
#include <memory>
#include <string>
#include <vector>
#include <sys/stat.h>

#define BIG_TESTS_OUTPUT_DIR "manual_tests_output"

inline void creatDirectory(const std::string &dirname)
{
    std::vector<std::string> tokens;
    pystring::split(dirname, tokens, "/");
    std::string partialDir;
    for (const auto &token : tokens)
    {
        partialDir = pystring::os::path::join(partialDir, token);
    }
    mkdir(partialDir.c_str(), S_IRWXU | S_IRWXG | S_IRWXO);
}
inline void creatSubTestDirectory(const std::string &classname, const std::string &casename)
{
    std::string subTestDir = pystring::os::path::join(BIG_TESTS_OUTPUT_DIR, classname);
    creatDirectory(subTestDir);//first subDir

    std::string caseDir = pystring::os::path::join(subTestDir, casename);
    // std::cout << caseDir;
    creatDirectory(caseDir);//second subDir       
}

#define BIG_TESTS(testSetName)                                                            \
    class testSetName##Tests : public ::testing::Test                                     \
    {                                                                                     \
    private:                                                                              \
        std::string _testCollectionDir;                                                   \
        std::string _currentTestCaseName;                                                 \
        std::string _currentTestDir;                                                      \
                                                                                          \
    protected:                                                                            \
        void SetUp() override                                                             \
        {                                                                                 \
            _testCollectionDir = pystring::os::path::join(                                \
                BIG_TESTS_OUTPUT_DIR, #testSetName);                                      \
            creatDirectory(_testCollectionDir);                                           \
        }                                                                                 \
        void creatTestDirectory(const std::string &name)                                  \
        {                                                                                 \
            _currentTestDir = pystring::os::path::join(_testCollectionDir, name);         \
            creatDirectory(_currentTestDir);                                              \
        }                                                                                 \
        std::string getFullFilePath(const std::string &name)                              \
        {                                                                                 \
            if (!_currentTestDir.empty())                                                 \
            {                                                                             \
                return pystring::os::path::join(_currentTestDir, name);                   \
            }                                                                             \
            else                                                                          \
            {                                                                             \
                return name; /*false return */                                            \
            }                                                                             \
        }                                                                                 \
        template <typename T>                                                             \
        void saveData(                                                                    \
            const ConstArrayAccessor1<T> &data,                                           \
            const std::string &name)                                                      \
        {                                                                                 \
            std::string filename = getFullFilePath(name);                                 \
            std::vector<std::size_t> datashape = {static_cast<std::size_t>(data.size())}; \
            cnpy::npy_save(filename, data.data(), datashape, "w");                        \
        }                                                                                 \
    };

#define BIG_BEGIN_TEST_F(testSetName, testCaseName) \
    TEST_F(testSetName##Tests, testCaseName)        \
    {                                               \
        creatTestDirectory(#testCaseName);

#define BIG_END_TEST_F }




#endif