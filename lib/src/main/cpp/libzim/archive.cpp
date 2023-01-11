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
#include "org_kiwix_libzim_Archive.h"

#include <utils.h>

#include <iostream>
#include <string>

#include <zim/archive.h>
#include <zim/item.h>

/* Kiwix Reader JNI functions */
JNIEXPORT void JNICALL Java_org_kiwix_libzim_Archive_setNativeArchive(
    JNIEnv* env, jobject thisObj, jstring filename)
{
  std::string cPath = TO_C(filename);

  LOG("Attempting to create reader with: %s", cPath.c_str());
  Lock l;
  try {
    auto archive = std::make_shared<zim::Archive>(cPath);
    SET_PTR(archive);
  } catch (std::exception& e) {
    LOG("Error opening ZIM file");
      LOG("%s", e.what());
  }
}

namespace
{

int jni2fd(const jobject& fdObj, JNIEnv* env)
{
  jclass class_fdesc = env->FindClass("java/io/FileDescriptor");
  jfieldID field_fd = env->GetFieldID(class_fdesc, "fd", "I");
  if ( field_fd == NULL )
  {
    env->ExceptionClear();
    // Under Android the (private) 'fd' field of java.io.FileDescriptor has been
    // renamed to 'descriptor'. See, for example,
    // https://android.googlesource.com/platform/libcore/+/refs/tags/android-8.1.0_r1/ojluni/src/main/java/java/io/FileDescriptor.java#55
    field_fd = env->GetFieldID(class_fdesc, "descriptor", "I");
  }
  return env->GetIntField(fdObj, field_fd);
}

} // unnamed namespace

JNIEXPORT void JNICALL Java_org_kiwix_libzim_Archive_setNativeArchiveByFD(
    JNIEnv* env, jobject thisObj, jobject fdObj)
{
#ifndef _WIN32
  int fd = jni2fd(fdObj, env);

  LOG("Attempting to create reader with fd: %d", fd);
  Lock l;
  try {
    auto archive = std::make_shared<zim::Archive>(fd);
    SET_PTR(archive);
  } catch (std::exception& e) {
    LOG("Error opening ZIM file");
       LOG("%s", e.what());
  }
#else
  jclass exception = env->FindClass("java/lang/UnsupportedOperationException");
  env->ThrowNew(exception, "org.kiwix.libzim.Archive.setNativeArchiveByFD() is not supported under Windows");
#endif
}

JNIEXPORT void JNICALL Java_org_kiwix_libzim_Archive_setNativeArchiveEmbedded(
    JNIEnv* env, jobject thisObj, jobject fdObj, jlong offset, jlong size)
{
#ifndef _WIN32
  int fd = jni2fd(fdObj, env);

  LOG("Attempting to create reader with fd: %d", fd);
  Lock l;
  try {
    auto archive = std::make_shared<zim::Archive>(fd, offset, size);
    SET_PTR(archive);
  } catch (std::exception& e) {
    LOG("Error opening ZIM file");
       LOG("%s", e.what());
  }
#else
  jclass exception = env->FindClass("java/lang/UnsupportedOperationException");
  env->ThrowNew(exception, "org.kiwix.libzim.Archive.setNativeArchiveEmbedded() is not supported under Windows");
#endif
}

JNIEXPORT void JNICALL
Java_org_kiwix_libzim_Archive_dispose(JNIEnv* env, jobject thisObj)
{
  dispose<zim::Archive>(env, thisObj);
}

#define THIS GET_PTR(zim::Archive)
#define GETTER(retType, name) JNIEXPORT retType JNICALL \
Java_org_kiwix_libzim_Archive_##name (JNIEnv* env, jobject thisObj) \
{ \
  return TO_JNI(THIS->name()); \
}


GETTER(jstring, getFilename)
GETTER(jlong, getFilesize)
GETTER(jint, getAllEntryCount)
GETTER(jint, getEntryCount)
GETTER(jint, getArticleCount)
GETTER(jint, getMediaCount)

METHOD0(jstring, Archive, getUuid) {
  return TO_JNI(std::string(THIS->getUuid()));
}

METHOD(jstring, Archive, getMetadata, jstring name) {
  return TO_JNI(THIS->getMetadata(TO_C(name)));
}

METHOD(jobject, Archive, getMetadataItem, jstring name) {
  auto obj = NEW_OBJECT("org/kiwix/libzim/Item");
  SET_HANDLE(zim::Item, obj, THIS->getMetadataItem(TO_C(name)));
  return obj;
}

GETTER(jobjectArray, getMetadataKeys)

METHOD(jobject, Archive, getIllustrationItem, jint size) {
  auto obj = NEW_OBJECT("org/kiwix/libzim/Item");
  SET_HANDLE(zim::Item, obj, THIS->getIllustrationItem(TO_C(size)));
  return obj;
}

METHOD(jboolean, Archive, hasIllustration, jint size) {
  return TO_JNI(THIS->hasIllustration(TO_C(size)));
}

GETTER(jlongArray, getIllustrationSizes)

METHOD(jobject, Archive, getEntryByPath, jlong index) {
  auto obj = NEW_OBJECT("org/kiwix/libzim/Entry");
  SET_HANDLE(zim::Entry, obj, THIS->getEntryByPath(TO_C(index)));
  return obj;
}

METHOD(jobject, Archive, getEntryByPath, jstring path) {
  auto obj = NEW_OBJECT("org/kiwix/libzim/Entry");
  SET_HANDLE(zim::Entry, obj, THIS->getEntryByPath(TO_C(path)));
  return obj;
}

METHOD(jobject, Archive, getEntryByTitle, jlong index) {
  auto obj = NEW_OBJECT("org/kiwix/libzim/Entry");
  SET_HANDLE(zim::Entry, obj, THIS->getEntryByTitle(TO_C(index)));
  return obj;
}

METHOD(jobject, Archive, getEntryByTitle, jstring title) {
  auto obj = NEW_OBJECT("org/kiwix/libzim/Entry");
  SET_HANDLE(zim::Entry, obj, THIS->getEntryByTitle(TO_C(title)));
  return obj;
}

METHOD(jobject, Archive, getEntryByClusterOrder, jlong index) {
  auto obj = NEW_OBJECT("org/kiwix/libzim/Entry");
  SET_HANDLE(zim::Entry, obj, THIS->getEntryByClusterOrder(TO_C(index)));
  return obj;
}

METHOD0(jobject, Archive, getMainEntry) {
  auto obj = NEW_OBJECT("org/kiwix/libzim/Entry");
  SET_HANDLE(zim::Entry, obj, THIS->getMainEntry());
  return obj;
}

METHOD0(jobject, Archive, getRandomEntry) {
  auto obj = NEW_OBJECT("org/kiwix/libzim/Entry");
  SET_HANDLE(zim::Entry, obj, THIS->getRandomEntry());
  return obj;
}

METHOD(jboolean, Archive, hasEntryByPath, jstring path) {
  return TO_JNI(THIS->hasEntryByPath(TO_C(path)));
}

METHOD(jboolean, Archive, hasEntryByTitle, jstring title) {
  return TO_JNI(THIS->hasEntryByPath(TO_C(title)));
}

GETTER(jboolean, hasMainEntry)

METHOD(jboolean, Archive, hasIllustration, jlong size) {
  return TO_JNI(THIS->hasIllustration(TO_C(size)));
}

GETTER(jboolean, hasFulltextIndex)
GETTER(jboolean, hasTitleIndex)
GETTER(jboolean, hasChecksum)
GETTER(jstring, getChecksum)
GETTER(jboolean, check)

GETTER(jboolean, isMultiPart)
GETTER(jboolean, hasNewNamespaceScheme)



