#ifndef MyTypes_H_INCLUDED
#define MyTypes_H_INCLUDED

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/variant.hpp>
#include <boost/optional.hpp>
#include <vector>

using std::vector;

template<class nodeType>
class Node;

typedef enum e_operations {ADD, SUB, MUL, DIV, SQ, SQRT} operations;

typedef boost::variant<int, double> myVariant;
typedef boost::shared_ptr<myVariant> myVariant_ptr;
typedef boost::shared_ptr<Node<myVariant>> myNode_ptr;
typedef vector<myNode_ptr> nodeVec;

#endif
