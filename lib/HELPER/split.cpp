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

std::vector<String> HELPER::smartTokenize(String input) {
    std::vector<String> tokens;
    String currentToken = "";
    bool inQuotes = false;
    bool escaped = false;

    for (int i = 0; i < input.length(); i++) {
        char c = input[i];

        if (escaped) {
            if (c == 'n') currentToken += '\n';
            else if (c == 'r') currentToken += '\r';
            else if (c == 't') currentToken += '\t';
            else currentToken += c;
            escaped = false;
        } else if (c == '\\') {
            escaped = true;
        } else if (c == '"') {
            inQuotes = !inQuotes;
        } else if (c == ' ' && !inQuotes) {
            if (currentToken.length() > 0) {
                tokens.push_back(currentToken);
                currentToken = "";
            }
        } else {
            currentToken += c;
        }
    }
    if (currentToken.length() > 0) tokens.push_back(currentToken);
    return tokens;
}
