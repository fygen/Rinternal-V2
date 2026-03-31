#include "HELPER.h"

bool HELPER::copyto(char *response, size_t size, const char* format, ...) {
    va_list args;
    va_start(args, format);
    
    // Mesajı yaz
    int len = vsnprintf_P(response, size - 3, format, args);
    
    // Manuel olarak satır sonu ekle (Eğer yer varsa)
    if (len >= 0 && (size_t)len < size - 3) {
        response[len] = '\r';
        response[len + 1] = '\n';
        response[len + 2] = '\0';
    }
    
    va_end(args);
    return true;
}

String HELPER::getFreeHeap() {
    char buf[64];
    sprintf(buf, "Free Heap: %u bytes, Fragmentation: %u%%", ESP.getFreeHeap(), ESP.getHeapFragmentation());
    return String(buf);
}