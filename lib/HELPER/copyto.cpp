#include "HELPER.h"

bool HELPER::copyto(char *response,const char* format, ...) {
    va_list args;
    va_start(args, format);
    
    // Mesajı yaz
    int len = vsnprintf_P(response, sizeof(response) - 2, format, args);
    
    // Manuel olarak satır sonu ekle (Eğer yer varsa)
    if (len > 0 && len < (int)sizeof(response) - 2) {
        response[len] = '\r';
        response[len + 1] = '\n';
        response[len + 2] = '\0';
    }
    
    va_end(args);
    return true;
}