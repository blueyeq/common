#include <iostream>
#include <string>
#include <unordered_map>
#include <queue>
#include <vector>

using namespace std;

// primitive, unoptimized trie with mem. leak etc.
class TrieItem
{
private:  
  unordered_map<char, TrieItem*> next_;
  string word_; // simplification, should be only a flag
  char letter_;

public:
  TrieItem() :word_("") { }
  TrieItem(char letter) : letter_(letter) { }

  void addWord(const string& word) { addWord(word, 0); }
  TrieItem* getNext(char letter) 
  {
    auto it = next_.find(letter);
    if(it != next_.end()) return it->second;
    return nullptr;
  }
  bool isWord() const { return word_.length() > 0; }
  string word() const { return word_; }
  char letter() const { return letter_; }

private:
  void addWord(const string& word, int index)
  {
    if(index == word.length())
    { 
      word_ = word.substr(0, index + 1);
    }
    else
    {
      auto it = next_.find(word[index]);
      TrieItem *item;
      if(it != next_.end())
      { 
        item = it->second;
      }
      else
      { 
        item = new TrieItem(word[index]);
        next_[word[index]] = item;
      }
      item->addWord(word, index + 1);
    }
  }
};

// priority queue item
struct PrioQItem 
{
  int prio;
  int index;
  TrieItem* tItem;

  PrioQItem(int p, int i, TrieItem* ti) 
    : prio(p), index(i), tItem(ti) {}
};

// priority queue less predicate 
struct PQItemLess
{
  bool operator() (const PrioQItem& a, const PrioQItem& b) const 
  {
    return a.prio > b.prio;
  }
};

string findWordWithMinimalDeleting(const string& input, TrieItem* dict) 
{
  priority_queue<PrioQItem, vector<PrioQItem>, PQItemLess> q;
  int n = input.length();

  // initialize priority queue  
  q.push(PrioQItem(0, 0, dict)); 

  while(q.size() > 0) {
    TrieItem* cti = q.top().tItem; // current trie item
    int i = q.top().index; // index in input string
    int p = q.top().prio; // prio = delete char counter
    q.pop(); // remove item
    if(i == n && cti->isWord()) return cti->word(); // if we matched all and it's word
    if(i == n) continue;
    TrieItem* ntim = cti->getNext(input[i]);
    if(ntim != nullptr)  {   // next trie itme if match
      q.push(PrioQItem(p, i + 1, ntim));
    }
    q.push(PrioQItem(p+1, i + 1, cti));

  }
  return string("");
}

int main()
{
  TrieItem trie;
  trie.addWord("abc");
  trie.addWord("acde");
  trie.addWord("achk");
  trie.addWord("acdk");

  cout << "the word is \"" << findWordWithMinimalDeleting("acfhk", &trie) << "\"" << endl;
}
/* sw=2;ts=2;sts=2;expandtab */
