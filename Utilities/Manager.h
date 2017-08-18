#pragma once

#include<map>

namespace Utilities
{
	template<typename X,typename T>
	class Manager
	{
		std::map<X,T> store;
	public:
		T* get( X id )
		{
			std::map<X,T>::iterator iter = store.find(id);
			if(iter != store.end()) return iter->second;
			else return 0;
		}
		void add(X id, T node)
		{
			this->store.insert(std::make_pair(id, node));
		}	
	};
}