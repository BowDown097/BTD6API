// Generated C++ file by Il2CppInspector - http://www.djkaty.com - https://github.com/djkaty
// Logging functions

#pragma once
#include <string>
#include <sstream>
#include <iomanip>

extern const LPCWSTR LOG_FILE;

// Helper function to append text to a file
void LogWrite(std::string text);

// Helper function to convert a pointer to hex
template<typename T> std::string to_hex_string(T i) {
	std::stringstream stream;
	stream << "0x" << std::setfill('0') << std::setw(sizeof(T) * 2) << std::hex << i;
	return stream.str();
}