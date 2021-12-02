/*
  Copyright 2015 Fred Martin, 
  Y. Rykalova, 2020
*/

#include "CircularBuffer.h"
#include "StringSound.h"

#include <math.h>
#include <limits.h>

#include <iostream>
#include <string>
#include <exception>
#include <stdexcept>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

#define CONCERT_A 220.0
#define SAMPLES_PER_SEC 44100

std::vector<sf::Int16> makeSamples(StringSound& gs) { //NOLINT
        std::vector<sf::Int16> samples;
        gs.pluck();
        int duration = 8;  // seconds
        int i;
        for (i= 0; i < SAMPLES_PER_SEC * duration; i++) {
                gs.tic();
                samples.push_back(gs.sample());
        }
        return samples;
}

int main() {
        sf::RenderWindow window(sf::VideoMode(1025, 325), "SFML Guitar");
        sf::Image input_image;
        sf::Texture input_texture;
        sf::Sprite input_sprite;
        input_image.loadFromFile("Image.PNG");
        input_texture.loadFromImage(input_image);
        input_sprite.setTexture(input_texture);
        std::string keys = "q2we4r5ty7u8i9op-[=zxdcfvgbnjmk,.;/' ";
        std::string error = "sf::SoundBuffer: failed to load from samples.";
        sf::Event event;
        double freq;
        sf::Sound sound;
        std::vector<sf::Sound> sounds;
        sf::SoundBuffer* buf;
        for (int i = 0; i < 37; ++i) {
                std::vector<sf::Int16> samples;
                freq = 440 * pow(2, (i - 24) / 12.0);
                StringSound ss(freq);
                samples = makeSamples(ss);
                buf = new sf::SoundBuffer;
                if (!buf->loadFromSamples(&samples[0], samples.size(),
                2, SAMPLES_PER_SEC)) {
                        throw std::runtime_error(error);
                }
        sound.setBuffer(*buf);
        sounds.push_back(sound);
        }

        while (window.isOpen()) {
                while (window.pollEvent(event)) {
                        if (event.type == sf::Event::Closed) {
                                window.close();
                        } else if (event.type == sf::Event::TextEntered) {
                                int i = keys.find(event.text.unicode);
                                if (i >= 0 && i <= 36) {
                                        sounds[i].play();
                                }
                        }
                        window.clear();
                        window.draw(input_sprite);
                        window.display();
                }
        }
        return 0;
}
