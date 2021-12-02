// Copyright [2021] Nuno Mestre
#ifndef _HOME_NUNO_PS4B_STRINGSOUND_H_
#define _HOME_NUNO_PS4B_STRINGSOUND_H_
#include <stdint.h>
#include <iostream>
#include <vector>
#include <random>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "CircularBuffer.h"
class StringSound {
 public:
        explicit StringSound(double frequency);
        explicit StringSound(std::vector<sf::Int16> init);
        ~StringSound();
        void pluck();
        void tic();
        sf::Int16 sample();
        int time();
 private:
        CircularBuffer * _cb;
        int _time;
};
#endif  // _HOME_NUNO_PS4B_STRINGSOUND_H_
