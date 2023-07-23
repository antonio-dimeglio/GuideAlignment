#include "../include/fasta_entry.hpp"

FastaEntry::FastaEntry(std::string header, std::string sequence){
    this->header = header;
    this->sequence = sequence;
}