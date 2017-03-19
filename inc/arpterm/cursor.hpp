
#ifndef ARPTERM_CURSOR_HPP
#define ARPTERM_CURSOR_HPP

#include "arpterm/util/debug.hpp"
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
		static constexpr char_T CHARS_TO_IGNORE = '\n';

		struct choord_t { 
			unsigned x;
			unsigned y;
		};

		public: //-- public functions --//

			cursor(string_T& str):
				buffer_(str), index_(str.size()) {

			}

			~cursor() = default;


			void push_back(const char_T& ch) {

				this->buffer_.assign(this->index_,ch);
				this->move_cur_right(1);
			}

			void erase() {
				//this->buffer_[this->index_] = ' ';
			}

			void mv_cur_up(size_t n) {
				size_t col_index = this->column_index();
				for (size_t i = 0; i < n; i++) {
					this->mv_prev_line_term();
				}
				this->index_++; // because we're at \r;
				size_t i = this->index_;
				for (; i < col_index && i < this->bufer_.size(); i++) {
					char_T cur_char = this->buffer_[i];
					if (is_char_to_ignore(cur_char)) {
						col_index++;
					}
					if (is_visual_line_term(this->buffer_[i])) {
						this->buffer_.insert(i, static_cast<char_T>(' '));
					}
				}
				this->index_ = i;
			}




		public: //-- private functions --//

			bool is_visual_line_term(char_T c) const {
				return c == VISUAL_LINE_TERM;
			}

			bool is_char_to_ignore(char_T c) const {
				return c == CHARS_TO_IGNORE;
			}


			// NOTE This calculates every character from the latest \r or 0
			// that means this will be inconsistent fuck when one line is terminated
			// by \r\n and the other is terminated by \r
			size_t column_index() const {
				size_t i = this->index_;
				size_t chars_ignored = 0;
				for (; i > 0; && !is_visual_line_term(this->buffer_[i]); i--) {
					if (is_char_to_ignore(this->buffer_[i])) {
						chars_ignored++;
					}
				}
				if (this->index_ == 0 && !is_visual_line_term(i)) {
					return this->index_ -i + chars_ignored +1;
				}
				return this->index_ -i + chars_ignored; // the "real column index"
			}

			void mv_prev_line_term() {
				size_t i = this->index_;
				for (; i > 0 && !is_visual_line_term(this->buffer_[i]); i--);
				if (i == 0 && !is_visual_line_term()) {
					this->buffer_.insert(i, static_cast<char_T>(VISUAL_LINE_TERM));
				}
				this->index_ = i;
			}

			void mv_next_line_term() {
				size_t i = this->index_;
				size_t buf_size = this->buffer_.size();
				for (; i < buf_size && !is_visual_line_term(this->buffer_[i]); i++);
				if (i == this->buffer_.size()) {
					this->buffer_.insert(i, static_cast<char_T>(VISUAL_LINE_TERM));
				}
				this->index_ = i;
			}


# ifdef DEBUG
			void index(size_t index) {
				this->index_ = index;
			}
#endif



		private: //-- private variables --//

			string_T& buffer_;

			size_t index_;



	};

} // namespace arpterm


#endif // ARPTERM_CURSOR_HPP
