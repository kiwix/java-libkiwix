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

#define NATIVE_TYPE kiwix::Book
#define TYPENAME libkiwix_Book
#include <macros.h>

METHOD0(void, allocate)
{
  SET_PTR(std::make_shared<NATIVE_TYPE>());
}

DISPOSE

METHOD(void, update__Lorg_kiwix_libkiwix_Book_2, jobject otherBook)
{
  THIS->update(*getPtr<kiwix::Book>(env, otherBook));
}

METHOD(void, update__Lorg_kiwix_libkiwix_JNIKiwixReader_2, jobject archive)
{
  THIS->update(*getPtr<zim::Archive>(env, archive));
}

GETTER(jstring, getId)

GETTER(jstring, getPath)

GETTER(jstring, getHumanReadableIdFromPath)

GETTER(jboolean, isPathValid)

GETTER(jstring, getTitle)

GETTER(jstring, getDescription)

GETTER(jstring, getLanguage)

GETTER(jstring, getCreator)

GETTER(jstring, getPublisher)

GETTER(jstring, getDate)

GETTER(jstring, getUrl)

GETTER(jstring, getName)

GETTER(jstring, getFlavour)

GETTER(jstring, getCategory)

GETTER(jstring, getTags)

METHOD(jstring, getTagStr, jstring tagName) try {
  return TO_JNI(THIS->getTagStr(TO_C(tagName)));
} catch(...) {
  return c2jni<std::string>("", env);
}

GETTER(jlong, getArticleCount)

GETTER(jlong, getMediaCount)

GETTER(jlong, getSize)

METHOD0(jobjectArray, getIllustrations) {
  auto illustrations = THIS->getIllustrations();
  jobjectArray retArray = createArray(env, illustrations.size(), "org/kiwix/libkiwix/Illustration");
  size_t index = 0;
  for (auto illu: illustrations) {
    auto wrapper = BUILD_WRAPPER("org/kiwix/libkiwx/Illustration", illu);
    env->SetObjectArrayElement(retArray, index++, wrapper);
  }
  return retArray;
}

METHOD(jobject, getIllustration, jint size) {
  return BUILD_WRAPPER("org/kiwix/libkiwix/Illustration", THIS->getIllustration(TO_C(size)));
}
