#ifndef Graph_HPP_INCLUDED
#define Graph_HPP_INCLUDED

#include <boost/shared_ptr.hpp>
#include <boost/variant.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "MyTypes.h"
#include "Node.hpp"

using std::vector;
using std::string;

template<class nodeType>
class Graph
{
private:
  nodeVec nodes;
	int outputCount;

public:
	inline Graph(int outputCount) {this->outputCount = outputCount;}
	inline ~Graph(){}

	inline nodeVec getAllNodes() const {return nodes;}
	shared_ptr<Node<nodeType>> getNode(string);

	bool addNode(shared_ptr<Node<nodeType>>);
	bool eraseNode(string);

	vector<nodeType> run();
	void BFS();
	void DFS();
};

//returns false if the Node is already in the Graph
//returns true if insert occured
template<class nodeType>
bool Graph<nodeType>::addNode(shared_ptr<Node<nodeType>> node)
{
	for(vector<shared_ptr<Node<nodeType>>>::iterator it = nodes.begin(); it != nodes.end(); ++it)
	{
		shared_ptr<Node<nodeType>> current = *it;
		if(current->getLabel() == node->getLabel())
		{
			return false;
		}
	}
	nodes.push_back(node);
	return true;
}

template<class nodeType>
shared_ptr<Node<nodeType>> Graph<nodeType>::getNode(string label)
{
	for(vector<shared_ptr<Node<nodeType>>>::iterator it = nodes.begin(); it != nodes.end(); ++it)
	{
		shared_ptr<Node<nodeType>> current = *it;
		if(current->getLabel() == label)
		{
			return current;
		}
	}
	return nodes[0];
}

//returns false if the Node is not found in the Graph
//returns true if erase occured
template<class nodeType>
bool Graph<nodeType>::eraseNode(string label)
{
	bool inGraph = false;
	for(vector<shared_ptr<Node<nodeType>>>::iterator it = nodes.begin(); it != nodes.end(); ++it)
	{
		shared_ptr<Node<nodeType>> current = *it;
		if(current->getLabel() == label)
		{
			inGraph = true;
			for(unsigned j = 0; j < nodes.size(); j++)
			{
				for(unsigned k = 0; k < nodes[j]->getInputs().size(); k++)
				{
					if(nodes[j]->getInputs()[k]->getLabel() == nodes[i]->getLabel())
					{
						nodes[j]->getInputs().erase(nodes[j]->getInputs().begin() + k);
					}
				}
			}
		}
	}
	return inGraph;
}

template<class nodeType>
vector<nodeType> Graph<nodeType>::run()
{
	int finalOutputsReady = 0;
	vector<nodeType> outputs;
	while(finalOutputsReady != outputCount)
	{
		for(unsigned i = 0; i < nodes.size(); i++)
		{
			if(!nodes[i]->outputReady)
			{
				if(nodes[i]->isReady())
				{
					nodes[i]->calculate(*nodes[i]);
					for(unsigned j = 0; j < nodes.size(); j++)
					{
						for(unsigned k = 0; k < nodes[j]->getInputs().size(); k++)
						{
							if(nodes[j]->getInputs()[k]->getLabel() == nodes[i]->getLabel())
							{
								nodes[j]->getInputs()[k]->outputReady = true;
							}
						}
					}
					if(nodes[i]->finalOutput)
					{
						outputs.push_back(nodes[i]->getOutput());
						finalOutputsReady++;
					}
				}
			}
		}
	}
	return outputs;
}

#endif
