#include "BATTERY.h"

BATTERY::BATTERY(uint8_t pin) {
    _loadPin = pin; // Pini değişkene kaydet
}

BATTERY::BATTERY(uint8_t pin, float resistorValue) {
    _loadPin = pin;
    _loadResistor = resistorValue;
}

BATTERY::BATTERY(float resistorValue)
{
    _loadResistor = resistorValue;
}

void BATTERY::begin() {
    ads.begin();
    pinMode(_loadPin, OUTPUT); // Kaydedilen pini burada ayarla
    digitalWrite(_loadPin, LOW);
}

float BATTERY::getVoltage() {
    int16_t adc0 = ads.readADC_SingleEnded(0);
    float voltage = adc0 * (4.096 / 32768.0); // ADS1115'in referans gerilimi ve çözünürlüğü
    return voltage;
}

// Bu fonksiyonu loop içinde sürekli çağırmalısın
// Ölçüm bittiğinde TRUE, devam ediyorsa FALSE döner.
bool BATTERY::updateMeasurement() {
    switch (_suankiDurum) {
        
        case BEKLEMEDE:
            // Ölçümü başlatan tetik burası (Örn: Bir butonla tetiklendiğinde)
            digitalWrite(_loadPin, HIGH);
            _timer.start(); // 100ms beklemek için timer başlar
            _suankiDurum = YUK_ALTINDA_OKUMA;
            break;

        case YUK_ALTINDA_OKUMA:
            if (_timer.isExpired(100)) {
                _vUnderLoad = getVoltage();
                digitalWrite(_loadPin, LOW); // Yükü kaldır
                _timer.start(); // Tekrar 100ms başlat
                _suankiDurum = YUKSUZ_OKUMA;
            }
            break;

        case YUKSUZ_OKUMA:
            if (_timer.isExpired(100)) {
                _vNoLoad = getVoltage();
                _suankiDurum = BEKLEMEDE; // Başa dön
                return true; // Ölçüm TAMAMLANDI
            }
            break;
    }
    return false; // Ölçüm hala DEVAM EDİYOR
}

// Sonucu hesaplayan yardımcı fonksiyon
float BATTERY::getLastResult() {
    float currentLoad = _vUnderLoad / _loadResistor;
    if (currentLoad <= 0) return 0;
    return (_vNoLoad - _vUnderLoad) / currentLoad;
}

void BATTERY::baslatTest(int testSayisi, float loadResistor) {
    _loadResistor = loadResistor;
    _toplamTest = testSayisi;
    _kalanTest = testSayisi;
    _toplamDirenc = 0;
    _testCalisiyor = true;
    _suankiDurum = BEKLEMEDE; // Ölçüm motorunu hazırla
}

String BATTERY::testRaporu() {
    float ortalama = _toplamDirenc / _toplamTest;
    String rapor = F("--- TEST SONUCU ---\n");
    rapor += F("Adet: ") + String(_toplamTest) + F("\n");
    rapor += F("Ortalama IR: ") + String(ortalama, 4) + F(" Ohm\n");
    return rapor;
}

bool BATTERY::testUpdate() {
    if (!_testCalisiyor) return false;

    // Tek bir ölçümün (Load -> Wait -> Read -> Unload -> Wait -> Read) bitişi
    if (updateMeasurement()) { 
        float sonuc = getLastResult();
        _toplamDirenc += sonuc;
        _kalanTest--;

        // Anlık raporu hazırla
        int suankiSira = _toplamTest - _kalanTest;
        _araRapor = String(suankiSira) + F(". Olcum: ") + String(sonuc, 4) + F(" Ohm");
        _yeniVeriVar = true; // Loop'ta yakalamak için bayrak

        if (_kalanTest <= 0) {
            _testCalisiyor = false;
        } else {
            _suankiDurum = BEKLEMEDE; // Bir sonraki tur için motoru kur
        }
    }
    return false;
}

// Yeni veri gelip gelmediğini kontrol eden yardımcı
String BATTERY::getInstantReport() {
    if (_yeniVeriVar) {
        _yeniVeriVar = false;
        return _araRapor;
    }
    return "";
}