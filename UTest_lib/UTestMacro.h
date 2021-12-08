#ifndef UTEST_UTESTMACRO_H
#define UTEST_UTESTMACRO_H

#define ASSERT_VALUES(x)                                                        \
if (!(x)) {                                                                     \
    throw AssertFailedException(__LINE__, #x);                                  \
}                                                                               \

#define NAME_CONCATENATION(begin, row) begin##row
#define CLASS_NAME(row) NAME_CONCATENATION(UTest, row)
#define INSTANCE_NAME(row) NAME_CONCATENATION(instance, row)
#define END_TEST } INSTANCE_NAME(__LINE__);
#define CONTAINER container() override
#define USER(param) void user(param) override

#define TEST(type, name)                                  \
class CLASS_NAME(__LINE__) : public UTest<type> {         \
public:                                                   \
    CLASS_NAME(__LINE__)() : UTest() {                    \
       this->run(name);                                   \
    }                                                     \
    type                                                  \


#endif
