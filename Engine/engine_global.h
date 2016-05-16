#ifndef ENGINE_GLOBAL_H
#define ENGINE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(ENGINE_LIBRARY)
#  define ENGINESHARED_EXPORT Q_DECL_EXPORT
#else
#  define ENGINESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // ENGINE_GLOBAL_H
