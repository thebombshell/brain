
#ifndef BRAIN_NEURON_H
#define BRAIN_NEURON_H

#include "data.h"
#include <vector>

namespace brain
{
	
	template<typename T_VALUE_TYPE, template<typename> typename T_DATA_TYPE = Data>
	class Node
	{
	public:

		virtual ~Node() { }

		virtual void Update() = 0;

		T_VALUE_TYPE Get() const
		{
			if (!m_pData)
				throw std::runtime_error("node does not reference a data object");
			return m_pData->Get();
		}

	protected:

		Node() { }

		Node(T_DATA_TYPE<T_VALUE_TYPE>* t_pData) : m_pData{ t_pData } { }

		Node(const Node&) { }

		T_DATA_TYPE<T_VALUE_TYPE>* m_pData{ nullptr };
	};

	template<typename T_VALUE_OUT_TYPE>
	class IPullable
	{
	public:

		virtual ~IPullable() { }

		virtual T_VALUE_OUT_TYPE Pull() const = 0;

	protected:

		IPullable() { }
	};

	template<typename T_DATA_IN_TYPE, typename T_VALUE_OUT_TYPE, template<typename> typename T_PULL_TYPE = IPullable>
	class Connection : public T_PULL_TYPE<T_VALUE_OUT_TYPE>
	{
	public:

		virtual ~Connection() { }

	protected:

		Connection() : T_PULL_TYPE<T_VALUE_OUT_TYPE>{ } { }

		Connection(T_DATA_IN_TYPE* t_pInput) : T_PULL_TYPE<T_VALUE_OUT_TYPE>{ }, m_pInput{ t_pInput } { }

		Connection(const Connection& t_other) : T_PULL_TYPE<T_VALUE_OUT_TYPE>{ }, m_pInput{ t_other.m_pInput } { }

		T_DATA_IN_TYPE* m_pInput{ nullptr };
	};

	template<typename T_VALUE_TYPE, template<typename> typename T_DATA_TYPE = Data, template<typename> typename T_PULL_TYPE = IPullable>
	class FeedForwardNode : public Node<T_VALUE_TYPE>
	{
	public:

		virtual ~FeedForwardNode() { }

	protected:

		FeedForwardNode() : Node<T_VALUE_TYPE>{ } { }

		FeedForwardNode(T_DATA_TYPE<T_VALUE_TYPE>* t_pData) : Node<T_VALUE_TYPE>{ t_pData } { }

		FeedForwardNode(const FeedForwardNode& t_other) : Node<T_VALUE_TYPE>{ t_other } { }

		std::vector<T_PULL_TYPE<T_VALUE_TYPE>*> m_inputs{};
	};
}

#endif
