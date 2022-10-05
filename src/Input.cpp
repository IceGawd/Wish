#include "Input.hpp"

Input::Input() {

}

Input::Input(string from) : Input(*reinterpret_cast<const Input*>(from.c_str())) {

}

string Input::toString() {
	char* itsAStringNow = reinterpret_cast<char*>(this) + '\0';
	string stringForm(itsAStringNow);
	return stringForm;
}