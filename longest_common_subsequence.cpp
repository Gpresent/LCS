#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <chrono>

using std::vector, std::max, std::cout, std::endl;

vector<char> lcs_helper(const vector<char>& a, const vector<char>& b, vector<vector<vector<char>>>& dynamicSpace, vector<vector<int>>& spaceCheck, long int i, long int j);

vector<char> lcs_helper(const vector<char>& a, const vector<char>& b, vector<vector<vector<char>>>& dynamicSpace, vector<vector<int>>& spaceCheck, long int i, long int j) {
    if (i < 0 || j < 0) return vector<char>{};
    else if (spaceCheck.at(i).at(j)) return dynamicSpace.at(i).at(j);
    else if (a.at(i) == b.at(j)) {
        vector<char> res = lcs_helper(a, b, dynamicSpace, spaceCheck, i - 1, j - 1);
        res.push_back(a.at(i));
        return res;
    }
    if (i == 0 || j == 0) return vector<char>{};
    vector<char> up;
    vector<char> left;
    if (spaceCheck.at(i).at(j - 1)) {
        up = dynamicSpace.at(i).at(j - 1);
    } else {
        up = lcs_helper(a, b, dynamicSpace, spaceCheck, i, j - 1);
        spaceCheck.at(i).at(j - 1) = 1;
        dynamicSpace.at(i).at(j - 1) = up;
    }
    if (spaceCheck.at(i - 1).at(j)) {
        left = dynamicSpace.at(i - 1).at(j);
    } else {
        left = lcs_helper(a, b, dynamicSpace, spaceCheck, i - 1, j);
        spaceCheck.at(i - 1).at(j) = 1;
        dynamicSpace.at(i - 1).at(j) = left;
    }
    vector<char> current;
    up.size() > left.size() ? current = up : current = left;
    spaceCheck.at(i).at(j) = 1;
    dynamicSpace.at(i).at(j) = current;
    return current;
}

vector<char> lcs(vector<char>& a, vector<char>& b) {
    vector<vector<vector<char>>> dynamicSpace(a.size(), vector<vector<char>>(b.size(), vector<char>{}));
    vector<vector<int>> spaceCheck(a.size(), vector<int>(b.size(), 0));

    return lcs_helper(a, b, dynamicSpace, spaceCheck, a.size() - 1, b.size() - 1);
}

vector<char> lcs_bad(vector<char>& a, vector<char>& b, long int i, long int j);

vector<char> lcs_bad(vector<char>& a, vector<char>& b, long int i, long int j) {
    if (i < 0 || j < 0) return vector<char>{};
    else if (a.at(i) == b.at(j)) {
        vector<char> res = lcs_bad(a, b, i - 1, j - 1);
        res.push_back(a.at(i));
        return res;
    }
    if (i == 0 || j == 0) return vector<char>{};
    vector<char> up = lcs_bad(a, b, i, j - 1);
    vector<char> left = lcs_bad(a, b, i - 1, j);
    if (up.size() > left.size()) return up;
    else return left;
}

int main() {
    std::ifstream infs("chars.txt");
    std::ofstream ofs("static_v_dynamic.csv");
    ofs << "Characters, Dynamic Solution (microseconds), Static Solution (microseconds)\n";
    for (int charset = 1; charset <= 14; charset++) {
        vector<char> x;
        vector<char> y;
        for (int i = 0; i < charset; i++) {
            char a;
            infs >> a;
            x.push_back(a);
            infs >> a;
            y.push_back(a);
        }
        ofs << charset << ", ";
        auto start = std::chrono::high_resolution_clock::now();
        vector<char> z = lcs(x, y);
        auto stop = std::chrono::high_resolution_clock::now();
        auto durationMicro = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        ofs << durationMicro.count() << ", ";

        start = std::chrono::high_resolution_clock::now();
        vector<char> z2 = lcs_bad(x, y, x.size() - 1, y.size() - 1);
        stop = std::chrono::high_resolution_clock::now();
        durationMicro = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        ofs << durationMicro.count() << "\n";
    }



    // for (int i = 0; i < charset; i++) {
    //     char a;
    //     infs >> a;
    //     x.push_back(a);
    //     infs >> a;
    //     y.push_back(a);
    // }

    // cout << "Character set 1:\n";
    // for (char c : x) cout << c << " ";
    // cout << endl;
    // cout << "Character set 2:\n";
    // for (char c : y) cout << c << " ";
    // cout << "\n\n";

    // auto start = std::chrono::high_resolution_clock::now();
    // vector<char> z = lcs(x, y);
    // auto stop = std::chrono::high_resolution_clock::now();
    // auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    // auto durationMicro = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    // cout << "Solution found with dynamic programming in " << duration.count() << " milliseconds, or " << durationMicro.count() << " microseconds:\n";
    // for (char c : z) cout << c << " ";
    // cout << endl;

    // start = std::chrono::high_resolution_clock::now();
    // vector<char> z2 = lcs_bad(x, y, x.size() - 1, y.size() - 1);
    // stop = std::chrono::high_resolution_clock::now();
    // duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    // durationMicro = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    // cout << "Solution found without dynamic programming in " << duration.count() << " milliseconds, or " << durationMicro.count() << " microseconds\n";
    // for (char c : z2) cout << c << " ";
    // cout << endl;
}