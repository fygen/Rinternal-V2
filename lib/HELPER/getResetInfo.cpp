#include "HELPER.h"

String HELPER::wtf()
{
    return ESP.getResetInfo() + "\n" + ESP.getResetReason() + "\n" ;
}