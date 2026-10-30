#pragma once
#include <stdint.h>
#include <string>

class std_string_PVZ
{
public:
	uint8_t data[0x14];
	unsigned int _Mysize; // 0x14
	unsigned int _Myres; // 0x18

public:
	std_string_PVZ();
	std_string_PVZ(const char* _Ptr);
	//std_string_PVZ(const std::string& str);
	~std_string_PVZ();

	void append(const char* _Ptr, unsigned int _Count);
	void append(const char* _Ptr);
	const char* c_str() const;
};

_NODISCARD bool operator<(
	const std_string_PVZ& _Left, const std_string_PVZ& _Right) noexcept;