#pragma once

#include <string>
#include <type_traits>

class Object
{
public:
	Object() {}
	virtual ~Object() {}
};

template <typename T>
class Primitive : public Object
{
public:
	Primitive<T>(T data) {
		this->data = data;
	}
	virtual ~Primitive<T>() {}
public:
	T data;
public:
	operator T() const {
		return data;
	}
};

#define Boolean Primitive<bool>

#define Int8 Primitive<char>
#define Int16 Primitive<short>
#define Int32 Primitive<int>
#define Int64 Primitive<long long>

#define UInt8 Primitive<unsigned char>
#define UInt16 Primitive<unsigned short>
#define UInt32 Primitive<unsigned int>
#define UInt64 Primitive<unsigned long long>

#define Float Primitive<float>

#define String Primitive<std::wstring>