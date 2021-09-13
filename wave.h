#ifndef WAVE_H
#define WAVE_H

#endif // WAVE_H

class wave {
private:
    double amplitude;
    double frequency;
    double phase;

    wave (){}

    wave(double amp, double frq, double phs) {
        amplitude = amp;
        frequency = frq;
        phase = phs;
    }

public:
    double get_amplitude();
    double get_frequency();
    double get_phase();
};
