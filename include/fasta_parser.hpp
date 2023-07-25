#pragma once 

#include <string>
#include <vector>
#include "fasta_sequence.hpp"
#include <boost/filesystem/fstream.hpp>
#include <boost/algorithm/string.hpp>

namespace fs = boost::filesystem;

struct FastaParser{
    std::string filePath;

    FastaParser() = default;

    FastaParser(std::string filePath);
    std::vector<FastaSequence> parseFile();
};