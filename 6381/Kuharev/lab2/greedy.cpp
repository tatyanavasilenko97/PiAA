#include <iostream>
#include <vector>

struct connection
{
    connection(char n, float w) : name(n), weight(w) {}
    char name;
    float weight;
};

struct node 
{
    node(char n, connection dest_b) : name(n){ ways.push_back(dest_b);}
    char name;
    std::vector<connection> ways;
};

int find( char name, std::vector<node> nodes) 
{
    for(node& n : nodes)
        if( n.name == name )
            return &n - &nodes[0]; 
    return -1; 
}

int main(void)
{
    char begin, end;
    std::cin >> begin >> end;

    char dest_b, source_b;
    float weight;

    std::vector<node> nodes;
    int index;

    while( std::cin >> source_b >> dest_b >> weight )
    {
        index = find(source_b, nodes);

        if( index != -1 ) 
            nodes[index].ways.push_back(connection(dest_b, weight));
        else 
            nodes.push_back(node(source_b, connection(dest_b,weight)));
    }

    index = find(begin, nodes); 
    connection comp = nodes[index].ways[0]; 

    std::string been;

    std::cout << begin;
    while( true ) 
    {
        comp = nodes[index].ways[0];
        for(auto c : nodes[index].ways) 
        {
            if( c.name == end )
            {
                std::cout << end;
                return 0;
            }
            if( c.weight < comp.weight && been.find(c.name) != std::string::npos ) 
                comp = c;
        }
        std::cout << comp.name; 
        been.push_back(comp.name);
        index = find(comp.name, nodes); 
    }


    return 0;
}
