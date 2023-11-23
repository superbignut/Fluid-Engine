#include <iostream>
namespace big
{
    template <typename T>
    void bout(T &&vec)
    {
        for (auto &el : vec)
        {
            std::cout << el << " ";
        }
        std::cout << std::endl;
    }

}