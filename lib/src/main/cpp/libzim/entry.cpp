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
#include "org_kiwix_libzim_Entry.h"

#include <utils.h>

#include <string>

#include <zim/entry.h>
#include <zim/item.h>

#define NATIVE_TYPE zim::Entry

JNIEXPORT void JNICALL
Java_org_kiwix_kiwixlib_libzim_Entry_dispose(JNIEnv* env, jobject thisObj)
{
  dispose<zim::Entry>(env, thisObj);
}

#define THIS (Handle<zim::Entry>::getHandle(env, thisObj))
#define GETTER(retType, name) JNIEXPORT retType JNICALL \
Java_org_kiwix_libzim_Entry__##name (JNIEnv* env, jobject thisObj) \
{ \
  return TO_JNI(THIS->name()); \
}


GETTER(jboolean, isRedirect)
GETTER(jstring, getTitle)
GETTER(jstring, getPath)
METHOD(jobject, Entry, getItem, jboolean follow) {
  auto item = THIS->getItem(TO_C(follow));
  auto obj = CREATE_WRAPPER("org/kiwix/libzim/Item", item);
  return obj;
}

METHOD0(jobject, Entry, getRedirect) {
  auto item = THIS->getRedirect();
  auto obj = CREATE_WRAPPER("org/kiwix/libzim/Item", item);
  return obj;
}

METHOD0(jobject, Entry, getRedirectEntry) {
  auto entry = THIS->getRedirectEntry();
  auto obj = CREATE_WRAPPER("org/kiwix/libzim/Entry", entry);
  return obj;
}
