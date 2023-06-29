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
#include "org_kiwix_libzim_Entry.h"

#include <utils.h>

#include <string>

#include <zim/entry.h>
#include <zim/item.h>

#define CLASSNAME "org/kiwix/libzim/Entry"
#define NATIVE_TYPE zim::Entry
#define TYPENAME libzim_Entry
#include <macros.h>


DISPOSE

GETTER(jboolean, isRedirect)
GETTER(jstring, getTitle)
GETTER(jstring, getPath)
METHOD(jobject, getItem, jboolean follow) {
  return BUILD_WRAPPER("org/kiwix/libzim/Item", THIS->getItem(TO_C(follow)));
} CATCH_EXCEPTION(nullptr)

METHOD0(jobject, getRedirect) {
  return BUILD_WRAPPER("org/kiwix/libzim/Item", THIS->getRedirect());
} CATCH_EXCEPTION(nullptr)

METHOD0(jobject, getRedirectEntry) {
  return BUILD_WRAPPER("org/kiwix/libzim/Entry", THIS->getRedirectEntry());
} CATCH_EXCEPTION(nullptr)
