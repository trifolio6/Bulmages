#ifndef PDEFS_PLUGINBF_MINICONTABILIDAD_H
#define PDEFS_PLUGINBF_MINICONTABILIDAD_H


#ifdef WIN32

#ifdef PLUGINBF_MINICONTABILIDAD
#define PLUGINBF_MINICONTABILIDAD_EXPORT __declspec(dllexport)
#else
#define PLUGINBF_MINICONTABILIDAD_EXPORT __declspec(dllimport)
#endif

#else

#define PLUGINBF_MINICONTABILIDAD_EXPORT

#endif


#endif
