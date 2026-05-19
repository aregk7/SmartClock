//////////////////////////
// tune.h
// Autor: Areg Kalantaryan
//////////////////////////

#pragma once
#include <Arduino.h>
#include "notes.h"

struct TuneChannelPWM {
    TuneChannelPWM(TIM_TypeDef* pwm_timer_name, int pin) : pwm_timer(*new HardwareTimer(pwm_timer_name)), pin(pin) {}

    //Spielt einen Tick vom gegebenen Melodieblatt
    void play_tick(Note* sheet) volatile;

    HardwareTimer& pwm_timer;
    int pin;

    volatile int note_index;
    volatile int ticks_left;
};

struct TuneChannels {
    TuneChannels(int channels_count, TuneChannelPWM* channels, TIM_TypeDef* timer_name, int tick_speed_ns = 250000 / 4);
    /// @brief Hält die Wiedergabe und alle Kanal-Timer an
    void pause();
    void play_tune(Note** tune_sheet);
    TuneChannelPWM operator [] (int index) { return channels[index]; }

    int channels_count;

private:
    void play_tick();

    TuneChannelPWM* channels;
    HardwareTimer& timer_tick;
    Note** current_sheet;
};