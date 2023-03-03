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
#include "org_kiwix_libkiwix_Bookmark.h"

#include "utils.h"
#include "bookmark.h"

#define NATIVE_TYPE kiwix::Bookmark
#define TYPENAME libkiwix_Bookmark
#include "macros.h"

METHOD0(jobject, buildNativeBookmark)
{
  return NEW_RESOURCE(std::make_shared<NATIVE_TYPE>());
}

GETTER(jstring, getBookId)

GETTER(jstring, getBookTitle)

GETTER(jstring, getUrl)

GETTER(jstring, getTitle)

GETTER(jstring, getLanguage)

GETTER(jstring, getDate)

METHOD(void, setBookId, jstring bookId) {
  THIS->setBookId(TO_C(bookId));
}

METHOD(void, setBookTitle, jstring bookTitle) {
  THIS->setBookTitle(TO_C(bookTitle));
}

METHOD(void, setUrl, jstring url) {
  THIS->setUrl(TO_C(url));
}

METHOD(void, setTitle, jstring title) {
  THIS->setTitle(TO_C(title));
}

METHOD(void, setLanguage, jstring lang) {
  THIS->setLanguage(TO_C(lang));
}

METHOD(void, setDate, jstring date) {
  THIS->setDate(TO_C(date));
}
