//////////////////////////
// values_ui_manager.h
// Autor: Areg Kalantaryan
//////////////////////////

#pragma once
#include <Arduino.h>
#include "LiquidCrystal_PCF8574.h"

typedef void (*func_args_ptr)(u_int8_t*, int);

enum class SET_MODE {
    INCREMENT,
    DECREMENT,
    SET
};

struct ValuesUIManager {
    ValuesUIManager(LiquidCrystal_PCF8574& lcd) : lcd(lcd) {}
    void init(u_int8_t* args, u_int8_t* args_max_val, int arg_count, func_args_ptr callback_print, func_args_ptr callback_scroll_end);
    void update();
    void scroll();
    void change_value(SET_MODE set_mode, u_int8_t value = 0);
    u_int8_t operator [] (int index) { return args[index]; }

    u_int8_t* args;
    u_int8_t* args_max_val;
    int index;
    int arg_count;

private:
    func_args_ptr callback_print;
    func_args_ptr callback_scroll_end;
    LiquidCrystal_PCF8574& lcd;
};