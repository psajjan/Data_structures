/**
 *
 * @author P Sajjan Raj Jain
 *
 * @date 2015/08/17
 *
 * Program to illustrate Binary Indexed Tree data structure.
 *
 * Binary Indexed Tree data structure provides a O(log n) solution
 * for querying prefix sum and updating prefix sum.
 * Input array and the array used in Binary Indexed Tree is 1-index based.
 * Element at index 0 in both the array is dummy.
 *
 */

#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

//! @class BinaryIndexedTree
//! @brief Represent a binary indexed tree class.
//!
//! The array that stores the cumulative frequencies is 1-based index.
class BinaryIndexedTree
{
    public:
        BinaryIndexedTree();
        ~BinaryIndexedTree();

        void            createFenwickTree(vector<int> &input);
        int             getPrefixSum(int idx);
        void            updateTree(int idx, int value);
        int             getOriginalValue(int idx);
        int             getSum(int startIdx, int endIdx);
        void            printTree();
        void            testForGetSum();

    private:
        int             getPrev(int idx);
        int             getNext(int idx);

    private:
        int             _size;
        vector<int>     _bitArray;
};

//! @brief Constructor to create an object of binary indexed tree.
//! 
//! The binary indexed tree array of size zero is created.
BinaryIndexedTree::BinaryIndexedTree()
    : _size(0), _bitArray(0)
{
}

//! @brief Destructor to destroy an object of binary indexed tree.
//!
//! There is nothing to delete as of now.
BinaryIndexedTree::~BinaryIndexedTree()
{
}

//! @brief Get the index of previous element in Binary Indexed Tree.
//!
//! To get the previous element index just flip the right most set bit.
//! To do this
//!   1. 2's compliment the number
//!   2. And with original number
//!   3. Subtract from original number
int
BinaryIndexedTree::getPrev(int idx)
{
    return (idx - (idx & -idx));
}

//! @brief Get the index of next element in Binary Indexed Tree.
//!
//! To get the next element index just add the the right most set bit.
//! To do this
//!   1. 2's compliment the number
//!   2. And with original number
//!   3. Add to original number
int
BinaryIndexedTree::getNext(int idx)
{
    return (idx + (idx & -idx));
}

//! @brief Create a Binary Indexed Tree from the given input array.
//!
//! Given an input array of elements, this API creates a binary indexed tree array
//! which holds the cumulative sum. The input array must be 1-based index.
//! For this just insert a dummy element at index 0.
//!
//! @param [in]  input Original array of elements
//!
//! @return      void
void
BinaryIndexedTree::createFenwickTree(vector<int> &input)
{
    _size = input.size();
    _bitArray.resize(_size, 0);
    for (int idx = 1; idx < input.size(); ++idx) {
        updateTree(idx, input[idx]);
    }
}

//! @brief Get the prefix sum.
//!
//! This API returns the sum of the elements of the original array 
//! from index 1 to given index (inclusive).
//!
//! @param [in]  idx Index in the original array (>=1)
//!
//! @return      Sum of elements from index 1 to idx
int
BinaryIndexedTree::getPrefixSum(int idx)
{
    int sum = 0;

    if (idx >= _size) {
        return sum;
    }

    while (idx > 0) {
        sum += _bitArray[idx];
        idx = getPrev(idx);
    }
    return sum;
}

//! @brief Update the binary indexed tree.
//!
//! This API updates the binary indexed tree array by incrementing the
//! element at the given index with the given value.
//!
//! @param [in]  idx    Index in the original array (>=1)
//! @param [in]  value  Value by which element at idx is to be incremented
//!
//! @return      void
void
BinaryIndexedTree::updateTree(int idx, int value)
{
    while (idx < _size) {
        _bitArray[idx] += value;
        idx = getNext(idx);
    }
}

//! @brief Get the value of original array for the given index.
//!
//! Given an index, this API gets the value of the original array
//! using the binary indexed tree array.
//!
//! @param [in]  idx Index in the original array (>=1)
//!
//! @return      Element in the original array located at the given index
int
BinaryIndexedTree::getOriginalValue(int idx)
{
    int value = 0;
    if (idx >= _size) {
        return value;
    }

    //! To get the original value at the index 'idx',
    //! we get the partial cumulative sum stored at index 'idx' in binary
    //! indexed tree. We start from the predecessor element 'idx-1' and traverse
    //! till we reach the lowest common ancestor of the 'idx' and 'idx-1'.
    //! Along the path we keep subracting the sum from the value.

    value = _bitArray[idx];

    int ancesterIdx = getPrev(idx);
    int predecessorIdx = idx - 1;
    while (predecessorIdx > ancesterIdx) {
        value -= _bitArray[predecessorIdx];
        predecessorIdx= getPrev(predecessorIdx);
    }

    return value;
}

//! @brief Get sum of the original array for the given range.
//!
//! Given the starting and ending index in the original array,
//! return the sum of elements between them (both inclusive).
//!
//! @param[in]  startIdx Starting index in the range (>=1)
//! @param[in]  endIdx   Ending index in the range (>=1)
//!
//! @return     Sum of elements in the given range
int
BinaryIndexedTree::getSum(int startIdx, int endIdx)
{
    int sum = 0;
    if (startIdx > endIdx) {
        return sum;
    }

    /* Keep adding values from the tree until you reach 
       common ancestor of 'startIdx' and 'endIdx' */
    int ancestorIdx = endIdx;
    do {
        sum += _bitArray[ancestorIdx];
        ancestorIdx = getPrev(ancestorIdx);
    } while (ancestorIdx >= startIdx);

    int predecessorIdx = startIdx - 1;
    while (predecessorIdx > ancestorIdx) {
        sum -= _bitArray[predecessorIdx];
        predecessorIdx= getPrev(predecessorIdx);
    }

    return sum;
}

//! @brief Print the original array and Fenwick tree
//!
//! Prints the original array and the binary indexed tree array.
void
BinaryIndexedTree::printTree()
{
    cout << "********** ORIGINAL TREE *********" << endl;
    for (int idx = 1; idx < _size; ++idx) {
        cout << "    ARR[" << setw(2) << idx << "]: " << setw(4) << getOriginalValue(idx) << endl;
    }
    cout << "********** FENWICK TREE **********" << endl;
    for (int idx = 1; idx < _size; ++idx) {
        string sumStr("//");
        int prevIdx = getPrev(idx) + 1;
        while (prevIdx <= idx) {
            stringstream ss;
            ss << prevIdx;
            string iStr;
            ss >> iStr;
            sumStr += " + " + iStr;
            ++prevIdx;
        }
        cout << "    BIT[" << setw(2) << idx << "]: " << setw(4) << _bitArray[idx] << "    " << sumStr << endl;
    }
    cout << "**********************************" << endl;
}

//! @brief Tester API for getSum()
//!
//! This API tests the API getSum() by passing all possible value indices to it.
void
BinaryIndexedTree::testForGetSum()
{
    cout << "********** GETSUM - TEST *********" << endl;
    for (int i = 1; i < _size; ++i) {
        for (int j = i; j < _size; ++j) {
            cout << "    SUM[" << setw(2) << i << ":" << setw(2) << j << "] = " << setw(4) << getSum(i, j) << endl;
        }
    }
    cout << "**********************************" << endl;
}

//! @brief Main function
//!
//!
int main()
{
    vector<int> ARR = {0, 1, 2, 3, 4, 5};
    
    BinaryIndexedTree bitObj;
    bitObj.createFenwickTree(ARR);
    bitObj.printTree();
    bitObj.testForGetSum();

    return 0;
}
