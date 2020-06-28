#ifndef SIGNAL_H
#define SIGNAL_H

#include <functional>

namespace Emulator {

template<class _TOut, class ...Args>
    class Signal {
    public:
        using type_out = _TOut;
        using wave_fun = std::function<type_out(Args...)>;

    public:
        Signal(wave_fun signal_function) {
            wave = signal_function;
        }

        type_out operator()(Args const& ...args) {
            return wave(args...);
        }

    public:
        wave_fun wave;
    };

//                                out     x      B      A      C      D
class SimpleWave : public Signal<float, float, float, float, float, float> {
    /*
     * х - входное значение
     * A - амплитуда
     * B - сдвиг по Oy
     * C - частота
     * D - сдвиг по Ox (начальная фаза)
     */

public:
    SimpleWave(wave_fun wave, float A = 1, float B = 0, float C = 1, float D = 0);

    type_out operator()(float X) const {
        return wave(X, B, A, C, D);
    }

    void SetAmplitude(float val) noexcept { A = val; }
    void SetShiftOy  (float val) noexcept { B = val; }
    void SetFrequence(float val) noexcept { C = val; }
    void SetShiftOx  (float val) noexcept { D = val; }

    float GetAmplitude() const noexcept { return A; }
    float GetShiftOy  () const noexcept { return B; }
    float GetFrequence() const noexcept { return C; }
    float GetShiftOx  () const noexcept { return D; }
private:
    float A
        , B
        , C
        , D;
};

}

#endif // SIGNAL_H
