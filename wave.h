#ifndef WAVE_H
#define WAVE_H

#endif // WAVE_H

class wave {
private:
    double amplitude;
    double frequency;
    double phase;
    double kvalue;


public:
    wave (){
    amplitude = 1;
    frequency = 1;
    phase = 0;
    kvalue=1;
    }
    wave(double amp, double frq, double phs, double k) {
        amplitude = amp;
        frequency = frq;
        phase = phs;
        kvalue = k;
    }
    void set_amplitude(double amp);
    void set_kvalue(double k);
    void set_frequency(double frq);
    void set_phasee(double ph);
    double get_kvalue();
    double get_amplitude();
    double get_frequency();
    double get_phase();
};
