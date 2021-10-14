#ifndef MYAPPLICATION_SERIALIZE_H
#define MYAPPLICATION_SERIALIZE_H

#include <list>
//#include "../App_lib/Application.h"

namespace Serialize {

    template <typename T>
    void serialize(const T & valueToSerialize);

    template <typename TYPE>
    TYPE deserialize();
}

#endif
