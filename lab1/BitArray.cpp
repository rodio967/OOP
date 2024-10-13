#include "BitArray.h"
#include <stdexcept>
#include <algorithm>

const int BITS_PER_WORD = sizeof(unsigned long) * 8;

int words_needed(int bits) {
    return (bits + BITS_PER_WORD - 1) / BITS_PER_WORD;
}

static void clear_excess_bits(std::vector<unsigned long>& data, int num_bits) {
    int excess_bits = words_needed(num_bits) * BITS_PER_WORD - num_bits;

    if (excess_bits > 0 && !data.empty()) {
        unsigned long mask = (~0UL) >> excess_bits;
        data.back() &= mask;
    }
}

BitArray::BitArray() : num_bits_(0) {}

BitArray::~BitArray() = default;

BitArray::BitArray(int num_bits, unsigned long value) : num_bits_(num_bits) {
    if (num_bits < 0) {
        throw std::invalid_argument("Size must be non-negative");
    }

    int words = words_needed(num_bits);
    data_.resize(words, 0);
    if (words > 0) {
        data_[0] = value;
    }
}

BitArray::BitArray(const BitArray& b) : data_(b.data_), num_bits_(b.num_bits_) {}

void BitArray::swap(BitArray& b) {
    std::swap(data_, b.data_);
    std::swap(num_bits_, b.num_bits_);
}

BitArray& BitArray::operator=(const BitArray& b) {
    if (this != &b) {
        data_ = b.data_;
        num_bits_ = b.num_bits_;
    }
    return *this;
}

void BitArray::resize(int num_bits, bool value) {
    if (num_bits < 0) {
        throw std::invalid_argument("Number of bits cannot be negative");
    }

    int i = num_bits_;
    int old_words = words_needed(num_bits_);
    int new_words = words_needed(num_bits);
    num_bits_ = num_bits;

    data_.resize(new_words, 0);

    if (value) {
        for (int i; i < num_bits; ++i) {
            set(i, true);
        }
    }

    clear_excess_bits(data_, num_bits);
}

void BitArray::clear() {
    data_.clear();
    num_bits_ = 0;
}

void BitArray::push_back(bool bit) {
    resize(num_bits_+1,false);
    set(num_bits_-1,bit);
}

BitArray& BitArray::operator&=(const BitArray& b) {
    if (num_bits_ != b.num_bits_) {
        throw std::invalid_argument("BitArrays must be of the same size for AND operation");
    }
    for (size_t i = 0; i < data_.size(); ++i) {
        data_[i] &= b.data_[i];
    }
    return *this;
}

BitArray& BitArray::operator|=(const BitArray& b) {
    if (num_bits_ != b.num_bits_) {
        throw std::invalid_argument("BitArrays must be of the same size for OR operation");
    }
    for (size_t i = 0; i < data_.size(); ++i) {
        data_[i] |= b.data_[i];
    }
    return *this;
}

BitArray& BitArray::operator^=(const BitArray& b) {
    if (num_bits_ != b.num_bits_) {
        throw std::invalid_argument("BitArrays must be of the same size for XOR operation");
    }
    for (size_t i = 0; i < data_.size(); ++i) {
        data_[i] ^= b.data_[i];
    }
    return *this;
}

BitArray& BitArray::operator<<=(int n) {
    if (n < 0) {
        throw std::invalid_argument("Shift amount must be non-negative");
    }
    if (n == 0) return *this;

    if (n >= num_bits_) {
        clear();
        return *this;
    }

    for (int i = num_bits_ - 1; i >= n; i--) {
        set(i,(*this)[i - n]);
    }

    for (int i = n - 1; i >= 0; i--) {
        reset(i);
    }

    clear_excess_bits(data_, num_bits_);

    return *this;
}

BitArray& BitArray::operator>>=(int n) {
    if (n < 0) {
        throw std::invalid_argument("Shift amount must be non-negative");
    }
    if (n == 0) return *this;

    if (n >= num_bits_) {
        clear();
        return *this;
    }

    for (int i = 0; i + n < num_bits_; i++){
        set(i,(*this)[i + n]);
    }

    for (int i = num_bits_ - n; i < num_bits_; i++){
        reset(i);
    }

    clear_excess_bits(data_, num_bits_);

    return *this;
}

BitArray BitArray::operator<<(int n) const {
    BitArray result(*this);
    result <<= n;
    return result;
}

BitArray BitArray::operator>>(int n) const {
    BitArray result(*this);
    result >>= n;
    return result;
}

BitArray& BitArray::set(int n, bool val) {
    if (n < 0 || n >= num_bits_) {
        throw std::out_of_range("Bit index out of range");
    }
    int word = n / BITS_PER_WORD;
    int bit = n % BITS_PER_WORD;
    if (val) {
        data_[word] |= (1UL << bit);
    } else {
        data_[word] &= ~(1UL << bit);
    }
    return *this;
}

BitArray& BitArray::set() {
    for (size_t i = 0; i < data_.size(); ++i) {
        data_[i] = ~0UL;
    }

    clear_excess_bits(data_, num_bits_);
    return *this;
}

BitArray& BitArray::reset(int n) {
    return set(n, false);
}

BitArray& BitArray::reset() {
    for (auto& word : data_) {
        word = 0;
    }

    return *this;
}


bool BitArray::any() const {
    for (const auto& word : data_) {
        if (word != 0) return true;
    }
    return false;
}

bool BitArray::none() const {
    return !any();
}

BitArray BitArray::operator~() const {
    BitArray result(*this);
    for (auto& word : result.data_) {
        word = ~word;
    }


    clear_excess_bits(result.data_, num_bits_);
    return result;
}

int BitArray::count() const {
    int cnt = 0;
    for (const auto& word : data_) {
        for (int i = 0; i < BITS_PER_WORD; i++) {
            if (word & (1UL << i)) {
                cnt++;
            }
        }
    }
    return cnt;
}

bool BitArray::operator[](int i) const {
    if (i < 0 || i >= num_bits_) {
        throw std::out_of_range("Bit index out of range");
    }
    int word = i / BITS_PER_WORD;
    int bit = i % BITS_PER_WORD;
    return (data_[word] & (1UL << bit));
}

int BitArray::size() const {
    return num_bits_;
}

bool BitArray::empty() const {
    return num_bits_ == 0;
}

std::string BitArray::to_string() const {
    std::string s;
    for (int i = num_bits_ - 1; i >= 0; --i) {
        s += ((*this)[i] ? '1' : '0');
    }
    return s;
}

bool operator==(const BitArray & a, const BitArray & b) {
    return (a.num_bits_ == b.num_bits_) && (a.data_ == b.data_);
}

bool operator!=(const BitArray & a, const BitArray & b) {
    return !(a == b);
}

BitArray operator&(const BitArray& b1, const BitArray& b2) {
    if (b1.size() != b2.size()) {
        throw std::invalid_argument("BitArrays must be of the same size for AND operation");
    }
    BitArray result(b1);
    result &= b2;
    return result;
}

BitArray operator|(const BitArray& b1, const BitArray& b2) {
    if (b1.size() != b2.size()) {
        throw std::invalid_argument("BitArrays must be of the same size for OR operation");
    }
    BitArray result(b1);
    result |= b2;
    return result;
}

BitArray operator^(const BitArray& b1, const BitArray& b2) {
    if (b1.size() != b2.size()) {
        throw std::invalid_argument("BitArrays must be of the same size for XOR operation");
    }
    BitArray result(b1);
    result ^= b2;
    return result;
}
