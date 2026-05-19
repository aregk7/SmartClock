#include "values_ui_manager.h"

void ValuesUIManager::init(u_int8_t* args, u_int8_t* args_max_val, int arg_count, func_args_ptr callback_print, func_args_ptr callback_scroll_end) {
    this->args = args;
    this->args_max_val = args_max_val;
    this->arg_count = arg_count;
    this->callback_print = callback_print;
    this->callback_scroll_end = callback_scroll_end;
    index = 0;
    update();
}

void ValuesUIManager::update()
{
    lcd.clear();
    lcd.setCursor(0,0);
    callback_print(args, index);
}

void ValuesUIManager::scroll()
{
    if (++index == arg_count)
        callback_scroll_end(args, index);
    else
        update();
}

void ValuesUIManager::change_value(SET_MODE set_mode, u_int8_t value)
{
    if (set_mode == SET_MODE::INCREMENT)
        if (args[index] >= args_max_val[index])
            args[index] = 0;
        else args[index]++;
    else if (set_mode == SET_MODE::DECREMENT)
        if (args[index] == 0)
            args[index] = args_max_val[index];
        else args[index]--;
    else if (set_mode == SET_MODE::SET)
        if (value > args_max_val[index])
            args[index] = args_max_val[index] + 1;
        else
            args[index] = value;
        
    update();
}