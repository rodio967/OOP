#ifndef BITARRAY_H
#define BITARRAY_H

#include <vector>
#include <string>

/**
 * @class BitArray
 * @brief A dynamic array of bits with various bitwise operations.
 *
 * The BitArray class provides a compact representation of bits and 
 * allows for efficient manipulation and bitwise operations.
 */
class BitArray {
public:

    /**
     * @brief Default constructor. Initializes an empty BitArray.
     */
    BitArray();

    /**
     * @brief Destructor. Cleans up any allocated resources.
     */
    ~BitArray();

    /**
     * @brief Constructs a BitArray with a specified number of bits.
     *
     * The first sizeof(unsigned long) bits are initialized with the given value.
     *
     * @param num_bits The number of bits to allocate.
     * @param value The initial value for the first sizeof(unsigned long) bits.
     */
    explicit BitArray(int num_bits, unsigned long value = 0);

    /**
     * @brief Copy constructor.
     *
     * @param b The BitArray to copy from.
     */
    BitArray(const BitArray& b);

    /**
     * @brief Swaps the contents of this BitArray with another.
     *
     * @param b The BitArray to swap with.
     */
    void swap(BitArray& b);

    /**
     * @brief Assignment operator.
     *
     * @param b The BitArray to assign from.
     * @return Reference to this BitArray.
     */
    BitArray& operator=(const BitArray& b);

    /**
     * @brief Resizes the BitArray to a new size.
     *
     * If the array is expanded, new bits are initialized to the specified value.
     *
     * @param num_bits The new size in bits.
     * @param value The value to initialize new bits with (default is false).
     */
    void resize(int num_bits, bool value = false);

    /**
     * @brief Clears all bits in the BitArray.
     */
    void clear();

    /**
     * @brief Adds a new bit to the end of the BitArray.
     *
     * If necessary, reallocates memory to accommodate the new bit.
     *
     * @param bit The bit value to add (true or false).
     */
    void push_back(bool bit);

    /**
     * @brief Bitwise AND assignment operator.
     *
     * Operates only on BitArrays of the same size.
     *
     * @param b The BitArray to AND with.
     * @return Reference to this BitArray.
     */
    BitArray& operator&=(const BitArray& b);

    /**
     * @brief Bitwise OR assignment operator.
     *
     * Operates only on BitArrays of the same size.
     *
     * @param b The BitArray to OR with.
     * @return Reference to this BitArray.
     */
    BitArray& operator|=(const BitArray& b);

    /**
     * @brief Bitwise XOR assignment operator.
     *
     * Operates only on BitArrays of the same size.
     *
     * @param b The BitArray to XOR with.
     * @return Reference to this BitArray.
     */
    BitArray& operator^=(const BitArray& b);

    /**
     * @brief Left shift assignment operator with zero fill.
     *
     * @param n The number of bits to shift.
     * @return Reference to this BitArray.
     */
    BitArray& operator<<=(int n);

    /**
     * @brief Right shift assignment operator with zero fill.
     *
     * @param n The number of bits to shift.
     * @return Reference to this BitArray.
     */
    BitArray& operator>>=(int n);

    /**
     * @brief Left shift operator with zero fill.
     *
     * @param n The number of bits to shift.
     * @return A new BitArray that is the result of the shift.
     */
    BitArray operator<<(int n) const;

    /**
     * @brief Right shift operator with zero fill.
     *
     * @param n The number of bits to shift.
     * @return A new BitArray that is the result of the shift.
     */
    BitArray operator>>(int n) const;

    /**
     * @brief Sets the bit at the specified index to the given value.
     *
     * @param n The index of the bit to set.
     * @param val The value to set the bit to (default is true).
     * @return Reference to this BitArray.
     */
    BitArray& set(int n, bool val = true);

    /**
     * @brief Sets all bits in the BitArray to true.
     *
     * @return Reference to this BitArray.
     */
    BitArray& set();

    /**
     * @brief Resets the bit at the specified index to false.
     *
     * @param n The index of the bit to reset.
     * @return Reference to this BitArray.
     */
    BitArray& reset(int n);

    /**
     * @brief Resets all bits in the BitArray to false.
     *
     * @return Reference to this BitArray.
     */
    BitArray& reset();

    /**
     * @brief Checks if any bit in the BitArray is set to true.
     *
     * @return True if at least one bit is true, otherwise false.
     */
    bool any() const;

    /**
     * @brief Checks if all bits in the BitArray are set to false.
     *
     * @return True if all bits are false, otherwise false.
     */
    bool none() const;

    /**
     * @brief Bitwise NOT operator.
     *
     * @return A new BitArray that is the bitwise inversion of this BitArray.
     */
    BitArray operator~() const;

    /**
     * @brief Counts the number of bits set to true.
     *
     * @return The count of true bits.
     */
    int count() const;

    /**
     * @brief Accesses the bit at the specified index.
     *
     * @param i The index of the bit to access.
     * @return The value of the bit (true or false).
     */
    bool operator[](int i) const;

    /**
     * @brief Returns the number of bits in the BitArray.
     *
     * @return The size of the BitArray.
     */
    int size() const;

    /**
     * @brief Checks if the BitArray is empty.
     *
     * @return True if the BitArray is empty, otherwise false.
     */
    bool empty() const;

    /**
     * @brief Converts the BitArray to its string representation.
     *
     * @return A string representing the BitArray.
     */
    std::string to_string() const;

    /**
    * @brief Equality comparison operator for BitArray.
    *
    * @param a The first BitArray.
    * @param b The second BitArray.
    * @return True if both BitArrays are equal, otherwise false.
    */
    friend bool operator==(const BitArray& a, const BitArray& b);


    /**
    * @brief Inequality comparison operator for BitArray.
    *
    * @param a The first BitArray.
    * @param b The second BitArray.
    * @return True if BitArrays are not equal, otherwise false.
    */
    friend bool operator!=(const BitArray& a, const BitArray& b);

private:
    std::vector<unsigned long> data_; ///< Internal storage for bits.
    int num_bits_; ///< Number of bits in the BitArray.

    const int BITS_PER_WORD = sizeof(unsigned long) * 8;

    int words_needed(int bits) const{
        return (bits + BITS_PER_WORD - 1) / BITS_PER_WORD;
    }

    void clear_excess_bits(int num_bits) {
        int excess_bits = words_needed(num_bits) * BITS_PER_WORD - num_bits;
        if (excess_bits > 0 && !data_.empty()) {
            unsigned long mask = (~0UL) >> excess_bits;
            data_.back() &= mask;
        }
    }

    void ensure_capacity(int bit);
};


/**
 * @brief Bitwise AND operator for BitArray.
 *
 * @param b1 The first BitArray.
 * @param b2 The second BitArray.
 * @return A new BitArray that is the bitwise AND of b1 and b2.
 */
BitArray operator&(const BitArray& b1, const BitArray& b2);

/**
 * @brief Bitwise OR operator for BitArray.
 *
 * @param b1 The first BitArray.
 * @param b2 The second BitArray.
 * @return A new BitArray that is the bitwise OR of b1 and b2.
 */
BitArray operator|(const BitArray& b1, const BitArray& b2);

/**
 * @brief Bitwise XOR operator for BitArray.
 *
 * @param b1 The first BitArray.
 * @param b2 The second BitArray.
 * @return A new BitArray that is the bitwise XOR of b1 and b2.
 */
BitArray operator^(const BitArray& b1, const BitArray& b2);

#endif
