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
#define TYPENAME libkiwix_Server
#include <macros.h>



/* Kiwix Reader JNI functions */
METHOD(void, setNativeServer, jobject jLibrary)
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

METHOD0(void, dispose)
{
  dispose<NATIVE_TYPE>(env, thisObj);
}

/* Kiwix library functions */
METHOD(void, setRoot, jstring root)
{
  THIS->setRoot(TO_C(root));
}

METHOD(void, setAddress, jstring address)
{
  THIS->setAddress(TO_C(address));
}

METHOD(void, setPort, int port)
{
  THIS->setPort(TO_C(port));
}

METHOD(void, setNbThreads, int threads)
{
  THIS->setNbThreads(TO_C(threads));
}

METHOD(void, setTaskbar, jboolean withTaskbar, jboolean withLibraryButton)
{
  THIS->setTaskbar(TO_C(withTaskbar), TO_C(withLibraryButton));
}

METHOD(void, setBlockExternalLinks, jboolean blockExternalLinks)
{
  THIS->setBlockExternalLinks(TO_C(blockExternalLinks));
}

METHOD0(jboolean, start)
{
  return THIS->start();
}

METHOD0(void, stop)
{
  THIS->stop();
}
