// Copyright (c) 2012 Junheng Zang. All Rights Reserved.
//
#include <zbase/octets.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cassert>

namespace zbase
{
	Octets::Rep::Rep(const void* data, size_t size) 
		: m_data(NULL), m_capacity(size*2), m_size(size), m_refno(0)
	{
		if (size > 0) {
			m_data = malloc(m_capacity);
			if (NULL != data) {
				memcpy(m_data, data, size);
			}
			memset(static_cast<char*>(m_data) + size, 0, m_capacity - size);
		}
	}

	Octets::Rep::~Rep()
	{
		if (NULL != m_data) {
			free(m_data);
			m_data = NULL;
		}
	}

	void Octets::Rep::Reserve(size_t size)
	{
		if (m_capacity >= size) return;
		m_capacity = size * 2;
		if (realloc(m_data, m_capacity) == NULL) {
			// fatal error
			exit(EXIT_FAILURE);
		}
		memset(static_cast<char*>(m_data) + m_size, 0, m_capacity - m_size);
	}

	std::string Octets::Rep::Hex()
	{
		std::stringstream ss;
		char buf[3] = {0};
		for (size_t i = 0; i < m_size; ++i) {
			snprintf(buf, 2, "%02X", *(static_cast<char*>(m_data) + i));
			ss << buf;
			if (i + 1 < m_size) {
				ss << " ";
			}
		}
		return ss.str();
	}

	Octets::Octets() : m_rep(NULL)
	{
	}

	Octets::Octets(const void *data, size_t size)
	{
		assert(NULL != data && size > 0);
		m_rep = new Rep(data, size);
	}

	Octets::Octets(const std::string& str)
	{
		if (str.size() > 0) {
			m_rep = new Rep(str.c_str(), str.size());
		} else {
			m_rep = NULL;
		}
	}

	Octets::~Octets()
	{
		if (NULL != m_rep) {
			m_rep->Release();
		}
	}

	Octets::Octets(const Octets& other)
	{
		m_rep = const_cast<Rep*>(other.m_rep);
		if (NULL != m_rep) {
			m_rep->AddRef();
		}
	}

	Octets& Octets::operator = (const Octets& rhs)
	{
		// avoid self assignment
		if (m_rep == rhs.m_rep) {
			return *this;
		}
		if (NULL != m_rep) {
			m_rep->Release();
		}
		m_rep = const_cast<Rep*>(rhs.m_rep);
		if (NULL != m_rep) {
			m_rep->AddRef();
		}
		return *this;
	}

	int Octets::Compare(const Octets& rhs) const
	{
		size_t n = std::min(GetSize(), rhs.GetSize());
		int retcode = memcmp(GetData(), rhs.GetData(), n);
		if (0 == retcode && GetSize() != rhs.GetSize()) {
			retcode = (GetSize() > rhs.GetSize() ? 1 : -1);
		}
		return retcode;
	}

	Octets& Octets::Assign(const void *data, size_t size)
	{
		assert(NULL != data && size > 0);
		if (NULL == m_rep) {
			m_rep = new Rep(data, size);
		} else if (m_rep->IsShared()) {
			m_rep->Release();
			m_rep = new Rep(data, size);
		} else {
			if (m_rep->GetCapacity() < size) {
				m_rep->Reserve(size);
			}
			memcpy(m_rep->GetData(), data, size);
			m_rep->SetSize(size);
		}
		return *this;
	}

	Octets& Octets::Append(const void *data, size_t size)
	{
		assert(NULL != data && size > 0);
		if (NULL == m_rep) {
			m_rep = new Rep(data, size);
		} else {
			if (m_rep->IsShared()) {
				m_rep->Release();
				m_rep = m_rep->Clone();
			}
			if (m_rep->GetCapacity() - m_rep->GetSize() < size) {
				m_rep->Reserve(m_rep->GetSize() + size);
			}
			memcpy(static_cast<char*>(m_rep->GetData()) + m_rep->GetSize(), data, size);
			m_rep->SetSize(m_rep->GetSize() + size);
		}
		return *this;
	}

	Octets& Octets::Append(const Octets& o)
	{
		return Append(o.GetData(), o.GetSize());
	}

	void Octets::Swap(Octets& rhs)
	{
		Rep *p = m_rep;
		m_rep = rhs.m_rep;
		rhs.m_rep = p;
	}

	void Octets::Clear()
	{
		if (NULL != m_rep) {
			if (m_rep->IsShared()) {
				m_rep->Release();
				m_rep = NULL;
			} else {
				memset(m_rep->GetData(), 0, m_rep->GetSize());
				m_rep->SetSize(0);
			}
		}
	}

	Octets operator + (const Octets& a, const Octets& b)
	{
		return Octets(a) += b;
	}

	std::ostringstream& operator << (std::ostringstream& oss, const Octets& data)
	{
		oss.write(static_cast<const char*>(data.GetData()), data.GetSize());
		return oss;
	}

	std::ostream& operator << (std::ostream& oss, const Octets& data)
	{
		return oss.write(static_cast<const char*>(data.GetData()), data.GetSize());
	}

} // namespace zbase

