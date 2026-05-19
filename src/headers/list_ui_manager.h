//////////////////////////
// list_ui_manager.h
// Autor: Areg Kalantaryan
//////////////////////////

#pragma once
#include "LiquidCrystal_PCF8574.h"

struct ListUIManager {
    enum DISPLAY_MODE {
        SELECT,
        ENUMERATE
    };

    ListUIManager(LiquidCrystal_PCF8574& lcd) : lcd(lcd) {}
    void init(const char** items, unsigned short item_count, DISPLAY_MODE mode = SELECT);
    void update();
    void scroll_down();
    void scroll_up();
    
    const char** items;
    unsigned short item_count;
    unsigned short selected;
    DISPLAY_MODE mode;

private:
    LiquidCrystal_PCF8574& lcd;
    bool is_upper;
};