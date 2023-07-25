#pragma once

#include <string>

struct FastaSequence{
    std::string header;
    std::string sequence;

    FastaSequence() = default;

    FastaSequence(std::string header, std::string sequence);
};