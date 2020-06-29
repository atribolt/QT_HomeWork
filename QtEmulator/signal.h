#ifndef SIGNAL_H
#define SIGNAL_H

#include <functional>

namespace Emulator {

//template<class _TOut, class ...Args>
//    class Signal {
//    public:
//        using type_out = _TOut;
//        using wave_fun = std::function<type_out(Args...)>;
//
//    public:
//        Signal(wave_fun signal_function) {
//            wave = signal_function;
//        }
//
//        type_out operator()(Args const& ...args) {
//            return wave(args...);
//        }
//
//    public:
//        wave_fun wave;
//    };

//

class SimpleWave {
     using wave_fun = std::function<float(float, float, float, float, float)>;

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
