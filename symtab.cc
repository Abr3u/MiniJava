//jpms:bc
/*----------------------------------------------------------------------------*\
 * File:        symtab.cc
 *
 * Description: 
 *
 * Author:      jpms
 *
 *                                     Copyright (c) 2015, Joao Marques-Silva
\*----------------------------------------------------------------------------*/
//jpms:ec

#include "symtab.hh"

static int ind = 0;

bool TempElement::operator==(const TempElement& e) const{
		if (e.getName().compare(this->getName()) == 0){
				return true;		
		}
	return false;
	}

TabData* SymbolTable::lookup(string& var) {
    TabData *td = NULL;
	
    for(int i=ind; i>=0; --i) {
	cout << "Lookup for "<< var << " in "<< i<< endl;
	TabMap::iterator mpos = (*maps[i]).find(var);
	if (mpos != (*maps[i]).end()) {
	    td = mpos->second;
	    break;
	}
    }
    return td;
}

TabData* SymbolTable::lookup_top(string& var) {
   
	int i=ind;
	cout << "@lookupTOP searching "<< var <<" in scope " << i <<endl;
    TabMap::iterator mpos = (*maps[i]).find(var);

    TabData* td = (mpos != (*maps[i]).end()) ? mpos->second : NULL;

	
	if(td!=NULL && td->get_m()!=this->method){return NULL;}
	return td;
}

TabData* SymbolTable::lookupclass() {
    TabData *td = NULL;
	TabMap::iterator mpos = (*maps[0]).begin();
	for ( mpos; mpos != (*maps[0]).end(); ++mpos){
		if (mpos->second->is_class()){
			td = mpos->second;
		}
	}
    
    return td;
}

TabData* SymbolTable::lookupBY(int a) {
	TabData *td = NULL;
	TabMap::iterator mpos = (*maps[0]).begin();
	for ( mpos; mpos != (*maps[0]).end(); ++mpos){
		if (mpos->second->get_classID() == a){
			td = mpos->second;}
	}
    return td;
}

TabData* SymbolTable::lookupFim(string& s, int z){
	TabData *td = NULL;
    TabMap::iterator mpos = (*maps[1]).begin();
	for ( mpos; mpos != (*maps[1]).end(); ++mpos){
		if (mpos->second->get_name() == s){
			cout<<"@fim " << z << " getclassID()-> "<< mpos->second->get_classID()<<endl;
			if(mpos->second->get_classID()==z){
				td = mpos->second;}
		}
	}
    return td;
}

TabData* SymbolTable::lookupFim2(string& s, int z){
	TabData *td = NULL;
    TabMap::iterator mpos = (*maps[2]).begin();
	for ( mpos; mpos != (*maps[2]).end(); ++mpos){
		if (mpos->second->get_name() == s){
			cout<<"@fim2 "<< s<< "  " << z << " getM()-> "<< mpos->second->get_m()<< "@ class "<< mpos->second->get_classID()<< endl;
			if(mpos->second->get_m()==z){
				return mpos->second;}
		}
	}
	return NULL;
}

TabData* SymbolTable::lookup2nd(string& var) {
	TabData *td = NULL;
    TabMap::iterator mpos = (*maps[0]).begin();
	for ( mpos; mpos != (*maps[0]).end(); ++mpos){
		if (mpos->second->get_name() == var){
			td = mpos->second;
		}
	}
    return td;
}

TabData* SymbolTable::lookupmethod(string& var) {
    TabData *td = NULL;
	TabMap::iterator mpos = (*maps[1]).find(var);
	if (mpos != (*maps[1]).end()) {
	    td = mpos->second;
	
	}
	if (td != NULL && td->is_method())
    		return td;
    return NULL;
}


TabData* SymbolTable::insert(string& var, int type)
{
    assert(lookup_top(var) == NULL);

    TabData* vdata = new TabData(var, type,this->globalClass);
    vdata->set_m(this->method);
	
	cout << "Insert with method "<<this->method << endl;
    (*maps[ind])[var] = vdata;	
    return vdata;
}

TabData* SymbolTable::insertExt(string& var, int type, int etended)
{
    assert(lookup_top(var) == NULL);

    TabData* vdata = new TabData(var, type, etended);
    (*maps[ind])[var] = vdata;	
    return vdata;
}

void SymbolTable::push_scope()
{
	if(ind==0){
		if (maps[1] == NULL){
			TabMap* tmap = new TabMap();
	    		maps.push_back(tmap);
		}
	}
	else{
		if (ind==1){
			if(maps[2] == NULL){
				TabMap* tmap = new TabMap();
	    			maps.push_back(tmap);
			}
		}
		else{
			if(ind >=2){ 
			TabMap* tmap = new TabMap();
	    		maps.push_back(tmap);}
		}
	}
	ind++;


}

void SymbolTable::pop_scope()
{
	assert(ind >= 0);
	if(ind>=3){
	    TabMap* tmap = maps[ind];
	    delete tmap;
	    maps.pop_back();
	}

	ind--;
}

void SymbolTable::incGlobalClass(){
	this->globalClass++;
}

void SymbolTable::incM(){
	
	this->method++;	
	cout << "Inrement method kount to "<<this->method << endl;
}

void SymbolTable::hideM(){
	this->method = 0;
}



/*----------------------------------------------------------------------------*/
