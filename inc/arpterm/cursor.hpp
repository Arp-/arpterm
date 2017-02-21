
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
				size_t col = this->column_index();
				for (size_t i = 0; i < count; i++) {
					this->move_to_prev_line_end();
				}
				size_t newcol = this->column_index();
				std::cout << "col: " << col << std::endl;
				std::cout << "newcol: " << newcol << std::endl;
				if (col > newcol) {
					// add col-newcol spaces
					this->buffer_.insert(this->index_, col - newcol, 
							static_cast<char_T>(' '));
					return;
				}
				this->index_ -= (newcol - col);
			}

			void move_cur_down(size_t count);

			void move_cur_right(size_t count);

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


			void move_to_next_line_end() {
				this->move_to_line_end();
				size_t i = this->index_;
			}

			void move_to_line_end() {
				size_t i = this->index_;
				const size_t buf_size = this->buffer_.size();
				if (this->index_ == buf_size) {
					return;
				}
				while (!is_line_term(this->buffer_[i+1]) && (i+1) != buf_size) {
					i++;
					std::cout << "i: " << i << std::endl;
					std::cout << "bufi: " << this->buffer_[i] << std::endl;
				}
				if ((i+1) == buf_size) {
					i++;
				}
				this->index_ = i;
			}

			void move_to_line_beg() {
				this->index_ -= column_index();
			}

			// moves to \r character
			// NOTE there must be a previous line othervise it goes to the first
			// character
			void move_to_prev_line_end() { 
				this->move_to_line_beg();
				std::cout << "ind: " << this->index_ << std::endl;
				size_t i = this->index_;
				while (is_line_term(this->buffer_[i-1]) && (i-1) != 0 && i != 0) {
					i--;
				}
				if ((i-1) == 0 || i == 0) {
					this->buffer_.insert(0, 1, static_cast<char_T>('\r'));
					i = 0;
					printf("first: %02x\n", this->buffer_[0] & 0xff);
				}
				this->index_ = i;
			}

			size_t column_index() const {
				if (this->index_ == 0 ) {
					return 0;
				}
				size_t i = this->index_;
				while (!is_line_term(this->buffer_[i-1]) && (i-1) != 0) {
					i--;
				}
				if ((i-1) == 0) {
					i--;
				}
				return this->index_ - i;
			}




		private: //-- private variables --//

			string_T& buffer_;

			size_t index_;



	};

} // namespace arpterm


#endif // ARPTERM_CURSOR_HPP
