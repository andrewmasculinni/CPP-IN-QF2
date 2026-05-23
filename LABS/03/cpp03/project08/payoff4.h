#ifndef PAYOFF4_H
#define PAYOFF4_H

class PayOff
{
public:
    PayOff() {};

    virtual double operator()(double spot) const = 0;
    virtual ~PayOff() {};
    virtual PayOff *clone() const = 0;

private:
};

class PayOffCall : public PayOff
{
public:
    PayOffCall(double strike_);

    virtual double operator()(double spot) const;
    virtual ~PayOffCall() {};
    virtual PayOff *clone() const;

private:
    double strike;
};

class PayOffPut : public PayOff
{
public:
    PayOffPut(double strike_);
    virtual double operator()(double spot) const;
    virtual ~PayOffPut() {};
    virtual PayOff *clone() const;

private:
    double strike;
};

class PayOffBarrierCall : public PayOff
{
public:
    PayOffBarrierCall(double strike1_, double strike2_);
    virtual double operator()(double spot) const;
    virtual ~PayOffBarrierCall() {}
    virtual PayOff *clone() const;
private:
    double strike1;
    double strike2;
};

class PayOffBarrierPut : public PayOff
{
public:
    PayOffBarrierPut(double strike1_, double strike2_);
    virtual double operator()(double spot) const;
    virtual ~PayOffBarrierPut() {}
    virtual PayOff *clone() const;
private:
    double strike1;
    double strike2;
};

#endif
