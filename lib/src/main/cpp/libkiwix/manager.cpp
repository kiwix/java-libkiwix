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
#include "org_kiwix_libkiwix_Manager.h"

#include "manager.h"
#include "utils.h"

#define NATIVE_TYPE kiwix::Manager
#define TYPENAME libkiwix_Manager
#include <macros.h>

METHOD(void, allocate, jobject libraryObj)
{
  auto lib = getPtr<kiwix::Library>(env, libraryObj);
  SET_PTR(std::make_shared<NATIVE_TYPE>(lib.get()));
} CATCH_EXCEPTION()

DISPOSE

/* Kiwix manager functions */
METHOD(jboolean, readFile, jstring path)
{
  auto cPath = TO_C(path);

  return THIS->readFile(cPath, false);
} CATCH_EXCEPTION(false)

METHOD(jboolean, readXml, jstring content, jstring libraryPath)
{
  auto cContent = TO_C(content);
  auto cPath = TO_C(libraryPath);

  return THIS->readXml(cContent, false, cPath);
} CATCH_EXCEPTION(false)

METHOD(jboolean, readOpds, jstring content, jstring urlHost)
{
  auto cContent = TO_C(content);
  auto cUrl = TO_C(urlHost);

  return THIS->readOpds(cContent, cUrl);
} CATCH_EXCEPTION(false)

METHOD(jboolean, readBookmarkFile, jstring path)
{
  auto cPath = TO_C(path);
  return THIS->readBookmarkFile(cPath);
} CATCH_EXCEPTION(false)

METHOD(jstring, addBookFromPath, jstring pathToOpen, jstring pathToSave, jstring url, jboolean checkMetaData)
{
  auto cPathToOpen = TO_C(pathToOpen);
  auto cPathToSave = TO_C(pathToSave);
  auto cUrl = TO_C(url);
  jstring id = NULL;

  auto cId = THIS->addBookFromPathAndGetId(cPathToOpen, cPathToSave, cUrl, checkMetaData);
  if ( !cId.empty() ) {
    id = c2jni(cId, env);
  }

  return id;
} CATCH_EXCEPTION(0)
