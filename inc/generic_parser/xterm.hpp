
#ifndef GENERIC_PARSER_XTERM_PARSER_HPP
#define GENERIC_PARSER_XTERM_PARSER_HPP

#include <array>
#include <cstdint>
#include <type_traits>
#include "generic_parser/error_code.hpp"

namespace generic_parser {

	template <typename context_T,
			typename char_T = char, size_t term_seq_max_len_V = 4>
	class xterm {

		static_assert(std::is_integral<char_T>::value, 
				"template parameter char_T is not an integral_type!");

		public: //-- public types --//

			// let's try to fit into my L1 cacheline
			struct descriptor_t {

				public: //-- public functions --//

					inline descriptor_t(
							std::array<char,term_seq_max_len_V> s,
							std::array<char,term_seq_max_len_V> e):
						begin(s),
						end(e) {

						}

					inline ~descriptor_t() = default;
					
				public: //-- public members --//

					std::array<char, term_seq_max_len_V> begin; // default CSI is 16 bit length 

					std::array<char, term_seq_max_len_V> end; // 0 bites at the end will be ignored
			};

		private: //-- private typedefs --//
			using param_t = int;
		public: //-- public types --//
			using char_vec_t = std::vector<char_T>;
			using param_vec_t = std::vector<param_t>;
			// context_T the type of the context we'll give
			typedef void (*callback_t)(context_T&, const std::vector<param_t>&);

			typedef void (*trap_handler_t)(context_T&, const std::vector<char_T>&);

			using com_vec_t = std::vector<std::pair<descriptor_t, callback_t>>;

		public: //-- public functions --//

			xterm(context_T& ctx):
				buffer_(),
				descriptor_(),
				trap_handler_(NULL),
				context_(ctx) {};

			xterm(context_T& ctx, com_vec_t&& cv, trap_handler_t&& th):
				buffer_(), descriptor_(cv), trap_handler_(th), context_(ctx) {}

			inline ~xterm() = default;

			void add_command(descriptor_t&& desc, callback_t&& cb) {
				this->descriptor_t_.emplace_back(
						std::make_pair(std::forward(desc), std::forward(cb)));
			}

			void set_trap(trap_handler_t&& tcb) {
				this->trap_callback_ = tcb;
			}

			ec parse(const char_T ch) {
				this->buffer_.push_back(ch);
				for (const auto& pair : this->descriptor_) {
					const auto& desc = pair.first;
					size_t param_size = util::param_arr_len(desc.begin) + 
						util::param_arr_len(desc.end);
					bool start_match = 
						util::start_match(desc.begin, this->buffer_, this->buffer_.size());
					bool end_match = util::end_match(desc.end, this->buffer_);
					if (param_size >= this->buffer_.size() && start_match && end_match) {
						auto&& param_buf = 
							util::get_param_vec(desc.begin, desc.end, this->buffer_);
						// TODO parse the params
						std::vector<param_t> param_vec;
						if (!util::parse_param_vec(param_buf, param_vec)) {
							pair.second(this->context_, param_vec); 
							this->clear_state();
							return ec::OK;
						} else {
							std::cerr << "TRAPPED INVALID PARAMETER!!!" << std::endl;
							this->trap_handler_(this->context_, this->buffer_);
							this->clear_state();
							return ec::FAIL;
						}
					} else if (start_match) {
						return ec::OK; // NOTE this needs some refining 
					}
				}

				std::cerr << "TRAPPED NO MATCH" << std::endl;
				this->trap_handler_(this->context_, this->buffer_);
				this->clear_state();
				return ec::OK;
			}

		private: //-- private functions --//

			void clear_state() {
				this->buffer_.clear();
			}




		private: //-- private functions --//

			std::vector<char_T> buffer_;

			com_vec_t descriptor_;

			trap_handler_t trap_handler_;

			context_T& context_;


	};


} // namespace generic_parser


#endif // GENERIC_PARSER_XTERM_PARSER_HPP
