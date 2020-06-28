#ifndef SINUSOIDA_H
#define SINUSOIDA_H

#include "signal.h"

namespace Emulator {
    class Sinusoida final : public SimpleWave {
    public:
        Sinusoida();
    };

    class Cosinusoida final : public SimpleWave {
    public:
        Cosinusoida();
    };

    class RandomWave final : public SimpleWave {
    public:
        RandomWave();
    };
}

#endif // SINUSOIDA_H
