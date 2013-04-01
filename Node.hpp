#ifndef Node_HPP_INCLUDED
#define Node_HPP_INCLUDED

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/variant.hpp>
#include <boost/optional.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "MyTypes.h"

using std::vector;
using std::string;
using boost::make_shared;
using boost::shared_ptr;
using boost::function;
using boost::get;

template<class nodeType>
class Node
{
protected:
  string label; 
	shared_ptr<nodeType> output;

public:
	bool outputReady;
	bool finalOutput;
	bool runnable;

	nodeVec getInputs() const;
	inline nodeType getOutput() const {return *output;}
	inline string getLabel() const {return label;}
	virtual bool isReady();

	function<void(Node<nodeType>&)> calculate;

	virtual ~Node();
};

template<class nodeType>
class InputNode : public Node<nodeType>
{
public:
	InputNode(string, nodeType);
	inline ~InputNode(){}
	inline bool isReady() {return true;}
};

template<class nodeType> 
class RunnableNode : public Node <nodeType>
{
private:
	nodeVec inputs;
	operations op;

public:
	RunnableNode(string, nodeVec, operations, bool);
	inline ~RunnableNode(){}

	bool isReady();
	inline nodeVec getInputs() const {return inputs;}
	inline operations getNodeOperation() const {return op;}

	void setOutput(nodeType);

	function<void(Node<nodeType>&)> calculate;
	void addFunction();
	void subsFunction();
	void mulFunction();
	void divFunction();
	void sqFunction();
	void sqrtFunction();
};

template<class nodeType>
nodeVec Node<nodeType>::getInputs() const
{
	nodeVec n;
	return n;
}

template<class nodeType>
InputNode<nodeType>::InputNode(string label, nodeType value)
{
	label = label;
	output = make_shared<nodeType>(value);
	outputReady = true;
	finalOutput = false;
	runnable = false;
}

template<class nodeType>
RunnableNode<nodeType>::RunnableNode(string label, nodeVec inputs, operations op, bool finalOutput)
{
	this->label = label;
	this->inputs = inputs;
	this->op = op;
	this->finalOutput = finalOutput;
	outputReady = false;
	runnable = true;
	switch(op)
	{
		case 0:
		{
			calculate = &RunnableNode<nodeType>::addFunction;
			break;
		}
		case 1:
		{
			calculate = &RunnableNode<nodeType>::subsFunction;
			break;
		}
		case 2:
		{
			calculate = &RunnableNode<nodeType>::mulFunction;
			break;
		}
		case 3:
		{
			calculate = &RunnableNode<nodeType>::divFunction;
			break;
		}
		case 4:
		{
			calculate = &RunnableNode<nodeType>::sqFunction;
			break;
		}
		case 5:
		{
			calculate = &RunnableNode<nodeType>::sqrtFunction;
			break;
		}
	}
}

template<class nodeType>
void RunnableNode<nodeType>::setOutput(nodeType calculated) 
{
	output = make_shared<nodeType>(calculated);
	outputReady = true;
}

template<class nodeType>
bool RunnableNode<nodeType>::isReady()
{
	for(vector<shared_ptr<Node<nodeType>>>::iterator it = inputs.begin(); it != inputs.end(); ++it)
	{
		shared_ptr<Node<nodeType>> current = *it;
		if(!current->outputReady)
			return false;
	}
	return true;
}

template<class nodeType>
void RunnableNode<nodeType>::addFunction()
{
	double temp1 = 0, temp2 = 0;
	for(vector<shared_ptr<Node<nodeType>>>::iterator it = inputs.begin(); it != inputs.end(); ++it)
	{
		shared_ptr<Node<nodeType>> current = *it;
		temp1 = get<double>(current->getOutput());
		temp2 += temp1;
	}
	nodeType calculated = temp2;
	setOutput(calculated);
}

template<class nodeType>
void RunnableNode<nodeType>::subsFunction()
{
	double temp1 = 0,temp2 = 0;
	int whichOperand = 0;
	for(vector<shared_ptr<Node<nodeType>>>::iterator it = inputs.begin(); it != inputs.end(); ++it)
	{
		shared_ptr<Node<nodeType>> current = *it;
		if(whichOperand == 0)
		{
			temp1 = get<double>(current->getOutput());
			whichOperand++;
		}
		else
		{
			temp2 = get<double>(current->getOutput());
		}
	}
	temp1 -= temp2;
	nodeType calculated = temp1;
	setOutput(calculated);
}

template<class nodeType>
void RunnableNode<nodeType>::mulFunction()
{
	double temp1 = 1, temp2 = 1;
	for(vector<shared_ptr<Node<nodeType>>>::iterator it = inputs.begin(); it != inputs.end(); ++it)
	{
		shared_ptr<Node<nodeType>> current = *it;
		temp1 = get<double>(current->getOutput());
		temp2 *= temp1;
	}
	nodeType calculated = temp2;
	setOutput(calculated);
}

template<class nodeType>
void RunnableNode<nodeType>::divFunction()
{
	double temp1 = 0,temp2 = 0;
	int whichOperand = 0;
	for(vector<shared_ptr<Node<nodeType>>>::iterator it = inputs.begin(); it != inputs.end(); ++it)
	{
		shared_ptr<Node<nodeType>> current = *it;
		if(whichOperand == 0)
		{
			temp1 = get<double>(current->getOutput());
			whichOperand++;
		}
		else
		{
			temp2 = get<double>(current->getOutput());
		}
	}
	temp1 /= temp2;
	nodeType calculated = temp1;
	setOutput(calculated);
}

template<class nodeType>
void RunnableNode<nodeType>::sqFunction()
{
	double temp = get<double>(inputs[0]->getOutput());
	nodeType calculated = (temp * temp);
	setOutput(calculated);
}

template<class nodeType>
void RunnableNode<nodeType>::sqrtFunction()
{
	double temp = get<double>(inputs[0]->getOutput());
	nodeType calculated = sqrt(temp);
	setOutput(calculated);
}

#endif
