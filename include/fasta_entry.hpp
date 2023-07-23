#pragma once

#include <string>

class FastaEntry{
    public:
        std::string header;
        std::string sequence;

    FastaEntry(std::string header, std::string sequence);
};