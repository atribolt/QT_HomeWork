#include "signal.h"

#include <QtMath>

Emulator::SimpleWave::SimpleWave(
          wave_fun func
        , float amplitude
        , float biasOY
        , float frequence
        , float biasOX    )
{
    wave = func;

    this->biasOY    = biasOY   ;
    this->biasOX    = biasOX   ;
    this->amplitude = amplitude;
    this->frequence = frequence;
}
