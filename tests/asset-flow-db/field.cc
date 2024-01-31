#include <gtest/gtest.h>

// #include "asset-flow-db/field.hpp"

// // Demonstrate some basic assertions.
// TEST(FieldClass, CheckSetValueByEqOperator) {
//     Field<int> f1("field1");
//     f1 = 10;
//     EXPECT_EQ(f1.get(), 10);
// }

// TEST(FieldClass, CheckSetValueByFunction) {
//     Field<int> f1("field1");
//     f1.set(20);
//     EXPECT_EQ(f1.get(), 20);
// }

// TEST(FieldClass, CheckEqFieldClass) {
//     Field<int> f1("field1");
//     f1.set(20);
//     Field<int> f2("field2");
//     f2 = 20;

//     auto res = f1 == f2;
//     EXPECT_TRUE(res.result);

// }
// TEST(FieldClass, CheckEqValue) {
//     Field<int> f1("field1");
//     f1.set(20);

//     auto res = f1 == 20;
//     EXPECT_TRUE(res.result);
// }
// TEST(FieldClass, CheckNonEqFieldClass) {
//     Field<int> f1("field1");
//     f1.set(20);
//     Field<int> f2("field2");
//     f2 = 20;

//     auto res = f1 != f2;
//     EXPECT_FALSE(res.result);
// }
// TEST(FieldClass, CheckNonEqValue) {
//     Field<int> f1("field1");
//     f1.set(20);

//     auto res = f1 != 20;
//     EXPECT_FALSE(res.result);
// }
