#pragma once

#include <utility>

#include "make_unique.h"
#include "enumerable.h"
#include "concat_traits.h"
#include "concat_enumerator.h"

namespace linq {

template <typename Source>
class concat_enumerable : public enumerable<typename concat_traits<Source>::inner_value_type>
{
public:
	typedef concat_enumerator<typename Source::enumerator_type> enumerator_type;
	typedef typename enumerator_type::value_type value_type;
	
private:
	Source source;

	concat_enumerable(concat_enumerable const&); // not defined
	concat_enumerable& operator=(concat_enumerable const&); // not defined
	
public:
	concat_enumerable(concat_enumerable&& other)
		: source(std::move(other.source))
	{
	}

	concat_enumerable(Source&& source)
		: source(std::move(source))
	{
	}

	enumerator_type get_enumerator()
	{
		enumerator_type e(std::move(source.get_enumerator()));
		return e;
	}

	std::unique_ptr<enumerator<value_type>> get_enumerator_ptr()
	{
		return make_unique<enumerator_type>(std::move(get_enumerator()));
	}
};

}