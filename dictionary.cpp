//
// Dictionary
// UCF Online High School Programming Contest 2019
// Jim Geist jimg@knights.ucf.edu
//
#include <algorithm>
#include <array>
#include <iostream>
#include <string>
#include <vector>

const int LETTERS = 'z' - 'a' + 1;

struct Word {
    std::string word;
    std::array<int, LETTERS> hist;

    Word(const std::string &w) {
        std::fill(hist.begin(), hist.end(), 0);
        word = w;
        for(int i = 0; i < w.size(); i++) {
            hist[w[i] - 'a']++;
        }
    }
};

int main()
{
    int cases;
    std::cin >> cases;
    for (int c = 1; c <= cases; c++) {
        int nwords;
        std::cin >> nwords;

        std::vector<Word> words {};
        words.reserve(nwords);

        for (int i = 0; i < nwords; i++) {
            std::string word {};
            std::cin >> word;
            words.push_back(Word {word});
        }

        std::sort(
            words.begin(),
            words.end(),
            [](const Word &left, const Word &right) {
                for (int i = 0; i < LETTERS; i++) {
                    if (left.hist[i] > right.hist[i]) {
                        return true;
                    }
                    if (left.hist[i] < right.hist[i]) {
                        return false;
                    }
                }

                return left.word < right.word;
            });

        std::cout << "Dictionary #" << c << ":" << std::endl;
        std::for_each(
            words.begin(),
            words.end(),
            [](const Word &word) {
                std::cout << word.word << std::endl;
            });

        std::cout << std::endl;
    }
}
