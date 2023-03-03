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
#include "org_kiwix_libzim_SuggestionSearcher.h"

#include <utils.h>

#include <string>

#include <zim/suggestion.h>

#define NATIVE_TYPE zim::SuggestionSearcher
#define TYPENAME libzim_SuggestionSearcher
#include <macros.h>


METHOD(jobject, buildNativeSearcher, jobject archive)
{
  auto cArchive = getPtr<zim::Archive>(env, archive);
  auto searcher = std::make_shared<zim::SuggestionSearcher>(*cArchive);
  return NEW_RESOURCE(searcher);
}

METHOD(jobject, suggest, jstring query) {
  //return BUILD_WRAPPER("org/kiwix/libzim/SuggestionSearch", THIS->suggest(TO_C(query)));
  return BUILD_WRAPPER(std::make_shared<zim::SuggestionSearch>(THIS->suggest(TO_C(query))));
}

METHOD(void, setVerbose, jboolean verbose) {
  THIS->setVerbose(TO_C(verbose));
}

