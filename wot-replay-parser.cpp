// wot-replay-parser.cpp

#include <fstream>
#include <iostream>

#include "parser.hpp"
#include "Version.hpp"

namespace WRP = WotReplayParser;

int main(int argc, char** argv)
{
	std::cout << "Herro worrdo!" << std::endl;

    std::ifstream in("G:\\test2.wotreplay", std::ios::binary);

    WRP::Parser parser;
    parser.parse(in);

	return EXIT_SUCCESS;
}