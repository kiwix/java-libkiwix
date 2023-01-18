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
#include "org_kiwix_libkiwix_JNIKiwixServer.h"

#include "server.h"
#include "utils.h"

#define NATIVE_TYPE kiwix::Server
#define THIS GET_PTR(NATIVE_TYPE)

/* Kiwix Reader JNI functions */
JNIEXPORT void JNICALL Java_org_kiwix_kiwixlib_JNIKiwixServer_setNativeServer(
    JNIEnv* env, jobject thisObj, jobject jLibrary)
{
  LOG("Attempting to create server");
  Lock l;
  try {
    auto library = getPtr<kiwix::Library>(env, jLibrary);
    SET_PTR(std::make_shared<NATIVE_TYPE>(library.get()));
  } catch (std::exception& e) {
    LOG("Error creating the server");
    LOG("%s", e.what());
  }
}

JNIEXPORT void JNICALL
Java_org_kiwix_kiwixlib_JNIKiwixServer_dispose(JNIEnv* env, jobject obj)
{
  dispose<NATIVE_TYPE>(env, obj);
}

/* Kiwix library functions */
JNIEXPORT void JNICALL
Java_org_kiwix_kiwixlib_JNIKiwixServer_setRoot(JNIEnv* env, jobject thisObj, jstring root)
{
  THIS->setRoot(TO_C(root));
}

JNIEXPORT void JNICALL
Java_org_kiwix_kiwixlib_JNIKiwixServer_setAddress(JNIEnv* env, jobject thisObj, jstring address)
{
  THIS->setAddress(TO_C(address));
}

JNIEXPORT void JNICALL
Java_org_kiwix_kiwixlib_JNIKiwixServer_setPort(JNIEnv* env, jobject thisObj, int port)
{
  THIS->setPort(TO_C(port));
}

JNIEXPORT void JNICALL
Java_org_kiwix_kiwixlib_JNIKiwixServer_setNbThreads(JNIEnv* env, jobject thisObj, int threads)
{
  THIS->setNbThreads(TO_C(threads));
}

JNIEXPORT void JNICALL
Java_org_kiwix_kiwixlib_JNIKiwixServer_setTaskbar(JNIEnv* env, jobject thisObj, jboolean withTaskbar, jboolean withLibraryButton)
{
  THIS->setTaskbar(TO_C(withTaskbar), TO_C(withLibraryButton));
}

JNIEXPORT void JNICALL
Java_org_kiwix_kiwixlib_JNIKiwixServer_setBlockExternalLinks(JNIEnv* env, jobject thisObj, jboolean blockExternalLinks)
{
  THIS->setBlockExternalLinks(TO_C(blockExternalLinks));
}

JNIEXPORT jboolean JNICALL
Java_org_kiwix_kiwixlib_JNIKiwixServer_start(JNIEnv* env, jobject thisObj)
{
  return THIS->start();
}

JNIEXPORT void JNICALL
Java_org_kiwix_kiwixlib_JNIKiwixServer_stop(JNIEnv* env, jobject thisObj)
{
  THIS->stop();
}
