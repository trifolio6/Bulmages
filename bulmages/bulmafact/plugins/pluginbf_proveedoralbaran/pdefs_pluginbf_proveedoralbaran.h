#ifndef PDEFS_PLUGINBF_PROVEEDORALBARAN_H
#define PDEFS_PLUGINBF_PROVEEDORALBARAN_H


#ifdef WIN32

#ifdef PLUGINBF_PROVEEDORALBARAN
#define PLUGINBF_PROVEEDORALBARAN_EXPORT __declspec(dllexport)
#else
#define PLUGINBF_PROVEEDORALBARAN_EXPORT __declspec(dllimport)
#endif

#else

#define PLUGINBF_PROVEEDORALBARAN_EXPORT

#endif


#endif
