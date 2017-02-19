
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

			void move_to_line_begin() {
				std::cout << "col_pos: " << this->column_position() << std::endl;
				this->index_ -= this->column_position();
				std::cout << "index: " << this->index_ << std::endl;
			}

			void move_cur_up(size_t count) {
				size_t col = this->column_position();
				for (size_t i = 0; i < count; i++) {
					this->move_to_prev_line_end();
					std::cout << "line_beg: " << this->index_ << std::endl;
				}
				std::cout << "index: " << this->index_ << std::endl;
				size_t row_end = this->column_position();
				std::cout << "COL: " << col << std::endl;
				std::cout << "index: " << this->index_ << std::endl;
				std::cout << "ROW_END: " << row_end << std::endl;
				size_t col_diff = std::abs((long int)col - (long int)row_end);
				std::cout << "COL_DIFF: " << col_diff << std::endl;
				if (col > row_end) {
					this->buffer_.insert(row_end+1, col_diff, ' ');
					this->index_ += col_diff;
				} else if (this->index_ > (col_diff)) {
					this->index_ -= col_diff;
				} else {
					this->index_ = 0;
				}
			}

			void move_cur_down(size_t count);

			void move_cur_right(size_t count);

			void move_cur_left(size_t count);

			size_t index() { 
				return this->index_;
			}


		private: //-- private functions --//

			void move_to_prev_line_end() {
				this->move_to_line_begin();
				if (this->index_ != 0) {
					this->index_--;
				}
				this->skip_line_term_backwards();
			}

			void skip_line_term_backwards() {
				while (this->is_line_term(this->buffer_[this->index_])
						&& this->index_ != 0) {
					this->index_--;
					std::cout << "ltb, index: " << this->index_ << std::endl;
				}
			}

			bool is_line_term(char_T c) const {
				return c == VISUAL_LINE_TERM || c == LOGICAL_LINE_TERM;
			}

			size_t column_position() const {
				size_t p = this->index_;
				if (p == this->buffer_.size()) {
					p--;
				}
				if (is_line_term(this->buffer_[p])) {
					p--;
				}
				while (!this->is_line_term(this->buffer_[p]) && 
						p != 0) {
					p--;
				}
				return this->index_ - (p+1);
			}



		private: //-- private variables --//

			string_T& buffer_;

			size_t index_;



	};

} // namespace arpterm


#endif // ARPTERM_CURSOR_HPP
