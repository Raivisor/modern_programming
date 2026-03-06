#include "LongNumber.hpp"

using mogger::LongNumber;

// ----------------------------------------------------------
// AUXILIARY FUNCTIONS
// ----------------------------------------------------------
LongNumber LongNumber::add_abs(const LongNumber& x, const LongNumber& y) {
	int max_length = (x.length > y.length) ? x.length : y.length;
	LongNumber result(max_length + 1, 1);

	int carry = 0;
	int i;
	for(i = 0; i < max_length; i++) {
		int sum = (i < x.length ? x.numbers[i] : 0) \
				+ (i < y.length ? y.numbers[i] : 0) + carry;
		result.numbers[i] = sum % 10;
		carry = sum / 10;
	}

	if(carry) {
		result.numbers[i] = carry;
	}
	else {
		result.length = max_length;
	}

	return result;
}

int LongNumber::compare_abs(const LongNumber& x, const LongNumber& y) {
	if(x.length != y.length) return (x.length > y.length) ? 1 : -1;

	for(int i = x.length-1; i >= 0; i--) {
		if(x.numbers[i] != y.numbers[i]) return (x.numbers[i] > y.numbers[i])\
		? 1 : -1;
	}

	return 0;
}

LongNumber LongNumber::subtract_abs(const LongNumber& x, const LongNumber& y) {
	LongNumber result(x.length, 1);

	int borrow = 0;
	for(int i = 0; i < x.length; i++) {
		int diff = x.numbers[i] - \
		(i < y.length ? y.numbers[i] : 0) - borrow;

		if(diff < 0) {
			diff += 10;
			borrow = 1;
		} else {
			borrow = 0;
		}

		result.numbers[i] = diff;
	}

	while(result.length > 1 && result.numbers[result.length-1] == 0){
		result.length--;
	}

	return result;
}

LongNumber LongNumber::multiply_abs(const LongNumber& x, const LongNumber& y) {
	int result_length = x.length + y.length;
	LongNumber result(result_length, 1);

	for(int i = 0; i < x.length; i++) {
		int carry = 0;
		for(int j = 0; j < y.length; j++) {
			int product = result.numbers[i + j] + x.numbers[i] * y.numbers[j] +\
			carry;
			result.numbers[i + j] = product % 10;
			carry = product / 10;
		}
		if(carry) {
			result.numbers[i + y.length] += carry;
		}
	}

	while(result.length > 1 && result.numbers[result.length-1] == 0){
		result.length--;
	}

	return result;

}

LongNumber LongNumber::divide_abs(const LongNumber& x, const LongNumber& y) {
	int result_length = x.length;
    LongNumber result(result_length, 1);
    LongNumber remainder(1, 1);

    for(int i = x.length - 1; i >= 0; i--) {
        remainder = multiply_abs(remainder, from_int(10));
        remainder = add_abs(remainder, from_digit(x.numbers[i]));

        int digit = 0;
		LongNumber temp = remainder;
        while(compare_abs(temp, y) >= 0) {
			temp = subtract_abs(temp, y);
			digit++;
		}

        result.numbers[i] = digit;
        remainder = temp;
    }

    while(result.length > 1 && result.numbers[result.length - 1] == 0) {
        result.length--;
    }
    
    return result;
}

// ----------------------------------------------------------
// CONSTRUCTORS
// ----------------------------------------------------------
LongNumber::LongNumber() {
	this->numbers = nullptr;
	this->length = 0;
	this->sign = 1;
}

LongNumber::LongNumber(int length, int sign) {
	if(length < 0) {
		this->length = 0;
		this->sign = 1;
		this->numbers = nullptr;
		return;
	}

	this->length = length;
	this->sign = (sign >= 0) ? 1 : -1;
	this->numbers = new int[this->length]();

	this->normalize();
}

LongNumber::LongNumber(const char* const str) {
	if(str == nullptr) {
		this->numbers = nullptr;
		this->length = 0;
		this->sign = 1;
		return;
	}

	int start_index = 0;
	if(str[start_index] == '-'){
		this->sign = -1;
		start_index = 1;
	} else {
		this->sign = 1;
	}

	int digit_count = 0;
	for(int i = start_index; str[i] != '\0'; i++) {
		if(str[i] == '0' && digit_count == 0){
			start_index += 1;
			continue;
		}
		if(str[i] >= '0' && str[i] <= '9') {
			digit_count += 1;
		} else {
			break;
		}
	}

	if(digit_count == 0){
		this->numbers = nullptr;
		this->length = 0;
		this->sign = 1;
		return;
	}

	this->length = digit_count;
	this->numbers = new int[this->length];
	for(int i = 0; i < this->length; i++){
		this->numbers[i] = str[start_index + this->length - i - 1]-'0';
	}

	this->normalize();
}

LongNumber::LongNumber(const LongNumber& x) {
	this->length = x.length;
	this->sign = x.sign;
	if(x.numbers == nullptr && x.length == 0) {
		this->numbers = nullptr;
	} else {
		this->numbers = new int[x.length];
		for(int i = 0; i < x.length; i++) {
			this->numbers[i] = x.numbers[i];
		}
	}

	this->normalize();
}

LongNumber::LongNumber(LongNumber&& x) {
	this->length = x.length;
	this->sign = x.sign;
	this->numbers = x.numbers;

	x.numbers = nullptr;
	x.length = 0;
	x.sign = 1;

	this->normalize();
}

// ----------------------------------------------------------
// DESTRUCTOR
// ----------------------------------------------------------
LongNumber::~LongNumber() {
	delete[] numbers;
}

// ----------------------------------------------------------
// ASSIGNMENT OPERATORS
// ----------------------------------------------------------
LongNumber& LongNumber::operator = (const char* const str) {
	delete[] numbers;
	this->numbers = nullptr;
	this->length = 0;
	this->sign = 1;

	if(str == nullptr) {
		return *this;
	}

	int start_index = 0;
	if(str[start_index] == '-'){
		this->sign = -1;
		start_index = 1;
	} else {
		this->sign = 1;
	}

	int digit_count = 0;
	for(int i = start_index; str[i] != '\0'; i++) {
		if(str[i] == '0' && digit_count == 0){
			start_index += 1;
			continue;
		}
		if(str[i] >= '0' && str[i] <= '9') {
			digit_count += 1;
		} else {
			break;
		}
	}

	if(digit_count == 0){
		this->numbers = nullptr;
		this->length = 0;
		this->sign = 1;
		return *this;
	}

	this->length = digit_count;
	this->numbers = new int[this->length];
	for(int i = 0; i < this->length; i++){
		this->numbers[i] = str[start_index + this->length - i - 1]-'0';
	}

	this->normalize();

	return *this;
}

LongNumber& LongNumber::operator = (const LongNumber& x) {
	if(this == &x) return *this;

	delete[] numbers;

	this->length = x.length;
	this->sign = x.sign;

	if(x.numbers == nullptr && x.length == 0) {
		this->numbers = nullptr;
	} else {
		this->numbers = new int[x.length];
		for(int i = 0; i < x.length; i++) {
			this->numbers[i] = x.numbers[i];
		}
	}

	this->normalize();

	return *this;
}

LongNumber& LongNumber::operator = (LongNumber&& x) {
	if(this == &x) return *this;

	delete[] numbers;

	this->length = x.length;
	this->sign = x.sign;
	this->numbers = x.numbers;

	x.numbers = nullptr;
	x.length = 0;
	x.sign = 1;

	this->normalize();

	return *this;
}

// ----------------------------------------------------------
// COMPARE OPERATORS
// ----------------------------------------------------------
bool LongNumber::operator == (const LongNumber& x) const {
	if(this == &x) return true;

	if(this->sign != x.sign || this->length != x.length) {
		return false;
	}

	for(int i = this->length - 1; i >= 0; i--) {
		if(this->numbers[i] != x.numbers[i]) return false;
	}

	return true;
}

bool LongNumber::operator != (const LongNumber& x) const {
	return !(*this == x);
}

bool LongNumber::operator > (const LongNumber& x) const {
	if(this == &x) return false;

	if(this->sign != x.sign) {
		return this->sign > x.sign;
	}

	if(this->length != x.length) {
		if(this->sign == 1) return this->length > x.length;
		else return this->length < x.length;
	}

	for(int i = this->length - 1; i >= 0; i--) {
		if(this->numbers[i] != x.numbers[i]) {
			if(this->sign == 1) return this->numbers[i] > x.numbers[i];
			else return this->numbers[i] < x.numbers[i];
		}

	}

	return false;
}

bool LongNumber::operator < (const LongNumber& x) const {
	return !(*this == x || *this > x);
}

// ----------------------------------------------------------
// ARITHMETIC OPERATORS
// ----------------------------------------------------------
LongNumber LongNumber::operator - () const {
	LongNumber result = *this;

	if(!result.is_zero()) {
		result.sign = -result.sign;
	}

	return result;
}

LongNumber LongNumber::operator + (const LongNumber& x) const {
	if(this->is_zero()) return x;
	if(x.is_zero()) return *this;

	if(this->sign == x.sign) {
		LongNumber result = add_abs(*this, x);
		result.sign = this->sign;
		return result;
	} else {
		int compare = compare_abs(*this, x);

		if(compare == 0) {
			LongNumber result;
			return result;
		} else if(compare == 1) {
			LongNumber result = subtract_abs(*this, x);
			result.sign = this->sign;
			return result;
		} else {
			LongNumber result = subtract_abs(x, *this);
			result.sign = x.sign;
			return result;
		}
	}
}

LongNumber LongNumber::operator - (const LongNumber& x) const {
	return *this + (-x);
}

LongNumber LongNumber::operator * (const LongNumber& x) const {
	if(this->is_zero()) return LongNumber();
	if(x.is_zero()) return LongNumber();

	LongNumber result = multiply_abs(*this, x);

	if(this->sign == x.sign) {
		result.sign = 1;
	} else {
		result.sign = -1;
	}

	return result;
}

LongNumber LongNumber::operator / (const LongNumber& x) const {
	if(x.is_zero()) throw std::runtime_error("Division by zero");
	if(this->is_zero()) return LongNumber();

	LongNumber result = divide_abs(*this, x);

	if(this->sign == x.sign) {
		result.sign = 1;
	} else {
		result.sign = -1;
	}

	return result;
}

LongNumber LongNumber::operator % (const LongNumber& x) const {
	if(x.is_zero()) throw std::runtime_error("Division by zero");

	LongNumber quotient = *this / x;
	LongNumber product = quotient * x;
	LongNumber remainder = *this - product;

	return remainder;
}

// ----------------------------------------------------------
// INFORMATION FUNCTIONS
// ----------------------------------------------------------

bool LongNumber::is_negative() const noexcept {
	return this->sign == -1;
}

bool LongNumber::is_zero() const noexcept {
	if(this->length == 0) return true;

	for(int i = 0; i < length; i++) {
		if(this->numbers[i] != 0) return false;
	}

	return true;
}

// ----------------------------------------------------------
// OTHERS PRIVATE FUNCTIONS
// ----------------------------------------------------------
int LongNumber::get_length(const char* const str) const noexcept {
	if(str == nullptr) return 0;
    
    const char* p = str;
    while(*p != '\0') {
        p++;
    }
    return p - str;
}

void LongNumber::normalize() {
	if(this->is_zero()) this->sign = 1;
}

LongNumber LongNumber::from_digit(int digit) {
    if(digit < 0 || digit > 9) {
        throw std::invalid_argument("Digit must be 0-9");
    }
    LongNumber result(1, 1);
    result.numbers[0] = digit;
    return result;
}

LongNumber LongNumber::from_int(int x) {
    if(x < 0) {
        LongNumber result = from_int(-x);
        result.sign = -1;
        return result;
    }
    
    if(x == 0) {
        return LongNumber();
    }
    
    int len = 0;
    int temp = x;
    while(temp > 0) {
        len++;
        temp /= 10;
    }
    
    LongNumber result(len, 1);
    temp = x;
    for(int i = 0; i < len; i++) {
        result.numbers[i] = temp % 10;
        temp /= 10;
    }
    
    return result;
}

// ----------------------------------------------------------
// FRIENDLY
// ----------------------------------------------------------
namespace mogger {
	std::ostream& operator << (std::ostream &os, const LongNumber& x) {
		if(x.sign == -1) os << '-';

		if(x.numbers == nullptr || x.length == 0) {
			os << "0";
			return os;
		}

		for(int i = x.length - 1; i >= 0; i--) {
			os << x.numbers[i];
		}

		return os;
	}
}