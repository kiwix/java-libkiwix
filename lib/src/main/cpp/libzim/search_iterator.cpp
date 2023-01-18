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
#include "org_kiwix_libzim_SearchIterator.h"

#include <utils.h>

#include <string>

#include <zim/entry.h>
#include <zim/search.h>

#define NATIVE_TYPE zim::SearchIterator

METHOD0(void, libzim_SearchIterator, dispose)
{
  // Delete end iterator
  dispose<NATIVE_TYPE>(env, thisObj, "nativeHandleEnd");
  dispose<NATIVE_TYPE>(env, thisObj);
}

#define THIS GET_PTR(NATIVE_TYPE)
#define GETTER(retType, name) METHOD0(retType, libzim_SearchIterator, name) \
{ \
  return TO_JNI(THIS->name()); \
}

GETTER(jstring, getPath)
GETTER(jstring, getTitle)
GETTER(jint, getScore)
GETTER(jstring, getSnippet)
GETTER(jint, getWordCount)
GETTER(jint, getFileIndex)
GETTER(jint, getSize)

METHOD0(jstring, libzim_SearchIterator, getZimId) {
    return TO_JNI(std::string(THIS->getZimId()));
}

METHOD0(jboolean, libzim_SearchIterator, hasNext) {
  zim::SearchIterator next(*THIS);
  next++;
  auto end = getPtr<NATIVE_TYPE>(env, thisObj, "nativeHandleEnd");
  return next == *end;
}

METHOD0(jobject, libzim_SearchIterator, next) {
  (*THIS)++;
  zim::Entry entry = **THIS;
  auto obj = NEW_OBJECT("org/kiwix/libzim/Entry");
  SET_HANDLE(zim::Entry, obj, entry);
  return obj;
}

