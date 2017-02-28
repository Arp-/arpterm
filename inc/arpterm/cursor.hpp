
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

		using char_T = typename string_T::value_type;
		using iterator_T = typename string_T::iterator;

		static constexpr char_T VISUAL_LINE_TERM = '\r';
		static constexpr char_T LOGICAL_LINE_TERM = '\n';

		struct choord_t { 
			unsigned x;
			unsigned y;
		};

		public: //-- public functions --//

			cursor(string_T& str):
				buffer_(str), index_(str.size()) {

			}

			~cursor() = default;


			void move_cur_up(size_t count) {
			}

			void move_cur_down(size_t count) {
			}

			void move_cur_right(size_t count) {
			}

			void move_cur_left(size_t count);

			size_t index() { 
				return this->index_;
			}


		public: //-- private functions --//

			bool is_visual_line_term(char_T c) const {
				return c == VISUAL_LINE_TERM;
			}

			bool is_logical_line_term(char_T c) const {
				return c == LOGICAL_LINE_TERM;
			}

			bool is_line_term(char_T c) const {
				return is_logical_line_term(c) || is_visual_line_term(c);
			}

			void next_visual_line_term() { 
				size_t i = this->index_;
				if (is_visual_line_term(this->buffer_[i])) { i++; }
				if (is_logical_line_term(this->buffer_[i])) { i++; }
				for (; i < this->buffer_.size() && !is_line_term(this->buffer_[i]); i++);
				if (i == this->buffer_.size()) {
					this->buffer_.push_back('\r'); // add a new visual_line_term
				}
				this->index_ = i;
			}

			void prev_visual_line_term() {
				size_t i = this->index_;
				if (is_logical_line_term(this->buffer_[i])) {
					i--;
				}
				if (is_visual_line_term(this->buffer_[i])) {
					i--;
				}
				for (; i != 0 && !is_line_term(this->buffer_[i]); i--);
				if (i == 0) {
					this->buffer_.insert(i, 1, static_cast<char_T>('\r'));
				}
				if (is_logical_line_term(this->buffer_[i])) {
					i--;
				}
			}



		private: //-- private variables --//

			string_T& buffer_;

			size_t index_;



	};

} // namespace arpterm


#endif // ARPTERM_CURSOR_HPP
