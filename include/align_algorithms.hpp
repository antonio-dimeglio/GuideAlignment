#pragma once 

#include "fasta_sequence.hpp"
#include <string>
#include "sub_matrix.hpp"
#include "boost/multi_array.hpp"
#include <algorithm>

struct PairwiseAlignmentOutput{
    FastaSequence first;
    FastaSequence second;

    PairwiseAlignmentOutput() = default;

    PairwiseAlignmentOutput(FastaSequence first, FastaSequence second);
};

int** pairwiseLocalAlignmentMatrix(
    FastaSequence first, 
    FastaSequence second, 
    SubstitutionMatrix sm,
    int indelPenalty
);

PairwiseAlignmentOutput pairwiseLocalAlignment(
    FastaSequence first,
    FastaSequence second,
    SubstitutionMatrix sm,
    int indelPenalty
);