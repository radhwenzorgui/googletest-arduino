#if !defined(ARDUINO)
#include <gtest/gtest.h>
#include "math.hpp"  // This should contain the declaration of `add(int, int)`

#include <iostream>
#include <nlohmann/json.hpp>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    if(RUN_ALL_TESTS());
    return 0;
}
namespace {
 
struct Test {
    int a;
    int b;
    int sum;
};
 
class CalculatorParameterizedTest : public testing::TestWithParam<Test> {
};

// Unit tests
TEST_P(CalculatorParameterizedTest, BasicCases) {


    EXPECT_EQ(add(GetParam().a, GetParam().b), GetParam().sum) << "sum of " <<GetParam().a << "and " << GetParam().b << "differ from expected" << GetParam().sum;
}


inline void from_json(const nlohmann::json& j, Test& test)
{
    j.at("a").get_to(test.a);
    j.at("b").get_to(test.b);
    j.at("sum").get_to(test.sum);
}
 
std::vector<Test> GetTests(const std::string& path)
{
    std::ifstream input(path);
    nlohmann::json j;
    input >> j;
    return j.get<std::vector<Test>>();
}
 
INSTANTIATE_TEST_SUITE_P(
    Json,
    CalculatorParameterizedTest,
    testing::ValuesIn(GetTests("C:\\Users\\radhwenzorgui\\Documents\\PlatformIO\\Projects\\googletest-arduino\\test\\test_dummy\\input.json")),
    [](const testing::TestParamInfo<Test>& info)      { std::stringstream ss;
        ss << "Case_" << info.index << "_" << info.param.a << "_" << info.param.b << "_Expect_" << info.param.sum;
        return ss.str();
    }
);
// --- New code: buffer/gain tests ---
struct TestBuffer {
    std::vector<int> input;
    double gain;
    std::vector<int> expected;
};

inline void from_json(const nlohmann::json& j, TestBuffer& tb)
{
    j.at("input").get_to(tb.input);
    j.at("gain").get_to(tb.gain);
    j.at("expected").get_to(tb.expected);
}

std::vector<TestBuffer> GetBufferTests(const std::string& path)
{
    std::ifstream input(path);
    nlohmann::json j;
    input >> j;
    return j.get<std::vector<TestBuffer>>();
}

class BufferParameterizedTest : public testing::TestWithParam<TestBuffer> {
};

TEST_P(BufferParameterizedTest, AppliesGainCorrectly) {
    TestBuffer params = GetParam();
    std::vector<int> actual = params.input; // copy
    apply_gain(actual, params.gain);
    EXPECT_EQ(actual, params.expected);
}

} // namespace


// Instantiate the new buffer tests
INSTANTIATE_TEST_SUITE_P(
    JsonBuffer,
    BufferParameterizedTest,
    testing::ValuesIn(GetBufferTests("C:\\Users\\radhwenzorgui\\Documents\\PlatformIO\\Projects\\googletest-arduino\\test\\test_dummy\\input_buffer.json")),
    [](const testing::TestParamInfo<TestBuffer>& info) {
        std::stringstream ss;
        ss << "BufCase_" << info.index << "_gain";
        return ss.str();
    }
);

TEST(addTest, AddsNegativeNumbers) {
    EXPECT_EQ(add(-2, -3), -5 ) << "sum of  -2 and -3  = "<< add(-2, -3) << "differ from 0 ";
}

TEST(addTest, AddsMixedNumbers) {
    EXPECT_EQ(add(-2, 3), 1);
}




#endif

