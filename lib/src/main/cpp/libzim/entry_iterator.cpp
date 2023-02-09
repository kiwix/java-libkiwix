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
#include "org_kiwix_libzim_EntryIterator.h"

#include <utils.h>

#include <string>

#include <zim/entry.h>
#include <zim/search.h>

#define CLASSNAME "org/kiwix/libzim/EntryIterator"
#define TYPENAME libzim_EntryIterator
#include "macros.h"

#define PATH_NATIVE_TYPE zim::Archive::iterator<zim::EntryOrder::pathOrder>
#define TITLE_NATIVE_TYPE zim::Archive::iterator<zim::EntryOrder::titleOrder>
#define EFFICIENT_NATIVE_TYPE zim::Archive::iterator<zim::EntryOrder::efficientOrder>

inline int get_order(JNIEnv* env, jobject thisObj) {
  jclass thisClass = env->GetObjectClass(thisObj);
  jfieldID fieldId = env->GetFieldID(thisClass, "order", "I");
  return TO_C(env->GetIntField(thisObj, fieldId));
}

METHOD0(void, dispose)
{
  // Delete end iterator
  switch (get_order(env, thisObj)) {
    case 0:
       dispose<PATH_NATIVE_TYPE>(env, thisObj, "nativeHandleEnd");
       dispose<PATH_NATIVE_TYPE>(env, thisObj);
       break;
    case 1:
      dispose<TITLE_NATIVE_TYPE>(env, thisObj, "nativeHandleEnd");
      dispose<TITLE_NATIVE_TYPE>(env, thisObj);
      break;
    case 2:
      dispose<EFFICIENT_NATIVE_TYPE>(env, thisObj, "nativeHandleEnd");
      dispose<EFFICIENT_NATIVE_TYPE>(env, thisObj);
      break;
  }
}


METHOD0(jboolean, hasNext) {
  switch (get_order(env, thisObj)) {
    case 0: {
      PATH_NATIVE_TYPE next(*GET_PTR(PATH_NATIVE_TYPE));
      next++;
      auto end = getPtr<PATH_NATIVE_TYPE>(env, thisObj, "nativeHandleEnd");
      return next == *end;
    }
    case 1: {
      TITLE_NATIVE_TYPE next(*GET_PTR(TITLE_NATIVE_TYPE));
      next++;
      auto end = getPtr<TITLE_NATIVE_TYPE>(env, thisObj, "nativeHandleEnd");
      return next == *end;
    }
    case 2: {
      EFFICIENT_NATIVE_TYPE next(*GET_PTR(EFFICIENT_NATIVE_TYPE));
      next++;
      auto end = getPtr<EFFICIENT_NATIVE_TYPE>(env, thisObj, "nativeHandleEnd");
      return next == *end;
    }
    default:
      // unreachable!()
      return false;
  }
}

METHOD0(jobject, next) {
  switch (get_order(env, thisObj)) {
    case 0: {
      (*GET_PTR(PATH_NATIVE_TYPE))++;
      zim::Entry entry = **GET_PTR(PATH_NATIVE_TYPE);
      return BUILD_WRAPPER("org/kiwix/libzim/Entry", entry);
    }
    case 1: {
      (*GET_PTR(TITLE_NATIVE_TYPE))++;
      zim::Entry entry = **GET_PTR(TITLE_NATIVE_TYPE);
      return BUILD_WRAPPER("org/kiwix/libzim/Entry", entry);
    }
    case 2: {
      (*GET_PTR(EFFICIENT_NATIVE_TYPE))++;
      zim::Entry entry = **GET_PTR(EFFICIENT_NATIVE_TYPE);
      return BUILD_WRAPPER("org/kiwix/libzim/Entry", entry);
    }
    default:
      // unreachable!()
      return nullptr;
  }
}

