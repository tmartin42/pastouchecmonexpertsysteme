// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Expr.hpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: fperruch <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/10/18 19:00:40 by fperruch          #+#    #+#             //
//   Updated: 2017/12/21 16:55:44 by fperruch         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef EXPR_HPP
# define EXPR_HPP

# include <vector>
# include <string>
# include <exception>
# include <cstdlib>
# include <iostream>
# include "expert.hpp"
# include "IElement.hpp"

enum eGate{SUB, NOT, AND, OR, XOR, IMPLIES};

class Expr : public IElement {
private:
    std::vector<IElement *>	_vars;
    std::vector<eGate>		_gates;
	IElement				*_implies;

public:
    Expr();

    Expr(std::vector<IElement *> vars);    
    Expr(std::vector<IElement *> vars, std::vector <eGate> gates);
    Expr(std::vector<IElement *> vars, std::vector <eGate> gates, IElement *implies, int no);

    Expr(Expr const &rhs);
    virtual ~Expr();

    int		val(void) const;

    void	isTrue(void);
	void	isNot(void);
    void addExpr(IElement *rule);
    void	refresh();

	IElement	*getImplies() const;

	std::vector<IElement *>	getVars() const;

	std::vector<eGate>	getGates() const;

    Expr	&operator=(Expr const &rhs);


protected:

};
/*
bool            operator==(Expr const &lhs, Expr const &rhs);

std::ostream&   operator<<(std::ostream& os, Expr const &t);
*/
#endif
