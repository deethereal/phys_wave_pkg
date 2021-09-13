#ifndef WAVE_H
#define WAVE_H

#endif // WAVE_H

class wave {
private:
    double amplitude;
    double frequency;
    double phase;


public:
    wave (){
    amplitude = 1;
    frequency = 1;
    phase = 0;
    }
    wave(double amp, double frq, double phs) {
        amplitude = amp;
        frequency = frq;
        phase = phs;
    }
    void set_amplitude(double amp);
    void set_frequency(double frq);
    void set_phasee(double ph);
    double get_amplitude();
    double get_frequency();
    double get_phase();
};
