#include <vector>
#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include "Graph.hpp"
#include "Node.hpp"
#include "MyTypes.h"

using std::vector;
using std::cout;
using std::endl;
using boost::shared_ptr;
using boost::make_shared;

int main()
{
  myVariant a,b,c;
	a = 10.0;
	b = 40.0;
	c = 5.0;

	vector<myVariant> finalOutputs;

	Graph<myVariant> g(2);

	nodeVec tempInputs;

	g.addNode(make_shared<InputNode<myVariant>>(InputNode<myVariant>("a", a)));
	g.addNode(make_shared<InputNode<myVariant>>(InputNode<myVariant>("b", b)));
	g.addNode(make_shared<InputNode<myVariant>>(InputNode<myVariant>("c", c)));
	g.addNode(make_shared<InputNode<myVariant>>(InputNode<myVariant>("-1", myVariant(-1.0))));
	g.addNode(make_shared<InputNode<myVariant>>(InputNode<myVariant>("2", myVariant(2.0))));
	g.addNode(make_shared<InputNode<myVariant>>(InputNode<myVariant>("4", myVariant(4.0))));

	tempInputs.push_back(g.getNode("-1"));
	tempInputs.push_back(g.getNode("b"));
	g.addNode(make_shared<RunnableNode<myVariant>>(RunnableNode<myVariant>("-b", tempInputs, MUL, false)));
	tempInputs.clear();	
	
	tempInputs.push_back(g.getNode("2"));
	tempInputs.push_back(g.getNode("a"));
	g.addNode(make_shared<RunnableNode<myVariant>>(RunnableNode<myVariant>("2a", tempInputs, MUL, false)));
	tempInputs.clear();	

	tempInputs.push_back(g.getNode("4"));
	tempInputs.push_back(g.getNode("a"));
	tempInputs.push_back(g.getNode("c"));
	g.addNode(make_shared<RunnableNode<myVariant>>(RunnableNode<myVariant>("4ac", tempInputs, MUL, false)));
	tempInputs.clear();

	tempInputs.push_back(g.getNode("b"));
	g.addNode(make_shared<RunnableNode<myVariant>>(RunnableNode<myVariant>("b^2", tempInputs, SQ, false)));
	tempInputs.clear();

	tempInputs.push_back(g.getNode("b^2"));
	tempInputs.push_back(g.getNode("4ac"));
	g.addNode(make_shared<RunnableNode<myVariant>>(RunnableNode<myVariant>("b^2 - 4ac", tempInputs, SUB, false)));
	tempInputs.clear();

	tempInputs.push_back(g.getNode("b^2 - 4ac"));
	g.addNode(make_shared<RunnableNode<myVariant>>(RunnableNode<myVariant>("sqrt(b^2 - 4ac)", tempInputs, SQRT, false)));
	tempInputs.clear();

	tempInputs.push_back(g.getNode("-b"));
	tempInputs.push_back(g.getNode("sqrt(b^2 - 4ac)"));
	g.addNode(make_shared<RunnableNode<myVariant>>(RunnableNode<myVariant>("-b + sqrt(b^2 - 4ac)", tempInputs, ADD, false)));
	tempInputs.clear();

	tempInputs.push_back(g.getNode("-b"));
	tempInputs.push_back(g.getNode("sqrt(b^2 - 4ac)"));
	g.addNode(make_shared<RunnableNode<myVariant>>(RunnableNode<myVariant>("-b - sqrt(b^2 - 4ac)", tempInputs, SUB, false)));
	tempInputs.clear();

	tempInputs.push_back(g.getNode("-b - sqrt(b^2 - 4ac)"));
	tempInputs.push_back(g.getNode("2a"));
	g.addNode(make_shared<RunnableNode<myVariant>>(RunnableNode<myVariant>("(-b - sqrt(b^2 - 4ac)) / 2a", tempInputs, DIV, true)));
	tempInputs.clear();

	tempInputs.push_back(g.getNode("-b + sqrt(b^2 - 4ac)"));
	tempInputs.push_back(g.getNode("2a"));
	g.addNode(make_shared<RunnableNode<myVariant>>(RunnableNode<myVariant>("(-b + sqrt(b^2 - 4ac)) / 2a", tempInputs, DIV, true)));
	tempInputs.clear();

	finalOutputs = g.run();

	for(vector<myVariant>::iterator it = finalOutputs.begin(); it != finalOutputs.end(); ++it)
	{
		myVariant current = *it;
		cout << boost::get<double>(current) << endl;
	}
	return 0;
}
