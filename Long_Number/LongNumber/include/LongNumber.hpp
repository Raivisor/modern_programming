#pragma once

#include <iostream>

namespace mogger {
	class LongNumber {
		private:
			int* numbers;
			int length;
			int sign;
		
		public:
			LongNumber();
			LongNumber(int length, int sign);
			LongNumber(const char* const str);
			LongNumber(const LongNumber& x);
			LongNumber(LongNumber&& x);
			
			~LongNumber();
			
			LongNumber& operator = (const char* const str);
			LongNumber& operator = (const LongNumber& x);
			LongNumber& operator = (LongNumber&& x);
			
			bool operator == (const LongNumber& x) const;
			bool operator != (const LongNumber& x) const;
			bool operator > (const LongNumber& x) const;
			bool operator < (const LongNumber& x) const;
			
			LongNumber operator - () const;
			LongNumber operator + (const LongNumber& x) const;
			LongNumber operator - (const LongNumber& x) const;
			LongNumber operator * (const LongNumber& x) const;
			LongNumber operator / (const LongNumber& x) const;
			LongNumber operator % (const LongNumber& x) const;
			
			bool is_negative() const noexcept;
			bool is_zero() const noexcept;
			
			friend std::ostream& operator << (std::ostream &os, const LongNumber& x);
			
		private:
			int get_length(const char* const str) const noexcept;
			void normalize();

			static LongNumber add_abs(const LongNumber& x, const LongNumber& y);
			static int compare_abs(const LongNumber& x, const LongNumber& y);
			static LongNumber subtract_abs(const LongNumber& x, const LongNumber& y);
			static LongNumber multiply_abs(const LongNumber& x, const LongNumber& y);
			static LongNumber divide_abs(const LongNumber& x, const LongNumber& y);
			static LongNumber from_digit(const int digit);
			static LongNumber from_int(const int x);
	};
}