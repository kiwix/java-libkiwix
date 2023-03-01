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

#define CLASSNAME "org/kiwix/libzim/Archive"
#define NATIVE_TYPE zim::Archive
#define TYPENAME libzim_Archive
#include <macros.h>

/* Kiwix Reader JNI functions */
METHOD(jobject, buildNativeArchive, jstring filename)
{
  std::string cPath = TO_C(filename);

  LOG("Attempting to create reader with: %s", cPath.c_str());
  auto archive = std::make_shared<NATIVE_TYPE>(cPath);
  return NEW_RESOURCE(archive);
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

JNIEXPORT jobject JNICALL Java_org_kiwix_libzim_Archive_buildNativeArchiveByFD(
    JNIEnv* env, jobject thisObj, jobject fdObj)
{
#ifndef _WIN32
  int fd = jni2fd(fdObj, env);

  LOG("Attempting to create reader with fd: %d", fd);
  try {
    auto archive = std::make_shared<zim::Archive>(fd);
    return NEW_RESOURCE(archive);
  } CATCH("Error opening ZIM file")
#else
  jclass exception = env->FindClass("java/lang/UnsupportedOperationException");
  env->ThrowNew(exception, "org.kiwix.libzim.Archive.setNativeArchiveByFD() is not supported under Windows");
#endif
  return nullptr;
}

JNIEXPORT jobject JNICALL Java_org_kiwix_libzim_Archive_buildNativeArchiveEmbedded(
    JNIEnv* env, jobject thisObj, jobject fdObj, jlong offset, jlong size)
{
#ifndef _WIN32
  int fd = jni2fd(fdObj, env);

  LOG("Attempting to create reader with fd: %d", fd);
  try {
    auto archive = std::make_shared<zim::Archive>(fd, offset, size);
    return NEW_RESOURCE(archive);
  } CATCH("Error opening ZIM file")
#else
  jclass exception = env->FindClass("java/lang/UnsupportedOperationException");
  env->ThrowNew(exception, "org.kiwix.libzim.Archive.setNativeArchiveEmbedded() is not supported under Windows");
#endif
  return nullptr;
}

GETTER(jstring, getFilename)
GETTER(jlong, getFilesize)
GETTER(jint, getAllEntryCount)
GETTER(jint, getEntryCount)
GETTER(jint, getArticleCount)
GETTER(jint, getMediaCount)

METHOD0(jstring, getUuid) {
  return TO_JNI(std::string(THIS->getUuid()));
}

METHOD(jstring, getMetadata, jstring name) {
  return TO_JNI(THIS->getMetadata(TO_C(name)));
}

METHOD(jobject, getMetadataItem, jstring name) {
  return BUILD_WRAPPER(THIS->getMetadataItem(TO_C(name)));
}

GETTER(jobjectArray, getMetadataKeys)

METHOD(jobject, getIllustrationItem, jint size) {
  return BUILD_WRAPPER(THIS->getIllustrationItem(TO_C(size)));
}

METHOD(jboolean, hasIllustration, jint size) {
  return TO_JNI(THIS->hasIllustration(TO_C(size)));
}

GETTER(jlongArray, getIllustrationSizes)

METHOD(jobject, getEntryByPath__Ljava_lang_String_2, jstring path) {
  return BUILD_WRAPPER(THIS->getEntryByPath(TO_C(path)));
}

METHOD(jobject, getEntryByPath__I, jint index) {
  return BUILD_WRAPPER(THIS->getEntryByPath(TO_C(index)));
}

METHOD(jboolean, hasEntryByPath, jstring path) {
  return TO_JNI(THIS->hasEntryByPath(TO_C(path)));
}

METHOD(jobject, getEntryByTitle__Ljava_lang_String_2, jstring title) {
  return BUILD_WRAPPER(THIS->getEntryByTitle(TO_C(title)));
}

METHOD(jobject, getEntryByTitle__I, jint index) {
  return BUILD_WRAPPER(THIS->getEntryByTitle(TO_C(index)));
}

METHOD(jboolean, hasEntryByTitle, jstring title) {
  return TO_JNI(THIS->hasEntryByPath(TO_C(title)));
}

METHOD(jobject, getEntryByClusterOrder, jint index) {
  return BUILD_WRAPPER(THIS->getEntryByClusterOrder(TO_C(index)));
}

METHOD0(jobject, getMainEntry) {
  return BUILD_WRAPPER(THIS->getMainEntry());
}

GETTER(jboolean, hasMainEntry)

METHOD0(jobject, getRandomEntry) {
  return BUILD_WRAPPER(THIS->getRandomEntry());
}

GETTER(jboolean, hasFulltextIndex)
GETTER(jboolean, hasTitleIndex)
GETTER(jboolean, hasChecksum)
GETTER(jstring, getChecksum)
GETTER(jboolean, check)
GETTER(jboolean, isMultiPart)
GETTER(jboolean, hasNewNamespaceScheme)

#define ITER_BY_PATH 0
#define ITER_BY_TITLE 1
#define ITER_EFFICIENT 2


// No use of the macro BUILD_WRAPPER as `EntryIterator` takes a integer(I) to
// track the order. So the signature of the constructor is not the same.
// The same way, as we are building a iterator, it has two nativeHandle (for begin and end).
METHOD0(jobject, iterByPath) {
  auto range = THIS->iterByPath();
  auto beginIter = NEW_RESOURCE(range.begin());
  auto endIter = NEW_RESOURCE(range.end());

  jclass wrapperClass = env->FindClass("org/kiwix/libzim/EntryIterator");
  jmethodID initMethod = env->GetMethodID(wrapperClass, "<init>", "(org/kiwix/Wrapper/Resource;org/kiwix/Wrapper/Resource)V");
  return env->NewObject(wrapperClass, initMethod, beginIter, endIter);
}

METHOD0(jobject, iterByTitle) {
  auto range = THIS->iterByTitle();
  auto beginIter = NEW_RESOURCE(range.begin());
  auto endIter = NEW_RESOURCE(range.end());

  jclass wrapperClass = env->FindClass("org/kiwix/libzim/EntryIterator");
  jmethodID initMethod = env->GetMethodID(wrapperClass, "<init>", "(org/kiwix/Wrapper/Resource;org/kiwix/Wrapper/Resource)V");
  return env->NewObject(wrapperClass, initMethod, beginIter, endIter);
}

METHOD0(jobject, iterEfficient) {
  auto range = THIS->iterEfficient();
  auto beginIter = NEW_RESOURCE(range.begin());
  auto endIter = NEW_RESOURCE(range.end());

  jclass wrapperClass = env->FindClass("org/kiwix/libzim/EntryIterator");
  jmethodID initMethod = env->GetMethodID(wrapperClass, "<init>", "(org/kiwix/Wrapper/Resource;org/kiwix/Wrapper/Resource)V");
  return env->NewObject(wrapperClass, initMethod, beginIter, endIter);
}

METHOD(jobject, findByPath, jstring path) {
  auto range = THIS->findByPath(TO_C(path));
  auto beginIter = NEW_RESOURCE(range.begin());
  auto endIter = NEW_RESOURCE(range.end());

  jclass wrapperClass = env->FindClass("org/kiwix/libzim/EntryIterator");
  jmethodID initMethod = env->GetMethodID(wrapperClass, "<init>", "(org/kiwix/Wrapper/Resource;org/kiwix/Wrapper/Resource)V");
  return env->NewObject(wrapperClass, initMethod, beginIter, endIter);
}

METHOD(jobject, findByTitle, jstring title) {
  auto range = THIS->findByTitle(TO_C(title));
  auto beginIter = NEW_RESOURCE(range.begin());
  auto endIter = NEW_RESOURCE(range.end());

  jclass wrapperClass = env->FindClass("org/kiwix/libzim/EntryIterator");
  jmethodID initMethod = env->GetMethodID(wrapperClass, "<init>", "(org/kiwix/Wrapper/Resource;org/kiwix/Wrapper/Resource)V");
  return env->NewObject(wrapperClass, initMethod, beginIter, endIter);
}
