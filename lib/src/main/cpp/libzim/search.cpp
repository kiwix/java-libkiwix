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
#include "org_kiwix_libzim_Search.h"

#include <utils.h>

#include <string>

#include <zim/search.h>

#define CLASSNAME "org/kiwix/libzim/Search"
#define NATIVE_TYPE zim::Search
#define TYPENAME libzim_Search
#include <macros.h>

METHOD(jobject, getResults, jint start, jint maxResults) {
  auto results = THIS->getResults(TO_C(start), TO_C(maxResults));
  auto beginResource = NEW_RESOURCE(results.begin());
  auto endResource =  NEW_RESOURCE(results.end());

  jclass wrapperClass = env->FindClass("org/kiwix/libzim/SearchIterator");
  jmethodID initMethod = env->GetMethodID(wrapperClass, "<init>", "(org/kiwix/Wrapper/Resource;org/kiwix/Wrapper/Resource)V");
  return env->NewObject(wrapperClass, initMethod, beginResource, endResource);
}

GETTER(jlong, getEstimatedMatches)
