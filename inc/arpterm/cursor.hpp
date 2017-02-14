
#ifndef ARPTERM_CURSOR_HPP
#define ARPTERM_CURSOR_HPP

#include "arpterm/util/util.hpp"

namespace arpterm {

	/**
	 * A class that can insert the given string at a specific position
	 * should only overwrite characters if they are not defined
	 * NOTE the row terminator should be either \n \r or both
	 *
	 */
	template <typename string_T>
	class cursor {

		using char_T = typename string_T::CharT;

		struct choord_t { 
			unsigned x;
			unsigned y;
		};

		public: //-- public functions --//

			cursor(string_T& str):
				buffer_(str) {

			}

			~cursor() = default;

			// negative direction goes up, positive goes down?
			void move_row(int direction) {
				unsigned chars_from_line_start = this->chars_from_line_start();
				char* nth_line_start = this->nth_line_start(direction);
			}

			// negative direction goes left, positive goes rigth?
			void move_column(int direction) {

			}


		private: //-- private functions --//

			inline char_T* buffer_end() { 
				return this->buffer_[this->buffer_.size()-1];
			}

			inline char_T* buffer_start() {
				return &(this->buffer_[0]);
			}

			inline bool is_buf_start(char_T* ch) {
				return ch == this->buffer_start();
			}

			unsigned chars_from_line_start() {
				unsigned count = 0;
				for (long int i = this->buffer_.size()-1; 
						i >= 0 && util::is_line_term(this->buffer_[i]);
						i--, count++);
				return count;
			}

			char_T* move_to_visual_line_start(char_T* pos) {
				do {
					--pos;
				} while (!util::is_visual_line_term(*pos) && !is_buf_start(pos));
				if (is_visual_line_term(*pos)) {
					return (++pos);
				}
				return pos;
			}

			char_T* nth_line_start(int direction) { 
				char_T* line_start = this->buffer_end();
				if (direction >= 0) {
					for (int i = 0; i <= direction; i++) {
						line_start = move_to_visual_line_start(line_start);
					}
				} else if (direction < 1) {

				}

			}


		private: //-- private variables --//

			string_T& buffer_;



	};

} // namespace arpterm


#endif // ARPTERM_CURSOR_HPP
