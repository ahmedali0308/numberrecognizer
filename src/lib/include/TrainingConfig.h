#pragma once

struct TrainingConfig {
    int hiddenLayers;
    int epochs;
    float learningRate;
    int neuronsPerLayer;
    int activationFunc;
};