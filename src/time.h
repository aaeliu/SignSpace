#pragma once
#include <memory>
#include <sstream>
#include <iostream>

struct TimeExprNode {

	TimeExprNode() {};

	virtual ~TimeExprNode() = default;
	virtual std::string str() const = 0;

	virtual bool isNum() const = 0;
	virtual bool isMul() const = 0;
};

struct TimeExpr {
	// because we need to wrap a virtual class..
	std::shared_ptr<TimeExprNode> expr;
	//bool is_single_num = false;
	//float val = -1;

	TimeExpr() {};
	TimeExpr(float x);
	TimeExpr(const std::shared_ptr<TimeExprNode> t) { expr = t; }

	template<typename T, typename std::enable_if<std::is_base_of<TimeExprNode, T>::value, int>::type = 0>
	TimeExpr(const std::shared_ptr<const T> p)
		: expr(std::static_pointer_cast<const TimeExprNode>(p)) {
	}

	TimeExpr(const TimeExpr& other) {
		expr = other.expr;
	}

	TimeExpr(TimeExpr&& other) noexcept {
		expr = other.expr;
	}

	// std::ostream& operator<<(std::ostream& stream);
	friend std::ostream& operator<<(std::ostream& stream, const TimeExpr& t) {
		stream << t.expr->str();
		return stream;
	}
	// std::string str() {}
	// void print(std::ostream& stream);

	TimeExpr operator=(const TimeExpr& other) const {
		return other;
	}

	TimeExpr operator+(const TimeExpr& other) const;
	TimeExpr operator-(const TimeExpr& other) const;
	TimeExpr operator-() const;
	TimeExpr operator/(const TimeExpr& other) const;
	TimeExpr operator*(const TimeExpr& other) const;


};

inline TimeExpr operator+(float f, const TimeExpr& other) {
	return (other + f);
}

inline TimeExpr operator*(float f, const TimeExpr& other) {
	return (other * f);
}


struct Add : public TimeExprNode {
	TimeExpr lhs, rhs;

	Add(const TimeExpr& a, const TimeExpr& b) : lhs(a), rhs(b) {}
	~Add() override = default;
	std::string  str() const override;
	bool isNum() const override { return false; }
	bool isMul() const override { return false; }

};

struct Subtract : public TimeExprNode {
	TimeExpr lhs, rhs;

	Subtract(const TimeExpr& a, const TimeExpr& b) : lhs(a), rhs(b) {}
	~Subtract() override = default;
	std::string  str() const override;
	bool isNum() const override { return false; }
	bool isMul() const override { return false; }

};

struct Neg : public TimeExprNode {
	TimeExpr t_;

	Neg(const TimeExpr& t) : t_(t) {}
	~Neg() override = default;
	std::string  str() const override;
	bool isNum() const override { return false; }
	bool isMul() const override { return false; }

};

struct Div : public TimeExprNode {
	TimeExpr lhs, rhs;

	Div(const TimeExpr& a, const TimeExpr& b) : lhs(a), rhs(b) {}
	~Div() override = default;
	std::string  str() const override;
	bool isNum() const override { return false; }
	bool isMul() const override { return false; }

};

struct Mul : public TimeExprNode {
	TimeExpr lhs, rhs;

	Mul(const TimeExpr& a, const TimeExpr& b) : lhs(a), rhs(b) {}
	~Mul() override = default;
	std::string  str() const override;
	bool isNum() const override { return false; }
	bool isMul() const override { return true; }

};

struct Sin : public TimeExprNode {
	TimeExpr t;
	Sin(const TimeExpr& t_) : t(t_) {}
	~Sin() override = default;
	std::string  str() const override;
	bool isNum() const override { return false; }
	bool isMul() const override { return false; }

};

inline TimeExpr sin(const TimeExpr& t) {
	return TimeExpr(std::make_shared<Sin>(t));
}

struct Cos : public TimeExprNode {
	TimeExpr t;
	Cos(const TimeExpr& t_) : t(t_) {}
	~Cos() override = default;
	std::string  str() const override;
	bool isNum() const override { return false; }
	bool isMul() const override { return false; }

};

inline TimeExpr cos(const TimeExpr& t) {
	return TimeExpr(std::make_shared<Cos>(t));
}

struct TimeVariable : public TimeExprNode {
	TimeVariable() {}
	~TimeVariable() override = default;
	std::string  str() const override;
	bool isNum() const override { return false; }
	bool isMul() const override { return false; }
};

struct Num : public TimeExprNode {
	float val;
	Num(float v_) : val(v_) {  }
	~Num() override = default;
	std::string str() const override;
	bool isNum() const override { return true; }
	bool isMul() const override { return false; }
};
extern struct TimeExpr t;