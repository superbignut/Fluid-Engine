#ifndef INCLUDE_BIG_FIELD3_H_
#define INCLUDE_BIG_FIELD3_H_

#include <memory>

namespace big{

class Field3{
    public:
        Field3();

        virtual ~Field3();
};

typedef std::shared_ptr<Field3> Field3Ptr;
}

    


#endif