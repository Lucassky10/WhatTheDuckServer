#include "Message.h"

using namespace std;

// Get type
messageType Message::getType() {
    return type;
}

// Get text for enum
string Message::getTextForEnum(int enumVal)
{
    return enumMessageTypes[enumVal];
}

/**
 * Asking Configuration
 */

// Asking configuration Message
AskingConfigurationMessage::AskingConfigurationMessage() {
    // Asking configuration type
    type = ASKING_CONFIGURATION;
}

// Construct asking configuration message
string AskingConfigurationMessage::constructMessage() {
    message = to_string(type);
    return message;
}

/**
 * Configuration
 */

// Configuration Message
ConfigurationMessage::ConfigurationMessage() {
    // Configuration type
    type = CONFIGURATION;
}

// Construct configuration message
string ConfigurationMessage::constructMessage() {
    message = to_string(type) + DELIMITER + data;
    return message;
}

// Set message
void ConfigurationMessage::setMessage(string data) {
    setData(data);
}

// Set Data
void ConfigurationMessage::setData(string configData) {
    data = configData;
}

// Get data
string ConfigurationMessage::getData() {
    return data;
}

/**
 * All Ducks Found Message
 */

AllDucksFoundMessage::AllDucksFoundMessage() {
    // All ducks found type
    type = ALL_DUCKS_FOUND;
}

// Construct all ducks found message
string AllDucksFoundMessage::constructMessage() {
    message = to_string(type);
    return message;
}

/**
 * Coordinates Message
 */
CoordinatesMessage::CoordinatesMessage() {
    // Coordinates type
    type = COORDINATES;
}

// Construct coordinates message
string CoordinatesMessage::constructMessage() {
    message = to_string(type);
    return message;
}

// Set position
void CoordinatesMessage::setPosition(int x, int y, int z) {
    position[0] = x;
    position[1] = y;
    position[2] = z;
}

// Get position
int* CoordinatesMessage::getPosition() {
    return position;
}