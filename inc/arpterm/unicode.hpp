/**
 * few untility unicode functions
 * i might not need them, i might, still don't know
 */
#ifndef ARPTERM_UNICODE_HPP
#define ARPTERM_UNICODE_HPP

#include <type_traits>

namespace arpterm { namespace unicode {

	enum class unicode_type {
		U8 = 1,
		U16 = 2,
		U32 = 3
	};

	struct trimmed_unicode_t { 
		unicode_type type;
		union {
			uint8_t u8;
			uint16_t u16;
			uint32_t u32;
		};
	};


	inline size_t get_unicode_valuable_size(uint32_t uc) {
		uint32_t mask = 0xff << 24;
		size_t i = 0;
		for (i = 4; (mask & uc) == 0 && i > 0; i--) {
			mask |= mask >> 8;
		}
		return i;
	}

	inline trimmed_unicode_t trim(uint32_t uc) {
		size_t len = get_unicode_valuable_size(uc);	
		trimmed_unicode_t trimmed;
		switch (len) {
			case 4:
			case 3:
				trimmed.type = unicode_type::U32;
				trimmed.u32 = uc;
				break;
			case 2:
				trimmed.type = unicode_type::U16;
				trimmed.u16 = static_cast<uint16_t>(uc);
				break;
			case 1:
			case 0:
				trimmed.type = unicode_type::U8;
				trimmed.u8 = static_cast<uint8_t>(uc);
				break;
		}
		return trimmed;
	}

	template <bool expr, typename true_T, typename false_T>
	struct static_if {
		using type = false_T;
		static constexpr bool value = false;
	};

	template <typename true_T, typename false_T>
	struct static_if<true, true_T, false_T> {
		using type = true_T;
		static constexpr bool value = true;
	};

	template <typename ... Args>
	struct void_t {
		using type = void;
	};

	template <typename T>
	struct is_of_unicode {
		using helper_type = 
				static_if<std::is_same<T, uint8_t>::value, T,
					typename static_if<std::is_same<T, uint16_t>::value, T,
						typename static_if<std::is_same<T, uint32_t>::value, T, std::false_type >::type
					>::type
				>;
		using type = typename helper_type::type;
		static constexpr bool value = helper_type::value;
	};

} } // arpterm // unicode

#endif // ARPTERM_UNICODE_HPP
