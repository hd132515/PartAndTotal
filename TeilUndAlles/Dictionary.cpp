#include "stdafx.h"
#include "Dictionary.h"
#include <typeinfo>

Dictionary::Dictionary()
{
}

Dictionary::~Dictionary()
{
	for (auto elem : dict)
	{
		delete elem.second;
	}
}

void Dictionary::write(std::wstring key, bool data)
{
	Object* _data = new Boolean(data);
	dict[key] = _data;
}

void Dictionary::write(std::wstring key, char data)
{
	Object* _data = new Int8(data);
	dict[key] = _data;
}

void Dictionary::write(std::wstring key, short data)
{
	Object* _data = new Int16(data);
	dict[key] = _data;
}

void Dictionary::write(std::wstring key, int data)
{
	Object* _data = new Int32(data);
	dict[key] = _data;
}

void Dictionary::write(std::wstring key, long long data)
{
	Object* _data = new Int64(data);
	dict[key] = _data;
}

void Dictionary::write(std::wstring key, unsigned char data)
{
	Object* _data = new UInt8(data);
	dict[key] = _data;
}

void Dictionary::write(std::wstring key, unsigned short data)
{
	Object* _data = new UInt16(data);
	dict[key] = _data;
}

void Dictionary::write(std::wstring key, unsigned int data)
{
	Object* _data = new UInt32(data);
	dict[key] = _data;
}

void Dictionary::write(std::wstring key, unsigned long long data)
{
	Object* _data = new UInt64(data);
	dict[key] = _data;
}

void Dictionary::write(std::wstring key, float data)
{
	Object* _data = new Float(data);
	dict[key] = _data;
}

void Dictionary::write(std::wstring key, std::wstring data)
{
	Object* _data = new String(data);
	dict[key] = _data;
}

bool Dictionary::get(std::wstring key, bool default_val)
{
	if (!dict.count(key))
	{
		return default_val;
	}
	else
	{
		Object* obj = dict[key];
		if (typeid(*obj) == typeid(Boolean))
		{
			return *(Boolean*)obj;
		}
		else
			return default_val;
	}
}

char Dictionary::get(std::wstring key, char default_val)
{
	if (!dict.count(key))
	{
		return default_val;
	}
	else
	{
		Object* obj = dict[key];
		if (typeid(*obj) == typeid(Int8))
		{
			return *(Int8*)obj;
		}
		else
			return default_val;
	}
}

short Dictionary::get(std::wstring key, short default_val)
{
	if (!dict.count(key))
	{
		return default_val;
	}
	else
	{
		Object* obj = dict[key];
		if (typeid(*obj) == typeid(Int16))
		{
			return *(Int16*)obj;
		}
		else
			return default_val;
	}
}

int Dictionary::get(std::wstring key, int default_val)
{
	if (!dict.count(key))
	{
		return default_val;
	}
	else
	{
		Object* obj = dict[key];
		if (typeid(*obj) == typeid(Int32))
		{
			return *(Int32*)obj;
		}
		else
			return default_val;
	}
}

long long Dictionary::get(std::wstring key, long long default_val)
{
	if (!dict.count(key))
	{
		return default_val;
	}
	else
	{
		Object* obj = dict[key];
		if (typeid(*obj) == typeid(Int64))
		{
			return *(Int64*)obj;
		}
		else
			return default_val;
	}
}

unsigned char Dictionary::get(std::wstring key, unsigned char default_val)
{
	if (!dict.count(key))
	{
		return default_val;
	}
	else
	{
		Object* obj = dict[key];
		if (typeid(*obj) == typeid(UInt8))
		{
			return *(UInt8*)obj;
		}
		else
			return default_val;
	}
}

unsigned short Dictionary::get(std::wstring key, unsigned short default_val)
{
	if (!dict.count(key))
	{
		return default_val;
	}
	else
	{
		Object* obj = dict[key];
		if (typeid(*obj) == typeid(UInt16))
		{
			return *(UInt16*)obj;
		}
		else
			return default_val;
	}
}

unsigned int Dictionary::get(std::wstring key, unsigned int default_val)
{
	if (!dict.count(key))
	{
		return default_val;
	}
	else
	{
		Object* obj = dict[key];
		if (typeid(*obj) == typeid(UInt32))
		{
			return *(UInt32*)obj;
		}
		else
			return default_val;
	}
}

unsigned long long Dictionary::get(std::wstring key, unsigned long long default_val)
{
	if (!dict.count(key))
	{
		return default_val;
	}
	else
	{
		Object* obj = dict[key];
		if (typeid(*obj) == typeid(UInt64))
		{
			return *(UInt64*)obj;
		}
		else
			return default_val;
	}
}

float Dictionary::get(std::wstring key, float default_val)
{
	if (!dict.count(key))
	{
		return default_val;
	}
	else
	{
		Object* obj = dict[key];
		if (typeid(*obj) == typeid(Float))
		{
			return *(Float*)obj;
		}
		else
			return default_val;
	}
}

std::wstring Dictionary::get(std::wstring key, std::wstring default_val)
{
	if (!dict.count(key))
	{
		return default_val;
	}
	else
	{
		Object* obj = dict[key];
		if (typeid(*obj) == typeid(String))
		{
			return *(String*)obj;
		}
		else
			return default_val;
	}
}

DictType* Dictionary::getAll()
{
	return &dict;
}

#define DICT_TYPE_SZ_OPERATION_START size_t _typeid = typeid(*keyval.second).hash_code();
#define DICT_TYPE_SZ_OPERATION(t)\
if (_typeid == typeid(t).hash_code())\
{\
	total_len += sizeof(((t*)keyval.second)->data);\
}\

unsigned int Dictionary::get_serializing_length()
{
	unsigned int total_len = 1;

	for (auto keyval : dict)
	{
		total_len += (keyval.first.length()+1); // include delimiter
		total_len += sizeof(size_t);			// data typeid
		DICT_TYPE_SZ_OPERATION_START;

		//data
		DICT_TYPE_SZ_OPERATION(Boolean)
		DICT_TYPE_SZ_OPERATION(Int8)
		DICT_TYPE_SZ_OPERATION(Int16)
		DICT_TYPE_SZ_OPERATION(Int32)
		DICT_TYPE_SZ_OPERATION(Int64)
		DICT_TYPE_SZ_OPERATION(UInt8)
		DICT_TYPE_SZ_OPERATION(UInt16)
		DICT_TYPE_SZ_OPERATION(UInt32)
		DICT_TYPE_SZ_OPERATION(UInt64)
		DICT_TYPE_SZ_OPERATION(Float)
		if (_typeid == typeid(String).hash_code())
		{
			total_len += ((String*)keyval.second)->data.length()*sizeof(wchar_t) + 1;
		}
	}

	return total_len * sizeof(unsigned char) + 1;
}

int Dictionary::serialize_all(unsigned char** buffer_pointer)
{
	if (buffer_pointer == NULL)
		return -1;

	unsigned int total_len = get_serializing_length();
	if (total_len == 0) return -2;

	unsigned char* buffer = new unsigned char[total_len];
	unsigned int pos = 1;
	buffer[0] = '[';

	for (auto keyval : dict)
	{
		//key string
		memcpy(buffer_pointer + pos, keyval.first.c_str(), sizeof(wchar_t) * keyval.first.length());
		pos += sizeof(wchar_t) * keyval.first.length();
		
		//delimiter
		*(buffer_pointer + pos) = 0;
		pos += 1;
			
		//typeid
		size_t _typeid = typeid(*keyval.second).hash_code();
		*(size_t*)(buffer_pointer + pos) = _typeid;
		pos += sizeof(size_t);

		//data
		if (_typeid == typeid(Boolean).hash_code())
		{
			*(bool*)(buffer_pointer + pos) = ((Boolean*)keyval.second)->data;
			pos += sizeof(bool);
		}
		else if (_typeid == typeid(Int8).hash_code())
		{
			*(char*)(buffer_pointer + pos) = ((Int8*)keyval.second)->data;
			pos += sizeof(char);
		}
		else if (_typeid == typeid(Int16).hash_code())
		{
			*(short*)(buffer_pointer + pos) = ((Int16*)keyval.second)->data;
			pos += sizeof(short);
		}
		else if (_typeid == typeid(Int32).hash_code())
		{
			*(int*)(buffer_pointer + pos) = ((Int32*)keyval.second)->data;
			pos += sizeof(int);
		}
		else if (_typeid == typeid(Int64).hash_code())
		{
			*(long long*)(buffer_pointer + pos) = ((Int64*)keyval.second)->data;
			pos += sizeof(long long);
		}
		else if (_typeid == typeid(UInt8).hash_code())
		{
			*(unsigned char*)(buffer_pointer + pos) = ((UInt8*)keyval.second)->data;
			pos += sizeof(unsigned char);
		}
		else if (_typeid == typeid(UInt16).hash_code())
		{
			*(unsigned short*)(buffer_pointer + pos) = ((UInt16*)keyval.second)->data;
			pos += sizeof(unsigned short);
		}
		else if (_typeid == typeid(UInt32).hash_code())
		{
			*(unsigned int*)(buffer_pointer + pos) = ((UInt32*)keyval.second)->data;
			pos += sizeof(unsigned int);
		}
		else if (_typeid == typeid(UInt64).hash_code())
		{
			*(unsigned long long*)(buffer_pointer + pos) = ((UInt64*)keyval.second)->data;
			pos += sizeof(unsigned long long);
		}
		else if (_typeid == typeid(Float).hash_code())
		{
			*(float*)(buffer_pointer + pos) = ((Float*)keyval.second)->data;
			pos += sizeof(float);
		}
		else if (_typeid == typeid(String).hash_code())
		{
			std::wstring str = ((String*)keyval.second)->data;

			//data string
			memcpy(buffer_pointer + pos, str.c_str(), sizeof(wchar_t) * str.length());
			pos += sizeof(wchar_t) * str.length();

			//delimiter
			*(buffer_pointer + pos) = 0;
			pos += 1;
		}
	}

	buffer[pos] = ']';
	*buffer_pointer = buffer;

	return 0;
}