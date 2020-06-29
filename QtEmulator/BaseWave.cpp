#include "BaseWave.hpp"

#include <QtMath>
#include <QRandomGenerator>
#include <chrono>


float SinusWave (float x, float b, float a, float c, float d) {
    float res = 0.f;
    res = b + a * sinf( c*x + d );
    return res;
};
Emulator::Sinusoida::Sinusoida()
    : SimpleWave(SinusWave) {}


float CosinusWave (float x, float b, float a, float c, float d) {
    float res = 0.f;
    res = b + a * cosf(c*x + d);
    return res;
};
Emulator::Cosinusoida::Cosinusoida()
    : SimpleWave(CosinusWave) {}


float RandWave (float x, float b, float a, float c, float d) {
    using std::chrono::duration_cast;
    using std::chrono::milliseconds;
    using std::chrono::system_clock;

    float res = 0.f;
    QRandomGenerator rg( duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() );

    b = rg.bounded( 80, 150 ) / 100;
    a = rg.bounded( 80, 150 ) / 100;
    c = rg.bounded( 80, 150 ) / 100;

    res = b + a * cosf(c*x + d);

    return res;
};

Emulator::RandomWave::RandomWave()
    : SimpleWave(RandWave)
{}
