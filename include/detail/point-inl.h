#ifndef INCLUDE_BIG_POINT_INL_H
#define INCLUDE_BIG_POINT_INL_H

namespace big{

template <typename T, std::size_t N>
Point<T, N>::Point(){
    for (auto& elem : _elements){
        elem = static_cast<T>(0);
    }
}

}

#endif