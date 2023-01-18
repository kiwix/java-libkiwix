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
#include "org_kiwix_libzim_SuggestionSearch.h"

#include <utils.h>

#include <string>

#include <zim/suggestion.h>

#define NATIVE_TYPE zim::SuggestionSearch

METHOD0(void, libzim_SuggestionSearch, dispose)
{
  dispose<NATIVE_TYPE>(env, thisObj);
}

#define THIS GET_PTR(NATIVE_TYPE)

METHOD(jobject, libzim_SuggestionSearch, getResults, jint start, jint maxResults) {
  auto results = THIS->getResults(TO_C(start), TO_C(maxResults));
  auto obj = NEW_OBJECT("ork/kiwix/libzim/SuggestionIterator");
  SET_HANDLE(zim::SuggestionIterator, obj, results.begin());

  // We have to set the nativeHandleEnd but no macro ease our work here.
  auto end_ptr = std::make_shared<zim::SuggestionIterator>(results.end());
  setPtr(env, obj, std::move(end_ptr), "nativeHandleEnd");
  return obj;
}

METHOD0(jlong, libzim_SuggestionSearch, getEstimatedMatches) {
  return TO_JNI(THIS->getEstimatedMatches());
}

