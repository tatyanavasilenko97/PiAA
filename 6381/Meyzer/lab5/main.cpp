#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <stdexcept>
// #define DEBUG
// #define OUT_INP

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

	struct uuStruct
	{
		unsigned a;
		unsigned b;
	};


	class Trie
	{
	public:
		struct Node
		{
			vector<int> next; // Keeps edges to each symbol
				// -1 if there is no edge to symbol with index
			unsigned parent = 0; // Parent addr
			char parentChar = 0; // Symbol in edge between parent and current node
			int pattNum = -1; // = -1 if resulting string is not a pattern
			int ref = 0; // = 0 by default
			Node()
			{
				next = vector<int>(alphabet.size(), -1);
			}
		};

		Trie(const vector<string>& patterns, char joker = -1)
		{
			buildTrie(patterns, joker);
		}

		bool hasString(const string &arg)
		{
			unsigned current = 0;
			for (char i : arg)
			{
				if (nodes[current].next[to_uns(i)] != -1)
					current = nodes[current].next[to_uns(i)];
				else return false;
			}
			return (nodes[current].pattNum != -1);
		}

		void searchSubStrings(const string& text, list<uuStruct>& result)
		{
			unsigned current = 0;
			// For each character
			for (unsigned i = 0, size = text.size(); i < size; ++i)
			{
				char c = text[i];
				// While there is no edge with such char we are going to other node by ref until its root
				while ((nodes[current].next[to_uns(c)] == -1) && current != 0)
				{
					current = nodes[current].ref;
				}
				if (nodes[current].next[to_uns(c)] != -1)
				{
					current = nodes[current].next[to_uns(c)];
				}
				else
					continue;

				// For current node and all its references
				// If it's one of the patterns then add it to result
				unsigned tmp = current;
				while (tmp != 0)
				{
					// cout << tmp;
					if (nodes[tmp].pattNum != -1)
						result.push_back({i+2-pattSizes[nodes[tmp].pattNum-1],
							static_cast<unsigned>(nodes[tmp].pattNum)});
					tmp = nodes[tmp].ref;
				}
			}
		}

		// Prints all the patterns that trie keeps
		void print() const
		{
			_print(nodes[0], "");
		}
	private:
		vector<Node> nodes;
		vector<int> pattSizes;
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
			calcReferences();
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
				else if (nodes[current].next[to_uns(i)] != -1)
				{
					#ifdef DEBUG
						cout << "   Edge with " << i
							<< " character is already exists. Moving to it." << endl;
					#endif
					current = nodes[current].next[to_uns(i)];
				}
				// Else we are adding new edge, creating vertex and reference
				else
				{
					// Creating empty node
					nodes.push_back(Node{});
					// Setting parent node in new node
					nodes.back().parent = current;
					nodes.back().parentChar = i;
					// Setting edge to the new node from the current
					nodes[current].next[to_uns(i)] = nodes.size() - 1;

					#ifdef DEBUG
						cout << "   There is no edge with " << i
							<< " character. Creating it and new node." << endl
							<< "      Number of the new node is      "
							<< nodes.size() - 1 << endl
							<< "      It's parent is                 "
							<< nodes.back().parent << endl;
					#endif
					// Moving to the created node
					current = nodes.size() - 1;
				}
			}
			#ifdef DEBUG
				cout << "   Added pattern " << pattern << " with number "
					<< pattN << endl;
			#endif
			nodes[current].pattNum = pattN;
			pattSizes.push_back(pattern.size());
		}
		void calcReferences()
		{
			#ifdef DEBUG
				cout << endl << "Calculating references:" << endl;
			#endif
			list<unsigned> queue;
			queue.push_back(0);
			while(!queue.empty())
			{
				unsigned current = queue.front();
				queue.pop_front();
				for(int i : nodes[current].next)
				{
					if (i != -1)
						queue.push_back(i);
				}
				if (nodes[current].parent == 0)
					continue;
				// Setting reference in the new node:
				// Moving on reference in parent node and looking for edge with i symbol
				// If found, sets a reference to the node after this edge
				// Else sets a reference to the root(which set on it by default)
				unsigned parRef = nodes[nodes[current].parent].ref;
				char parChar = nodes[current].parentChar;
				if (nodes[parRef].next[to_uns(parChar)] != -1)
					nodes[current].ref = nodes[parRef].next[to_uns(parChar)];
				#ifdef DEBUG
					cout << "   Reference in node " << current << " is set to "
						<< nodes[current].ref << endl;
				#endif
			}
		}
		void _print(const Node &arg, string str) const
		{
			for (unsigned i = 0, size = alphabet.size(); i < size; ++i)
				if (arg.next[i] != -1)
					_print(nodes[arg.next[i]], str+to_char(i));
			if (arg.pattNum != -1)
				cout << arg.pattNum << " " << str << endl;
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
	list<DM::uuStruct> result;
	unsigned pattN = 0;
	vector<string> patterns;
	readData(text, pattN, patterns);
	DM::Trie trie{patterns};
	trie.searchSubStrings(text, result);
	result.sort([](const DM::uuStruct &lhs, const DM::uuStruct &rhs)
		{
			return lhs.b<rhs.b;
		});
	result.sort([](const DM::uuStruct &lhs, const DM::uuStruct &rhs)
		{
			return lhs.a<rhs.a;
		});
	for (auto &i : result)
		cout << i.a << " " << i.b << endl;
	return 0;
}
