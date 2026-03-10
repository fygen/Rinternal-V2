#include "HELPER.h"

std::vector<String> HELPER::splitString(String str, char delimiter) {
    std::vector<String> result;
    int start = 0;
    int end = str.indexOf(delimiter);
    while (end != -1) {
        result.push_back(str.substring(start, end));
        start = end + 1;
        end = str.indexOf(delimiter, start);
    }
    result.push_back(str.substring(start)); // Son parçayı ekle
    return result;
}
