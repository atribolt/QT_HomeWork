#ifndef SIGNAL_H
#define SIGNAL_H

//#include <functional>

namespace Emulator {

class SimpleWave {
     using wave_fun = float(*)(float, float, float, float, float);
    //              = std::function<float(float, float, float, float, float)>;

public:
    SimpleWave( wave_fun wave
              , float amplitude = 1
              , float biasOY    = 0
              , float frequence = 1
              , float biasOX    = 0);

    float operator()(float X) const {
        return wave( X
                   , biasOY
                   , amplitude
                   , frequence
                   , biasOX);
    }

    void SetAmplitude(float val) noexcept { amplitude  = val; }
    void SetShiftOy  (float val) noexcept { biasOY     = val; }
    void SetFrequence(float val) noexcept { frequence  = val; }
    void SetShiftOx  (float val) noexcept { biasOX     = val; }

    float GetAmplitude() const noexcept { return amplitude ; }
    float GetShiftOy  () const noexcept { return biasOY    ; }
    float GetFrequence() const noexcept { return frequence ; }
    float GetShiftOx  () const noexcept { return biasOX    ; }

    wave_fun wave;
private:
    float amplitude
        , biasOY
        , frequence
        , biasOX;
};

}

#endif // SIGNAL_H
