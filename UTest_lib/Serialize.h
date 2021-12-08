#ifndef UTEST_SERIALIZE_H
#define UTEST_SERIALIZE_H

namespace Serialize {

    template <typename T>
    void serialize(const T & valueToSerialize);

    template <typename TYPE>
    TYPE deserialize();
}

#endif
