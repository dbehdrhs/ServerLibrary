#pragma once

#define SIZE_64 64
#define SIZE_IO_MAX 1024


typedef TiXmlDocument	xml_t;
typedef TiXmlElement	xmlNode_t;
typedef TiXmlHandle		xmlHandle_t;

#define SAFE_DELETE(data)	\
{							\
	if(data)				\
		delete (data);		\
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