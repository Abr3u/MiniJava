//jpms:bc
/*----------------------------------------------------------------------------*\
 * File:        typechecker.hh
 *
 * Description: Type check the RIXPR language.
 *
 * Author:      jpms
 * 
 *                                     Copyright (c) 2015, Joao Marques-Silva
\*----------------------------------------------------------------------------*/
//jpms:ec

#ifndef _TYPECHECKER_H
#define _TYPECHECKER_H 1

#include "visitor.hh"


class TypeChecker : public Visitor {

public:

    TypeChecker() : Visitor(), typeok(true) { }
 
	void visit(ASTProgramNode& n){
		n.node1->accept(*this);
		n.node2->accept(*this);
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
		
		bool tok = (*n.node1->get_type() == *n.node5->get_type());
		typeok = typeok && tok;
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
		n.node2->accept(*this);
		n.node3->accept(*this);
		bool tok = (*n.node1->get_type() == bol);
		typeok = tok && typeok;
	}
	
	void visit(ASTStWhileNode& n){
		n.node1->accept(*this);
		if(n.node2!=NULL){n.node2->accept(*this);}
		bool tok = (*n.node1->get_type() == bol);
		typeok = tok && typeok;	
	}
	

	void visit(ASTStPrintNode& n){
		n.node1->accept(*this);
		bool tok = ((*n.node1->get_type()) != nili);
		typeok = tok && typeok;
	}


	void visit(ASTStEqNode& n){
		n.node1->accept(*this);
		n.node2->accept(*this);
		bool tok = (*n.node1->get_type() == *n.node2->get_type());
		typeok = tok && typeok;	
	}

	void visit(ASTStArrayEqNode& n){
		n.node1->accept(*this);
		n.node2->accept(*this);
		n.node3->accept(*this);
		bool tok = ( (*n.node1->get_type() == intarray) && (*n.node2->get_type() == inteiro) && (*n.node3->get_type() == inteiro));
		typeok = tok && typeok;
	}

	void visit(ASTStReadersNode& n){}

	void visit(ASTExpThisNode& n){}

	void visit(ASTExpBoolNode& n){}

	void visit(ASTExpOperatorNode& n){
		n.node1->accept(*this);
		n.node2->accept(*this);
		bool tok = ( (*n.node1->get_type()==inteiro) && (*n.node2->get_type() == inteiro) );
		typeok = tok && typeok;
	}

	void visit(ASTExpOperatorLNode& n){
		n.node1->accept(*this);
		n.node2->accept(*this);
		bool tok = ( (*n.node1->get_type()==inteiro) && (*n.node2->get_type() == inteiro) );
		bool tokL = ( (*n.node1->get_type()==bol) && (*n.node2->get_type() == bol) );
		tok = tok || tokL;
		typeok = tok && typeok;
	}

	void visit(ASTExpArrayNode& n){
		n.node1->accept(*this);
		n.node2->accept(*this);
		bool tok = ( (*n.node2->get_type() == inteiro) && (*n.node1->get_type() == intarray) );
		typeok = tok && typeok;
	}	

	void visit(ASTExpLengthNode& n){
		n.node1->accept(*this);
		bool tok = (*n.node1->get_type() == intarray);
		typeok = tok && typeok;
	}
	
	void visit(ASTExpCallNode& n){
		n.node1->accept(*this);
		if(n.node2!=NULL) {n.node2->accept(*this);}
		string* ola = n.get_type();
		bool tok;
		ASTFormRestNode* formRest;
		ASTExpRestNode* epRest;
		ASTFormListNode* formList = (ASTFormListNode*) n.getMnode()->node2;
		ASTExpListNode* epList = (ASTExpListNode*) n.node2;
		/*if (epList == NULL){
			if (formList != NULL){cout << "Missing arguments"<<endl; tok = false;}
		}
		else{
			cout << "Tou a andar para a FRENTE!!!" << endl;
			if (formList == NULL){cout << "Too many arguments"<<endl; tok = false;}

			else if (epList->node1->get_type() != formList->node1->get_type()){
						cout << "Invalid arguments" << endl; tok = false;}

			epRest = (ASTExpRestNode*) epList->node2;
			formRest = (ASTFormRestNode*) formList->node2;
			while (epRest != NULL){
				if (formRest == NULL){
					cout << "Too many arguments" << endl; tok = false; break;}
				else{
					if (epRest->node1->get_type() != formRest->node1->get_type()) {
						cout << "Invalid arguments" << endl; tok = false;} 
				}
				epRest = (ASTExpRestNode*) epList->node2;
				formRest = (ASTFormRestNode*) formList->node2;
				
			}
		}*/
	}
	
	void visit(ASTExpIntNode& n){}

	void visit(ASTIDRefNode& n){}

	void visit(ASTIntArrayNode& n){
		n.node1->accept(*this);
		bool tok = (*n.node1->get_type() == inteiro);
		typeok = tok && typeok;
	}

	void visit(ASTObjectNode& n){
		bool tok = ((*n.get_type() != inteiro) && (*n.get_type()!=bol));
		typeok = tok && typeok;
	}

	void visit(ASTNegationNode& n){
		n.node1->accept(*this);
		bool tok = (*n.get_type() == bol);
		typeok = tok && typeok;
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

    bool typeok;

};

#endif /* _TYPECHECKER_H */

/*----------------------------------------------------------------------------*/
