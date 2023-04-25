#include <iostream>
#include <vector>
#include <fstream>


std::vector<std::vector<uint64_t> > parce(const std::string &path, uint16_t width, uint16_t height);

void realization(std::vector<std::vector<uint64_t> > &ASM, uint16_t width, uint16_t height);

bool is_stable(std::vector<std::vector<uint64_t> > &ASM, uint16_t width, uint16_t height);

