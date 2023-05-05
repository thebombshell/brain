
#ifndef BRAIN_DATA_H
#define BRAIN_DATA_H

#include <memory>
#include <stdexcept>

namespace brain
{
	template<typename T_VALUE_TYPE>
	class Data
	{
	public:

		Data() { }

		Data(const Data& t_other) : m_value{ t_other.m_value } { }

		virtual ~Data() { }

		virtual void Set(const T_VALUE_TYPE& t_new_value) { m_value = t_new_value; }

		virtual const T_VALUE_TYPE& Get() const { return m_value; }

	protected:

		T_VALUE_TYPE m_value{ };
	};

	template<typename T_VALUE_TYPE, template<typename> typename T_DATA_TYPE = Data>
	class DataSet
	{
	public:

		DataSet() { }

		DataSet(size_t t_size) : m_size{ t_size }, m_pData{ std::make_unique<T_DATA_TYPE<T_VALUE_TYPE>>(new T_DATA_TYPE[m_size]) } { }

		DataSet(const DataSet& t_other)
			: m_size{ t_other.m_size }, m_pData{ std::make_unique<T_DATA_TYPE<T_VALUE_TYPE>>(new T_DATA_TYPE[m_size]) }
		{
			std::memcpy(m_pData.get(), t_other.m_pData.get(), sizeof(T_DATA_TYPE) * m_size);
		}

		T_DATA_TYPE<T_VALUE_TYPE>* Get() const
		{
			return m_pData ? m_pData.get() : nullptr;
		}

		T_DATA_TYPE<T_VALUE_TYPE>* Get(size_t t_offset) const
		{
			if (t_offset >= m_size)
				throw std::runtime_error("offset requested is outside of data set range");
			return m_pData ? m_pData.get() + t_offset : nullptr;
		}

	private:

		size_t m_size{ 0 };
		std::unique_ptr<T_DATA_TYPE<T_VALUE_TYPE>[]> m_pData{ nullptr };
	};

	template<typename T_VALUE_TYPE, template<typename> typename T_DATA_TYPE = Data, template<typename, template<typename> typename> typename T_DATA_SET_TYPE = DataSet>
	class DataTable
	{
	public:

		DataTable() { }

		DataTable(size_t t_width, size_t t_height) : m_width{ t_width }, m_height{ t_height }, m_dataSet{ m_width * m_height } { }
		
		DataTable(const DataTable& t_other) : m_width{ t_other.m_width }, m_height{ t_other.m_height }, m_dataSet{ t_other.m_dataSet } { }

		~DataTable() { }

		T_DATA_TYPE<T_VALUE_TYPE>* Get() const { return m_dataSet.Get(); }

		T_DATA_TYPE<T_VALUE_TYPE>* Get(size_t t_x, size_t t_y) const
		{
			if (t_x >= m_width)
				throw std::runtime_error("x is outside of data table range");
			if (t_y >= m_height)
				throw std::runtime_error("y is outside of data tabel range");
			return m_dataSet.Get(t_y * m_width + t_x);
		}

	private:

		size_t m_width{ 0 };
		size_t m_height{ 0 };
		T_DATA_SET_TYPE<T_VALUE_TYPE, T_DATA_TYPE> m_dataSet{ };
	};
}

#endif
