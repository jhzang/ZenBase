// Copyright (c) 2012 Junheng Zang. All Rights Reserved.
//
// Foundamental byte stream implementation
//
#ifndef ZBASE__OCTETSTREAM_H
#define ZBASE__OCTETSTREAM_H

#include <cassert>
#include <stdexcept>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <deque>
#include <set>
#include <map>
#include <cstring>

#include <zbase/inttypes.h>
#include <zbase/octets.h>
#include <zbase/byteorder.h>

namespace zbase
{
	class OctetStream;

	class ISerialize
	{
	public:
		virtual OctetStream* Serialize(OctetStream *stream) const = 0;
		virtual OctetStream* Deserialize(OctetStream *stream) = 0;
	};

	class OctetStream
	{
	public:
		typedef unsigned char byte_t;
		static const size_t PAGE_SIZE;

	public:
		// constructor and destructor
		OctetStream();
		OctetStream(const void *data, size_t n, bool is_attach = false);
		OctetStream(Octets& data, bool is_attach = false);
		virtual ~OctetStream();

		// copy constructor
		OctetStream(const OctetStream& rhs);
		// assignment operator
		OctetStream& operator = (const OctetStream& rhs);

		// member accessors
		bool IsAttachMode() const { return m_is_attach_mode; }
		size_t GetCapacity() const { return m_capacity; }
		size_t GetSize() const { return m_write_pos - m_read_pos; }
		bool IsEmpty() const { return GetSize() == 0; }
		const void* GetData() const { return m_buffer + m_read_pos; }
		const void* begin() const { return m_buffer; }
		const void* end() const { return m_buffer + m_write_pos; }
		const void* GetWriteBuffer() const { return m_buffer + m_write_pos; }
		int GetWriteBufferSize() const { return m_capacity - m_write_pos; }

		// conversions
		operator Octets() { return Octets(m_buffer + m_read_pos, GetSize()); }
		std::string ToString() const { return std::string((char*)(m_buffer + m_read_pos), GetSize()); }
		std::string Hex() const;

		// member modifier
		OctetStream& Attach(const void *data, size_t n);
		void Swap(OctetStream& rhs);
		void Reserve(size_t n);
		void Shrink();
		void Clear();
		OctetStream& Insert(size_t pos, const void *data, size_t n);
		template<typename IntT> OctetStream& InsertInteger(size_t pos, IntT value)
		{
			assert(!m_is_attach_mode);

			value = byteorder::HToLE(value);
			return Insert(pos, &value, sizeof(value));
		}
		OctetStream& Write(const void *data, size_t n) { PushByte(data, n); return *this; }
		OctetStream& Read(void *data, size_t n) { PopByte(data, n); return *this; }
		OctetStream& Ignore(size_t n);
		OctetStream& Unget(size_t n);

		// get pack size
		template<typename IntT> static size_t GetPackSize(IntT value) { return sizeof(value); }

		template<typename IntT> IntT PeekInteger()
		{
			IntT value = 0;
			PeekByte(&value, sizeof(IntT));
			return byteorder::LEToH(value);
		}
		template<typename IntT> IntT PopInteger() throw (std::length_error)
		{
			IntT value = 0;
			PopByte(&value, sizeof(IntT));
			return byteorder::LEToH(value);
		}
		template<typename IntT> void PushInteger(IntT value)
		{
			assert(!m_is_attach_mode);

			value = byteorder::HToLE(value);
			PushByte(&value, sizeof(value));
		}

		//
		// insertion operator
		//
		OctetStream& operator << (bool value)             { char tmp = (value ? 1 : 0); PushByte(&tmp, sizeof(tmp)); return *this; }
		OctetStream& operator << (int8_t value)           { PushByte(&value, sizeof(value)); return *this; }
		OctetStream& operator << (uint8_t value)          { PushByte(&value, sizeof(value)); return *this; }
		OctetStream& operator << (int16_t value)          { PushInteger<int16_t>(value); return *this; }
		OctetStream& operator << (uint16_t value)         { PushInteger<uint16_t>(value); return *this; }
		OctetStream& operator << (int32_t value)          { PushInteger<int32_t>(value); return *this; }
		OctetStream& operator << (uint32_t value)         { PushInteger<uint32_t>(value); return *this; }
		OctetStream& operator << (int64_t value)          { PushInteger<int64_t>(value); return *this; }
		OctetStream& operator << (uint64_t value)         { PushInteger<uint64_t>(value); return *this; }
		OctetStream& operator << (float value)            { PushByte(&value, sizeof(value)); return *this; }
		OctetStream& operator << (double value)           { PushByte(&value, sizeof(value)); return *this; }
		OctetStream& operator << (long double value)      { PushByte(&value, sizeof(value)); return *this; }
		OctetStream& operator << (const ISerialize &data) { assert(!m_is_attach_mode); return *data.Serialize(const_cast<OctetStream*>(this)); }
		OctetStream& operator << (const Octets& value);
		OctetStream& operator << (const OctetStream& value);
		OctetStream& operator << (const std::string& data);
		template <typename T> OctetStream& operator << (const std::vector<T> &data);
		template <typename T> OctetStream& operator << (const std::list<T> &data);
		template <typename T> OctetStream& operator << (const std::deque<T> &data);
		template <typename T> OctetStream& operator << (const std::set<T> &data);
		template <typename T> OctetStream& operator << (const std::multiset<T> &data);
		template <typename T1, typename T2> OctetStream& operator << (const std::pair<T1, T2> &data);
		template <typename T1, typename T2> OctetStream& operator << (const std::pair<const T1, T2> &data);
		template <typename KeyType, typename ValueType> OctetStream& operator << (const std::map<KeyType, ValueType> &data);
		template <typename KeyType, typename ValueType> OctetStream& operator << (const std::multimap<KeyType, ValueType> &data);

		//
		// extraction operator
		//
		OctetStream& operator >> (bool &value)        { char tmp; PopByte(&tmp, sizeof(tmp)); value = tmp ? true : false; return *this; }
		OctetStream& operator >> (int8_t& value)      { PopByte(&value, sizeof(value)); return *this; }
		OctetStream& operator >> (uint8_t& value)     { PopByte(&value, sizeof(value)); return *this; }
		OctetStream& operator >> (int16_t& value)     { value = PopInteger<int16_t>(); return *this; }
		OctetStream& operator >> (uint16_t& value)    { value = PopInteger<uint16_t>(); return *this; }
		OctetStream& operator >> (int32_t& value)     { value = PopInteger<int32_t>(); return *this; }
		OctetStream& operator >> (uint32_t& value)    { value = PopInteger<uint32_t>(); return *this; }
		OctetStream& operator >> (int64_t& value)     { value = PopInteger<int64_t>(); return *this; }
		OctetStream& operator >> (uint64_t& value)    { value = PopInteger<uint64_t>(); return *this; }
		OctetStream& operator >> (float& value)       { PopByte(&value, sizeof(value)); return *this; }
		OctetStream& operator >> (double& value)      { PopByte(&value, sizeof(value)); return *this; }
		OctetStream& operator >> (long double& value) { PopByte(&value, sizeof(value)); return *this; }
		OctetStream& operator >> (ISerialize &data)   { return *data.Deserialize(this); }
		OctetStream& operator >> (Octets& value);
		OctetStream& operator >> (OctetStream& value);
		OctetStream& operator >> (std::string& data);
		template <typename T> OctetStream& operator >> (std::vector<T> &data);
		template <typename T> OctetStream& operator >> (std::list<T> &data);
		template <typename T> OctetStream& operator >> (std::deque<T> &data);
		template <typename T> OctetStream& operator >> (std::set<T> &data);
		template <typename T> OctetStream& operator >> (std::multiset<T> &data);
		template <typename T1, typename T2> OctetStream& operator >> (std::pair<T1, T2> &data);
		template <typename T1, typename T2> OctetStream& operator >> (std::pair<const T1, T2> &data);
		template <typename KeyType, typename ValueType> OctetStream& operator >> (std::map<KeyType, ValueType> &data);
		template <typename KeyType, typename ValueType> OctetStream& operator >> (std::multimap<KeyType, ValueType> &data);

	protected:
		void Release();

		bool PeekByte(void* data, size_t n);
		void PopByte(void* data, size_t n) throw (std::length_error);
		void PushByte(const void* data, size_t n);

	private:
		byte_t *m_buffer;   // begin of the buffer
		int m_capacity;
		int m_read_pos;
		int m_write_pos;

		// Attach mode is a special mode optimized for readonly scenarios, such as data parsing, 
		// to avoid memory duplication. In attach mode, the memory must be guaranteed to be available 
		// in the life period of the OctetStream object and released externally when appropriate.
		bool m_is_attach_mode;
	}; // class OctetStream

	std::ostringstream& operator << (std::ostringstream& oss, const OctetStream& ipStream);
	std::ostream& operator << (std::ostream& oss, const OctetStream& ipStream);

	//
	// STL Container Serialize/Deserialize implementation
	//
	template <typename Container>
	class STLContainer1_Serializer : public ISerialize
	{
	public:
		explicit STLContainer1_Serializer(const Container *container) : m_container(*const_cast<Container*>(container)) {}

		virtual OctetStream* Serialize(OctetStream *stream) const
		{
			if (m_container.size() > 0) {
				*stream << (uint32_t)m_container.size();
				for (typename Container::const_iterator it = m_container.begin(); it != m_container.end(); ++it) {
					*stream << *it;
				}
			}
			return stream;
		}

		virtual OctetStream* Deserialize(OctetStream *stream)
		{
			uint32_t count = stream->PeekInteger<uint32_t>();
			if (count > 0) {
				stream->PopInteger<uint32_t>();
				for (size_t i = 0; i < count && !stream->IsEmpty(); ++i) {
					typename Container::value_type value;
					*stream >> value;
					m_container.insert(m_container.end(), value);
				}
			}
			return stream;
		}

	private:
		Container &m_container;
	};

	template <typename T>
	OctetStream& OctetStream::operator << (const std::vector<T> &data)
	{
		assert(!m_is_attach_mode);
		return *this << STLContainer1_Serializer<std::vector<T> >(&data);
	}

	template <typename T>
	OctetStream& OctetStream::operator << (const std::list<T> &data)
	{
		assert(!m_is_attach_mode);
		return *this << STLContainer1_Serializer<std::list<T> >(&data);
	}

	template <typename T>
	OctetStream& OctetStream::operator << (const std::deque<T> &data)
	{
		assert(!m_is_attach_mode);
		return *this << STLContainer1_Serializer<std::deque<T> >(&data);
	}

	template <typename T>
	OctetStream& OctetStream::operator << (const std::set<T> &data)
	{
		assert(!m_is_attach_mode);
		return *this << STLContainer1_Serializer<std::set<T> >(&data);
	}

	template <typename T>
	OctetStream& OctetStream::operator << (const std::multiset<T> &data)
	{
		assert(!m_is_attach_mode);
		return *this << STLContainer1_Serializer<std::multiset<T> >(&data);
	}

	template <typename T1, typename T2>
	OctetStream& OctetStream::operator << (const std::pair<T1, T2> &data)
	{
		assert(!m_is_attach_mode);
		return *this << data.first << data.second;
	}

	template <typename T1, typename T2>
	OctetStream& OctetStream::operator << (const std::pair<const T1, T2> &data)
	{
		assert(!m_is_attach_mode);
		return *this << data.first << data.second;
	}

	template <typename KeyType, typename T>
	OctetStream& OctetStream::operator << (const std::map<KeyType, T> &data)
	{
		assert(!m_is_attach_mode);
		return *this << STLContainer1_Serializer<std::map<KeyType, T> >(&data);
	}

	template <typename KeyType, typename T>
	OctetStream& OctetStream::operator << (const std::multimap<KeyType, T> &data)
	{
		assert(!m_is_attach_mode);
		return *this << STLContainer1_Serializer<std::multimap<KeyType, T> >(&data);
	}


	template <typename T>
	OctetStream& OctetStream::operator >> (std::vector<T> &data)
	{
		STLContainer1_Serializer<std::vector<T> > holder(&data);
		return *this >> holder;
	}

	template <typename T> 
	OctetStream& OctetStream::operator >> (std::list<T> &data)
	{
		STLContainer1_Serializer<std::list<T> > holder(&data);
		return *this >> holder;
	}

	template <typename T>
	OctetStream& OctetStream::operator >> (std::deque<T> &data)
	{
		STLContainer1_Serializer<std::deque<T> > holder(&data);
		return *this >> holder;
	}

	template <typename T>
	OctetStream& OctetStream::operator >> (std::set<T> &data)
	{
		STLContainer1_Serializer<std::set<T> > holder(&data);
		return *this >> holder;
	}

	template <typename T>
	OctetStream& OctetStream::operator >> (std::multiset<T> &data)
	{
		STLContainer1_Serializer<std::multiset<T> > holder(&data);
		return *this >> holder;
	}

	template <typename T1, typename T2>
	OctetStream& OctetStream::operator >> (std::pair<T1, T2> &data)
	{
		return *this >> data.first >> data.second;
	}

	template <typename T1, typename T2>
	OctetStream& OctetStream::operator >> (std::pair<const T1, T2> &data)
	{
		T1 *key = const_cast<T1*>(&data.first);
		return *this >> *key >> data.second;
	}

	template <typename KeyType, typename T> 
	OctetStream& OctetStream::operator >> (std::map<KeyType, T> &data)
	{
		STLContainer1_Serializer<std::map<KeyType, T> > holder(&data);
		return *this >> holder;
	}

	template <typename KeyType, typename T>
	OctetStream& OctetStream::operator >> (std::multimap<KeyType, T> &data)
	{
		STLContainer1_Serializer<std::multimap<KeyType, T> > holder(&data);
		return *this >> holder;
	}

} // namespace zbase
#endif // ZBASE__OCTETSTREAM_H

