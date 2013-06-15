#pragma once

#include <iterator>

#include "enumerator.h"

template <typename Iterator>
class from_enumerator : public enumerator<typename std::iterator_traits<Iterator>::reference>
{
private:
	Iterator curr;
	Iterator end;
	
	from_enumerator(from_enumerator const&); // not defined
	from_enumerator& operator=(from_enumerator const&); // not defined

public:
	from_enumerator(from_enumerator&& other)
		: curr(std::move(other.curr))
		, end(std::move(other.end))
	{
	}

	from_enumerator(Iterator const& begin, Iterator const& end)
		: curr(begin)
		, end(end)
	{
	}

	bool move_first()
	{
		return curr != end;
	}
	
	bool move_next()
	{
		++curr;
		return curr != end;
	}
	
	value_type& current()
	{
		return *curr;
	}
};