#include <iostream>
#include <string>
#include "Util.h"

using namespace std;
using namespace Util;

int* radix(int* arr, int length)
{
    for (int i = 0; i < length; i++)
    {
        if (arr[i] < 0)
        {
            throw exception("expected non-negative integer in array");
        }
    }

    int maxDigits = 0;

    // find the largest digit count
    for (int i = 0; i < length; i++)
    {
        int current = to_string(arr[i]).size();
        if (current > maxDigits)
        {
            maxDigits = current;
        }
    }

    int minDigits = maxDigits;

    // find the smallest digit count
    for (int i = 0; i < length; i++) {
        int current = to_string(arr[i]).size();
        if (current < minDigits) {
            minDigits = current;
        }
    }

    // divide the numbers by digit count
    int steps = maxDigits - minDigits;

    // array with final result
    int* sorted = new int[length];

    // size of previous number group
    int offset = 0;

    for (int s = 0; s < steps + 1; s++)
    {
        int count = 0;
        int* buffer = new int[0];

        // count and fill the buffer
        for (int i = 0; i < length; i++)
        {
            if (to_string(arr[i]).size() == minDigits + s)
            {
                count++;
                
                int* new_buffer = new int[count];
                for (int j = 0; j < count - 1; j++)
                {
                    new_buffer[j] = buffer[j];
                }
                new_buffer[count - 1] = arr[i];
                buffer = new_buffer;
            }
        }

        if (count > 1)
        {
            // iterate by group number
            // [12, 23, 32] - d = 0
            // [321, 458, 943] - d = 1
            for (int d = 0; d < minDigits + s; d++)
            {
                if (buffer == NULL)
                {
                    throw exception("buffer empty");
                }

                int* fr = frequencies(buffer, count, d);
                int* prSum = prefixSum(fr, 10);

                int* result = new int[count];

                for (int i = 0; i < count; i++)
                {
                    // reverse
                    int reverseI = count - i - 1;

                    // find the digit of number
                    int digit = getDigit(buffer[reverseI], d);

                    // find corresponding insert index
                    // and MODIFY array
                    int prIndx = --prSum[digit];

                    if (prIndx < 0 || prIndx >= count)
                    {
                        throw exception("this error should not occur");
                    }

                    if (isEmpty(prIndx, result, count, buffer, count))
                    {
                        result[prIndx] = buffer[reverseI];
                    }
                    else
                    {
                        throw exception("this error should not occur");
                    }
                }
                buffer = result;
            }
        }

        for (int i = 0; i < count; i++)
        {
            sorted[i + offset] = buffer[i];
        }
        offset += count;
    }

    return sorted;
}


int main()
{
    cout << "Radix sort:\n";
    try
    {
        int arr[10] = {1, 6, 24, 12, 55, 128, 10976, 99, 0, 1};
        int size = sizeof(arr) / sizeof(arr[0]);
        cout << endl;
        display(arr, size);
        cout << endl;

        int* radixRes = radix(arr, size);

        cout << "Sorted ";
        display(radixRes, size);
    }
    catch (const exception e)
    {
        cout << "Error occurred: " << e.what();
    }
    
}
