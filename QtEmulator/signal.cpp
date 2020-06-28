#include "signal.h"

#include <QtMath>

Emulator::SimpleWave::SimpleWave(
          wave_fun func
        , float A
        , float B
        , float C
        , float D )
    : Signal( func )
{
    this->A = A;
    this->B = B;
    this->C = C;
    this->D = D;
}
