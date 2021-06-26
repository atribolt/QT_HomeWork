#pragma once

#include <cmath>
#include <vector>
#include <chrono>
#include <functional>

using WaveFunction = std::function<double(double X, 
                                          double amplitutde,
                                          double biasX,
                                          double biasY,
                                          double frequesnce)>;

#define WaveFunctionDef [](double X,                           \
                           double amplitude = 1.f,             \
                           double biasX = 0.f,                 \
                           double biasY = 0.f,                 \
                           double frequence = 1.f) -> double

namespace Waves {
  inline WaveFunction WaveSinus = WaveFunctionDef {
    return amplitude * std::sin(frequence * X + biasX) + biasY;
  };
  
  inline WaveFunction WaveDigist01 = WaveFunctionDef {
    static auto time = std::chrono::high_resolution_clock::now();
    
    long long dt = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - time).count();
    X = std::copysign(dt % 2000 - 1000, X); 
      
    return amplitude * (frequence * X + biasX) + biasY;
  };
  
  inline WaveFunction WaveCosinus = WaveFunctionDef {
    return amplitude * std::cos(frequence * X + biasX) + biasY;
  };
}

#undef WaveFunctionDef
