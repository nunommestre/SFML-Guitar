// Copyright [2021] Nuno Mestre
#include "StringSound.h"

StringSound::StringSound(double frequency) {
        if (110 > frequency || 880 < frequency) {
                throw std::invalid_argument
                ("Constructor(double): Frequency must be between 110 and 880");
        }
        _cb = new CircularBuffer(ceil(44100 / frequency));
        _time = 0;
}
StringSound::StringSound(std::vector<sf::Int16> init) {
        if (init.size() == 0) {
                throw std::invalid_argument
                ("Constructor(vector): init has no values to input");
        }
        _cb = new CircularBuffer(init.size());
        for (int i = 0; i < _cb->get_size(); ++i) {
                _cb->enqueue(init[i]);
        }
        _time = 0;
}
StringSound::~StringSound() {
        delete _cb;
        _cb = nullptr;
        _time = 0;
}
void StringSound::pluck() {
        while (!_cb->isEmpty()) {
                _cb->dequeue();
        }
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<int16_t> dist(-32768, 32767);
        while (!_cb->isFull()) {
                _cb->enqueue(dist(mt));
        }
}
void StringSound::tic() {
        int16_t t1 = _cb->dequeue();
        int16_t t2 = _cb->peek();
        int16_t karplus_strong = (0.996 * 0.5 * (t1 + t2));
        _cb->enqueue(karplus_strong);
        ++_time;
}
sf::Int16 StringSound::sample() {
        if (_cb->get_size() <= 0) {
                throw std::runtime_error
                ("Sample: there is nothing to be sampled");
        }
        return _cb->peek();
}
int StringSound::time() {
       return _time;
}
