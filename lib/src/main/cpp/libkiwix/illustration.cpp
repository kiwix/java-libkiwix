/*
 * Copyright (C) 2020 Matthieu Gautier <mgautier@kymeria.fr>
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
#include "org_kiwix_libkiwix_Book.h"

#include "utils.h"
#include "book.h"
#include <zim/archive.h>

#define NATIVE_TYPE kiwix::Book::Illustration
#define TYPENAME libkiwix_Illustration
#include <macros.h>

METHOD0(void, dispose)
{
  dispose<NATIVE_TYPE>(env, thisObj);
}

METHOD0(jint, width) {
  return TO_JNI(THIS->width);
}

METHOD0(jint, height) {
  return TO_JNI(THIS->width);
}

METHOD0(jstring, mimeType) {
  return TO_JNI(THIS->mimeType);
}

METHOD0(jstring, url) {
  return TO_JNI(THIS->url);
}

GETTER(jstring, getData)
