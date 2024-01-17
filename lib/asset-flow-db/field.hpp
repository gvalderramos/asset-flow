#pragma once

#include <string>


template <class T>
struct FieldResult {
	const std::string name;
	const T value;
	const bool result;

	FieldResult(const std::string& n, const T& v, const bool& rs) 
		: name(n), value(v), result(rs) {};
};


template <class T>
class Field
{
private:
	T m_value;
	std::string m_fieldName;

public:
	Field(const std::string& fieldName) : m_fieldName(fieldName) {};
	~Field() {};

	inline T get() const { return m_value; };
	inline std::string name() const {return m_fieldName; };
	inline void set(const T& value) { m_value = value; };

	Field& operator=(const T& value){
		m_value = value;
		return *this;
	};
	Field& operator=(const Field& field){
		m_value = field.m_value;
		m_fieldName = field.m_fieldName;
		return *this;
	};

	FieldResult<T> operator==(const T& value) const {
		return FieldResult<T>(m_fieldName, m_value, m_value==value);
	};
	FieldResult<T> operator==(const Field& field) const{
		return FieldResult<T>(m_fieldName, m_value, m_value==field.get()); 
	};

	FieldResult<T> operator!=(const T& value) const {
		return FieldResult<T>(m_fieldName, m_value, m_value!=value);
	};
	FieldResult<T> operator!=(const Field& field) const{
		return FieldResult<T>(m_fieldName, m_value, m_value!=field.get()); 
	};
};

