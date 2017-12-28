
#ifndef FACT_HPP
# define FACT_HPP

# include <vector>
# include <string>
# include <exception>
# include <cstdlib>
# include <iostream>
# include "Expr.hpp"
# include "expert.hpp"
# include "IElement.hpp"

class Expr;

class Fact : public IElement {
private:
    std::vector <Expr *> _rules;

public:
   	char                i;
   	int 				v;

    Fact();
    Fact(int va);
    Fact(char ia, int va);
    Fact(Fact const &rhs);
    virtual ~Fact();

    Fact    &operator=(Fact const &rhs);

    int		val(void) const;

	char	getName() const;

    void	isTrue(void);
    void	change(int newVal);
    void	addExpr(IElement *rule);
    void	set(int val);
protected:

};
/*
bool            operator==(Fact const &lhs, Fact const &rhs);
*/
std::ostream&   operator<<(std::ostream& os, Fact const &t);

#endif
