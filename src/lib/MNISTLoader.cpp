#include <../include/MNISTLoader.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>

std::vector<MNISTSample> MNISTLoader::loadFromCSV(const std::string& filepath, int maxSamples) {
    std::vector<MNISTSample> dataset;
    std::ifstream file(filepath);
    
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filepath);
    }
    
    std::string line;
    bool isFirstLine = true;
    int sampleCount = 0;
    
    std::cout << "Loading MNIST data from: " << filepath << std::endl;
    
    while (std::getline(file, line)) {
        if (isFirstLine) {
            isFirstLine = false;
            if (line.find("label") != std::string::npos || !std::isdigit(line[0])) {
                continue;
            }
        }
        
        // Parse CSV line
        std::stringstream ss(line);
        std::string value;
        
        // Read label
        std::getline(ss, value, ',');
        int label = std::stoi(value);
        
        // Read pixels
        Matrix image(784, 1);
        int pixelIndex = 0;
        
        while (std::getline(ss, value, ',') && pixelIndex < 784) {
            float pixelValue = std::stof(value);
            image(pixelIndex, 0) = pixelValue;
            pixelIndex++;
        }
        
        normalizeImage(image);
        
        dataset.emplace_back(image, label);
        sampleCount++;
        
        // For debugging
        if (sampleCount % 10000 == 0) {
            std::cout << "Loaded " << sampleCount << " samples..." << std::endl;
        }
        
        if (maxSamples > 0 && sampleCount >= maxSamples) {
            break;
        }
    }
    
    file.close();
    std::cout << "Successfully loaded " << dataset.size() << " samples!" << std::endl;
    
    return dataset;
}

Matrix MNISTLoader::createOneHot(int label, int numClasses) {
    if (label < 0 || label >= numClasses) {
        throw std::invalid_argument("Label out of range");
    }
    
    Matrix oneHot(numClasses, 1);
    
    for (int i = 0; i < numClasses; i++) {
        oneHot(i, 0) = 0.0f;
    }
    
    oneHot(label, 0) = 1.0f;
    
    return oneHot;
}

void MNISTLoader::normalizeImage(Matrix& image) {
    for (int i = 0; i < 784; i++) {
        image(i, 0) = image(i, 0) / 255.0f;
    }
}