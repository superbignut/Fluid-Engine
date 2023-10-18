#ifndef INCLUDE_BIG_FIELD2_H_
#define INCLUDE_BIG_FIELD2_H_

#include <memory>

namespace big{

class Field2{
    public:
        Field2();

        virtual ~Field2();
};

typedef std::shared_ptr<Field2> Field2Ptr;
}

#endif