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

    desc.add_options()
        ("help,h", "Produce help message")
        ("input-file,i", po::value<std::string>(), "Input FASTA file, required")
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

    FastaParser fp(inputFile);
    auto sequences = fp.parseFile();

    FastaSequence first = sequences.at(0);
    FastaSequence second = sequences.at(1);

    auto result = pairwiseLocalAlignment(first, second, Nucleotide, -2);

    std::cout << 
        result.first.header << '\n' <<
        result.first.sequence << '\n' << 
        result.second.header << '\n' << 
        result.second.sequence << '\n';

    return 0;
}