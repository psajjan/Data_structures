/**
 *
 * @author P Sajjan Raj Jain
 *
 * @date 2015/08/27
 *
 * Program to illustrate Binary Indexed Tree data structure.
 *
 * Binary Indexed Tree data structure provides a O(log n) solution
 * for querying prefix sum and updating prefix sum.
 * The array used in Binary Indexed Tree is 1-index based.
 * Element at index 0 in the array is dummy.
 *
 */

#include <iostream>
#include <vector>

using namespace std;

//! @class BinaryIndexedTree_Compact
//! @brief Represent a minimal binary indexed tree class.
class BinaryIndexedTree_Compact
{
  public:
    //! @brief Constructor to sets size of the array to zero.
    BinaryIndexedTree_Compact(): N(0), BIT(0)
    {
    }
    
    //! @brief Initialize the binary indexed tree array
    void init(int size)
    {
        if (size <= 0) return;
        N = size;
        BIT.resize(N, 0);
    }
    
    //! @brief Get the set bit from right side (LSB)
    int lowbit(int id)
    {
        return id & (-id);
    }
    
    //! @brief Update the binary indexed tree.
    void add(int id, int num)
    {
        for (int i = id; check(i); i += lowbit(i))
            BIT[i] += num;
    }
    
    //! @brief Get the prefix sum.
    int sum(int id)
    {
        int ret = 0;
        for (int i = id; check(i); i -= lowbit(i))
            ret += BIT[i];
        return ret;
    }

    //! @brief Check whether the given index is correct or not.
    bool check(int id)
    {
        return (1 <= id && id < N);
    }
  
  private:
    int                 N;      // Size of the BIT array
    vector<int>         BIT;    // Elements start at index 1
};

//! @brief Main function
//!
//!
int main()
{
    int   n = 0;
    int  ch = 0;
    int val = 0;
    int  id = 0;
    BinaryIndexedTree_Compact BIT;

    cout << "Enter number of elements: ";
    cin >> n;

    BIT.init(n+1);

    cout << endl;
    cout << "1. Add a number at an index" << endl;
    cout << "2. Query sum" << endl;
    cout << "3. Quit" << endl;

    while (1) {
        cout << endl;
        cout << "Enter your choice: ";
        cin >> ch;
        cout << endl;

        switch (ch) {
            case 1:
                cout << "  Enter number to add: ";
                cin >> val;
                cout << "  Enter index: ";
                cin >> id;
                if (BIT.check(id)) {
                    BIT.add(id, val);
                } else {
                    cout << "  incorrect index given..." << endl;
                }
                break;

            case 2:
                cout << "  Enter index: ";
                cin >> id;
                if (BIT.check(id)) {
                    cout << "    sum = " << BIT.sum(id) << endl;
                } else {
                    cout << "  incorrect index given..." << endl;
                }
                break;

            case 3:
            default:
                return 0;
        }
    };

    return 0;
}
