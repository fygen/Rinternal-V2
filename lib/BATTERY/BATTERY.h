#ifndef BATTERY_H
#define BATTERY_H

#include <Adafruit_ADS1X15.h>
#include "TIMER.h"

class BATTERY
{
public:
    BATTERY(uint8_t pin);
    BATTERY(uint8_t pin, float resistorValue);
    BATTERY(float resistorValue);
    void begin();
    float getVoltage();
    bool updateMeasurement();
    float getLastResult();
    void baslatTest(int adet, float direnValue); // Testi tetikler
    bool testUpdate();                           // Loop'ta döner, bittiğinde raporu hazırlar
    String getInstantReport();
    String testRaporu();

private:
    // Test sonuçlarını ve durumunu tutacak değişkenler
    String _araRapor = "";
    bool _yeniVeriVar = false;
    int _toplamTest = 0;
    int _kalanTest = 0;
    float _toplamDirenc = 0;
    bool _testCalisiyor = false;
    // Durum takibi için enum ve değişken ve timer tanımları
    TIMER _timer;
    enum Durum
    {
        BEKLEMEDE,
        YUK_ALTINDA_OKUMA,
        YUKSUZ_OKUMA
    };
    Durum _suankiDurum = BEKLEMEDE;
    float _vUnderLoad, _vNoLoad;
    // PIN ayarlamaları ve classların tanımlanması ve gerçek dünya değişkenleri
    Adafruit_ADS1115 ads;
    uint8_t _loadPin = D8;      // Mosfet'i tetikleyen pin
    float _loadResistor = 10.0; // Kullandığın taş direncin değeri
};

#endif