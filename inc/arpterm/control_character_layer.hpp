
#ifndef ARPTERM_CONTROL_CHARACTER_LAYER_HPP
#define ARPTERM_CONTROL_CHARACTER_LAYER_HPP

#include <gtkmm/textiter.h>


namespace arpterm {

	/**
	 * \param state the state of the control keys in gtkmm
	 * \param ch the character that was pressed/released
	 */
	gunichar control_character_layer(guint state, gunichar ch);

 }   // namespace arpterm 


#endif // ARPTERM_CONTROL_CHARACTER_LAYER_HPP
