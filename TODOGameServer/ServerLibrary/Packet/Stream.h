#pragma once

class Stream
{
private:
	size_t offset_;
	size_t readPt_;
	array<UCHAR, SOCKET_BUF_SIZE> stream_;
public:
	Stream();
	Stream(UCHAR* data, size_t size);
	~Stream();

	void Init();
	void Release();

	void operator = (Stream& stream);

	bool CheckWriteBound(size_t len);

	template<typename T>
	void operator << (const T& value);
	void operator << (const bool& value);
	void operator << (const INT8& value);
	void operator << (const INT16& value);
	void operator << (const INT32& value);
	void operator << (const INT64& value);
	void operator << (const UINT8& value);
	void operator << (const UINT16& value);
	void operator << (const UINT32& value);
	void operator << (const UINT64& value);

	bool CheckReadBound(size_t len);

	template<typename T>
	void operator >> (T& value);
	void operator >> (bool& value);
	void operator >> (INT8& value);
	void operator >> (INT16& value);
	void operator >> (INT32& value);
	void operator >> (INT64& value);
	void operator >> (UINT8& value);
	void operator >> (UINT16& value);
	void operator >> (UINT32& value);
	void operator >> (UINT64& value);

	void operator >> (string& value);

public:
	UCHAR* Data() { return stream_.data(); }
	size_t Size() { return offset_; }
};