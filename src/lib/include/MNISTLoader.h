#pragma once

#include "matrix.h"
#include <vector>
#include <string>

struct MNISTSample {
    Matrix image; 
    int label; 
    
    MNISTSample(Matrix img, int lbl) : image(img), label(lbl) {}
};

class MNISTLoader {
public:
    std::vector<MNISTSample> loadFromCSV(const std::string& filepath, int maxSamples = -1);
    
    Matrix createOneHot(int label, int numClasses = 10);
    
    void normalizeImage(Matrix& image);
};
