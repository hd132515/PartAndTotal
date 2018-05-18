#pragma once

#include <unordered_map>
#include <string>
#include "Primitives.h"

typedef std::unordered_map<std::wstring, Object*> DictType;

class Dictionary
{
public:
	Dictionary();
	~Dictionary();
private:
	DictType dict;
public:
	void write(std::wstring key, bool data);

	void write(std::wstring key, char data);
	void write(std::wstring key, short data);
	void write(std::wstring key, int data);
	void write(std::wstring key, long long data);

	void write(std::wstring key, unsigned char data);
	void write(std::wstring key, unsigned short data);
	void write(std::wstring key, unsigned int data);
	void write(std::wstring key, unsigned long long data);

	void write(std::wstring key, float data);

	void write(std::wstring key, std::wstring data);



	bool get(std::wstring key, bool default_val);

	char get(std::wstring key, char default_val);
	short get(std::wstring key, short default_val);
	int get(std::wstring key, int default_val);
	long long get(std::wstring key, long long default_val);

	unsigned char get(std::wstring key, unsigned char default_val);
	unsigned short get(std::wstring key, unsigned short default_val);
	unsigned int get(std::wstring key, unsigned int default_val);
	unsigned long long get(std::wstring key, unsigned long long default_val);

	float get(std::wstring key, float default_val);

	std::wstring get(std::wstring key, std::wstring default_val);



	DictType* getAll();

	unsigned int get_serializing_length();
	int serialize_all(unsigned char** buffer_pointer);
	int deserialize_all(unsigned char* buffer);
};