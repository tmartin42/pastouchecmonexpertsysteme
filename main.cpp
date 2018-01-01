
#include "expert.hpp"

//std::vector<IElement *>  mapL;

IElement *opSub(IElement *l){
	std::cout << "SUB " << l->val();
	return(new Fact(l->val()));
}

IElement *opNot(IElement *l){
	std::cout << "NOT " << ((Fact *)l)->i << ": " << l->val();
	if (l->val() == 1) {

		std::cout << " TRUE !!!!" << std::endl;
		return(new Fact(0));
	}
		std::cout << std::endl;
	return (new Fact(1));
}
IElement *opAnd(IElement *l, IElement *r){
//	std::cout << "lol ?" << std::endl;
	std::cout << "AND " << ((Fact *)l)->i << ": " << l->val() << ", " << ((Fact *)r)->i << ": " << r->val();
	if (l->val() && r->val()) {

		std::cout << " TRUE !!!!" << std::endl;
		return(new Fact(1));
	}
		std::cout << std::endl;
	return (new Fact(0));
}
IElement *opOr(IElement *l, IElement *r){
	std::cout << "OR " << ((Fact *)l)->i << ": " << l->val() << ", " << ((Fact *)r)->i << ": " << r->val();
	if (l->val() || r->val()) {

		std::cout << " TRUE !!!!" << std::endl;
		return(new Fact(1));
	}
		std::cout << std::endl;
	return (new Fact(0));
}
IElement *opXor(IElement *l, IElement *r){
	std::cout << "XOR " << ((Fact *)l)->i << ": " << l->val() << ", " << ((Fact *)r)->i << ": " << r->val();
	if ((l->val() && !r->val()) || (!l->val() && r->val())) {
		std::cout << " TRUE !!!!" << std::endl;
		return(new Fact(1));
	}
		std::cout << std::endl;
	return (new Fact(0));
}


/*
int main(void)
{

	char i = 'A';
	while (i <= 'Z') {


		if (i == 'A')
			mapL.push_back(new Fact(i, 1));
		else 
			mapL.push_back(new Fact(i, 0));
		i++;
	}


	std::vector<Expr *> rules;

	std::vector<IElement *> vars;
	std::vector<eGate> gates;
	IElement *implies;

	vars.push_back(mapL['A' - 'A']);
	vars.push_back(mapL['B' - 'A']);
	vars.push_back(mapL['C' - 'A']);

	gates.push_back(OR);
	gates.push_back(AND);

	implies = mapL['C' - 'A'];

 implies->isTrue();

	//std::cout << "i mapl: " <<<< std::endl;

	rules.push_back(new Expr(vars, gates, implies, 1));
//rules[0]->_implies->isTrue();

	for (int j = 0; j < (int)rules.size(); j++) {
	//	std::cout << "j: " << j << std::endl;
		rules[j]->refresh();
	}

	std::cout << "C: " << mapL['C' - 'A']->val() << std::endl;

	}*/
