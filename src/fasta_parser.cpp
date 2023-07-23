#include "../include/fasta_parser.hpp"

FastaParser::FastaParser(std::string filePath){
    this->filePath = filePath;
}

std::vector<FastaEntry> FastaParser::parseFile(){
    std::vector<FastaEntry> sequences;
    fs::ifstream fileHandler(this->filePath);
    std::string line;
    std::string header; 
    std::string sequence;
    

    while(getline(fileHandler, line)) {
        boost::trim_right(line);
        switch (line.at(0)){
            case ';':
                continue;
            case '>':
                if (!header.empty()){
                    sequences.push_back(FastaEntry(header, sequence));
                    sequence.clear();
                }

                header = line.substr(1);

            default:
                sequence.append(line);
                break;
        }
    }

    if (!sequence.empty()){
        sequences.push_back(FastaEntry(header, sequence));
    }

    return sequences;
}