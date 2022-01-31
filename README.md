This framework is based on executing code (functions) in Docker
container, which means Docker has to be installed on your device.

Main essence of this framework consist of macro which allows user
to make unit tests safer for his device.

Example of code (for test) : 

```c++
int sum(int a, int b) {
    return a+b
}
```

Example of unit test (via framework Macro) :

```c++
TEST(int, "TEST_SUM")
    CONTAINER {
        return sum(2,3);
    }
    WINDOWS(int realValue) {
        int expectedValue{21};
        ASSERT_VALUES(realValue == expectedValue)
    }
END_TEST
```

Whole project was made as my bachelor thesis.<br>
Many thanks to Ing. Vladislav Novák for his help and advice during
development process.

University : STU <br>
Faculty : FEI <br>
Authors : Tomáš Koštrna <br>
Leader : Ing. Vladislav Novák


