// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   expert.hpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: fperruch <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/12/18 19:34:40 by fperruch          #+#    #+#             //
//   Updated: 2017/12/21 14:45:09 by fperruch         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef EXPERT_HPP
#define EXPERT_HPP

#include <vector>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <exception>

#include "IElement.hpp"

#include "Expr.hpp"
#include "Fact.hpp"

class Fact;

extern std::vector<Fact *>  mapL;

IElement *opNot(IElement *l);
IElement *opAnd(IElement *l, IElement *r);
IElement *opOr(IElement *l, IElement *r);
IElement *opXor(IElement *l, IElement *r);



//extern std::map<char, int>      mapL;

#endif
