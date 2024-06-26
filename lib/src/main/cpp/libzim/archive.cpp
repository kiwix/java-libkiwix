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
METHOD(void, setNativeArchive, jstring filename)
{
  std::string cPath = TO_C(filename);

  auto archive = std::make_shared<zim::Archive>(cPath);
  SET_PTR(archive);
} CATCH_EXCEPTION()

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

zim::FdInput jni2fdInput(const jobject& fdInputObj, JNIEnv* env)
{
  jclass class_fdesc = env->FindClass("org/kiwix/libzim/FdInput");

  jfieldID field_id = env->GetFieldID(class_fdesc, "fd", "Ljava/io/FileDescriptor;");
  jobject fdObj = env->GetObjectField(fdInputObj, field_id);
  int fd = jni2fd(fdObj, env);

  field_id = env->GetFieldID(class_fdesc, "offset", "J");
  long offset = env->GetLongField(fdInputObj, field_id);

  field_id = env->GetFieldID(class_fdesc, "size", "J");
  long size = env->GetLongField(fdInputObj, field_id);

  return zim::FdInput(fd, offset, size);
}

} // unnamed namespace

JNIEXPORT void JNICALL Java_org_kiwix_libzim_Archive_setNativeArchiveByFD(
    JNIEnv* env, jobject thisObj, jobject fdObj) try
{
#ifndef _WIN32
  int fd = jni2fd(fdObj, env);

  LOG("Attempting to create reader with fd: %d", fd);
  auto archive = std::make_shared<zim::Archive>(fd);
  SET_PTR(archive);
#else
  jclass exception = env->FindClass("java/lang/UnsupportedOperationException");
  env->ThrowNew(exception, "org.kiwix.libzim.Archive.setNativeArchiveByFD() is not supported under Windows");
#endif
} CATCH_EXCEPTION()

JNIEXPORT void JNICALL Java_org_kiwix_libzim_Archive_setNativeArchiveEmbedded(
    JNIEnv* env, jobject thisObj, jobject fdObj, jlong offset, jlong size) try
{
#ifndef _WIN32
  int fd = jni2fd(fdObj, env);

  LOG("Attempting to create reader with fd: %d", fd);
  auto archive = std::make_shared<zim::Archive>(fd, offset, size);
  SET_PTR(archive);
#else
  jclass exception = env->FindClass("java/lang/UnsupportedOperationException");
  env->ThrowNew(exception, "org.kiwix.libzim.Archive.setNativeArchiveEmbedded() is not supported under Windows");
#endif
} CATCH_EXCEPTION()

JNIEXPORT void JNICALL Java_org_kiwix_libzim_Archive_setNativeArchiveEmbeddedFd(
    JNIEnv* env, jobject thisObj, jobject fdObj) try
{
#ifndef _WIN32
  auto fdInput = jni2fdInput(fdObj, env);

  auto archive = std::make_shared<zim::Archive>(fdInput);
  SET_PTR(archive);
#else
  jclass exception = env->FindClass("java/lang/UnsupportedOperationException");
  env->ThrowNew(exception, "org.kiwix.libzim.Archive.setNativeArchiveEmbedded() is not supported under Windows");
#endif
} CATCH_EXCEPTION()


JNIEXPORT void JNICALL Java_org_kiwix_libzim_Archive_setNativeArchiveEmbeddedFds(
    JNIEnv* env, jobject thisObj, jobjectArray fdsObj) try
{
#ifndef _WIN32

  jsize length = env->GetArrayLength(fdsObj);
  std::vector<zim::FdInput> v;

  int i;
  for(i = 0; i<length; i++) {
    jobject fdObj = env->GetObjectArrayElement(fdsObj, i);
    auto fdInput = jni2fdInput(fdObj, env);
    v.push_back(fdInput);
  }

  auto archive = std::make_shared<zim::Archive>(v);
  SET_PTR(archive);
#else
  jclass exception = env->FindClass("java/lang/UnsupportedOperationException");
  env->ThrowNew(exception, "org.kiwix.libzim.Archive.setNativeArchiveEmbedded() is not supported under Windows");
#endif
} CATCH_EXCEPTION()

DISPOSE

GETTER(jstring, getFilename)
GETTER(jlong, getFilesize)
GETTER(jint, getAllEntryCount)
GETTER(jint, getEntryCount)
GETTER(jint, getArticleCount)
GETTER(jint, getMediaCount)

METHOD0(jstring, getUuid) {
  return TO_JNI(std::string(THIS->getUuid()));
} CATCH_EXCEPTION(nullptr)

METHOD(jstring, getMetadata, jstring name) {
  return TO_JNI(THIS->getMetadata(TO_C(name)));
} CATCH_EXCEPTION(nullptr)

METHOD(jobject, getMetadataItem, jstring name) {
  return BUILD_WRAPPER("org/kiwix/libzim/Item", THIS->getMetadataItem(TO_C(name)));
} CATCH_EXCEPTION(nullptr)

GETTER(jobjectArray, getMetadataKeys)

METHOD(jobject, getIllustrationItem, jint size) {
  return BUILD_WRAPPER("org/kiwix/libzim/Item", THIS->getIllustrationItem(TO_C(size)));
} CATCH_EXCEPTION(nullptr)

METHOD(jboolean, hasIllustration, jint size) {
  return TO_JNI(THIS->hasIllustration(TO_C(size)));
} CATCH_EXCEPTION(false)

GETTER(jlongArray, getIllustrationSizes)

METHOD(jobject, getEntryByPath__Ljava_lang_String_2, jstring path) {
  return BUILD_WRAPPER("org/kiwix/libzim/Entry", THIS->getEntryByPath(TO_C(path)));
} CATCH_EXCEPTION(nullptr)

METHOD(jobject, getEntryByPath__I, jint index) {
  return BUILD_WRAPPER("org/kiwix/libzim/Entry", THIS->getEntryByPath(TO_C(index)));
} CATCH_EXCEPTION(nullptr)

METHOD(jboolean, hasEntryByPath, jstring path) {
  return TO_JNI(THIS->hasEntryByPath(TO_C(path)));
} CATCH_EXCEPTION(false)

METHOD(jobject, getEntryByTitle__Ljava_lang_String_2, jstring title) {
  return BUILD_WRAPPER("org/kiwix/libzim/Entry", THIS->getEntryByTitle(TO_C(title)));
} CATCH_EXCEPTION(nullptr)

METHOD(jobject, getEntryByTitle__I, jint index) {
  return BUILD_WRAPPER("org/kiwix/libzim/Entry", THIS->getEntryByTitle(TO_C(index)));
} CATCH_EXCEPTION(nullptr)

METHOD(jboolean, hasEntryByTitle, jstring title) {
  return TO_JNI(THIS->hasEntryByTitle(TO_C(title)));
} CATCH_EXCEPTION(false)

METHOD(jobject, getEntryByClusterOrder, jint index) {
  return BUILD_WRAPPER("org/kiwix/libzim/Entry", THIS->getEntryByClusterOrder(TO_C(index)));
} CATCH_EXCEPTION(nullptr)

METHOD0(jobject, getMainEntry) {
  return BUILD_WRAPPER("org/kiwix/libzim/Entry", THIS->getMainEntry());
} CATCH_EXCEPTION(nullptr)

GETTER(jboolean, hasMainEntry)

METHOD0(jobject, getRandomEntry) {
  return BUILD_WRAPPER("org/kiwix/libzim/Entry", THIS->getRandomEntry());
} CATCH_EXCEPTION(nullptr)

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
METHOD0(jobject, iterByPath) {
  auto range = THIS->iterByPath();
  jclass objClass = env->FindClass("org/kiwix/libzim/EntryIterator");
  jmethodID initMethod = env->GetMethodID(objClass, "<init>", "(I)V");
  jobject obj = env->NewObject(objClass, initMethod, ITER_BY_PATH);
  SET_HANDLE(zim::Archive::iterator<zim::EntryOrder::pathOrder>, obj, range.begin());

  auto end_ptr = std::make_shared<zim::Archive::iterator<zim::EntryOrder::pathOrder>>(range.end());
  setPtr(env, obj, std::move(end_ptr), "nativeHandleEnd");
  return obj;
} CATCH_EXCEPTION(nullptr)

METHOD0(jobject, iterByTitle) {
  auto range = THIS->iterByTitle();
  jclass objClass = env->FindClass("org/kiwix/libzim/EntryIterator");
  jmethodID initMethod = env->GetMethodID(objClass, "<init>", "(I)V");
  jobject obj = env->NewObject(objClass, initMethod, ITER_BY_TITLE);
  SET_HANDLE(zim::Archive::iterator<zim::EntryOrder::titleOrder>, obj, range.begin());

  auto end_ptr = std::make_shared<zim::Archive::iterator<zim::EntryOrder::titleOrder>>(range.end());
  setPtr(env, obj, std::move(end_ptr), "nativeHandleEnd");
  return obj;
} CATCH_EXCEPTION(nullptr)

METHOD0(jobject, iterEfficient) {
  auto range = THIS->iterEfficient();
  jclass objClass = env->FindClass("org/kiwix/libzim/EntryIterator");
  jmethodID initMethod = env->GetMethodID(objClass, "<init>", "(I)V");
  jobject obj = env->NewObject(objClass, initMethod, ITER_EFFICIENT);
  SET_HANDLE(zim::Archive::iterator<zim::EntryOrder::efficientOrder>, obj, range.begin());

  auto end_ptr = std::make_shared<zim::Archive::iterator<zim::EntryOrder::efficientOrder>>(range.end());
  setPtr(env, obj, std::move(end_ptr), "nativeHandleEnd");
  return obj;
} CATCH_EXCEPTION(nullptr)

METHOD(jobject, findByPath, jstring path) {
  auto range = THIS->findByPath(TO_C(path));
  jclass objClass = env->FindClass("org/kiwix/libzim/EntryIterator");
  jmethodID initMethod = env->GetMethodID(objClass, "<init>", "(I)V");
  jobject obj = env->NewObject(objClass, initMethod, ITER_BY_PATH);
  SET_HANDLE(zim::Archive::iterator<zim::EntryOrder::pathOrder>, obj, range.begin());

  auto end_ptr = std::make_shared<zim::Archive::iterator<zim::EntryOrder::pathOrder>>(range.end());
  setPtr(env, obj, std::move(end_ptr), "nativeHandleEnd");
  return obj;
} CATCH_EXCEPTION(nullptr)

METHOD(jobject, findByTitle, jstring title) {
  auto range = THIS->findByTitle(TO_C(title));
  jclass objClass = env->FindClass("org/kiwix/libzim/EntryIterator");
  jmethodID initMethod = env->GetMethodID(objClass, "<init>", "(I)V");
  jobject obj = env->NewObject(objClass, initMethod, ITER_BY_TITLE);
  SET_HANDLE(zim::Archive::iterator<zim::EntryOrder::titleOrder>, obj, range.begin());

  auto end_ptr = std::make_shared<zim::Archive::iterator<zim::EntryOrder::titleOrder>>(range.end());
  setPtr(env, obj, std::move(end_ptr), "nativeHandleEnd");
  return obj;
} CATCH_EXCEPTION(nullptr)
