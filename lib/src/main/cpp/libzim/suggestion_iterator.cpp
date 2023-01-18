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
#include "org_kiwix_libzim_SuggestionIterator.h"

#include <utils.h>

#include <string>

#include <zim/suggestion.h>

#define CLASSNAME "org/kiwix/libzim/SuggestionIterator"
#define NATIVE_TYPE zim::SuggestionIterator
#define TYPENAME libzim_SuggestionIterator
#include <macros.h>


METHOD0(void, dispose)
{
  // Delete end iterator
  dispose<NATIVE_TYPE>(env, thisObj, "nativeHandleEnd");
  dispose<NATIVE_TYPE>(env, thisObj);
}

METHOD0(jboolean, hasNext) {
  NATIVE_TYPE next(*THIS);
  next++;
  auto end = getPtr<NATIVE_TYPE>(env, thisObj, "nativeHandleEnd");
  return next == *end;
}

METHOD0(jobject, next) {
  (*THIS)++;
  zim::SuggestionItem item = **THIS;
  auto obj = NEW_OBJECT("org/kiwix/libzim/SuggestionItem");
  SET_HANDLE(zim::SuggestionItem, obj, item);
  return obj;
}

