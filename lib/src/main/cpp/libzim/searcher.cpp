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

#define CLASSNAME "org/kiwix/libzim/Searcher"
#define NATIVE_TYPE zim::Searcher
#define TYPENAME libzim_Searcher
#include <macros.h>

METHOD(jobject, buildNativeSearcher, jobject archive)
{
  auto cArchive = getPtr<zim::Archive>(env, archive);
  auto searcher = std::make_shared<zim::Searcher>(*cArchive);
  return NEW_RESOURCE(searcher);
}

METHOD(jobject, buildNativeSearcherMulti, jobjectArray archives)
{
  std::vector<zim::Archive> cArchives;
  jsize nbArchives = env->GetArrayLength(archives);
  for(int i=0; i<nbArchives; i++) {
    jobject archive = env->GetObjectArrayElement(archives, i);
    auto cArchive = getPtr<zim::Archive>(env, archive);
    cArchives.push_back(*cArchive);
  }
  auto searcher = std::make_shared<zim::Searcher>(cArchives);
  return NEW_RESOURCE(searcher);
}

METHOD(jobject, addArchive, jobject archive) {
  auto cArchive = getPtr<zim::Archive>(env, archive);
  THIS->addArchive(*cArchive);
  return thisObj;
}

METHOD(jobject, search, jobject query) {
  auto cQuery = getPtr<zim::Query>(env, query);
  return BUILD_WRAPPER(THIS->search(*cQuery));
}

METHOD(void, setVerbose, jboolean verbose) {
  THIS->setVerbose(TO_C(verbose));
}

