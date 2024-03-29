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

#define CLASSNAME "org/kiwix/libzim/Item"
#define NATIVE_TYPE zim::Item
#define TYPENAME libzim_Item
#include <macros.h>

DISPOSE

GETTER(jstring, getTitle)
GETTER(jstring, getPath)
GETTER(jstring, getMimetype)

METHOD0(jobject, getData) {
  return BUILD_WRAPPER("org/kiwix/libzim/Blob", THIS->getData());
} CATCH_EXCEPTION(nullptr)

GETTER(jlong, getSize)


METHOD0(jobject, getDirectAccessInformation) {
  jobject directObjInfo = newObject("org/kiwix/libzim/DirectAccessInfo", env);
  setDaiObjValue("", 0, directObjInfo, env);

  auto cDirectObjInfo = THIS->getDirectAccessInformation();
  setDaiObjValue(cDirectObjInfo.first, cDirectObjInfo.second, directObjInfo, env);
  return directObjInfo;
} CATCH_EXCEPTION(nullptr)
