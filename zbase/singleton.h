// Copyright (c) 2012 Junheng Zang. All Rights Reserved.
//
#ifndef ZBASE__SINGLETON_H
#define ZBASE__SINGLETON_H

#define DECLARE_SINGLETON(T) \
public: \
	static T* Instance(); \
private: \
	static T *s_instance; \
	static boost::mutex s_mutex;

#define IMPLEMENT_SINGLETON(T) \
T* T::s_instance = NULL; \
boost::mutex T::s_mutex; \
T* T::Instance() \
{ \
	if (NULL == s_instance) { \
		boost::lock_guard<boost::mutex> guard(s_mutex); \
		T *tmp_instance = s_instance; \
		if (NULL == tmp_instance) { \
			tmp_instance = new T(); \
			s_instance = tmp_instance; \
		} \
	} \
	return s_instance; \
}

#endif

