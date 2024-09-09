#ifndef _BUILTIN_LED_H_
#define _BUILTIN_LED_H_

#include "led_strip.h"
#include "freertos/semphr.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"

#define BLINK_INFINITE -1
#define BLINK_TASK_STOPPED_BIT BIT0
#define BLINK_TASK_RUNNING_BIT BIT1

class BuiltinLed {
public:
    static BuiltinLed& GetInstance() {
        static BuiltinLed instance;
        return instance;
    }

    void BlinkOnce();
    void Blink(int times, int interval_ms);
    void StartContinuousBlink(int interval_ms);
    void TurnOn();
    void TurnOff();
    void SetColor(uint8_t r, uint8_t g, uint8_t b);
    void SetWhite() { SetColor(128, 128, 128); }
    void SetGrey() { SetColor(32, 32, 32); }
    void SetRed() { SetColor(128, 0, 0); }
    void SetGreen() { SetColor(0, 128, 0); }
    void SetBlue() { SetColor(0, 0, 128); }

private:
    BuiltinLed();
    ~BuiltinLed();
    BuiltinLed(const BuiltinLed&) = delete;
    BuiltinLed& operator=(const BuiltinLed&) = delete;

    SemaphoreHandle_t mutex_;
    EventGroupHandle_t blink_event_group_;
    TaskHandle_t blink_task_ = nullptr;
    led_strip_handle_t led_strip_ = nullptr;
    uint8_t r_ = 0, g_ = 0, b_ = 0;
    int blink_times_ = 0;
    int blink_interval_ms_ = 0;
    bool should_blink_ = false;

    void Configure();
    void StartBlinkTask(int times, int interval_ms);
    void StopBlinkInternal();
};

#endif // _BUILTIN_LED_H_
