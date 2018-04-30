#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#define DEBUG
#define OUT_INP

using namespace std;

namespace DM
{
	const vector<char> alphabet = {'A', 'C', 'G', 'T', 'N'};
	char to_char(unsigned index)
	{
		if ((index < 0) || (index >= alphabet.size()))
			throw out_of_range("There is no such symbol in alphabet with index " + to_string(index));
		return alphabet[index];
	}
	unsigned to_uns(char a)
	{
		for (unsigned i = 0; i < alphabet.size(); ++i)
		{
			if (alphabet[i]==a)
				return i;
		}
		throw out_of_range(string("There is no symbol ") + a + " in alphabet");
	}

	class Trie
	{
	public:
		struct Node
		{
			vector<int> next; // Keeps edges to each symbol
				// -1 if there is no edge to symbol with index
			int pat_num = -1; // = -1 if resulting string is not a pattern
			int suff_link = -1; // = -1 if no suffix link
			Node()
			{
				next = vector<int>(alphabet.size(), -1);
			}
		};
		Trie(const vector<string>& patterns, char joker = 0)
		{
			buildTrie(patterns, joker);
		}

		void print() const
		{
			_print(nodes[0], "");
		}
	private:
		vector<Node> nodes;
		void buildTrie(const vector<string>& patterns, char joker)
		{
			nodes.push_back(Node{});
			for (unsigned i = 0, size = patterns.size(); i < size; ++i)
			{
				#ifdef DEBUG
					cout << "Adding to trie pattern " << patterns[i] << endl;
				#endif
				addPattern(patterns[i], i+1, joker);
			}
		}
		void addPattern(const string &pattern, unsigned pattN, char joker)
		{
			// Node &tmp = nodes[0];
			unsigned current = 0;
			for (char i : pattern)
			{
				// If character is a joker then we are adding all the edges to this node
				if (i == joker)
				{
					//TODO
				}
				// If we already have edge with this symbol
					// Then we just move to it
				// else if (tmp.next[to_uns(i)] != -1)
				else if (nodes[current].next[to_uns(i)] != -1)
				{
					#ifdef DEBUG
						cout << "   Edge with " << i
							<< " character is already exists. Moving to it." << endl;
					#endif
					// tmp = nodes[tmp.next[to_uns(i)]];
					current = nodes[current].next[to_uns(i)];
				}
				// Else we are adding new edge and creating vertex
				else
				{
					#ifdef DEBUG
						cout << "   There is no edge with " << i
							<< " character. Creating it." << endl;
					#endif
					nodes.push_back(Node{});
					// tmp.next[to_uns(i)] = nodes.size()-1;
					nodes[current].next[to_uns(i)] = nodes.size() - 1;
					// tmp = nodes.back();
					current = nodes.size() - 1;
				}
			}
			#ifdef DEBUG
				cout << "   Added pattern " << pattern << " with number "
					<< pattN << endl;
			#endif
			// tmp.pat_num = pattN;
			nodes[current].pat_num = pattN;
		}
		void _print(const Node &arg, string str) const
		{
			for (unsigned i = 0, size = alphabet.size(); i < size; ++i)
				if (arg.next[i] != -1)
					_print(nodes[arg.next[i]], str+to_char(i));
			if (arg.pat_num != -1)
				cout << arg.pat_num << " " << str << endl;
		}
	};
};

void readData(string &text, unsigned& pattN, vector<string> &patterns)
{
	cin >> text >> pattN;
	string Pattern;
	for (unsigned i = 0; i < pattN; ++i)
	{
		cin >> Pattern;
		patterns.push_back(Pattern);
	}
	#ifdef OUT_INP
		cout << text << '\n' << pattN << endl;
		for (auto &i : patterns)
			cout << i << endl;
	#endif
}

int main()
{
	string text;
	unsigned pattN = 0;
	vector<string> patterns;
	readData(text, pattN, patterns);
	DM::Trie trie{patterns};
	trie.print();
	return 0;
}
