#ifndef BIG_MANUAL_TESTS_H_
#define BIG_MANUAL_TESTS_H_

#include "array_accessor1.h"
#include "array_accessor2.h"
#include "array_accessor3.h"
#include <cnpy.h>
#include <pystring.h>
// #include <gtest/gtest.h>
#include <fstream>
#include <memory>
#include <string>
#include <vector>
#include <sys/stat.h>


namespace big
{
    class sdata
    {
    public:
        inline static void creatDirectory(const std::string &dirname)
        {
            std::vector<std::string> tokens;
            pystring::split(dirname, tokens, "/");
            std::string partialDir;
            for (const auto &token : tokens)
            {
                partialDir = pystring::os::path::join(partialDir, token);
                mkdir(partialDir.c_str(), S_IRWXU | S_IRWXG | S_IRWXO);
            }
            
        }

        template <typename T>
        inline static void saveData(
            const ConstArrayAccessor1<T> &data,
            const std::string &dirname,
            const std::string &name)
        {
            std::string filename = pystring::os::path::join(dirname, name);
            std::vector<std::size_t> datashape = {static_cast<std::size_t>(data.size())};
            cnpy::npy_save(filename, data.data(), datashape, "w");
        }

    };

}

#endif