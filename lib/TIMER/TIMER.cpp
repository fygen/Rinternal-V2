#include "TIMER.h"
// Constructor: Sınıf ilk oluştuğunda değerleri sıfırlar
TIMER::TIMER()
{
    startTime = 0;
    active = false;
}

// Zamanlayıcıyı başlatır
char* TIMER::start()
{
    startTime = millis();
    active = true;
    return "Zaman Baslatildi.";
}

// Belirlenen süre doldu mu kontrol eder (True/False döner)
bool TIMER::isExpired(unsigned long sure)
{
    if (active && (millis() - startTime >= sure))
    {
        active = false; // Tekrar tetiklenmemesi için durdurur
        return true;
    }
    return false;
}

// Zamanlayıcıyı manuel sıfırlamak istersen
char* TIMER::stop()
{
    active = false;
    snprintf(response, sizeof(response),"Timer Durduruldu.");
    return response;
}

char* TIMER::reset(){
    startTime = 0;
    active = false;
    strcpy(response,"Timer resetlendi.");
    return response;
}

char* TIMER::getElapsedMillis(){
    return itoa(millis() - startTime,response, 10);
}