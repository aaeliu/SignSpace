#include "time.h"

using namespace std;

TimeExpr t = TimeExpr(std::make_shared<TimeVariable>());

/* 
*  A class that representing equations that use
*  the time variable...
*/

TimeExpr::TimeExpr(float x) {
	expr = std::make_shared<Num>(x);
}
TimeExpr TimeExpr::operator+(const TimeExpr& other) const {
	return TimeExpr(std::make_shared<Add>(*this, other));
}
TimeExpr TimeExpr::operator-(const TimeExpr& other) const {
	return TimeExpr(std::make_shared<Subtract>(*this, other));
}

TimeExpr TimeExpr::operator/(const TimeExpr& other) const {
	if (other.expr->isNum()) {
		
		if (expr->isNum()) {
			// std::cout << "expr->val: " << std::static_pointer_cast<Num>(expr)->val << "other.expr->val: " << std::static_pointer_cast<Num>(other.expr)->val << std::endl;
			return TimeExpr(std::make_shared<Num>(std::static_pointer_cast<Num>(expr)->val / std::static_pointer_cast<Num>(other.expr)->val));
		}

		return (*this) * TimeExpr(std::make_shared<Num>(1.0f / std::static_pointer_cast<Num>(other.expr)->val));
		//return TimeExpr(std::make_shared<Mul>(*this, TimeExpr (std::make_shared<Num> (1.0f/ std::static_pointer_cast<Num>(other.expr)->val))));
	}
	return TimeExpr(std::make_shared<Div>(*this, other));
}

TimeExpr TimeExpr::operator-() const {
	return TimeExpr(std::make_shared<Neg>(*this));
}

TimeExpr TimeExpr::operator*(const TimeExpr& other) const {
	if (other.expr->isNum()) {
		//std::cout << "TEST2" << std::static_pointer_cast<Num>(other.expr)->val << "\n";
		if (expr->isMul()) {
			std::shared_ptr<Mul> mul_expr = std::static_pointer_cast<Mul> (expr);
			std::shared_ptr<Num> num_expr;
			//std::cout << "TEST\n";
			if (mul_expr->lhs.expr->isNum()) {
				num_expr = std::static_pointer_cast<Num> (mul_expr->lhs.expr);
				num_expr->val *= std::static_pointer_cast<Num>(other.expr)->val;
				return *this;
			}
			if (mul_expr->rhs.expr->isNum()) {
				num_expr = std::static_pointer_cast<Num> (mul_expr->rhs.expr);
				num_expr->val *= std::static_pointer_cast<Num>(other.expr)->val;
				return *this;
			}
		}
		//std::cout << "TEST3\n";
	}
	return TimeExpr(std::make_shared<Mul>(*this, other));
}

std::string Add::str() const {
	return '(' + lhs.expr->str() + '+' + rhs.expr->str() + ')';

}

std::string Subtract::str() const {
	return '(' + lhs.expr->str() + '-' + rhs.expr->str() + ')';

}

std::string Neg::str() const {
	return  "-(" + t_.expr->str() + ')';

}

std::string Mul::str() const {
	return '(' + lhs.expr->str() + '*' + rhs.expr->str() + ')';

}

std::string Div::str() const {
	return '(' + lhs.expr->str() + '/' + rhs.expr->str() + ')';

}

std::string Sin::str() const {
	return "sin(" + t.expr->str() + ")";

}

std::string Cos::str() const {
	return "cos(" + t.expr->str() + ")";

}

std::string TimeVariable::str() const {
	return "time";
}

std::string Num::str() const {
	// std::cout << "Meow?" << val << "\n";
	return to_string (val);

}