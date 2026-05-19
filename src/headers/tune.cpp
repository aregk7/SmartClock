#include "tune.h"
#include <Arduino.h>
#include "notes.h"

void TuneChannelPWM::play_tick(Note* sheet) volatile {
    if (--ticks_left != 0)
        return;
	
    note_index = (sheet[++note_index].frequency == SHEET_END) ? 0 : note_index;
	ticks_left = sheet[note_index].length;

	if (sheet[note_index].frequency == REST) {
		pwm_timer.pause();
		return;
	}
	
	if (!pwm_timer.isRunning())
		pwm_timer.resume();
        
    pwm_timer.setPWM(1, pin, sheet[note_index].frequency, 50);
}

TuneChannels::TuneChannels(int channels_count, TuneChannelPWM* channels, TIM_TypeDef* timer_name, int tick_speed_ns) 
                : timer_tick(*new HardwareTimer(timer_name)), channels_count(channels_count), channels(channels) {
    timer_tick.setOverflow(tick_speed_ns, MICROSEC_FORMAT);
}

void TuneChannels::pause()
{
    timer_tick.pause();
    for (int i = 0; i < channels_count; i++)
        channels[i].pwm_timer.pause();
    return;
}

void TuneChannels::play_tune(Note **tune_sheet)
{
    pause();
    
    if (tune_sheet == nullptr)    
        return;
    
    current_sheet = tune_sheet;
    for (int i = 0; i < channels_count; i++)
    {
        channels[i].note_index = -1;
        channels[i].ticks_left = 1;
    }

    play_tick();
    timer_tick.attachInterrupt([this](){play_tick();});
    timer_tick.setCount(0);
    timer_tick.resume();
}

void TuneChannels::play_tick() {
    for (int i = 0; i < channels_count; i++)
        if (current_sheet[i] != nullptr)
            channels[i].play_tick(current_sheet[i]);
}