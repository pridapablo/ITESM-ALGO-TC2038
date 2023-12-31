#ifndef DP_HPP
#define DP_HPP

#include <vector>

using namespace std;

/*
    Dynamic Programming implementation of the coin change problem
    Bottom-up approach for space efficiency
    Time complexity: O(n * m) where n is the change and m is the number of denominations (matrix size since we need to check all combinations)
    @param qty: the amount of change to be given
    @param denom: the vector with the denominations of the coins (sorted)

    @return: a vector with the coins used to give the change (returns {} if solution does not exist or is incorrect)
*/
vector<int> dpChange(int qty, vector<int> denom)
{
    const int IMPOSSIBLE = qty + 1; // impossible value for change since max change is change
    int initQty = qty;              // save initial qty to check if solution is correct

    // initialize all values to impossible
    vector<pair<int, int>> matrix(IMPOSSIBLE, {IMPOSSIBLE, -1}); // {no. coins, who tagged it}

    matrix[0] = {0, -1}; // base case: 0 coins tag -1 (no coin)

    for (int i = 0; i < denom.size(); i++)
    {
        for (int j = 0; j <= qty; j++)
        {
            // if the denomination is less than the change
            if (denom[i] <= j)
            {
                // If the number of coins in the current combination is less than the minimum number of coins so far
                if (matrix[j - denom[i]].first + 1 < matrix[j].first)
                {
                    matrix[j].first = matrix[j - denom[i]].first + 1;
                    matrix[j].second = i; // Tag it with the coin used
                }
            }
        }
    }

    // If change is not possible
    if (matrix[qty].first == IMPOSSIBLE)
    {
        return {}; // Solution not possible since value is unattainable (change + 1)
    }
    else
    {
        // Get the coins used
        vector<int> coinsUsed;
        int i = qty;
        while (i != 0)
        {
            int coin = denom[matrix[i].second];
            coinsUsed.push_back(coin);
            i -= coin;
        }

        // check if solution is correct
        int sum = 0;
        for (int i = 0; i < coinsUsed.size(); i++)
        {
            sum += coinsUsed[i];
        }
        if (sum != initQty)
        {
            return {}; // Solution is incorrect, so it does not exist (with this algorithm)
        }
        return coinsUsed;
    }
}

#endif