#ifndef TIMER_H
#define TIMER_H
#include <Arduino.h>

class TIMER
{
private:
    unsigned long startTime;
    bool active;
    char response[30];

public:
    // Constructor: Sınıf ilk oluştuğunda değerleri sıfırlar
    TIMER();
    // Zamanlayıcıyı başlatır
    char* start();
    // Belirlenen süre doldu mu kontrol eder (True/False döner)
    bool isExpired(unsigned long sure);
    char* getElapsedMillis();
    // Zamanlayıcıyı manuel sıfırlamak istersen
    char* stop();
    char* reset();
};

#endif