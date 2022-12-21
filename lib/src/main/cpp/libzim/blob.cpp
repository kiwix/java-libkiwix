/*
 * Copyright (C) 2013 Emmanuel Engelhart <kelson@kiwix.org>
 * Copyright (C) 2017 Matthieu Gautier <mgautier@kymeria.fr>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU  General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */

#include <jni.h>
#include <exception>
#include "org_kiwix_libzim_Blob.h"

#include "utils.h"

#include <string>

#include <zim/blob.h>

JNIEXPORT void JNICALL
Java_org_kiwix_kiwixlib_libzim_Blob_dispose(JNIEnv* env, jobject thisObj)
{
  dispose<zim::Blob>(env, thisObj);
}

#define THIS (Handle<zim::Blob>::getHandle(env, thisObj))
#define GETTER(retType, name) JNIEXPORT retType JNICALL \
Java_org_kiwix_libzim_Blob__##name (JNIEnv* env, jobject thisObj) \
{ \
  return TO_JNI(THIS->name()); \
}

METHOD0(jstring, Blob, getData) {
  return TO_JNI(std::string(**THIS));
}
GETTER(jlong, size)