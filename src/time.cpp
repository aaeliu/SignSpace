#include "time.h"

using namespace std;

TimeExpr t = TimeExpr(std::make_shared<TimeVariable>());

/* 
*  A class that representing equations that use
*  the time variable...
*/

/*TimeExprNode::TimeExprNode(const TimeExprNode& x) {
	std::cout << "not int "  << std::endl;
}*/

TimeExpr::TimeExpr(float x) {
	expr = std::make_shared<Num>(x);
}
TimeExpr TimeExpr::operator+(const TimeExpr& other) const {
	return TimeExpr(std::make_shared<Add>(*this, other));
}

TimeExpr TimeExpr::operator/(const TimeExpr& other) const {
	if (other.expr->isNum()) {
		
		if (expr->isNum()) {
			std::cout << "expr->val: " << std::static_pointer_cast<Num>(expr)->val << "other.expr->val: " << std::static_pointer_cast<Num>(other.expr)->val << std::endl;
			return TimeExpr(std::make_shared<Num>(std::static_pointer_cast<Num>(expr)->val / std::static_pointer_cast<Num>(other.expr)->val));
		}

		return TimeExpr(std::make_shared<Mul>(*this, TimeExpr (std::make_shared<Num> (1.0f/ std::static_pointer_cast<Num>(other.expr)->val))));
	}
	return TimeExpr(std::make_shared<Div>(*this, other));
}

TimeExpr TimeExpr::operator*(const TimeExpr& other) const {
	return TimeExpr(std::make_shared<Mul>(*this, other));
}
/*std::ostream& TimeExpr::operator<<(std::ostream& stream) {
	stream << "meow";
	return stream;
	print(stream);
}*/
/*std::stringstream& TimeExpr::operator<<(std::stringstream& stream, const TimeExpr& t) {
	stream << "meow";
	return stream;
	print(stream);
}*/

std::string Add::str() const {
	return '(' + lhs.expr->str() + '+' + rhs.expr->str() + ')';

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

std::string TimeVariable::str() const {
	return "time";
}

std::string Num::str() const {
	std::cout << "Meow?" << val << "\n";
	return to_string (val);

}