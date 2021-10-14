#include <iterator>
#include <typeinfo>
template<typename IterT, typename DistT>
void advance(IterT& iter, DistT d)
{
	if(typeid(typename std::iterator_traits<IterT>::iterator_category) == typeid(std::random_access_iterator_tag)){
		iter+=d;
	}else{
		if(d >= 0){while(d--) ++iter;}
		else{while(d++) --iter;}
	}
}