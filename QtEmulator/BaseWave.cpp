#include "BaseWave.hpp"

#include <QtMath>
#include <QRandomGenerator>
#include <chrono>


static float SinusWave ( float x
                       , float biasOY
                       , float amplitud
                       , float freq
                       , float biasOX)
{
    float res = 0.f;
    res = biasOY + amplitud * sinf( freq*x + biasOX );
    return res;
};
Emulator::Sinusoida::Sinusoida()
    : SimpleWave(SinusWave) {}


static float CosinusWave ( float x
                         , float biasOY
                         , float amplitud
                         , float freq
                         , float biasOX)
{
    float res = 0.f;
    res = biasOY + amplitud * cosf(freq*x + biasOX);
    return res;
};
Emulator::Cosinusoida::Cosinusoida()
    : SimpleWave(CosinusWave) {}


static float RandWave ( float x
                      , float biasOY
                      , float amplitud
                      , float freq
                      , float biasOX)
{
    using std::chrono::duration_cast;
    using std::chrono::milliseconds;
    using std::chrono::system_clock;

    float res = 0.f;
    QRandomGenerator rg( duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() );

    biasOY   = rg.bounded( 80, 150 ) / 100;
    amplitud = rg.bounded( 80, 150 ) / 100;
    freq     = rg.bounded( 80, 150 ) / 100;

    res = biasOY + amplitud * cosf(freq*x + biasOX);

    return res;
};

Emulator::RandomWave::RandomWave()
    : SimpleWave(RandWave)
{}
