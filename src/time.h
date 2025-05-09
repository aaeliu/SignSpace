#pragma once
#include <memory>
#include <sstream>
#include <iostream>

struct TimeExprNode {

	TimeExprNode() {};

	virtual ~TimeExprNode() = default;
	virtual std::string str() const = 0;

	virtual bool isNum() const = 0;
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
		std::cout << "begin printing TimeExpr object\n";
		stream << t.expr->str();
		std::cout << "end printing TimeExpr object\n";
		return stream;
	}
	// std::string str() {}
	// void print(std::ostream& stream);

	TimeExpr operator+(const TimeExpr& other) const;
	TimeExpr operator/(const TimeExpr& other) const;
	TimeExpr operator*(const TimeExpr& other) const;

};


struct Add : public TimeExprNode {
	TimeExpr lhs, rhs;

	Add(const TimeExpr& a, const TimeExpr& b) : lhs(a), rhs(b) {}
	~Add() override = default;
	std::string  str() const override;
	bool isNum() const override { return false; }

};

struct Div : public TimeExprNode {
	TimeExpr lhs, rhs;

	Div(const TimeExpr& a, const TimeExpr& b) : lhs(a), rhs(b) {}
	~Div() override = default;
	std::string  str() const override;
	bool isNum() const override { return false; }

};

struct Mul : public TimeExprNode {
	TimeExpr lhs, rhs;

	Mul(const TimeExpr& a, const TimeExpr& b) : lhs(a), rhs(b) {}
	~Mul() override = default;
	std::string  str() const override;
	bool isNum() const override { return false; }

};

struct Sin : public TimeExprNode {
	TimeExpr t;
	Sin(const TimeExpr& t_) : t(t_) {}
	~Sin() override = default;
	std::string  str() const override;
	bool isNum() const override { return false; }

};

inline TimeExpr sin(const TimeExpr& t) {
	return TimeExpr(std::make_shared<Sin>(t));
}

struct TimeVariable : public TimeExprNode {
	TimeVariable() {}
	~TimeVariable() override = default;
	std::string  str() const override;
	bool isNum() const override { return false; }
};

struct Num : public TimeExprNode {
	float val;
	Num(float v_) : val(v_) { std::cout << "val: " << v_ << "\n"; }
	~Num() override = default;
	std::string str() const override;
	bool isNum() const override { return true; }
};
extern struct TimeExpr t;