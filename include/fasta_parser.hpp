#pragma once 

#include <string>
#include <vector>
#include "fasta_entry.hpp"
#include <boost/filesystem/fstream.hpp>
#include <boost/algorithm/string.hpp>

namespace fs = boost::filesystem;

class FastaParser{
    public:
        std::string filePath;

        FastaParser(std::string filePath);
        std::vector<FastaEntry> parseFile();
};