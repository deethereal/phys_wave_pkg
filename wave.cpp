#include "wave.h"

double wave::get_amplitude()
{
    return amplitude;
}

double wave::get_frequency()
{
    return frequency;
}

double wave::get_phase()
{
    return phase;
}
double wave::get_kvalue()
{
    return kvalue;
}
void wave::set_amplitude(double amp)
{
    amplitude = amp;
}
void wave::set_frequency(double frq)
{
    frequency = frq;
}
void wave::set_phasee(double ph)
{
    phase = ph;
}
void wave::set_kvalue(double k)
{
    kvalue = k;
}
