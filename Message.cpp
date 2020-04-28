#include "Message.h"

using namespace std;

// Get type
messageType Message::getType() {
    return type;
}

// Get text for enum
string Message::getTextForEnum(int enumVal)
{
    return EnumMessageTypes[enumVal];
}

// Asking configuration Message
AskingConfigurationMessage::AskingConfigurationMessage() {
    // Asking configuration type
    type = ASKING_CONFIGURATION;
}

// Construct connection message
string AskingConfigurationMessage::constructMessage() {
    message = to_string(type);
    return message;
}


