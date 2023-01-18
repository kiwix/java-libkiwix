/*
 * Copyright (C) 2019-2020 Matthieu Gautier <mgautier@kymeria.fr>
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
#include "org_kiwix_libkiwix_Library.h"

#include "library.h"
#include "utils.h"

#define NATIVE_TYPE kiwix::Library
#define TYPENAME libkiwix_Library
#include "macros.h"

/* Kiwix Reader JNI functions */
METHOD0(void, allocate)
{
  SET_PTR(std::make_shared<NATIVE_TYPE>());
}

METHOD0(void, dispose)
{
  dispose<NATIVE_TYPE>(env, thisObj);
}

/* Kiwix library functions */
/*JNIEXPORT jboolean JNICALL
Java_org_kiwix_kiwixlib_Library_addBook(
  JNIEnv* env, jobject thisObj, jstring path)
{
  auto cPath = TO_C(path);

  try {
    kiwix::Reader reader(cPath);
    kiwix::Book book;
    book.update(reader);
    return LIBRARY->addBook(book);
  } catch (std::exception& e) {
    LOG("Unable to add the book");
    LOG(e.what()); }
  return false;
}*/

METHOD(jobject, getBookById, jstring id) {
  auto obj = NEW_OBJECT("org/kiwix/libkiwix/Book");
  SET_HANDLE(kiwix::Book, obj, THIS->getBookById(TO_C(id)));
  return obj;
}

METHOD(jint, getBookCount, jboolean localBooks, jboolean remoteBooks) {
  return THIS->getBookCount(localBooks, remoteBooks);
}

GETTER(jobjectArray, getBooksIds)
GETTER(jobjectArray, getBooksLanguages)
GETTER(jobjectArray, getBooksCreators)
GETTER(jobjectArray, getBooksPublishers)

METHOD(jobjectArray, filter, jobject filterObj) {
  auto filter = getPtr<kiwix::Filter>(env, filterObj);
  return c2jni(THIS->filter(*filter), env);
}

