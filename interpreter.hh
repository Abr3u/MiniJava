
#ifndef _INTERPRETER_H
#define _INTERPRETER_H 1

#include "visitor.hh"


class Interpreter : public Visitor {
public:

    Interpreter() : Visitor(), breakout(false) { }

    void visit(ASTProgramNode& n){
		n.node1->accept(*this);
	}

	void visit(ASTMainNode& n){
		n.node1->accept(*this);
	}

	void visit(ASTClassDeclAuxNode& n){
		n.node1->accept(*this);
		if(n.node2!=NULL) {n.node2->accept(*this);}
	}

	void visit(ASTClassDeclNode& n){
		if (n.node1 != NULL) n.node1->accept(*this);
		if (n.node2 != NULL) n.node2->accept(*this);
	}

	void visit(ASTTypeNode& n){
	}

	void visit(ASTExtClassDeclNode& n){
		if (n.node1 != NULL) n.node1->accept(*this);
		if (n.node2 != NULL) n.node2->accept(*this);
	}

	void visit(ASTVarDeclAuxNode& n){
	}

	void visit(ASTVarDeclNode& n){	
	}

	void visit(ASTMethodDeclAuxNode& n){
		n.node1->accept(*this);
		if(n.node2!=NULL){n.node2->accept(*this);}
	}

	void visit(ASTMethodDeclNode& n){
		if(n.node4 !=NULL)n.node4->accept(*this);
	}

	void visit(ASTFormListNode& n){
	}

	void visit(ASTFormRestAuxNode& n){
	}

	void visit(ASTFormRestNode& n){
	}

	void visit(ASTStAuxNode& n){
		if(n.node1 !=NULL) n.node1->accept(*this);
		if(n.node2 !=NULL) {n.node2->accept(*this);}
	}

	void visit(ASTStmtsNode& n){
		n.node1->accept(*this);
	}


	void visit(ASTStIfNode& n){
		
		n.node1->accept(*this);
	if (n.node1->value.bval) {
	    if (n.node2 != NULL) { n.node2->accept(*this); }
	} else {
	    if (n.node3 != NULL) { n.node3->accept(*this); }
	}
	}
	
	void visit(ASTStWhileNode& n){
	while(true) {
	    n.node1->accept(*this);
	    if (not n.node1->value.bval) {
		break;
	    } else {
		n.node2->accept(*this);
	    }
	}
	}
	

	void visit(ASTStPrintNode& n){
		n.node1->accept(*this);
	if (*n.node1->get_type() == inteiro) {
	    cout << n.node1->value.ival << endl;
	} else if (*n.node1->get_type() == bol) {
	    cout << n.node1->value.bval << endl;
	}
	}


	void visit(ASTStEqNode& n){
		n.node1->accept(*this);
	n.node2->accept(*this);
	n.node1->value.ival = n.node2->value.ival;
	n.node1->value.bval = n.node2->value.bval;
	}

	void visit(ASTStArrayEqNode& n){
	}

	void visit(ASTStReadersNode& n){}

	void visit(ASTExpThisNode& n){}

	void visit(ASTExpBoolNode& n){}

	void visit(ASTExpOperatorNode& n){
		n.node1->accept(*this);
	    n.node2->accept(*this);
	    string* oper = n.op1; 
	    if(oper == new string("+")){
		n.value.ival = n.node1->value.ival + n.node2->value.ival;}
	    if(oper == new string("-")){
		n.value.ival = n.node1->value.ival - n.node2->value.ival;}
	    if(oper == new string("*")){
		n.value.ival = n.node1->value.ival * n.node2->value.ival;}
	    
	}

	void visit(ASTExpOperatorLNode& n){
		n.node1->accept(*this);
		n.node2->accept(*this);
		string* operL = n.op1;
	if(operL == new string("<") || operL==new string(">")){
	    n.value.bval =
		(n.op1 == new string("<")) ?
		(n.node1->value.ival < n.node2->value.ival) :
		(n.node1->value.ival > n.node2->value.ival);
	}else if(operL == new string("&&")){
		n.value.bval = (n.node1->value.bval && n.node2->value.bval);
	}
	else{
		n.value.bval =
		(n.op1 == new string("==")) ?
		(n.node1->value.ival == n.node2->value.ival) :
		(n.node1->value.ival != n.node2->value.ival);
	}
	}

	void visit(ASTExpArrayNode& n){
		n.node1->accept(*this);
		n.node2->accept(*this);
	}	

	void visit(ASTExpLengthNode& n){
		n.node1->accept(*this);
	}
	
	void visit(ASTExpCallNode& n){
		cout << "Interpreting call" << endl;  
		n.node1->accept(*this);
		if(n.node2!=NULL) {n.node2->accept(*this);}
	}
	
	void visit(ASTExpIntNode& n){}

	void visit(ASTIDRefNode& n){}

	void visit(ASTIntArrayNode& n){
		n.node1->accept(*this);
	}

	void visit(ASTObjectNode& n){
	}

	void visit(ASTNegationNode& n){
		n.node1->accept(*this);
		n.value.bval = !n.node1->value.bval;
	}

	void visit(ASTExpListNode& n){
		n.node1->accept(*this);
		if(n.node2!=NULL){n.node2->accept(*this);}
	}

	void visit(ASTExpRestAuxNode& n){
		n.node1->accept(*this);
		if(n.node2!=NULL){n.node2->accept(*this);}
	}		
	
	void visit(ASTExpRestNode& n){
		n.node1->accept(*this);
	}

public:

    bool breakout;

};

#endif /* _INTERPRETER_H */

/*----------------------------------------------------------------------------*/
