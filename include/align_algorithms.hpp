#pragma once 

#include "fasta_entry.hpp"
#include "string"

struct PairwiseOutput{
    std::string first;
    std::string second; 
    long int score;
};

PairwiseOutput pairwise_local_alignment(FastaEntry firstSequence, FastaEntry secondSequence);

