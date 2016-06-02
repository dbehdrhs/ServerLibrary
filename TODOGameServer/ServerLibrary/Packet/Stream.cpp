#include "stdafx.h"
#include "Stream.h"


Stream::Stream()
{
	this->Init();
}

Stream::Stream(UCHAR * data, size_t size)
{
	this->Init();
	memcpy_s(stream_.data(), stream_.size(), data, size);
	offset_ = size;
}

Stream::~Stream()
{
	this->Release();
}

void Stream::Init()
{
}

void Stream::Release()
{
}

void Stream::operator=(Stream & stream)
{
	memcpy_s(stream_.data(), stream_.size(), stream.Data(), stream.Size());
	offset_ = stream.Size();
}

// Write
//------------------------------------------------------------------------------------------
bool Stream::CheckWriteBound(size_t len)
{
	if (offset_ + len > sizeof(stream_))
	{
		cout << "Write socket stream over" << endl;
		return false;
	}
	
	return true;
}

#define WRITE_STREAM(value)			\
{									\
	int size = sizeof(value);		\
	if (!CheckWriteBound(size))		\
		return;						\
									\
	memcpy_s((void*)(stream_.data() + offset_), (stream_.size() - offset_), (const void*)&value, size);	\
	offset_ += size;				\
}	

template<typename T>
void Stream::operator<<(const T & value)
{
	WRITE_STREAM(value);
}

void Stream::operator<<(const bool & value)
{
	WRITE_STREAM(value);
}

void Stream::operator<<(const INT8 & value)
{
	WRITE_STREAM(value);
}

void Stream::operator<<(const INT16 & value)
{
	WRITE_STREAM(value);
}

void Stream::operator<<(const INT32 & value)
{
	WRITE_STREAM(value);
}

void Stream::operator<<(const INT64 & value)
{
	WRITE_STREAM(value);
}

void Stream::operator<<(const UINT8 & value)
{
	WRITE_STREAM(value);
}

void Stream::operator<<(const UINT16 & value)
{
	WRITE_STREAM(value);
}

void Stream::operator<<(const UINT32 & value)
{
	WRITE_STREAM(value);
}

void Stream::operator<<(const UINT64 & value)
{
	WRITE_STREAM(value);
}

// read
//------------------------------------------------------------------------------------------
bool Stream::CheckReadBound(size_t len)
{
	if (readPt_ + len > offset_)
	{
		cout << "Read socket stream over" << endl;
		return false;
	}
	
	return true;
}

#define READ_STREAM(type, value)	\
{									\
	int size = sizeof(type);		\
	if (!CheckReadBound(size))		\
		return;						\
									\
	memcpy_s((void*)&value, size, (stream_.data() + readPt_), size);		\
	readPt_ += size;				\
}

template<typename T>
void Stream::operator>>(T & value)
{
	READ_STREAM(T, value);
}

void Stream::operator>>(bool & value)
{
	READ_STREAM(bool, value);
}

void Stream::operator>>(INT8 & value)
{
	READ_STREAM(INT8, value);
}

void Stream::operator>>(INT16 & value)
{
	READ_STREAM(INT16, value);
}

void Stream::operator>>(INT32 & value)
{
	READ_STREAM(INT32, value);
}

void Stream::operator>>(INT64 & value)
{
	READ_STREAM(INT64, value);
}

void Stream::operator>>(UINT8 & value)
{
	READ_STREAM(UINT8, value);
}

void Stream::operator>>(UINT16 & value)
{
	READ_STREAM(UINT16, value);
}

void Stream::operator>>(UINT32 & value)
{
	READ_STREAM(UINT32, value);
}

void Stream::operator>>(UINT64 & value)
{
	READ_STREAM(UINT64, value);
}

void Stream::operator>>(string & value)
{
	size_t size;
	*this >> size;

	char* buf = new char[size + 1];
	CopyMemory((void*)buf, stream_.data() + readPt_, size * sizeof(CHAR));
	readPt_ += size;

	buf[size] = '\0';
	value = buf;

	SAFE_DELETE(buf);
}