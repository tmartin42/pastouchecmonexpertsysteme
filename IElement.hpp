// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   IElement.hpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: fperruch <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/10/05 17:57:32 by fperruch          #+#    #+#             //
//   Updated: 2017/12/21 16:55:17 by fperruch         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef IELEMENT_HPP
# define IELEMENT_HPP

# include "expert.hpp"

class IElement {
public :
	virtual void isNot(void) = 0;
	virtual void isTrue(void) = 0;
    virtual int 	val(void) const = 0;
    virtual void addExpr(IElement *rule) = 0;
};

#endif
