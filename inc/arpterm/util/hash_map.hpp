#ifndef ARPTERM_UTIL_HASH_MAP
#define ARPTERM_UTIL_HASH_MAP
#include <cstdio>
#include <array>
#include <cstring>
#include <type_traits>

#include <iostream>

namespace arpterm { namespace util {


	template <typename key_T, typename val_T, size_t len_V>
	class hash_map {

		static_assert(std::is_same<key_T, typename std::remove_reference<key_T>::type>::value, 
				"HASH MAP KEY MUST NOT BE REFERENCE_TYPE");
		static_assert(std::is_same<val_T, typename std::remove_reference<val_T>::type>::value, 
				"HASH MAP VALUE MUST NOT BE A REFERENCE_TYPE");

		using key_container_t = std::array<key_T, len_V>;
		using val_container_t = std::array<val_T, len_V>;
		using set_container_t = std::array<bool, len_V>;
		using container_t = hash_map<key_T, val_T, len_V>;

		friend class iterator;

		class iterator {

			struct k_v_pair {
				key_T& key;
				val_T& val;
			};
			
			public: //-- public functiosn --//
				iterator(hash_map& map, int index): index_(index), hmap_(map) {};
				iterator(const iterator& it): index_(it.index_), hmap_(it.hmap_) {}; 
				~iterator() = default;
				iterator& operator++() { 
					const auto& isset = this->hmap_.set_container_;
					do { 
						this->index_++;
					} while (!isset[this->index_] && this->index_ < len_V);
					return *this; 
				}
				k_v_pair operator*() { return { this->hmap_.key_container_[this->index_], this->hmap_.val_container_[this->index_] }; }
				bool operator!=(const iterator& it) { return this->index_ != it.index_; }
				//bool operator==(const iterator& it) { return this->index_ == it.index_; }

			private: //-- private variables --//
				int index_ = 0;
				hash_map& hmap_;
		};


		public: //-- public boilerplate --//

			hash_map(): key_container_(), val_container_(), set_container_() {
				memset(&this->key_container_, 0, sizeof(this->key_container_));
				memset(&this->val_container_, 0, sizeof(this->val_container_));
				memset(&this->set_container_, false, sizeof(this->set_container_));
			}

			hash_map(const hash_map&) = delete;

			hash_map(hash_map&&) = delete;

			~hash_map() = default;

			hash_map& operator=(const hash_map&) = delete;

			hash_map& operator=(hash_map&&) = delete;

			container_t::iterator begin() { return iterator { *this, 0 }; }

			container_t::iterator end() { return iterator { *this, len_V }; }

		public: //-- public functions --//

			inline size_t size() noexcept { return len_V; }

			inline int set(const key_T& key, const val_T& val) noexcept {
				int i = this->get_first_unset_unique_index(key);
				if (i < 0) { i; }
				this->key_container_[i] = key;
				this->val_container_[i] = val;
				this->set_container_[i] = true;
				return 0;
			}

			inline val_T* get(const key_T& key) noexcept {
				for (int i = 0; i < len_V; i++) {
					const key_T& key_ref = this->key_container_[i];
					bool is_set = this->set_container_[i];
					if (key_ref == key && is_set) {
						return &(this->val_container_[i]);
					}
				}
				return nullptr;
			}

			inline int remove(const key_T& key) noexcept {
				for (int i = 0; i < len_V; i++) {
					const key_T& key_ref = this->key_container_[i];
					bool is_set = this->set_container_[i];
					if (key_ref == key && is_set) {
						this->set_container_[i] = false;
						return 0;
					}
				}
				return -1;
			}

		private: //-- private functions --//

			inline int get_first_unset_unique_index(const key_T& key) noexcept {
				int first_unset = -1;
				for (int i = len_V -1; i >= 0; i--) {
					const auto& key_ref = this->key_container_[i];
					bool is_set = this->set_container_[i];
					if (key_ref == key) {
						return i;
					}
					if (!is_set) {
						first_unset = i;
					}
				}
				return first_unset; // our container is full so return error
			}


		private: //-- private variables --//

			key_container_t key_container_;

			val_container_t val_container_;

			set_container_t set_container_;

	};





}} // namespace arpterm // namespace util

#endif // ARPTERM_UTIL_HASH_MAP
