#include <iostream>
#include <string>

using namespace std;

namespace Util
{
    void display(int* arr, int length)
    {
        cout << "Array: ";
        for (int i = 0; i < length; i++)
        {
            cout << arr[i] << (i < length - 1 ? " " : "");
        }
    }

    // pos is 0-based index
    int getDigit(int number, int pos)
    {
        if (pos < 0)
        {
            throw exception("expected pos to be >= 0");
        }

        int power = 1;

        for (int i = 0; i < pos; i++)
        {
            power *= 10;
        }

        return number / power % 10;
    }

    int* zeros(int length)
    {
        if (length < 0)
        {
            string message = "expected length >= 0. Got: " + to_string(length);
            throw runtime_error(message);
        }

        int* arr = new int[length];

        for (int i = 0; i < length; i++)
        {
            arr[i] = 0;
        }

        return arr;
    }

    int* frequencies(int* arr, int length, int digit)
    {
        if (length < 0)
        {
            throw exception("expected length >= 0");
        }

        int* result = zeros(10);

        for (int i = 0; i < length; i++)
        {
            int d = getDigit(arr[i], digit);
            result[d] += 1;
        }

        return result;
    }

    int* copyArr(int* arr, int length)
    {
        if (length < 0)
        {
            throw exception("expected length to be >= 0");
        }

        int* result = new int[length];

        for (int i = 0; i < length; i++)
        {
            result[i] = arr[i];
        }

        return result;
    }

    int* prefixSum(int* arr, int length)
    {
        if (length < 0)
        {
            throw exception("expected length >= 0");
        }

        int* result = copyArr(arr, length);

        for (int i = 1; i < length; i++)
        {
            result[i] += result[i - 1];
        }

        return result;
    }

    int getMax(int* arr, int length)
    {
        if (length > 0)
        {
            int max = arr[0];

            for (int i = 0; i < length; i++)
            {
                if (arr[i] > max)
                {
                    max = arr[i];
                }
            }

            return max;
        }
        else
        {
            throw exception("Expected length to be > 0");
        }
    }

    // checks whether item under id may be considered empty
    // item considered empty if it's not in a set
    bool isEmpty(int id, int* arr, int len1, int* set, int len2)
    {
        if (len1 < 0)
        {
            throw exception("Expected len1 >= 0");
        }

        if (len2 < 0)
        {
            throw exception("Expected len2 >= 0");
        }

        if (id < 0)
        {
            throw exception("Expected id >= 0");
        }

        bool empty = true;

        for (int i = 0; i < len2; i++)
        {
            if (arr[id] == set[i])
            {
                empty = false;
            }
        }

        return empty;
    }
}
