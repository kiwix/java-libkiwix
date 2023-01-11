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
#include "org_kiwix_libzim_Searcher.h"

#include <utils.h>

#include <string>

#include <zim/search.h>

#define NATIVE_TYPE zim::Query

JNIEXPORT void JNICALL Java_org_kiwix_libzim_Query_getNativeQuery(
    JNIEnv* env, jobject thisObj, jstring query)
{
  auto cQuery = TO_C(query);
  Lock l;
  try {
    auto query = std::make_shared<NATIVE_TYPE>(cQuery);
    SET_PTR(query);
  } catch (std::exception& e) {
    LOG("Cannot create query");
      LOG("%s", e.what());
  }
}


JNIEXPORT void JNICALL
Java_org_kiwix_kiwixlib_libzim_Query_dispose(JNIEnv* env, jobject thisObj)
{
  dispose<NATIVE_TYPE>(env, thisObj);
}

#define THIS GET_PTR(NATIVE_TYPE)

METHOD(jobject, Query, setQuery, jstring query) {
  THIS->setQuery(TO_C(query));
  return thisObj;
}

METHOD(jobject, Query, setGeorange, jfloat latitude, jfloat longitude, jfloat distance) {
  THIS->setGeorange(TO_C(latitude), TO_C(longitude), TO_C(distance));
  return thisObj;
}

