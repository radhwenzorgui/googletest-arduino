#ifndef MY_FUNCTIONS_H
#define MY_FUNCTIONS_H
#ifndef ARDUINO
#include <vector>
void apply_gain(std::vector<int>& buffer, double gain);
#endif
int add(int x, int y);

#endif