
#ifndef GENERIC_PARSER_COMMAND_HPP
#define GENERIC_PARSER_COMMAND_HPP

#include <iostream>
#include <vector>
#include <type_traits>
#include "generic_parser/util.hpp"

namespace generic_parser {

	template <typename Param>
	class command_parser_t {

		typedef void(*param_func_t)(Param&);
		using char_vec_t = std::vector<char>;
		using com_vec_t = std::vector<std::pair<char_vec_t, param_func_t>>;

		public: //-- public functions --//

			inline command_parser_t(Param& param, com_vec_t&& vec):
					depth_(0),
					param_(param),
					curr_buff_(),
					command_vec_(vec) {

			}

			inline command_parser_t(Param& param): 
					depth_(0),
					param_(param),
					curr_buff_(),
					command_vec_() {

			}

			void add_command(char_vec_t&& com, param_func_t func) {
				this->command_vec_.emplace_back(std::make_pair(com, func));
			}

			void parse(const char sign) {
				curr_buff_.emplace_back(sign);
				depth_++;
				for (const auto& elem : command_vec_) {
					const auto& com_str = elem.first;
					if (com_str.size() == depth_
							&& util::vector_compare(
								this->curr_buff_, com_str, this->depth_)) {
						elem.second(this->param_);
						this->clear_state();
					}
				}
			}

		private: //-- private functions --//

			void clear_state() {
				this->curr_buff_.clear();
				this->depth_ = 0;
			}


		private: //-- private members --//

			unsigned int depth_;

			Param& param_;

			char_vec_t curr_buff_;

			com_vec_t command_vec_;

	};




} // namespace xterm_parser


#endif // GENERIC_PARSER_CHAR_SEQUENCE_HPP
