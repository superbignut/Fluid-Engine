#ifndef INCLUDE_BIG_MACROS_H_
#define INCLUDE_BIG_MACROS_H_

#include <stdexcept>

#define BIG_THROW_INVALID_ARG_IF(expression) \
    if(expression) {throw std::invalid_argument(#expression);}
    
#define BIG_THROW_INVALID_ARG_WITH_MESSAGE_IF(expression, message) \
    if(expression) {throw std::invalid_argument(message);}


#endif