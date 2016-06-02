#pragma once
#include "stdafx.h"

#define RAND(type, maxVal)		(type) RandomMT::Instance().rand(maxVal)

class RandomMT : public Singleton<RandomMT>
{
public:
	uint64_t rand(int maxVal)
	{
		// seed
		std::random_device rd;
		std::mt19937 engine(rd());

		// range
		std::uniform_int_distribution<uint64_t> distribution(0, UINT64_MAX);

		auto generator = bind(distribution, engine);
		
		return (uint64_t)(generator() % maxVal);
	}
};