// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Fact.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: fperruch <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/12/21 16:51:50 by fperruch          #+#    #+#             //
//   Updated: 2017/12/21 16:51:51 by fperruch         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //


#include "Fact.hpp"

Fact::Fact() {
	i = 0;
	v = -1;
}

Fact::Fact(int va) {
	i = 0;
	v = va;
}

Fact::Fact(char ia, int va) {
	i = ia;
	v = va;
}

Fact::Fact(Fact const &rhs) {
	i = rhs.i;
	v = rhs.v;
}

Fact 	&Fact::operator=(Fact const &rhs) {
	i = rhs.i;
	v = rhs.v;
	return *this;
}

Fact::~Fact(){}

int Fact::val(void) const {
	return v;
}

void Fact::change(int newVal) {
	if (v != newVal) {
		//	std::cout << "refresh " << std::endl;
	v = newVal;
		std::cout << "refresh " << (char)i << " with val: "<< v << std::endl;
		for (int j = 0; j < (int)_rules.size(); j++) {
			_rules[j]->refresh();
		}
	}
}

void Fact::addExpr(IElement *rule)
{
	_rules.push_back((Expr *)rule);
}

void	Fact::isNot(void) {
	if (v == 1)
		change(0);
	else if (v == 0)
		change(1);
}

void Fact::isTrue(void) {
	

//	std::cout << "letter: " << i << std::endl;
	change(1);
}

void	Fact::set(int val) {
	v = val;
}

char	Fact::getName() const {
	return (i);
}

std::ostream&   operator<<(std::ostream& os, Fact const &t) {
	os << t.getName() << "=" << t.val();
	return (os);
}
