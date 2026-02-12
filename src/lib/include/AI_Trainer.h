#pragma once 
#include <SFML/Graphics.hpp>
#include <tuple>
#include <vector>
#include <string>
#include <iostream>
#include "NeuralNetwork.h"
#include "TrainingConfig.h"

NeuralNetwork Render_AI__Trainer_Window(sf::Color, sf::Color, sf::Font&);