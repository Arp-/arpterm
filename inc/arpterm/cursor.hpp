
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
				size_t prev_col = this->column_distance();
				for (size_t i = 0; i < count; i++) {
					this->prev_visual_line_term();
				}
				if (this->index_ == 0 || is_line_term(this->buffer_[this->index_-1])) {
					this->buffer_.insert(this->index_, 1, static_cast<char_T>(' '));
				}
				this->index_--;
				std::cout << AT_DBG(this->index_) << std::endl;
				size_t new_col = this->column_distance();
				std::cout << AT_DBG(new_col) << std::endl;
				std::cout << AT_DBG(prev_col) << std::endl;
				int col_diff = prev_col - new_col;
				std::cout << AT_DBG(col_diff) << std::endl;
				if (prev_col > new_col) { 
					this->buffer_.insert(
							this->index_ + 1, col_diff, static_cast<char_T>(' '));
					this->index_ += col_diff;
				} else {
					this->index_ += col_diff;
				}
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

			size_t column_distance() const {
				size_t i = this->index_;
				for (i = this->index_; i > 0 && !is_line_term(this->buffer_[i]); i--);
				if (i == 0) { return this->index_ - i +1; }
				return this->index_ - i;
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
				std::cout << AT_DBG(i) << std::endl;
				if (i == 0) {
					this->buffer_.insert(i, 1, static_cast<char_T>('\r'));
				}
				if (is_logical_line_term(this->buffer_[i])) {
					i--;
				}
				std::cout << AT_DBG(i) << std::endl;
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
