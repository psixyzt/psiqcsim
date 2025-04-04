// psi.h

#ifndef PSI_H
#define PSI_H

#include <iostream>
#include <complex>
#include <vector>
#include <algorithm>

namespace psi{
    class State{
    public:
        std::complex<double>* vec;
        int n, dim;
        State(std::complex<double> vec[], int n);
        State(const std::string& name);
        State(const State& state);
        State& operator=(const State& state);
        ~State();
        bool operator==(const State& state);
        bool operator!=(const State& state);
        friend std::ostream& operator<<(std::ostream& os, const State& state);
        friend State operator*(std::complex<double> c, const State& state);
    };
        
    class Gate{
    public:
        std::complex<double>** mat;
        int n, dim;
        Gate(std::complex<double>** mat, int n);
        Gate(const std::string& name);
        Gate(const Gate& gate);
        Gate& operator=(const Gate& other);
        ~Gate();
        Gate operator*(const Gate& gate);
        State operator*(const State& state);
        bool operator==(const Gate& gate);
        bool operator!=(const Gate& gate);
        friend Gate operator*(std::complex<double> c, const Gate& gate);
        friend std::ostream& operator<<(std::ostream& os, const Gate& gate);
    };
}

#endif  