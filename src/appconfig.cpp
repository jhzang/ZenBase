// Copyright (c) 2012 Junheng Zang. All Rights Reserved.
//
#include <zbase/appconfig.h>
#include <sstream>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/foreach.hpp>

namespace zbase
{

	bool AppConfig::LoadXml(const std::string &filename)
	{
		try {
			read_xml(filename, m_pt);
		} catch (boost::property_tree::xml_parser_error &e) {
			fprintf(stderr, "%s", e.what());
			return false;
		} catch (...) {
			fprintf(stderr, "Unknown error when parsing file %s", filename.c_str());
			return false;
		}
		return true;
	}

	bool AppConfig::LoadJson(const std::string &filename)
	{
		try {
			read_json(filename, m_pt);
		} catch (boost::property_tree::json_parser_error &e) {
			fprintf(stderr, "%s", e.what());
			return false;
		} catch (...) {
			fprintf(stderr, "Unknown error when parsing file %s", filename.c_str());
			return false;
		}
		return true;
	}

	bool AppConfig::LoadIni(const std::string &filename)
	{
		try {
			read_ini(filename, m_pt);
		} catch (boost::property_tree::ini_parser_error &e) {
			fprintf(stderr, "%s", e.what());
			return false;
		} catch (...) {
			fprintf(stderr, "Unknown error when parsing file %s", filename.c_str());
			return false;
		}
		return true;

	}

	bool AppConfig::SaveXml(const std::string &filename)
	{
		try {
			write_xml(filename, m_pt, std::locale(), boost::property_tree::xml_writer_make_settings(' ', 2));
		} catch (boost::property_tree::xml_parser_error &e) {
			fprintf(stderr, "%s", e.what());
			return false;
		} catch (...) {
			fprintf(stderr, "Unknown error when writting file %s", filename.c_str());
			return false;
		}
		return true;
	}

	bool AppConfig::SaveJson(const std::string &filename)
	{
		try {
			write_json(filename, m_pt);
		} catch (boost::property_tree::json_parser_error &e) {
			fprintf(stderr, "%s", e.what());
			return false;
		} catch (...) {
			fprintf(stderr, "Unknown error when writting file %s", filename.c_str());
			return false;
		}
		return true;
	}

	bool AppConfig::SaveIni(const std::string &filename)
	{
		try {
			write_ini(filename, m_pt);
		} catch (boost::property_tree::ini_parser_error &e) {
			fprintf(stderr, "%s", e.what());
			return false;
		} catch (...) {
			fprintf(stderr, "Unknown error when writting file %s", filename.c_str());
			return false;
		}
		return true;
	}

	bool AppConfig::Load(const std::string &filename, FILE_FORMAT fmt)
	{
		if (UNKNOWN == fmt) {
			size_t pos = filename.rfind(".");
			if (std::string::npos == pos) {
				return false;
			}
			std::string ext = filename.substr(pos+1, filename.size() - pos - 1);
			if (ext == "xml") {
				fmt = XML;
			} else if (ext == "json") {
				fmt = JSON;
			} else if (ext == "ini") {
				fmt = INI;
			} else {
				return false;
			}
		}
		if (XML == fmt) {
			return LoadXml(filename);
		} else if (JSON == fmt) {
			return LoadJson(filename);
		} else if (INI == fmt) {
			return LoadIni(filename);
		}
		return false;
	}

	bool AppConfig::Save(const std::string &filename, FILE_FORMAT fmt)
	{
		if (XML == fmt) {
			return SaveXml(filename);
		} else if (JSON == fmt) {
			return SaveJson(filename);
		} else if (INI == fmt) {
			return SaveIni(filename);
		}
		return false;
	}

	bool AppConfig::Exist(const char *path) const
	{
		assert(NULL != path);
		boost::optional<const boost::property_tree::ptree&> pt = m_pt.get_child_optional(path);
		return (bool)pt;
	}

	bool AppConfig::Exist(const char *path, const char *attribute_name)
	{
		assert(NULL != path && NULL != attribute_name);
		std::stringstream ss;
		ss << path << "<xmlattr>." << attribute_name;
		boost::optional<std::string> pt = m_pt.get_optional<std::string>(ss.str());
		return (bool)pt;
	}

} // namespace zbase

