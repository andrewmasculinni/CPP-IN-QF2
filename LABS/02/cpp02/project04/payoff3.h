// PayOff.h

#ifndef PAYOFF3_H
#define PAYOFF3_H

// declaration of a base class
class PayOff
{
public:
	// construtor
	PayOff() {};
	// method (function)
	virtual double operator()(double spot) const = 0;
	// destructor
	virtual ~PayOff() {}

private:
};

// declaration of the first inherited class
class PayOffCall : public PayOff
{
public:
	// construtor
	PayOffCall(double strike_);
	// method (function)
	virtual double operator()(double spot) const;
	// destructor
	virtual ~PayOffCall() {}

private:
	// member (attribute)
	double strike;
};

// declaration of the second inherited class
class PayOffPut : public PayOff
{
public:
	// construtor
	PayOffPut(double strike_);
	// method (function)
	virtual double operator()(double spot) const;
	// destructor
	virtual ~PayOffPut() {}

private:
	// member (attribute)
	double strike;
};


class PayOffDigital : public PayOff
{
public:
	PayOffDigital(double strike_);
	virtual double operator()(double spot) const;
	virtual ~PayOffDigital() {}
private:
	double strike;
};

class PayOffDoubleDigital : public PayOff
{
public:
	PayOffDoubleDigital(double strike_, double strike_upper_);
	virtual double operator()(double spot) const;
	virtual ~PayOffDoubleDigital() {}
private:
	double strike;
	double strike_upper;
};

class PayOffPower1 : public PayOff
{
public:
	PayOffPower1(double strike_, int type_);
	virtual double operator()(double spot) const;
	virtual ~PayOffPower1() {}
private:
	double strike;
	int type;
};

class PayOffPower2 : public PayOff
{
public:
	PayOffPower2(double strike_, int type_);
	virtual double operator()(double spot) const;
	virtual ~PayOffPower2() {}
private:
	double strike;
	int type;
};

#endif
