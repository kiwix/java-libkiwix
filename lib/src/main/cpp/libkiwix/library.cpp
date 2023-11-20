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
METHOD0(void, setNativeHandler)
{
  SET_PTR(NATIVE_TYPE::create());
} CATCH_EXCEPTION()

DISPOSE

/* Kiwix library functions */
METHOD(jboolean, addBook, jobject book)
{
  auto cBook = getPtr<kiwix::Book>(env, book);

  return THIS->addBook(*cBook);
} CATCH_EXCEPTION(false)

METHOD(jobject, getBookById, jstring id) {
  return BUILD_WRAPPER2("org/kiwix/libkiwix/Book", THIS->getBookById(TO_C(id)));
} CATCH_EXCEPTION(nullptr)

METHOD(jobject, getArchiveById, jstring id) {
  auto archive = THIS->getArchiveById(TO_C(id));
  std::cout << "archive is " << archive << std::endl;
  return BUILD_WRAPPER2("org/kiwix/libzim/Archive", archive);
} CATCH_EXCEPTION(nullptr)

METHOD(jboolean, removeBookById, jstring id) {
  return TO_JNI(THIS->removeBookById(TO_C(id)));
} CATCH_EXCEPTION(false)

METHOD(jboolean, writeToFile, jstring path) {
  return TO_JNI(THIS->writeToFile(TO_C(path)));
} CATCH_EXCEPTION(false)

METHOD(jboolean, writeBookmarksToFile, jstring path) {
  return TO_JNI(THIS->writeBookmarksToFile(TO_C(path)));
} CATCH_EXCEPTION(false)

METHOD(jint, getBookCount, jboolean localBooks, jboolean remoteBooks) {
  return TO_JNI(THIS->getBookCount(TO_C(localBooks), TO_C(remoteBooks)));
} CATCH_EXCEPTION(0)

GETTER(jobjectArray, getBooksIds)

METHOD(jobjectArray, filter, jobject filterObj) {
  auto filter = getPtr<kiwix::Filter>(env, filterObj);
  return c2jni(THIS->filter(*filter), env);
} CATCH_EXCEPTION(nullptr)

GETTER(jobjectArray, getBooksLanguages)
GETTER(jobjectArray, getBooksCategories)
GETTER(jobjectArray, getBooksCreators)
GETTER(jobjectArray, getBooksPublishers)

METHOD(void, addBookmark, jobject bookmark) {
  auto cBookmark = getPtr<kiwix::Bookmark>(env, bookmark);
  THIS->addBookmark(*cBookmark);
} CATCH_EXCEPTION()

METHOD(jboolean, removeBookmark, jstring zimId, jstring url) {
  return TO_JNI(THIS->removeBookmark(TO_C(zimId), TO_C(url)));
} CATCH_EXCEPTION(false)

METHOD(jobjectArray, getBookmarks, jboolean onlyValidBookmarks) {
  auto bookmarks = THIS->getBookmarks(TO_C(onlyValidBookmarks));
  jobjectArray retArray = createArray(env, bookmarks.size(), "org/kiwix/libkiwix/Bookmark");
  size_t index = 0;
  jclass wrapperClass = env->FindClass("org/kiwix/libkiwix/Bookmark");
  jmethodID initMethod = env->GetMethodID(wrapperClass, "<init>", "(J)V");

  for (auto bookmark: bookmarks) {
    // This double new is necessary as we need to allocate the bookmark itself (as a shared_ptr) on the heap but
    // we also want the shared_ptr to be stored in the head as we want to have a ptr (cast as long) to it.
    shared_ptr<kiwix::Bookmark>* handle = new shared_ptr<kiwix::Bookmark>(new kiwix::Bookmark(std::move(bookmark)));
    jobject wrapper = env->NewObject(wrapperClass, initMethod, reinterpret_cast<jlong>(handle));
    env->SetObjectArrayElement(retArray, index++, wrapper);
  }
  return retArray;
} CATCH_EXCEPTION(nullptr)
