#include "../inc/Operand.hpp"

// template<class T> Operand<T>::Operand()
// {
// 	this->_value = std::to_string(static_cast<T>(0));
// }

template<class T> Operand<T>::Operand(Operand<T> const & src)
{
	*this = src;
}

template<class T> Operand<T>::~Operand(){}

template<class T> Operand<T> & Operand<T>::operator=(Operand<T> const & rhs)
{
	this->_value = rhs._value; 
	return *this;
}

template<class T> Operand<T>::Operand(T value)
{
	this->_value = std::to_string(value);
}

template<class T> Operand<T>::Operand(eOperandType type, std::string str) //: Operand::toString(type), _value(str)
{
	this->_type = type;
	this->_value = str;
	// this->_value = std::to_string(static_cast<T>(std::stod(str)));
}

template<class T> int addOverflow(T x, T y)
{
	T xy = x + y;

	if ((x > 0) && (y > 0) && xy < 0)
		return 2;
	else if ((x < 0) && (y < 0) && xy > 0)
		return 1;
	return 0;
}

template<class T> IOperand const * Operand<T>::operator+(IOperand const & rhs) const
{
	Factory *factory = new Factory();
	eOperandType sum_type = MAX(this->getType(), rhs.getType());
	if (sum_type <= 3)
	{
		int sum = std::stoi(this->toString()) + std::stoi(rhs.toString());
		return factory->createOperand(sum_type, std::to_string(sum));
	} else {
		double sum = std::stod(this->toString()) + std::stod(rhs.toString());
		return factory->createOperand(sum_type, std::to_string(sum));
		//double
	}
	// if (this->getPrecision() < rhs.getPrecision())
	// 	return (rhs + *this);
	// T lval = static_cast<T>(std::stod(this->_value));
	// T rval = static_cast<T>(std::stod(rhs.toString()));
	// if (addOverflow<T>(lval, rval) == 1)
	// 	throw (Operand::UnderflowException());
	// else if (addOverflow<T>(lval, rval) == 2)
	// 	throw (Operand::OverflowException());
	// Factory *factory = new Factory();
	// IOperand const *res = factory->createOperand(this->getType(), std::to_string(static_cast<T>(std::stod(this->_value)) + rval));
	// delete factory;
	// return res;
}

template<class T> IOperand const * Operand<T>::operator-(IOperand const & rhs) const
{
	T lval = static_cast<T>(std::stod(this->_value));
	T rval = static_cast<T>(std::stod(rhs.toString()));
	if (addOverflow<T>(lval, rval * -1) == 1)
		throw (Operand::UnderflowException());
	if (addOverflow<T>(lval, rval * -1) == 2)
		throw (Operand::OverflowException());
	Factory *factory = new Factory();
	IOperand const *res = factory->createOperand(this->getType(), std::to_string(lval - rval));
	delete factory;
	return res;
}

template<class T> int mulOverflow(T x, T y)
{
	T x1;
	T y1;

	if (x < 0)
		x1 = x * -1;
	else
		x1 = x;
	if (y < 0)
		y1 = y * -1;
	else
		y1 = y;
	if (x1 > std::numeric_limits<T>::max() / y1)
	{
		if ((x < 0) && (y < 0))
			return 2;
		else if ((x > 0) && (y > 0))
			return 2;
		else
			return 1;
	}
	return 0;
}

template<class T> IOperand const * Operand<T>::operator*(IOperand const & rhs) const
{
	if (this->getPrecision() < rhs.getPrecision())
		return (rhs * *this);
	T lval = static_cast<T>(std::stod(this->_value));
	T rval = static_cast<T>(std::stod(rhs.toString()));
	if (mulOverflow<T>(lval, rval) == 1)
		throw (Operand::UnderflowException());
	else if (mulOverflow<T>(lval, rval) == 2)
		throw (Operand::OverflowException());
	Factory *factory = new Factory();
	IOperand const *res = factory->createOperand(this->getType(), std::to_string(lval * rval));
	delete factory;
	return res;
}

template<class T> IOperand const * Operand<T>::operator/(IOperand const & rhs) const
{
	double lval = stod(this->toString());
	double rval  = stod(rhs.toString());

	if (rval == 0)
		throw (Operand::DivideByZero());
	
	eOperandType t;

	if (this->getPrecision() < rhs.getPrecision())
		t = rhs.getType();
	else
		t = this->getType();

	Factory *factory = new Factory();
	IOperand const *res = factory->createOperand(t, std::to_string(lval / rval));
	delete factory;
	return res;
}

template<class T> IOperand const * Operand<T>::operator%(IOperand const & rhs) const
{
	long lval = stol(this->toString());
	long rval  = stol(rhs.toString());

	if (rval == 0)
		throw (Operand::DivideByZero());

	eOperandType t;

	if (this->getPrecision() < rhs.getPrecision())
		t = rhs.getType();
	else
		t = this->getType();

	Factory *factory = new Factory();
	IOperand const *res = factory->createOperand(t, std::to_string(lval % rval));
	delete factory;
	return res;
}

template<class T> std::string const & Operand<T>::toString() const
{
	return this->_value;
}

template<> int			Operand<int8_t>::getPrecision() const
{
	return Int8;
}

template<> eOperandType	Operand<int8_t>::getType() const
{
	return Int8;
}

template class Operand<int8_t>;

template<> int			Operand<int16_t>::getPrecision() const
{
	return Int16;
}

template<> eOperandType	Operand<int16_t>::getType() const
{
	return Int16;
}

template class Operand<int16_t>;

template<> int			Operand<int32_t>::getPrecision() const
{
	return Int32;
}

template<> eOperandType	Operand<int32_t>::getType() const
{
	return Int32;
}

template class Operand<int32_t>;

template<> int			Operand<float>::getPrecision() const
{
	return Float;
}

template<> eOperandType	Operand<float>::getType() const
{
	return Float;
}

template class Operand<float>;

template<> int			Operand<double>::getPrecision() const
{
	return Double;
}

template<> eOperandType	Operand<double>::getType() const
{
	return Double;
}

template class Operand<double>;
