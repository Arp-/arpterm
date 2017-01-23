
#ifndef GENERIC_PARSER_XTERM_PARSER_HPP
#define GENERIC_PARSER_XTERM_PARSER_HPP

#include <array>
#include <cstdint>
#include "generic_parser/error_code.hpp"

namespace generic_parser {

	template <typename context_T,
			typename char_T = char, size_t term_seq_max_len_V = 4>
	class xterm {

		public: //-- public types --//

			// let's try to fit into my L1 cacheline
			struct descriptor_t {

				public: //-- public functions --//

					inline descriptor_t(
							std::array<char,term_seq_max_len_V> s,
							std::array<char,term_seq_max_len_V> e):
						start(s),
						end(e) {

						}

					inline ~descriptor_t() = default;
					
				public: //-- public members --//

					std::array<char, term_seq_max_len_V> start; // default CSI is 16 bit length 

					std::array<char, term_seq_max_len_V> end; // 0 bites at the end will be ignored
			};

			using param_t = int;
			using char_T = char_T;
			// context_T the type of the context we'll give
			typedef void (*callback_t)(context_T&, const std::vector<param_t>&);

			typedef void (*trap_callback_t)(context_T&, std::vector<char_T>&);

		public: //-- public functions --//

			xterm(context_T& ctx)

			inline ~xterm() = default;

			void add_command(descriptor_t&& desc, callback_t&& cb) {
				this->descriptor_t_.emplace_back(
						std::make_pair(std::forward(desc), std::forward(cb)));
			}

			void set_trap(trap_callback_t&& tcb) {
				this->trap_callback_ = tcb;
			}

			ec parse(const char_T ch) {
				this->buffer_.add(ch);
				for (const auto& pair : this->descriptor_) {

				}

				this->trap_callback_(this->context_, this->buffer_);
				this->buffer_.erase();
			}

		private: //-- private functions --//

			bool compare_descriptor(const auto& descriptor_t desc,
					const std::vector<char_T>& char_vec) const {
				if (char_vec.size() < 2) { // parse the control char ESC or CSI or etc
					if (char_vec[0] == desc.start_char[0]) { // first char_matches
						if (desc.start_char[1] == 0) {
							goto head;
						} else if (char_vec[1] == desc.start_char[1]) {
							goto head;
						}
						return false;
					}
				}
			head: // we parsed the head now we chack if we have an extra param set?0
				if (desc.xterm_custom_param >= 0x3B && 
						desc.xterm_custom_param <= 0x3F) 


			}



		private: //-- private functions --//

			std::vector<char_T> buffer_;

			std::vector<std::pair<descriptor_t, callback_t>> descriptor_;

			context_T& context_;

			trap_callback_t trap_handler_;

	};


} // namespace generic_parser


#endif // GENERIC_PARSER_XTERM_PARSER_HPP
