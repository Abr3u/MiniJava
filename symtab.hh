//jpms:bc
/*----------------------------------------------------------------------------*\
 * File:        symtab.hh
 *
 * Description: 
 *
 * Author:      jpms
 * 
 *                                     Copyright (c) 2015, Joao Marques-Silva
\*----------------------------------------------------------------------------*/
//jpms:ec

#ifndef _SYMTAB_H
#define _SYMTAB_H 1

#include "includes.hh"

class TabData;
class ASTNode;


	
typedef unordered_map<string,TabData*> TabMap;


class TempElement{

public: 
	TempElement(string n, int id, bool vari): name(n), ID(id), var(vari) {}
	int getID() const {return ID;}
	string getName() const {return name;}
	bool isVar(){return var;}
	bool operator==(const TempElement& e) const;
protected:
	string name;
	int ID;	
	bool var;
};

class SymbolTable {
public:
    SymbolTable() : maps() { TabMap* tmap = new TabMap(); maps.push_back(tmap); globalClass = 0; method = 1; auMethod = 1;}

    TabData* lookup(string& var);
    TabData* lookupclass(); 
	TabData* lookup2nd(string& var);
    TabData* lookup_top(string& var);
	TabData* lookupFim(string& s, int z);
	TabData* lookupFim2(string& s, int z);
	TabData* lookupBY(int a);
    TabData* lookupmethod(string& method); 
    TabData* insert(string& var,int t);
    TabData* insertExt(string& var, int type, int etended);
	
void incGlobalClass();
void incM();
void hideM();

    void push_scope();

    void pop_scope();

 int globalClass;
 int method;
 int auMethod;
protected:
    vector<TabMap*> maps;
};

class TabData {
public:
    TabData(string& nm, int typee,int id) : name(nm), node(NULL),classID(id), type(typee) {}
	
    inline void set_node(ASTNode* nn) { node = nn; }

    inline ASTNode* get_node() { return node; }
	inline int get_classID() {return classID;}
	inline bool is_var() {if (type==1) return true; return false;}
	inline bool is_method() {if (type==2) return true; return false;}
	inline bool is_class() {if (type==3) return true; return false;}

    inline string& get_name() { return name; }
	inline void set_m(int m){methodID = m;}
	inline int get_m(){return methodID;}

protected:

    string& name;
	bool isvar;
	bool ismethod;
	bool isclass;
	int type;
	int classID;
	int methodID;

    ASTNode* node;

};

#endif /* _SYMTAB_H */

/*----------------------------------------------------------------------------*/
