//////////////////////////
// main.cpp
// Autor: Areg Kalantaryan
//////////////////////////

#include <Arduino.h>
#include "LiquidCrystal_PCF8574.h"
#include "STM32RTC.h"
#include "headers/constants.h"
#include "headers/list_ui_manager.h"
#include "headers/values_ui_manager.h"
#include "headers/tune.h"

#define BTN1 PA10
#define BTN2 PA6
#define BTN3 PA1
#define tone_channel(channel, frequency) (tune_channels[channel].pwm_timer.setPWM(1, tune_channels[channel].pin, frequency, 50))
#define attach_interrupt_debounce(pin, callback) (attachInterrupt(pin, [=]{ debounce(pin, callback); }, RISING))
#define attach_interrupt_debounce_ms(pin, callback, delay_ms) (attachInterrupt(pin, [=]{ debounce(pin, callback, delay_ms); }, RISING))

void wnd_main();
void wnd_set_timer();
void wnd_set_datetime();
void wnd_moreop();
void wnd_stopwatch();
void wnd_timestamps();
void wnd_tune();
void wnd_lang();
void wnd_credits();

void transition(const char* msg = "");
void attach_list_ui_interrupts(function_ptr callback_selected);
void attach_values_ui_interrupts();
void isr_check_time();
void alarm();
void debounce(int pin, function_ptr callback, int delay_ms = 50);

enum LANG {	EN, DE, JP };

LiquidCrystal_PCF8574 lcd(0x27);
HardwareTimer timer_alert(TIM5), timer_general(TIM7);
STM32RTC& rtc = STM32RTC::getInstance();

ListUIManager list_ui = ListUIManager(lcd);
ValuesUIManager values_ui(lcd);
TuneChannelPWM arr_tune_channels[] = {TuneChannelPWM(TIM9, PB13), TuneChannelPWM(TIM10, PB12), TuneChannelPWM(TIM11, PB15)};
TuneChannels tune_channels = TuneChannels(3, arr_tune_channels, TIM6);

LANG current_lang = DE;
Note** current_tune = tune_ring;

bool is_wnd_main = false;
bool is_wnd_stopwatch = false;
bool time_update = true;
int time_left_tim = UINT32_MAX;

function_ptr list_moreop_func[]	= {wnd_stopwatch, wnd_tune, wnd_lang, wnd_credits};

void setup() {
	//Die Tastenpins auf Output setzen
	pinMode(BTN1, INPUT_PULLDOWN);
	pinMode(BTN2, INPUT_PULLDOWN);
	pinMode(BTN3, INPUT_PULLDOWN);
	
	//LCD konfigurieren
	lcd.begin(16,2);
	lcd.setBacklight(255);

	for (int i = 1; i < 8; i++)
		lcd.createChar(i, custom_chars[i]);

	//Der Timer für Datum und Uhrzeit einstellen
	rtc.begin();
	timer_alert.setOverflow(1000000, MICROSEC_FORMAT);
	timer_alert.attachInterrupt(isr_check_time);
	timer_alert.resume();

	//Hohe Priorität für Timer und niedrige für Entprellung einstellen
	HAL_NVIC_SetPriority(EXTI15_10_IRQn, 15, 15);
	HAL_NVIC_SetPriority(EXTI9_5_IRQn, 15, 15);
	HAL_NVIC_SetPriority(EXTI1_IRQn, 15, 15);
	HAL_NVIC_SetPriority(TIM6_IRQn, 1, 1);
	HAL_NVIC_SetPriority(TIM9_IRQn, 1, 1);
	HAL_NVIC_SetPriority(TIM10_IRQn, 1, 1);
	HAL_NVIC_SetPriority(TIM11_IRQn, 1, 0);
	HAL_NVIC_SetPriority(TIM7_IRQn, 8, 8);

	wnd_main();

	//Startmelodie spielen
	tone_channel(0, NOTE_C4);
	delay(125);
	tone_channel(0, NOTE_G4);
	delay(875);
	tune_channels[0].pwm_timer.pause();
}

void wnd_main() {
	transition();
	is_wnd_main = true;

	//Interrupts anhängen
	delay(500); //Entprellung
	attach_interrupt_debounce_ms(BTN1, wnd_set_timer, 25);
	attach_interrupt_debounce_ms(BTN2, wnd_set_datetime, 25);
	attach_interrupt_debounce_ms(BTN3, wnd_moreop, 25);
}

uint8_t timer_vals[3] = {0, 0, 0};
uint8_t timer_vals_max[] = {99, 59, 59};

void wnd_set_timer() {
	transition(str_other[current_lang][0]);

	//Values UI initialisieren
	values_ui.init(timer_vals, timer_vals_max, 3,
	[](u_int8_t* args, int index){
		lcd.printf("    %02d:%02d:%02d", args[0], args[1], args[2]);
		lcd.setCursor(3 * (index % 3) + 3, 0);
		lcd.printf(">");
	},
	[](u_int8_t* args, int index){
		time_left_tim = args[0] * 3600 + args[1] * 60 + args[2];
		wnd_main(); 
	});

	attach_values_ui_interrupts();
}

uint8_t* time_vals = new uint8_t[6];
uint8_t time_vals_max[] = {31, 12, 99, 59, 59, 59};

void wnd_set_datetime() {
	//Datum und Uhrzeit abrufen
	time_vals[0] = rtc.getDay();
	time_vals[1] = rtc.getMonth();
	time_vals[2] = rtc.getYear();
	time_vals[3] = rtc.getHours();
	time_vals[4] = rtc.getMinutes();
	time_vals[5] = rtc.getSeconds();

	transition(str_other[current_lang][1]);
	
	//Values UI initialisieren
	values_ui.init(time_vals, time_vals_max, 6,
	[](u_int8_t* args, int index){
		lcd.printf("    %02d:%02d:%02d", args[0], args[1], args[2]);
		lcd.setCursor(0,1);
		lcd.printf("    %02d:%02d:%02d", args[3], args[4], args[5]);
		lcd.setCursor(3 * (index % 3) + 3, index / 3);
		lcd.printf(">");
	},
	[](u_int8_t* args, int){
		rtc.setDate(args[0], args[1], args[2]);
		rtc.setTime(args[3], args[4], args[5]);
		wnd_main();
	});

	attach_values_ui_interrupts();
}

void wnd_moreop() {
	transition(str_other[current_lang][2]);
	list_ui.init(str_moreop[current_lang], sizeof(str_moreop[0]) / 4);
	attach_list_ui_interrupts([]{ list_moreop_func[list_ui.selected](); });
}

volatile int* timestamps = new int[9];
volatile int timestamp_count = 0;
volatile int measured_cs; //cs steht für Zentisekunde (0,01 sekunde)

void wnd_stopwatch() {
	transition();
	
	//Variablen zurücksetzen
	measured_cs = 0;
	timestamp_count = 0;
	is_wnd_stopwatch = true;

	//Timer konfigurieren
	timer_general.setOverflow(10000, MICROSEC_FORMAT);
	timer_general.attachInterrupt([]{ measured_cs++; });

	attach_interrupt_debounce(BTN1, []{
		timer_general.resume();
		detachInterrupt(BTN1);
		attach_interrupt_debounce(BTN2, []{ if (timestamp_count != 9) timestamps[timestamp_count++] = measured_cs; });
		attach_interrupt_debounce(BTN3, []{ timer_general.pause(); wnd_timestamps(); });
	});
}

char timestamp_chars[10][12];
const char* str_timestamps[9];

void wnd_timestamps() {

	if (timestamp_count == 0) {
		delay(500); //Entprellung
		detachInterrupt(BTN2);
		attachInterrupt(BTN3, wnd_main, RISING);
	}
	else {
		transition();
		if (timestamp_count > 9) timestamp_count = 9;

		//Die Zeitstempelwerte in ein statisches String-Array schreiben
		for (int i = 0; i < timestamp_count; i++)
			sprintf(timestamp_chars[i], "%02d:%02d:%02d.%02d", timestamps[i] / 360000 % 60, timestamps[i] / 6000 % 60, timestamps[i] / 100 % 60, timestamps[i] % 100);

		//Daraus ein dynamisches Array initialisieren
		for (int i = 0; i < timestamp_count; i++)
			str_timestamps[i] = timestamp_chars[i];
			
		list_ui.init(str_timestamps, timestamp_count, ListUIManager::ENUMERATE);
		attach_list_ui_interrupts(wnd_main);
	}
}

void wnd_tune() {
	transition();
	list_ui.init(str_tune, sizeof(str_tune) / 4);

	attach_interrupt_debounce(BTN1, []{ list_ui.scroll_up();	tune_channels.play_tune(list_tunes[list_ui.selected]); });
	attach_interrupt_debounce(BTN2, []{ list_ui.scroll_down();	tune_channels.play_tune(list_tunes[list_ui.selected]); });
	delay(500); // Entprellung
	attach_interrupt_debounce_ms(BTN3, []{ current_tune = list_tunes[list_ui.selected]; wnd_main();}, 25);
}

void wnd_lang() {
	transition();
	list_ui.init(str_lang, sizeof(str_lang) / 4);
	attach_list_ui_interrupts([]{ current_lang = (LANG)list_ui.selected; wnd_main();});
}

void wnd_credits() {
	transition();
	lcd.print(str_credits[current_lang][0]);
	lcd.setCursor(0,1);
	lcd.print(str_credits[current_lang][1]);

	attach_interrupt_debounce_ms(BTN3, wnd_main, 25);
}

/// @brief Löscht Tasteninterrupts, stoppt die Melodie, setzt die Status zurück, löscht die LCD-Anzeige und zeigt eine Meldung an (optional).
void transition(const char* msg) {
	detachInterrupt(BTN1);
	detachInterrupt(BTN2);
	detachInterrupt(BTN3);
	tune_channels.pause();
	is_wnd_main = false;
	is_wnd_stopwatch = false;
	lcd.clear();
	lcd.setCursor(0,0);

	if (msg == "") return;

	lcd.printf(msg);
	delay(500);
	lcd.clear();
}

/// @brief Fügt Interrupt-Handler für Tasteninterrupts hinzu, um ein List UI zu steuern.
/// @param callback_selected Eine Callback-Funktion, die durch Drücken von BTN3 aufgerufen wird
void attach_list_ui_interrupts(function_ptr callback_selected) {
	attach_interrupt_debounce(BTN1, []{list_ui.scroll_up();});
	attach_interrupt_debounce(BTN2, []{list_ui.scroll_down();});
	delay(500); //Entprellung
	attach_interrupt_debounce_ms(BTN3, callback_selected, 25);
}

void attach_values_ui_interrupts() {
	attach_interrupt_debounce(BTN1, []{ values_ui.change_value(SET_MODE::INCREMENT); });
	attach_interrupt_debounce(BTN2, []{ values_ui.change_value(SET_MODE::DECREMENT); });
	attach_interrupt_debounce(BTN3, []{ values_ui.scroll(); });
}

void isr_check_time()
{
	time_update = true;

	if (time_left_tim != UINT32_MAX)
		if (--time_left_tim == 0)
			alarm();
}

volatile char backlight = 255;

void alarm() {
	transition();
	lcd.print(str_other[current_lang][3]);
	lcd.setCursor(0,1);
	lcd.printf("    %02d:%02d:%02d    ", rtc.getHours(), rtc.getMinutes(), rtc.getSeconds());
	tune_channels.play_tune(current_tune);
	
	timer_general.setOverflow(500000, MICROSEC_FORMAT);
	timer_general.attachInterrupt([]{ lcd.setBacklight(backlight); backlight = ~backlight; });
	timer_general.resume();

	attachInterrupt(BTN3, []{
		timer_general.detachInterrupt();
		lcd.setBacklight(255);
		wnd_main();
	}, RISING);
}

void debounce(int pin, function_ptr callback, int delay_ms)
{
	int ctr = 0;
	bool check;
	bool state = digitalRead(pin);
		
	while (check)
	{
		check = false;

		for (int i = 0; i < delay_ms * 100; i++)
		{
			if (++ctr == 300 * 100) return; //Erzwungene Beendigung

			delayMicroseconds(10);
			if(digitalRead(pin) == state) continue;

			check = true;
			break;
		}
	}
		
	if(state) callback();
}

void loop() {
	if (is_wnd_main && time_update){
		lcd.setCursor(0,0);
		lcd.printf("%02d.%02d.%02d", rtc.getDay(), rtc.getMonth(), rtc.getYear());
		
		//Die verbleibende Zeit des Timers anzeigen, falls eingestellt
		if(time_left_tim != UINT32_MAX){
			if(time_left_tim >= 3600)
				lcd.printf(" |\7%02d:%02d", time_left_tim / 3600, time_left_tim % 3600 / 60);
			else
				lcd.printf(" |\6%02d:%02d", time_left_tim / 60, time_left_tim % 60);
		}
		
		lcd.setCursor(0,1);
		lcd.printf("%02d:%02d:%02d", rtc.getHours(), rtc.getMinutes(), rtc.getSeconds());
		time_update = false;
	} else if (is_wnd_stopwatch){
		lcd.setCursor(2,0);
		lcd.printf("%02d:%02d:%02d.%02d", measured_cs / 360000 % 60, measured_cs / 6000 % 60, measured_cs / 100 % 60, measured_cs % 100);
		delay(1);
	}
}