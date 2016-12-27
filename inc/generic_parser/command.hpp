
#ifndef GENERIC_PARSER_COMMAND_HPP
#define GENERIC_PARSER_COMMAND_HPP

#include <iostream>
#include <vector>
#include <type_traits>
#include "generic_parser/util.hpp"

namespace generic_parser {

	enum class ec {
		OK = 0,
		FAIL = 1
	};

	template <typename Param, typename char_T = char>
	class command_parser_t {

		typedef void(*param_func_t)(Param&);
		using char_vec_t = std::vector<char_T>;
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

			inline void add_command(char_vec_t&& com, param_func_t func) {
				this->command_vec_.emplace_back(std::make_pair(com, func));
			}

			ec parse(const char_T sign) {
				curr_buff_.emplace_back(sign);
				depth_++;
				bool found = false;
				for (const auto& elem : command_vec_) {
					const auto& com_str = elem.first;
					if (util::vector_compare(this->curr_buff_, com_str, this->depth_)) {
						found = true;
						if (com_str.size() == depth_) {
							elem.second(this->param_);
							this->clear_state();
						}
					}
				}
				if (found) {
					return ec::OK;
				}
				// we couldn't partially parse anityhing
				this->clear_state();
				return ec::FAIL;
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
