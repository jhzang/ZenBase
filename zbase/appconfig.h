/**
 * @file      appconfig.h
 * @brief     Configuaration file operating utility. Support xml, json, ini.
 * @author    Junheng Zang (junheng.zang@gmail.com)
 * @copyright Copyright (c) 2012 Junheng Zang. All Rights Reserved.
 */
#ifndef ZBASE__APPCONFIG_H
#define ZBASE__APPCONFIG_H

#include <boost/property_tree/ptree.hpp>

/**
 * @namespace zbase
 */
namespace zbase
{
	/**
	 * @class AppConfig
	 * @brief Application configuration reader and writer
	 * @details Support xml, json, ini
	 */
	class AppConfig
	{
	public:
		/**
		 * @enum FILE_FORMAT
		 */
		enum FILE_FORMAT { UNKNOWN, XML, JSON, INI };

	public:
		/**
		 * @brief Load from file
		 * @param [in] filename Input filename
		 * @param [in] format File format @cite FILE_FORMAT
		 * @return true or false
		 */
		bool Load(const std::string &filename, FILE_FORMAT format = UNKNOWN);
		/**
		 * @brief Save to file
		 * @param [in] filename Output filename
		 * @param [in] format File format @cite FILE_FORMAT
		 * @return true or false
		 */
		bool Save(const std::string &filename, FILE_FORMAT format);

		/**
		 * @brief Check if the path exists
		 * @details Path pattern "a.b.c"
		 */
		bool Exist(const char *path) const;
		/**
		 * @brief Check if the attribute of path exists
		 * @details Path pattern "a.b.c"
		 */
		bool Exist(const char *path, const char *attribute_name);

		/**
		 * @brief Get value as the specified type
		 */
		template<typename T>
		T GetValue(const char *path, const T &default_value);

		/**
		 * @brief Put value of the specified type to path
		 */
		template<typename T>
		bool PutValue(const char *path, const T &value);

		/**
		 * @brief Get attribute of path as the specified type
		 */
		template<typename T>
		T GetAttribute(const char *path, const char *attribute_name, const T &default_value);

		/**
		 * @brief Put attribute of path
		 */
		template<typename T>
		bool PutAttribute(const char *path, const char *attribute_name, const T &value);

	protected:
		/**
		 * @brief Load from file in xml format
		 */
		bool LoadXml(const std::string &filename);
		/**
		 * @brief Load from file in json format
		 */
		bool LoadJson(const std::string &filename);
		/**
		 * @brief Load from file in ini format
		 */
		bool LoadIni(const std::string &filename);
		/**
		 * @brief Save to file in xml format
		 */
		bool SaveXml(const std::string &filename);
		/**
		 * @brief Save to file in json format
		 */
		bool SaveJson(const std::string &filename);
		/**
		 * @brief Save to file in ini format
		 */
		bool SaveIni(const std::string &filename);

	private:
		/**
		 * @brief Internal data structure
		 */
		boost::property_tree::ptree m_pt;
	}; // class AppConfig
} // namespace zbase

#include <zbase/detail/appconfig_impl.h>

#endif

