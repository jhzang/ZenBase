// Copyright (c) 2012 Junheng Zang. All Rights Reserved.
//
#ifndef ZBASE__DETAIL__APPCONFIG_IMPL_H
#define ZBASE__DETAIL__APPCONFIG_IMPL_H

#include <cstdio>
#include <sstream>

namespace zbase
{
	template<typename T>
	T AppConfig::GetValue(const char *path, const T &default_value)
	{
		return m_pt.get<T>(path, default_value);
	}

	template<typename T>
	bool AppConfig::PutValue(const char *path, const T &value)
	{
		try {
			m_pt.put<T>(path, value);
		} catch (boost::property_tree::ptree_bad_data &e) {
			fprintf(stderr, "%s", e.what());
			return false;
		} catch (...) {
			fprintf(stderr, "Unknown error caught when putting value to %s", path);
			return false;
		}
		return true;
	}

	template<typename T>
	T AppConfig::GetAttribute(const char *path, const char *attribute_name, const T &default_value)
	{
		assert(NULL != path && NULL != attribute_name);
		std::stringstream ss;
		ss << path << "<xmlattr>." << attribute_name;
		return GetValue<T>(ss.str().c_str(), default_value);
	}

	template<typename T>
	bool AppConfig::PutAttribute(const char *path, const char *attribute_name, const T &value)
	{
		assert(NULL != path && NULL != attribute_name);
		std::stringstream ss;
		ss << path << "<xmlattr>." << attribute_name;
		return PutValue<T>(ss.str().c_str(), value);
	}

} // namsepace zbase
#endif

