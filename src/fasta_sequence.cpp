#include "../include/fasta_sequence.hpp"

FastaSequence::FastaSequence(std::string header, std::string sequence){
    this->header = header;
    this->sequence = sequence;
}