// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   expert.cpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: fperruch <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/12/18 19:34:32 by fperruch          #+#    #+#             //
//   Updated: 2017/12/21 17:07:13 by fperruch         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Expr.hpp"
#include <expert.hpp>

std::vector<Fact *>  mapL;

IElement	*getExpr(std::string s) {
	IElement				*out;
	std::vector<IElement *>	elems;
	IElement 				*imp;
	std::vector<eGate>		ope;
	std::string				expr;
	int						nbpar;

	imp = NULL;
	out = NULL;
	for (unsigned i = 0; i < s.size(); i++) {
		if (s[i] == '+')
			ope.push_back(AND);
		if (s[i] == '|')
			ope.push_back(OR);
		if (s[i] == '!')
            ope.push_back(NOT);
		if (s[i] == '^')
            ope.push_back(XOR);
		if (s[i] == '=' && s[i + 1] == '>') {
			expr.clear();
			i++;
			while (++i < s.size())
				expr.push_back(s[i]);
			std::cout << s << " implies " << expr << std::endl;
			imp = getExpr(expr);
		}
		if (s[i] == '(') {
			expr.clear();
            i++;
            nbpar = 0;
			ope.push_back(SUB);
			while (nbpar > 0) {
                if (s[i] == '(')
                    nbpar++;
                if (s[i] == ')')
                    nbpar--;
				i++;
                expr.push_back(s[i]);
            }
			elems.push_back(getExpr(expr));
		}
		if (isupper(s[i]))
			elems.push_back(mapL[s[i] - 'A']);
	}
	if (elems.size() == 1 && !imp && ope.size() == 0)
	{
		std::cout << "retrun fact " << s << std::endl;
		out = elems[0];
	}
	else if (!imp) {
		std::cout << "return no impl " << s << std::endl;
		out = new Expr(elems, ope);
	}
	else {
		std::cout << "return imp " << s << std::endl;
		out = new Expr(elems, ope, imp, 1);
	}
	return (out);
}

void	invalid(int line, std::string s, char c, char d) {
	std::cout << "Invalid statement : \'" << c << (d ? d : '\0');
	std::cout << "\' at line : ";
	std::cout << line << " >> \"" << s << "\"" << std::endl;
}

std::vector<Expr *>	parse(char *av, std::string &input, std::string &output) {
	std::ifstream		f;
    char				str[1024];
    size_t				pos;
	std::string			s;
    unsigned			line;
	std::vector<Expr *>	out;
	int					nbPar;

	f.open(av, std::ifstream::in);
    if (!f.is_open()){
		std::cout << "Error : invalid file" << std::endl;
		throw (std::exception());
    }
    line = 0;
    while (!f.eof()) {
        line++;
        f.getline(str, 1024);
        if (f.fail())
            break ;
        s = str;
        if ((pos = s.find('#')) != s.npos)
            s.erase(pos, s.npos);
        while ((pos = s.find(' ')) != s.npos)
            s.erase(pos, 1);
		nbPar = 0;
        for (unsigned i = 0; i < s.size(); i++) {
            if (!strchr("ABCDEFGHIJKLMNOPQRSTUVWXYZ!()^+=><|?", s[i])) {
				invalid(line, s, s[i], 0);
                f.close();
				throw (std::exception());
            }
			if (i > 0 && s[i - 1] == s[i] && s[i] != '(' && s[i] != ')') {
				invalid(line, s, s[i - 1], s[i]);
				f.close();
				throw (std::exception());
			}
			if (strchr("!^+|?", s[i]) && strchr("!^+=<>|?", s[i + 1])
				&& s[i + 1] != '!' && !isupper(s[i + 1])) {
					invalid(line, s, s[i], s[i + 1]);
                    f.close();
                    throw (std::exception());
			}
			if (s[i] == '(') {
				nbPar++;
				if (s[i + 1] != '!' && s[i + 1] != '(' && !isupper(s[i + 1])) {
					invalid(line, s, s[i], s[i + 1]);
					f.close();
					throw (std::exception());
				}
			}
			if (s[i] == ')') {
				nbPar--;
				if (i > 0 && s[i - 1] != ')' && !isupper(s[i - 1])) {
					invalid(line, s, s[i], s[i - 1]);
                    f.close();
					throw (std::exception());
				}
			}
		}
		if (nbPar > 0) {
			std::cout << "Missing closing parenthesis at line " << line;
			std::cout << " >> \"" << s << "\"" << std::endl;
			throw (std::exception());
		}
		if (nbPar < 0) {
			std::cout << "Missing opening parenthesis at line " << line;
			std::cout << " >> \"" << s << "\"" << std::endl;
			throw (std::exception());
        }
        if (s[0] == '=') {
			if (!input.empty()) {
				std::cout << "Double input ignorded at line " << line;
				std::cout << " \"" << s << "\" previous one : \"=" << input;
				std::cout << "\"" << std::endl;
				continue ;
			}
			else
			{
				for (unsigned i = 1; i < s.size(); i++) {
					if (!strchr("ABCDEFGHIJKLMNOPQRSTUVWXYZ", s[i])) {
						std::cout << "Invalid input variable " << s[i];
						std::cout << " at line " << line;
						std::cout << " >> \"" << s << "\"" << std::endl;
						f.close();
					}
					else if (!strchr(input.c_str(), s[i]))
						input.push_back(s[i]);
				}
				continue ;
			}
        }
		if (s[0] == '?') {
			if (!output.empty()) {
				std::cout << "Double output ignored at line " << line;
				std::cout << " \"" << s << "\" previous one : \"=" << output;
				std::cout << "\"" << std::endl;
				continue ;
			}
            else
            {
                for (unsigned i = 1; i < s.size(); i++) {
                    if (!strchr("ABCDEFGHIJKLMNOPQRSTUVWXYZ", s[i])) {
						std::cout << "Invalid output variable " << s[i];
						std::cout << " at line " << line;
						std::cout << " >> \"" << s << "\"" << std::endl;
                        f.close();
					}
                    else if (!strchr(output.c_str(), s[i]))
                        output.push_back(s[i]);
				}
				continue ;
            }
        }
		if ((isupper(s[0]) || s[0] == '!') && !strstr(s.c_str(), "=>")) {
			std::cout << "rule without output statement ignored  at line ";
			std::cout << line << " >> \"" << s << "\"" << std::endl;
		}
		std::cout << "do expr " << s << std::endl;
		if (s[0])
			out.push_back((Expr *)getExpr(s));
    }
    f.close();
	return (out);
}

int		main(int ac, char** av) {
	std::string			input;
	std::string			output;
	std::vector<Expr *>	syst;

	for (unsigned i = 'A'; i <= 'Z'; ++i)
		mapL.push_back(new Fact(i, 0));
	if (ac != 2) {
		std::cout << "Usage : ./expert_system filename" << std::endl;
		return (EXIT_FAILURE);
	}
	try {
		syst = parse(av[1], input, output);
	} catch (std::exception e) {
		std::cout << "Invalid file. Stoped with error(s)" << std::endl;
		return (EXIT_FAILURE);
	}
	std::cout << "input : " << input << std::endl;
	std::cout << "output : " << output << std::endl;
	for (unsigned i = 0; i < input.size(); i++)
		mapL[input[i] - 'A']->set(1);
	std::cout << "All refreshes" << std::endl;
	for (unsigned i = 0; i < syst.size(); i++)
		syst[i]->refresh();
	std::cout << "results" << std::endl;
	for (unsigned i = 0; i < output.size(); i++)
		std::cout << *(Fact*)(mapL[output[i] - 'A']) << std::endl;
	return (EXIT_SUCCESS);
}
