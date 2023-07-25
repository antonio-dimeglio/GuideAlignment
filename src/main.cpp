#include <iostream>
#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>

#include "../include/fasta_sequence.hpp"
#include "../include/fasta_parser.hpp"
#include "../include/align_algorithms.hpp"
#include "../include/sub_matrix.hpp"

namespace po = boost::program_options;
namespace fs = boost::filesystem;

int main(int argc, char* argv[]){
    po::options_description desc("Allowed options");
    std::string inputFile = "";
    std::string outputFile = "output.fa";
    std::string sequenceType = "";

    desc.add_options()
        ("help,h", "Produce help message")
        ("input-file,i", po::value<std::string>(), "Input FASTA file, required")
        ("type-t", po::value<std::string>(), "Are the sequences nucleotides or aminoacids?, required, value can be nucl or aa")
        ("output-file,o", po::value<std::string>(), "Output .fa file, default value is output.fa");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help") || argc == 1) {
        std::cout << desc << std::endl;
        return 0;
    }

    if (vm.count("input-file")) {
        inputFile = vm["input-file"].as<std::string>();
    } else {
        std::cerr << "Missing input file path.\n";
        return 1;
    }

    if (!fs::exists(inputFile)){
        std::cerr << "The file " << inputFile << " was not found.\n";
        return 2;
    }

    if (vm.count("output-file")) {
        outputFile = vm["output-file"].as<std::string>();
    }

    if (vm.count("type")){
        sequenceType = vm["type"].as<std::string>();

        if (sequenceType != "nucl" || sequenceType != "aa"){
            std::cerr << "Unsupported sequence type: " << 
                sequenceType << "\n";
            exit(1);
        }

    } else{
        std::cerr << "Cannot run, did not specify sequence type\n";
        exit(1);
    }

    FastaParser fp(inputFile);
    auto sequences = fp.parseFile();

    FastaSequence first = sequences.at(0);
    FastaSequence second = sequences.at(1);
    SubstitutionMatrix sm;

    if (sequenceType == "nucl"){sm = Nucleotide;}
    else {sm = BLOSUM62;}    
    
    auto result = pairwiseLocalAlignment(first, second, BLOSUM62, -2);

    std::cout << 
        result.first.header << '\n' <<
        result.first.sequence << '\n' << 
        result.second.header << '\n' << 
        result.second.sequence << '\n';

    return 0;
}