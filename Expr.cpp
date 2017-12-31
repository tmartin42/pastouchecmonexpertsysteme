// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Expr.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: fperruch <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/12/21 15:59:25 by fperruch          #+#    #+#             //
//   Updated: 2017/12/21 16:54:04 by fperruch         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Expr.hpp"

Expr::Expr() {
}

Expr::Expr(std::vector<IElement *> vars) {
	_vars = vars;
}

Expr::Expr(std::vector<IElement *> vars, std::vector <eGate> gates) {
	_vars = vars;
	_gates = gates;
}


Expr::Expr(std::vector<IElement *> vars, std::vector <eGate> gates, IElement *implies, int no) {
	
	std::cout << "---------" << std::endl;
 for (int j = 0; j < (int)vars.size(); j++) {
		std::cout << "i: " << ((Fact *)vars[j])->i << ", v:"<< ((Fact *)vars[j])->v << ", j:" << j << std::endl;
	}
	std::cout << "--" << std::endl;
	for (int j = 0; j < (int)gates.size(); j++) {
		std::cout << "gate: " << gates[j] << std::endl;
	}


//	std::cout << "imp: " << (*_implies) << std::endl;
	std::cout << "---------" << std::endl;

	_vars = vars;
	_gates = gates;
	_implies = implies;

	if (no == 1) {
		for (int j = 0; j < (int)_vars.size(); j++) {
			Expr *tmp = new Expr (_vars, _gates, _implies, 0);

			_vars[j]->addExpr(tmp);
		}
	}
}


Expr::Expr(Expr const &rhs) {
	_vars = rhs._vars;
	_gates = rhs._gates;
}

Expr::~Expr() {}

Expr    &Expr::operator=(Expr const &rhs) {
	_vars = rhs._vars;
	_gates = rhs._gates;
	return *this;
}

void Expr::refresh() {

	std::vector<IElement *> cpy_vars = _vars;
	std::vector<eGate> cpy_gates = _gates;
/*
std::cout << "--- into refresh ---" << std::endl;
for (int j = 0; j < (int)_vars.size(); j++) {
		std::cout << "i: " << ((Fact *)_vars[j])->i << ", v:"<< ((Fact *)_vars[j])->v << ", j:" << j << std::endl;
	}
	std::cout << "--" << std::endl;
	for (int j = 0; j < (int)_gates.size(); j++) {
		std::cout << "gate: " << _gates[j] << std::endl;
	}
	std::cout << "---------asdasdasdasdasd" << std::endl;*/
       /* for (int j = 0; j < (int)cpy_vars.size(); j++) {
                std::cout << "i: " << ((Fact *)cpy_vars[j])->i << ", v:"<< ((Fact *)cpy_vars[j])->v << ", j:" << j  << std::endl;
        }*/
        std::cout << "--" << std::endl;
        for (int j = 0; j < (int)cpy_gates.size(); j++) {
                std::cout << "gate: " << cpy_vars[j]->val() << std::endl;
        	std::cout << "gateafter: " << cpy_vars[j]->val() << std::endl;
	}
        std::cout << "---------2" << std::endl;

        for (int j = 0; j < (int)cpy_gates.size(); j++) {
                if (cpy_gates[j] == SUB) {
                   	
			cpy_vars[j] = opSub(cpy_vars[j]);
                        cpy_gates.erase(cpy_gates.begin() + j);
                }
        }
	/*for (int j = 0; j < (int)cpy_vars.size(); j++) {
		std::cout << "i: " << ((Fact *)cpy_vars[j])->i << ", v:"<< ((Fact *)cpy_vars[j])->v << ", j:" << j  << std::endl;
	}
	std::cout << "--" << std::endl;
	for (int j = 0; j < (int)cpy_gates.size(); j++) {
		std::cout << "gate: " << cpy_gates[j] << std::endl;
	}
	std::cout << "---------2" << std::endl;*/

	for (int j = 0; j < (int)cpy_gates.size(); j++) {
		if (cpy_gates[j] == NOT) {
			cpy_vars[j] = opNot(cpy_vars[j]);
			cpy_gates.erase(cpy_gates.begin() + j);
		}
	}

	/*for (int j = 0; j < (int)cpy_vars.size(); j++) {
		std::cout << "i: " << ((Fact *)cpy_vars[j])->i << ", v:"<< ((Fact *)cpy_vars[j])->v << ", j:" << j << std::endl;
	}
	std::cout << "--" << std::endl;
	for (int j = 0; j < (int)cpy_gates.size(); j++) {
		std::cout << "gate: " << cpy_gates[j] << std::endl;
	}
	std::cout << "---------1" << std::endl;*/
	/*std::cout << "C: " << mapL['C' - 'A']->val() << std::endl;*/
	//std::cout << "cpy_gates2: " << cpy_gates.size() << std::endl;
	for (int j = 0; j < (int)cpy_gates.size(); j++) {
		if (cpy_gates[j] == AND) {
			cpy_vars[j] = opAnd(cpy_vars[j], cpy_vars[j + 1]);
			cpy_vars.erase(cpy_vars.begin()+ j + 1);
			cpy_gates.erase(cpy_gates.begin() + j);
		}
	}
	/*for (int j = 0; j < (int)cpy_vars.size(); j++) {
		std::cout << "i: " << ((Fact *)cpy_vars[j])->i << ", v:"<< ((Fact *)cpy_vars[j])->v << ", j:" << j  << std::endl;
	}
	std::cout << "--" << std::endl;
	for (int j = 0; j < (int)cpy_gates.size(); j++) {
		std::cout << "gate: " << cpy_gates[j] << std::endl;
	}
	std::cout << "---------2" << std::endl;*/

	for (int j = 0; j < (int)cpy_gates.size(); j++) {
		if (cpy_gates[j] == OR) {
			cpy_vars[j] = opOr(cpy_vars[j], cpy_vars[j + 1]);
			cpy_vars.erase(cpy_vars.begin() + j + 1);
			cpy_gates.erase(cpy_gates.begin() + j);
		}
	}
	/*for (int j = 0; j < (int)cpy_vars.size(); j++) {
		std::cout << "i: " << ((Fact *)cpy_vars[j])->i << ", v:"<< ((Fact *)cpy_vars[j])->v << ", j:" << j  << std::endl;
	}
	std::cout << "--" << std::endl;
	for (int j = 0; j < (int)cpy_gates.size(); j++) {
		std::cout << "gate: " << cpy_gates[j] << std::endl;
	}
	std::cout << "---------2" << std::endl;*/

	for (int j = 0; j < (int)cpy_gates.size(); j++) {
		if (cpy_gates[j] == XOR) {
			cpy_vars[j] = opXor(cpy_vars[j], cpy_vars[j + 1]);
			cpy_vars.erase(cpy_vars.begin() + j + 1);
			cpy_gates.erase(cpy_gates.begin() + j);
		}
	}


/*	for (int j = 0; j < (int)cpy_vars.size(); j++) {
		std::cout << "i: " << ((Fact *)cpy_vars[j])->i << ", v:"<< ((Fact *)cpy_vars[j])->v << ", j:" << j  << std::endl;
	}
	std::cout << "--" << std::endl;
	for (int j = 0; j < (int)cpy_gates.size(); j++) {
		std::cout << "gate: " << cpy_gates[j] << std::endl;
	}
	std::cout << "---------3" << std::endl;

	std::cout << "-1-- into refresh ---" << std::endl;*/
	//	std::cout << "j: " << j << std::endl;

	if (cpy_vars.back()->val() == 1 && _implies) {

	//std::cout << "imp: " << ((Fact *)_implies)->i << std::endl;
		_implies->isTrue();
	}
}

void Expr::isTrue (void) {
	for (int j = 0; j < (int)_vars.size(); j++) {
		if (_vars[j])
			_vars[j]->isTrue();
	}

	//std::cout << "expr true todo" << std::endl;
}

int Expr::val(void) const {
	std::cout << "LAPIREERREUR" << std::endl;
	
        std::vector<IElement *> cpy_vars = _vars;
        std::vector<eGate> cpy_gates = _gates;

	std::cout << "test" << std::endl;
 for (int j = 0; j < (int)cpy_gates.size(); j++) {
                if (cpy_gates[j] == SUB) {
                        cpy_vars[j] = opSub(cpy_vars[j]);
  //                      cpy_gates.erase(cpy_gates.begin() + j);
                }
        }
        std::cout << "test2" << std::endl;
        for (int j = 0; j < (int)cpy_gates.size(); j++) {
                if (cpy_gates[j] == NOT) {
                        cpy_vars[j] = opNot(cpy_vars[j]);
                        cpy_gates.erase(cpy_gates.begin() + j);
                }
        }
        std::cout << "test3" << std::endl;
      for (int j = 0; j < (int)cpy_gates.size(); j++) {
                if (cpy_gates[j] == AND) {
                        cpy_vars[j] = opAnd(cpy_vars[j], cpy_vars[j + 1]);
                        cpy_vars.erase(cpy_vars.begin()+ j + 1);
                        cpy_gates.erase(cpy_gates.begin() + j);
                }
        }
        std::cout << "test4" << std::endl;
        for (int j = 0; j < (int)cpy_gates.size(); j++) {
                if (cpy_gates[j] == OR) {
                        cpy_vars[j] = opOr(cpy_vars[j], cpy_vars[j + 1]);
                        cpy_vars.erase(cpy_vars.begin() + j + 1);
                        cpy_gates.erase(cpy_gates.begin() + j);
                }
        }
        std::cout << "test5" << std::endl;
        for (int j = 0; j < (int)cpy_gates.size(); j++) {
                if (cpy_gates[j] == XOR) {
                        cpy_vars[j] = opXor(cpy_vars[j], cpy_vars[j + 1]);
                        cpy_vars.erase(cpy_vars.begin() + j + 1);
                        cpy_gates.erase(cpy_gates.begin() + j);
                }
        }
        std::cout << "test6 " << cpy_vars.size() << std::endl;
	if (!cpy_vars.size())
	 return -1;	
	return (cpy_vars.back()->val());
}

IElement    *Expr::getImplies() const {
	return (_implies);
}

std::vector<IElement *> Expr::getVars() const {
	return (_vars);
}

std::vector<eGate>	Expr::getGates() const {
	return (_gates);
}

void Expr::addExpr(IElement *rule)
{
	(void)rule;
	std::cout << "(debug a enlever) add Expr expr" << std::endl;
}
