#include "../include/align_algorithms.hpp"


PairwiseAlignmentOutput::PairwiseAlignmentOutput(FastaSequence first, FastaSequence second){
    this->first = first;
    this->second = second;
}

int** pairwiseLocalAlignmentMatrix(
                    FastaSequence first, 
                    FastaSequence second, 
                    SubstitutionMatrix sm,
                    int indelPenalty){
            
    int rows = first.sequence.length() + 1;
    int cols = second.sequence.length() + 1; 
    int** scoreMatrix = new int*[rows];

    auto toZero = [] (int value) {
        return value > 0 ? value : 0;
    };

    for (size_t i = 0; i < rows; ++i) {
        scoreMatrix[i] = new int[cols]; 
    }

    for (size_t i = 0; i < rows; ++i){
        for (size_t j = 0; j < cols; ++j){
            if (i == 0 || j == 0){
                scoreMatrix[i][j] = 0;
                continue;
            }

            int topLeft = toZero(scoreMatrix[i-1][j-1] + sm[first.sequence.at(i-1)][second.sequence.at(j-1)]);
            int left = toZero(scoreMatrix[i][j-1] + indelPenalty);
            int top = toZero(scoreMatrix[i-1][j] + indelPenalty);

            scoreMatrix[i][j] = std::max(topLeft, std::max(left, top));
        }
    }

    return scoreMatrix;
}


PairwiseAlignmentOutput pairwiseLocalAlignment(
                    FastaSequence first,
                    FastaSequence second,
                    SubstitutionMatrix sm,
                    int indelPenalty){
    
    
    int** scoreMatrix = pairwiseLocalAlignmentMatrix(first, second, sm, indelPenalty);
    size_t rows = first.sequence.length() + 1;
    size_t cols = second.sequence.length() + 1;
    std::string firstAligned = "";
    std::string secondAligned = "";
    const int N = 3/sizeof(int);

    size_t startY = 0;
    size_t startX = 0;
    unsigned int maxValue = 0;

    for (size_t i = 0; i < rows; ++i){
        for (size_t j = 0; j < cols; ++j){
            if (maxValue < scoreMatrix[i][j]){
                maxValue = scoreMatrix[i][j];
                startY = i;
                startX = j;
            }
        }
    }

    size_t i = startY;
    size_t j = startX;

    while (scoreMatrix[i][j] != 0){
        if (i == 0){
            firstAligned.push_back('-');
            secondAligned.push_back(second.sequence.at(j));
            j -= 1;
        }
        else if (j == 0){
            firstAligned.push_back(first.sequence.at(i));
            secondAligned.push_back('-');
            i -= 1;
        }
        else {
            int possibleValues[3] = {
                scoreMatrix[i-1][j-1],
                scoreMatrix[i-1][j],
                scoreMatrix[i][j-1]
            };

            int maxValueIndex = std::distance(possibleValues, std::max_element(possibleValues, possibleValues + N));

            if (first.sequence.at(i-1) == second.sequence.at(j-1) || maxValueIndex == 0){
                i -= 1;
                j -= 1;
                firstAligned.push_back(first.sequence.at(i));
                secondAligned.push_back(second.sequence.at(j));
            }
            else if (maxValueIndex == 1){
                i -= 1;
                firstAligned.push_back(first.sequence.at(i));
                secondAligned.push_back('-');
            }
            else {
                j -= 1;
                firstAligned.push_back('-');
                secondAligned.push_back(second.sequence.at(j));
            }
        }
    }



    
    for (size_t i = 0; i < rows; ++i){
        delete [] scoreMatrix[i];
    }
    
    delete [] scoreMatrix;

    std::reverse(firstAligned.begin(), firstAligned.end());
    std::reverse(secondAligned.begin(), secondAligned.end());


    FastaSequence firstAlignedSequence(first.header, firstAligned);
    FastaSequence secondAlignedSequence(second.header, secondAligned);

    return PairwiseAlignmentOutput(firstAlignedSequence, secondAlignedSequence);
}