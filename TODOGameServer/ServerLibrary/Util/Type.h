#pragma once

#define SIZE_8				8
#define SIZE_16				16
#define SIZE_32				32
#define SIZE_64				64
#define SIZE_IO_MAX			1024
#define SOCKET_BUF_SIZE		1024 * 10

//컴파일 기본 메크로 회피용 __FUNCTION__ 같은..
#define __W(x)              L##x
#define _W(x)               __W(x)

#define GET_CURRENT_THREAD_ID		hash<thread::id>()(this_thread::get_id())

typedef TiXmlDocument			xml_t;
typedef TiXmlElement			xmlNode_t;
typedef TiXmlHandle				xmlHandle_t;

typedef std::recursive_mutex	lock_t;
typedef std::thread				thread_t;

#define SAFE_DELETE(data)	\
{							\
	if((data))	delete (data);		\
	(data) = nullptr;		\
}

#define SAFE_DELETE_ARRAY(data)		\
{									\
	if(data)						\
		delete []data;				\
	(data) = nullptr;				\
}

#define SAFE_FREE(data)				\
{									\
	if(data)						\
		free(data);					\
	(data) = nullptr;				\
}

#define SAFE_RELEASE(data)			\
{									\
	if(data)						\
		data->Release();			\
}