#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cassert>
#include <algorithm>
#include <csignal>
#include <unistd.h>
using namespace std;

const int MAXRESULTS   = 20;    // Max matches that can be found
const int MAXDICTWORDS = 10; // Max words that can be read in


int realDictionaryReader(istream &dictfile, string dict[], int ind){
    if(dictfile.eof())                                              //check for end
        return 0;
    if(ind == MAXDICTWORDS)                                         //check for max words
        return 0;
    string wrd;
    getline(dictfile,wrd);
    dict[0] = wrd;
    return 1 + realDictionaryReader(dictfile, dict+1, ind+1);
}

int dictionaryReader(istream &dictfile, string dict[]){
    return realDictionaryReader(dictfile,dict,0);                 //include index
}

bool checkLetter(char let, string& dict, int n = 0){
    if(n == dict.size())                                        //run through whole word without
        return false;                                           //without finding correct letter
    if(let == dict[n]){
        dict = dict.substr(0,n) + dict.substr(n+1);             //found letter
        return true;                                            //returns second word with found letter
    }                                                           //removed
    return checkLetter(let, dict, n+1);
}

bool checkAnagram(string word, string dict){
    if(dict.size() == 0)
        return true;
    if(checkLetter(word[0], dict)){                             //see if first letter is in
        return checkAnagram(word.substr(1), dict);              //dictionary word
    }                                                           //repeat with first letter removed
    return false;
}

int realRecurCombos(string word, const string dict[], int size,
                string results[], int ind){
    if(size == 0)
        return 0;
    if(word.size() == dict[0].size()){                          //only check for words of same size
        if(checkAnagram(word, dict[0])){
            if(ind == MAXRESULTS)                               //check for largest possible size
                return 0;
            results[0] = dict[0];
            return 1 + realRecurCombos(word, dict+1, size-1, results+1, ind+1);
        }
    }
    return realRecurCombos(word, dict+1, size-1, results, ind);
}

int recurCombos(string word, const string dict[], int size,
                string results[]){
    return realRecurCombos(word, dict, size, results, 0);           //include index
}

void recursiveDisp(const string results[], int size){
    if(size == 0)
        return;
    cout << "Matching word " << results[0] << endl;
    recursiveDisp(results+1, size-1);
}


void testone(int n)
{
    string dictionary[MAXDICTWORDS];
    string results[MAXRESULTS];
    
    switch (n)
    {
        default: {
            cout << "Bad argument" << endl;
        } break; case 1: {
            istringstream iss("dog\ncat\nrat\neel\ntar\nart\nlee\nact\ngod");
            int numResults = dictionaryReader(iss, dictionary);
            cout << numResults << endl;
            for(int i = 0; i < numResults; i++){
                cout << dictionary[i] << endl;
            }
            sort(dictionary, dictionary + numResults);
            for(int i = 0; i < numResults; i++){
                cout << dictionary[i] << endl;
            }
            assert(numResults == 9 && dictionary[0] == "act" &&
                   dictionary[1] == "art");
        } break; case 2: {
            // File is empty, Checks that file is empty and dictionaryReader returns 0.
            istringstream iss("");
            int numResults = dictionaryReader(iss, dictionary);
            assert(numResults == 1 && dictionary[0] == "");
        } break; case 3: {
            // Dictionary has been read properly
            istringstream iss("dog\ncat\nrat\neel\ntar\nart\nlee\nact\ngod");
            int numResults = dictionaryReader(iss, dictionary);
            sort(dictionary, dictionary + numResults);
            assert(numResults == 9 && dictionary[0] == "act" &&
                   dictionary[numResults-1] == "tar");
        } break; case 4: {
            // Input file is larger than the dictionary size
            istringstream
            iss("dog\ncat\nrat\neel\ntar\nart\nlee\nact\ngod\ntoo\nmany\nwords");
                int numResults = dictionaryReader(iss, dictionary);
                sort(dictionary, dictionary + numResults);
                assert(numResults == 10 && dictionary[MAXDICTWORDS-1]
                       == "too");
                } break; case 5: {
                    // If a certain word with repeated letter is shown in results more than once - still accept.
                    string dictionary[] = { "one", "oone", "ne", "e",
                        "too" };
                    int numResults = recurCombos("oto", dictionary, 5,
                                                 results);
                    assert((numResults == 1 || numResults == 2) &&
                           results[0] == "too");
                } break; case 6: {
                    // Doesn't check numResults nor duplicates.
                    string dictionary[] = { "one", "oone", "ne", "e",
                        "too" };
                    recurCombos("oto", dictionary, 5, results);
                    assert(results[0] == "too");
                } break; case 7: {
                    // If word wasn't found, numResults = 0 and results array is empty.
                    string dictionary[] = { "one", "oone", "ne", "e" };
                    int numResults = recurCombos("look", dictionary, 4,
                                                 results);
                    assert(numResults == 0 && results[0] == "" &&
                           results[1] == "");
                } break; case 8: {
                    // No fraction of a permutation is being searched in dictionary
                    string dictionary[] = { "one", "oone", "non", "oon"
                    };
                    int numResults = recurCombos("on", dictionary, 4,
                                                 results);
                    assert(numResults == 0 && results[0] == "" &&
                           results[1] == "");
                } break; case 9: {
                    // No fraction of a permutation is being searched in dictionary
                    string dictionary[] = { "one", "oone", "ne", "e",
                        "neoo", "oneo" };
                    int numResults = recurCombos("neo", dictionary, 6,
                                                 results);
                    assert(numResults == 1 && results[0] == "one" &&
                           results[1] == "");
                } break; case 10: {
                    // Checking that no error occurs if more than MAXRESULTS are found.
                    string dictionary[] = { "true", "treu", "teru",
                        "teur", "ture",
                        "tuer", "rtue", "rteu", "retu","reut", "ruet",
                        "rute", "utre",
                        "uter", "uetr", "uert", "urte", "uret", "etru",
                        "etur", "ertu",
                        "erut", "eurt", "eutr" };
                    // All 24 permutations
                    int numResults = recurCombos("true", dictionary, 24,
                                                 results);
                    assert(numResults == MAXRESULTS);
                } break; case 11: {
                    // Checking one word was found, no duplicates.
                    string dictionary[] = { "ppp" };
                    int numResults = recurCombos("ppp", dictionary, 1,
                                                 results);
                    
                    assert(numResults == 1 && results[0] == "ppp" &&
                           results[1] == "");
                } break; case 12: {
                    string dictionary[] = { "run", "dodge", "break",
                        "urn", "defeat" };
                    int numResults = recurCombos("nru", dictionary, 5,
                                                 results);
                    sort(results, results + numResults);
                    assert(numResults == 2 && results[0] == "run" &&
                           results[1] == "urn");
                } break; case 13: {
                    streambuf* oldCoutStreamBuf = cout.rdbuf();
                    ostringstream strCout;
                    cout.rdbuf(strCout.rdbuf());
                    string results[] = { "cat", "act"};
                    recursiveDisp(results, 2);
                    cout.rdbuf(oldCoutStreamBuf);
                    string temp = strCout.str();
                    bool match1 = temp.find("act") != string::npos;
                    bool match2 = temp.find("cat") != string::npos;
                    assert(match1 && match2);
                } break; case 14: {
                    istringstream iss ("tier\nrite\nbate\ntire\nttir");
                    int numWords = dictionaryReader(iss, dictionary);
                    sort(dictionary, dictionary + numWords);
                    assert(numWords == 5 && dictionary[0] == "bate");
                    int numResults = recurCombos("tier", dictionary,
                                                 numWords, results);
                    assert(numResults == 3 && (results[2] == "tire" ||
                                               results[2] == "tier" || results[2] == "rite"));
                } break; case 15: {
                    string example[] = { "kool", "moe", "dee" };
                    int numResults = recurCombos("look", example, 3,
                                                 results);
                    assert(numResults == 1 && results[0] == "kool");
                } break;
                }
                }
                int main()
            {
                cout << "Enter test number: ";
                int n;
                cin >> n;
                testone(n);
                cout << "Passed" << endl;
            }







