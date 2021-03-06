#pragma once

#include "enumerable.h"
#include "captured_enumerator.h"

namespace linq {

template <typename T>
class captured_enumerable : public enumerable<T>
{
public:
	typedef captured_enumerator<T> enumerator_type;
	typedef typename enumerator_type::value_type value_type;

private:
	std::shared_ptr<enumerable<value_type>> source_ptr;

	captured_enumerable(captured_enumerable const&); // not defined
	captured_enumerable& operator=(captured_enumerable const&); // not defined

public:
	captured_enumerable()
		: source_ptr()
	{
	}

	captured_enumerable(captured_enumerable&& other)
		: source_ptr(std::move(other.source_ptr))
	{
	}

	captured_enumerable& operator=(captured_enumerable&& other)
	{
		source_ptr = std::move(other.source_ptr);
		return *this;
	}

	captured_enumerable(std::shared_ptr<enumerable<value_type>> const& source_ptr)
		: source_ptr(source_ptr)
	{
	}
	
	enumerator_type get_enumerator()
	{
		return enumerator_type(std::move(get_enumerator_ptr()));
	}

	std::unique_ptr<enumerator<value_type>> get_enumerator_ptr()
	{
		return source_ptr->get_enumerator_ptr();
	}
};

}