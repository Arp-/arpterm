

#include "arpterm/control_character_layer.hpp"


namespace a = arpterm;

//-----------------------------------------------------------------------------//
// NOTE I actuall thought this will be bigger than one function :'D
gunichar
a:: control_character_layer(guint state, gunichar ch) {
	if (GDK_CONTROL_MASK & state) {
		// suprisingly the difference between ^C and C is 0x40 and simmilarly to
		// ^D and D and ... etc.
		if (ch >= 0x40ULL && ch < 0x60ULL ) {
			return ch - 0x40;
		}
		// convinience for little capital characters ???
		if (ch >= 0x61ULL && ch <= 0x7AULL) {
			return ch - 0x60;
		}
	}
	return ch;
}
