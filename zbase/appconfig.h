// Copyright (c) 2012 Junheng Zang. All Rights Reserved.
//
// Configuaration file operating utility
// Support xml, json, ini
//
#ifndef ZBASE__APPCONFIG_H
#define ZBASE__APPCONFIG_H

#include <boost/property_tree/ptree.hpp>

namespace zbase
{
	class AppConfig
	{
	public:
		enum FILE_FORMAT { UNKNOWN, XML, JSON, INI };

	public:
		bool Load(const std::string &filename, FILE_FORMAT format = UNKNOWN);
		bool Save(const std::string &filename, FILE_FORMAT format);

		bool Exist(const char *path) const;
		bool Exist(const char *path, const char *attribute_name);

		template<typename T>
		T GetValue(const char *path, const T &default_value);

		template<typename T>
		bool PutValue(const char *path, const T &value);

		template<typename T>
		T GetAttribute(const char *path, const char *attribute_name, const T &default_value);

		template<typename T>
		bool PutAttribute(const char *path, const char *attribute_name, const T &value);

	protected:
		bool LoadXml(const std::string &filename);
		bool LoadJson(const std::string &filename);
		bool LoadIni(const std::string &filename);
		bool SaveXml(const std::string &filename);
		bool SaveJson(const std::string &filename);
		bool SaveIni(const std::string &filename);

	private:
		boost::property_tree::ptree m_pt;
	}; // class AppConfig
} // namespace zbase

#include <zbase/detail/appconfig_impl.h>

#endif

