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
JNIEXPORT jlong JNICALL Java_org_kiwix_libzim_Archive_getNativeArchive(
    JNIEnv* env, jobject obj, jstring filename)
{
  std::string cPath = TO_C(filename);

  LOG("Attempting to create reader with: %s", cPath.c_str());
  Lock l;
  try {
    zim::Archive* reader = new zim::Archive(cPath);
    return reinterpret_cast<jlong>(new Handle<zim::Archive>(reader));
  } catch (std::exception& e) {
    LOG("Error opening ZIM file");
      LOG("%s", e.what());
    return 0;
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

JNIEXPORT jlong JNICALL Java_org_kiwix_libzim_Archive_getNativeArchiveByFD(
    JNIEnv* env, jobject obj, jobject fdObj)
{
#ifndef _WIN32
  int fd = jni2fd(fdObj, env);

  LOG("Attempting to create reader with fd: %d", fd);
  Lock l;
  try {
    zim::Archive* reader = new zim::Archive(fd);
    return reinterpret_cast<jlong>(new Handle<zim::Archive>(reader));
  } catch (std::exception& e) {
    LOG("Error opening ZIM file");
       LOG("%s", e.what());
    return 0;
  }
#else
  jclass exception = env->FindClass("java/lang/UnsupportedOperationException");
  env->ThrowNew(exception, "org.kiwix.libzim.Archive.getNativeArchiveByFD() is not supported under Windows");
  return 0;
#endif
}

JNIEXPORT jlong JNICALL Java_org_kiwix_libzim_Archive_getNativeArchiveEmbedded(
    JNIEnv* env, jobject obj, jobject fdObj, jlong offset, jlong size)
{
#ifndef _WIN32
  int fd = jni2fd(fdObj, env);

  LOG("Attempting to create reader with fd: %d", fd);
  Lock l;
  try {
    zim::Archive* reader = new zim::Archive(fd, offset, size);
    return reinterpret_cast<jlong>(new Handle<zim::Archive>(reader));
  } catch (std::exception& e) {
    LOG("Error opening ZIM file");
       LOG("%s", e.what());
    return 0;
  }
#else
  jclass exception = env->FindClass("java/lang/UnsupportedOperationException");
  env->ThrowNew(exception, "org.kiwix.libzim.Archive.getNativeArchiveEmbedded() is not supported under Windows");
  return 0;
#endif
}

JNIEXPORT void JNICALL
Java_org_kiwix_libzim_Archive_dispose(JNIEnv* env, jobject thisObj)
{
  dispose<zim::Archive>(env, thisObj);
}

#define THIS (Handle<zim::Archive>::getHandle(env, thisObj))
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
  auto item = THIS->getMetadataItem(TO_C(name));
  auto obj = CREATE_WRAPPER("org/kiwix/libzim/Item", item);
  return obj;
}

GETTER(jobjectArray, getMetadataKeys)

METHOD(jobject, Archive, getIllustrationItem, jint size) {
  auto item = THIS->getIllustrationItem(TO_C(size));
  auto obj = CREATE_WRAPPER("org/kiwix/libzim/Item", item);
  return obj;
}

METHOD(jboolean, Archive, hasIllustration, jint size) {
  return TO_JNI(THIS->hasIllustration(TO_C(size)));
}

GETTER(jlongArray, getIllustrationSizes)

METHOD(jobject, Archive, getEntryByPath, jlong index) {
  auto entry = THIS->getEntryByPath(TO_C(index));
  auto obj = CREATE_WRAPPER("org/kiwix/libzim/Entry", entry);
  return obj;
}

METHOD(jobject, Archive, getEntryByPath, jstring path) {
  auto entry = THIS->getEntryByPath(TO_C(path));
  auto obj = CREATE_WRAPPER("org/kiwix/libzim/Entry", entry);
  return obj;
}

METHOD(jobject, Archive, getEntryByTitle, jlong index) {
  auto entry = THIS->getEntryByTitle(TO_C(index));
  auto obj = CREATE_WRAPPER("org/kiwix/libzim/Entry", entry);
  return obj;
}

METHOD(jobject, Archive, getEntryByTitle, jstring title) {
  auto entry = THIS->getEntryByTitle(TO_C(title));
  auto obj = CREATE_WRAPPER("org/kiwix/libzim/Entry", entry);
  return obj;
}

METHOD(jobject, Archive, getEntryByClusterOrder, jlong index) {
  auto entry = THIS->getEntryByClusterOrder(TO_C(index));
  auto obj = CREATE_WRAPPER("org/kiwix/libzim/Entry", entry);
  return obj;
}

METHOD0(jobject, Archive, getMainEntry) {
  auto entry = THIS->getMainEntry();
  auto obj = CREATE_WRAPPER("org/kiwix/libzim/Entry", entry);
  return obj;
}

METHOD0(jobject, Archive, getRandomEntry) {
  auto entry = THIS->getRandomEntry();
  auto obj = CREATE_WRAPPER("org/kiwix/libzim/Entry", entry);
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



