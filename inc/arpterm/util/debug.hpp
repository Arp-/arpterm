

#ifndef ARPTERM_UTIL_DEBUG_HPP
#define ARPTERM_UTIL_DEBUG_HPP

#ifdef DEBUG


#define AT_DBG(X) #X << ": " << X

namespace arpterm { namespace util { 

	void str_hex_print(const std::string& str);

} } // namespace util // namespace arpterm


#endif // DEBUG
#endif // ARPTERM_UTIL_DEBUG_HPP
