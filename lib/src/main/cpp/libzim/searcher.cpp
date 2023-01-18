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

#define NATIVE_TYPE zim::Searcher

JNIEXPORT void JNICALL Java_org_kiwix_libzim_Searcher_setNativeSearcher(
    JNIEnv* env, jobject thisObj, jobject archive)
{

  Lock l;
  auto cArchive = getPtr<zim::Archive>(env, archive);
  try {
    auto searcher = std::make_shared<zim::Searcher>(*cArchive);
    SET_PTR(searcher);
  } catch (std::exception& e) {
    LOG("Cannot create searcher");
      LOG("%s", e.what());
  }
}


METHOD0(void, libzim_Searcher, dispose)
{
  dispose<NATIVE_TYPE>(env, thisObj);
}

#define THIS GET_PTR(NATIVE_TYPE)
#define GETTER(retType, name) METHOD0(retType, libzim_Searcher, name) \
{ \
  return TO_JNI(THIS->name()); \
}

METHOD(jobject, libzim_Searcher, addArchive, jobject archive) {
  auto cArchive = getPtr<zim::Archive>(env, archive);
  THIS->addArchive(*cArchive);
  return thisObj;
}

METHOD(jobject, libzim_Searcher, search, jobject query) {
  auto cQuery = getPtr<zim::Query>(env, query);
  auto obj = NEW_OBJECT("org/kiwix/libzim/Search");
  SET_HANDLE(zim::Search, obj, THIS->search(*cQuery));
  return obj;
}

METHOD(void, libzim_Searcher, setVerbose, jboolean verbose) {
  THIS->setVerbose(TO_C(verbose));
}

