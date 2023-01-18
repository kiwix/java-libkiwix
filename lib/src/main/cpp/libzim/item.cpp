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
#include "org_kiwix_libzim_Item.h"

#include <utils.h>

#include <string>

#include <zim/item.h>

#define NATIVE_TYPE zim::Item

JNIEXPORT void JNICALL
Java_org_kiwix_kiwixlib_libzim_Item_dispose(JNIEnv* env, jobject thisObj)
{
  dispose<NATIVE_TYPE>(env, thisObj);
}

#define THIS GET_PTR(NATIVE_TYPE)
#define GETTER(retType, name) GETTER_METHOD(retType, libzim_Item, THIS, name)

GETTER(jstring, getTitle)
GETTER(jstring, getPath)
GETTER(jstring, getMimetype)

METHOD0(jobject, libzim_Item, getData) {
  auto obj = NEW_OBJECT("org/kiwix/libzim/Blob");
  SET_HANDLE(zim::Blob, obj, THIS->getData());
  return obj;
}

GETTER(jlong, getSize)
