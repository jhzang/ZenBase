// Copyright (c) 2012 Junheng Zang. All Rights Reserved.
//
#include <zbase/octetstream.h>

#include <cstdlib>
#include <cstdio>

namespace zbase
{
	const size_t OctetStream::PAGE_SIZE = 256; // 256 Bytes

	OctetStream::OctetStream()
		: m_buffer(NULL), m_capacity(0), m_read_pos(0), m_write_pos(0), m_is_attach_mode(false)
	{
		//reserve(PAGE_SIZE);
	}

	OctetStream::OctetStream(const void *data, size_t n, bool is_attach)
		: m_buffer(NULL), m_capacity(0), m_read_pos(0), m_write_pos(0), m_is_attach_mode(is_attach)
	{
		if (is_attach) {
			Attach(data, n);
		} else {
			Reserve((n + PAGE_SIZE - 1) / PAGE_SIZE * PAGE_SIZE);
			memcpy(m_buffer, data, n);
			m_read_pos = 0;
			m_write_pos = n;
		}
	}

	OctetStream::OctetStream(Octets& data, bool is_attach)
		: m_buffer(NULL), m_capacity(0), m_read_pos(0), m_write_pos(0), m_is_attach_mode(is_attach)
	{
		if (is_attach) {
			Attach(data.GetData(), data.GetSize());
		} else {
			Reserve((data.GetSize() + PAGE_SIZE - 1) / PAGE_SIZE * PAGE_SIZE);
			memcpy(m_buffer, data.GetData(), data.GetSize());
			m_read_pos = 0;
			m_write_pos = data.GetSize();
		}
	}

	OctetStream::~OctetStream()
	{
		if (!m_is_attach_mode) {
			Release();
		}
	}

	OctetStream::OctetStream(const OctetStream& rhs)
		: m_buffer(NULL), m_capacity(0), m_read_pos(0), m_write_pos(0), m_is_attach_mode(false)
	{
		Reserve(rhs.m_capacity);
		memcpy(m_buffer, rhs.m_buffer, rhs.m_capacity);
		m_read_pos = rhs.m_read_pos;
		m_write_pos = rhs.m_write_pos;
	}

	OctetStream& OctetStream::operator = (const OctetStream& rhs)
	{
		// avoid self assignment
		if (this == &rhs) {
			return *this;
		}

		if (m_capacity < rhs.m_capacity) {
			Reserve(rhs.m_capacity);
		} else if (m_capacity > rhs.m_capacity) {
			memset(m_buffer, 0, m_capacity - rhs.m_capacity);
		}
		memcpy(m_buffer, rhs.m_buffer, rhs.m_capacity);
		m_read_pos = rhs.m_read_pos;
		m_write_pos = rhs.m_write_pos;
		m_is_attach_mode = false;
		return *this;
	}

	void OctetStream::Release()
	{
		if (!m_is_attach_mode && NULL != m_buffer) {
			delete[] m_buffer;
			m_buffer = NULL;
			m_capacity = m_read_pos = m_write_pos = 0;
		}
	}

	bool OctetStream::PeekByte(void* data, size_t n)
	{
		assert(m_write_pos >= m_read_pos);

		if (NULL == m_buffer || static_cast<size_t>(m_write_pos - m_read_pos) < n) {
			return false;
		}
		memcpy(data, m_buffer + m_read_pos, n);
		return true;
	}

	void OctetStream::PopByte(void* data, size_t n)
		throw (std::length_error)
	{
		if (!PeekByte(data, n)) {
			throw std::length_error("OctetStream::PopByte");
		}
		m_read_pos += n;
	}

	void OctetStream::PushByte(const void* data, size_t n)
	{
		assert(!m_is_attach_mode);
		assert(m_capacity >= m_write_pos);

		if (static_cast<size_t>(m_capacity - m_write_pos) < n) {
			Reserve(m_capacity + PAGE_SIZE);
		}
		memcpy(m_buffer + m_write_pos, data, n);
		m_write_pos += n;
	}


	void OctetStream::Reserve(size_t n)
	{
		assert(!m_is_attach_mode);

		if (static_cast<size_t>(m_capacity) < n) {
			m_capacity = (n + PAGE_SIZE - 1) / PAGE_SIZE * PAGE_SIZE;
			m_buffer = static_cast<byte_t*>(realloc(m_buffer, m_capacity));
			memset(m_buffer + m_write_pos, 0, m_capacity - m_write_pos);
		}
	}

	void OctetStream::Shrink()
	{
		assert(!m_is_attach_mode);

		if (m_capacity > m_write_pos) {
			m_buffer = static_cast<byte_t*>(realloc(m_buffer, m_write_pos - 1));
		}
	}

	OctetStream& OctetStream::Attach(const void *data, size_t n)
	{
		if (!m_is_attach_mode && NULL != m_buffer) {
			Release();
		}

		m_buffer = static_cast<byte_t*>(const_cast<void*>(data));
		m_capacity = n;
		m_read_pos = 0;
		m_write_pos = n;
		m_is_attach_mode = true;
		return *this;
	}

	void OctetStream::Swap(OctetStream& rhs)
	{
		assert(!m_is_attach_mode);

		byte_t *tmpptr = m_buffer;
		m_buffer = rhs.m_buffer;
		rhs.m_buffer = tmpptr;
		int tmppos = m_capacity;
		m_capacity = rhs.m_capacity;
		rhs.m_capacity = tmppos;
		tmppos = m_read_pos;
		m_read_pos = rhs.m_read_pos;
		rhs.m_read_pos = tmppos;
		tmppos = m_write_pos;
		m_write_pos = rhs.m_write_pos;
		rhs.m_write_pos = tmppos;
	}

	OctetStream& OctetStream::Insert(size_t pos, const void *data, size_t n)
	{
		assert(!m_is_attach_mode);
		assert(m_capacity >= m_write_pos);

		if (m_read_pos + (m_capacity - m_write_pos) < static_cast<int>(n)) {
			Reserve(m_write_pos - m_read_pos + n);
		}
		if (0 == pos) {
			if (static_cast<size_t>(m_read_pos) >= n) {
				m_read_pos -= n;
				memcpy(m_buffer + m_read_pos, data, n);
			} else {
				memmove(m_buffer + n, m_buffer + m_read_pos, m_write_pos - m_read_pos);
				memcpy(m_buffer, data, n);
				m_write_pos = n + (m_write_pos - m_read_pos);
				m_read_pos = 0;
			}
			return *this;
		} else if (pos >= GetSize()) {
			return Write(data, n);
		} else {
			memmove(m_buffer, m_buffer + m_read_pos, pos);
			memmove(m_buffer + pos + n, m_buffer + m_read_pos + pos, m_write_pos - m_read_pos - pos);
			memcpy(m_buffer + pos, data, n);
			m_write_pos = (m_write_pos - m_read_pos) + n;
			m_read_pos = 0;
			return *this;
		}
	}

	void OctetStream::Clear()
	{
		assert(!m_is_attach_mode);

		m_read_pos = m_write_pos = 0;
		memset(m_buffer, 0, m_capacity);
	}

	OctetStream& OctetStream::Ignore(size_t n)
	{
		if (static_cast<size_t>(m_write_pos - m_read_pos) >= n) {
			m_read_pos += n;
		} else {
			m_read_pos = m_write_pos;
		}
		return *this;
	}

	OctetStream& OctetStream::Unget(size_t n)
	{
		if (static_cast<size_t>(m_read_pos) > n) {
			m_read_pos -= n;
		} else {
			m_read_pos = 0;
		}
		return *this;
	}

	std::string OctetStream::Hex() const
	{
		std::stringstream ss;
		char buf[4] = {0};
		for (int i = m_read_pos; i < m_write_pos; ++i) {
			snprintf(buf, 3, "%02X ", *(m_buffer + i));
			ss << buf;
		}
		return ss.str();
	}

	OctetStream& OctetStream::operator << (const Octets& value)
	{
		uint32_t len = value.GetSize();
		PushInteger(len);
		if (len > 0) {
			PushByte(value.GetData(), len);
		}
		return *this;
	}

	OctetStream& OctetStream::operator << (const OctetStream& value)
	{
		uint32_t len = value.GetSize();
		PushInteger(len);
		if (len > 0) {
			PushByte(value.GetData(), len);
		}
		return *this;
	}

	OctetStream& OctetStream::operator << (const std::string& data)
	{
		uint32_t len = data.size();
		PushInteger(len);
		if (len > 0) {
			PushByte(data.c_str(), len);
		}
		return *this;
	}

	OctetStream& OctetStream::operator >> (Octets& value)
	{
		uint32_t len = PopInteger<uint32_t>();
		if (len > 0) {
			byte_t* buf = new byte_t[len];
			try {
				PopByte(buf, len);
			} catch (std::length_error &e) {
				delete [] buf;
				buf = NULL;
				throw;
			}
			value.Append(buf, len);
			delete [] buf;
			buf = NULL;
		}
		return *this;
	}

	OctetStream& OctetStream::operator >> (OctetStream& value)
	{
		uint32_t len = PopInteger<uint32_t>();
		if (len > 0) {
			byte_t* buf = new byte_t[len];
			try {
				PopByte(buf, len);
			} catch (std::length_error &e) {
				delete [] buf;
				buf = NULL;
				throw;
			}
			value.Write(buf, len);
			delete [] buf;
			buf = NULL;
		}
		return *this;
	}

	OctetStream& OctetStream::operator >> (std::string& data)
	{
		uint32_t len = PopInteger<uint32_t>();
		if (len > 0) {
			char* buf = new char[len];
			try {
				PopByte(buf, len);
			} catch (std::length_error &e) {
				delete [] buf;
				buf = NULL;
				throw;
			}
			data.append(buf, len);
			delete[] buf;
			buf = NULL;
		}
		return *this;
	}

	std::ostringstream& operator << (std::ostringstream& oss, const OctetStream& stream)
	{
		oss.write(static_cast<const char*>(stream.GetData()), stream.GetSize());
		return oss;
	}

	std::ostream& operator << (std::ostream& oss, const OctetStream& stream)
	{
		oss.write(static_cast<const char*>(stream.GetData()), stream.GetSize());
		return oss;
	}

} // namespace zbase

