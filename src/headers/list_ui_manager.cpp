#include "list_ui_manager.h"

void ListUIManager::init(const char** items, unsigned short item_count, DISPLAY_MODE mode) {
    this->items = items;
    this->item_count = item_count;
    this->mode = mode;
    is_upper = true;
    selected = 0;
    update();
}

void ListUIManager::update() {
    lcd.clear();
    lcd.setCursor(0,0);

    if (is_upper) {
        if (mode == SELECT) {
            lcd.printf("> %s", items[selected]);
            if (selected + 1 != item_count) {
                lcd.setCursor(0,1);
                lcd.printf("  %s", items[selected+1]);
            }
        }
        else if (mode == ENUMERATE) {
            lcd.printf("%d.%s", selected+1, items[selected]);
            if (selected + 1 != item_count) {
                lcd.setCursor(0,1);
                lcd.printf("%d.%s", selected+2, items[selected+1]);
            }
        }
    } else {
        if (mode == SELECT) {
            lcd.printf("  %s", items[selected-1]);
            lcd.setCursor(0,1);
            lcd.printf("> %s", items[selected]);
        }
        else if (mode == ENUMERATE) {
            lcd.printf("%d.%s", selected, items[selected-1]);
            lcd.setCursor(0,1);
            lcd.printf("%d.%s", selected+1, items[selected]);
        }
    }
}

void ListUIManager::scroll_down() {
    if (++selected == item_count) selected = 0;
    is_upper = (selected == 0);
    update();
}

void ListUIManager::scroll_up() {
    if (--selected == 65535) selected = item_count - 1;
    is_upper = (selected != item_count - 1);
    update();
}