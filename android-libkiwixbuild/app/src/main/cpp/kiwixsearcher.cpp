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


#include "org_kiwix_kiwixlib_JNIKiwixSearcher.h"
#include "org_kiwix_kiwixlib_JNIKiwixSearcher_Result.h"

#include <utils.h>
#include <zim/search.h>
#include <zim/item.h>
#include <zim/suggestion.h>
#include "library.h"

#define SEARCHER (Handle<zim::Searcher>::getHandle(env, obj))
#define RESULT (Handle<zim::SearchResultSet>::getHandle(env, obj))


JNIEXPORT void JNICALL
Java_org_kiwix_kiwixlib_JNIKiwixSearcher_dispose(JNIEnv* env, jobject obj)
{
  Handle<zim::Searcher>::dispose(env, obj);
}

/* Kiwix Reader JNI functions */
JNIEXPORT jlong JNICALL
Java_org_kiwix_kiwixlib_JNIKiwixSearcher_getNativeHandle(JNIEnv* env,
                                                          jobject obj, jstring filename)
  {
  std::string cPath = jni2c(filename, env);
  zim::Archive* archive = new zim::Archive(cPath);
  zim::Searcher* searcher = new zim::Searcher(*archive);
  return reinterpret_cast<jlong>(new Handle<zim::Searcher>(searcher));
}

JNIEXPORT void JNICALL Java_org_kiwix_kiwixlib_JNIKiwixSearcher_search(
    JNIEnv* env, jobject obj, jstring querySearch)
{
  std::string cQuery = jni2c(querySearch, env);
  zim::Query query;
  query.setQuery(cQuery);
  SEARCHER->search(query);
}

JNIEXPORT jobject JNICALL
Java_org_kiwix_kiwixlib_JNIKiwixSearcher_getNextResult(JNIEnv* env,jobject obj, jstring querySearch)
{
  jobject result = nullptr;
  std::string cQuery = jni2c(querySearch, env);
  zim::Query query;
  query.setQuery(cQuery);
  zim::Search search = SEARCHER->search(query);
  zim::SearchResultSet resultoutput = search.getResults(0,10);
  zim::SearchResultSet* cresult = &resultoutput;
    if (cresult != nullptr) {
    jclass resultclass
        = env->FindClass("org/kiwix/kiwixlib/JNIKiwixSearcher$SearchResultSet");
    jmethodID ctor = env->GetMethodID(
        resultclass, "<init>", "(Lorg/kiwix/kiwixlib/JNIKiwixSearcher;JLorg/kiwix/kiwixlib/JNIKiwixSearcher;)V");
    result = env->NewObject(resultclass, ctor, obj, reinterpret_cast<jlong>(new Handle<zim::SearchResultSet>(cresult)), obj);
  }
  return result;
}

JNIEXPORT void JNICALL Java_org_kiwix_kiwixlib_JNIKiwixSearcher_00024SearchResultSet_dispose(
    JNIEnv* env, jobject obj)
{
  Handle<zim::SearchResultSet>::dispose(env, obj);
}

JNIEXPORT jstring JNICALL
Java_org_kiwix_kiwixlib_JNIKiwixSearcher_00024SearchResultSet_getUrl(JNIEnv* env,
                                                        jobject obj)
{
  try {
     std::string getPath;
     zim::SearchResultSet result = *(*RESULT);
     for( auto searchIt = result.begin(); searchIt != result.end(); searchIt++) {
          getPath = searchIt.getPath();
     }
     return c2jni(getPath, env);
     } catch (...) {
     return nullptr;
     }
}

JNIEXPORT jstring JNICALL
Java_org_kiwix_kiwixlib_JNIKiwixSearcher_00024SearchResultSet_getTitle(JNIEnv* env,
                                                          jobject obj)
{
  try {
    std::string getTitle;
    zim::SearchResultSet result = *(*RESULT);
     for( auto searchIt = result.begin(); searchIt != result.end(); searchIt++) {
          getTitle = searchIt.getTitle();
     }
    return c2jni(getTitle, env);
  } catch (...) {
    return nullptr;
  }
}

JNIEXPORT jstring JNICALL
Java_org_kiwix_kiwixlib_JNIKiwixSearcher_00024SearchResultSet_getSnippet(JNIEnv* env,
                                                            jobject obj)
{
  std::string getSnippet;
  zim::SearchResultSet result = *(*RESULT);
  for( auto searchIt = result.begin(); searchIt != result.end(); searchIt++) {
      getSnippet = searchIt.getSnippet();
  }
  return c2jni(getSnippet, env);
}

JNIEXPORT jstring JNICALL
Java_org_kiwix_kiwixlib_JNIKiwixSearcher_00024SearchResultSet_getContent(JNIEnv* env,
                                                            jobject obj)
{
  std::string getContent;
  zim::SearchResultSet result = *(*RESULT);
  for( auto searchIt = result.begin(); searchIt != result.end(); searchIt++) {
      auto entry = *searchIt;
      auto item = entry.getItem(true);
      getContent = item.getData().data();
  }
  return c2jni(getContent, env);
}
