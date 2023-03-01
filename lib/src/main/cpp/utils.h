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


#ifndef _ANDROID_JNI_UTILS_H
#define _ANDROID_JNI_UTILS_H

#include <jni.h>

#include <mutex>
#include <string>
#include <vector>
#include <set>
#include <iostream>

#if __ANDROID__
 #include <android/log.h>
 #define LOG(...) __android_log_print(ANDROID_LOG_ERROR, "kiwix", __VA_ARGS__)
#else
 #define LOG(...)
#endif

#include <zim/archive.h>
#include <book.h>

using std::shared_ptr;

namespace zim {
  class Blob;
  class Searcher;
  class Query;
  class Search;
  class SearchIterator;
  class SuggestionSearcher;
  class SuggestionSearch;
  class SuggestionIterator;
  class SuggestionItem;

  class Entry;
  class Item;
}

namespace kiwix {
  class Library;
  class Bookmark;
  class Filter;
  class Manager;
  class Server;
}

enum class type_id :int  {
  Archive,
  Iterator_path,
  Iterator_title,
  Iterator_efficient,
  Blob,
  Searcher,
  Query,
  Search,
  SearchIterator,
  SuggestionSearcher,
  SuggestionSearch,
  SuggestionIterator,
  SuggestionItem,
  Entry,
  Item,

  Library,
  Filter,
  Manager,
  Server,
  Book,
  Bookmark,
  ConstBook,
  Illustration,
  ConstIllustration
};

template<typename T>
struct WrappedType { };

template<> struct WrappedType<zim::Archive>{
  static constexpr const type_id ID = type_id::Archive;
  static constexpr const char* CLASS_NAME =  "org/kiwix/libzim/Archive";
};

template<> struct WrappedType<zim::Archive::iterator<zim::EntryOrder::pathOrder>>{
  static constexpr const type_id ID = type_id::Iterator_path;
  //static constexpr const char* CLASS_NAME =  "org/kiwix/libzim/Archive";
};

template<> struct WrappedType<zim::Archive::iterator<zim::EntryOrder::titleOrder>>{
  static constexpr const type_id ID = type_id::Iterator_title;
  //static constexpr const char* CLASS_NAME =  "org/kiwix/libzim/Archive";
};

template<> struct WrappedType<zim::Archive::iterator<zim::EntryOrder::efficientOrder>>{
  static constexpr const type_id ID = type_id::Iterator_efficient;
  //static constexpr const char* CLASS_NAME =  "org/kiwix/libzim/Archive";
};

template<> struct WrappedType<zim::Blob>{
  static constexpr const type_id ID = type_id::Blob;
  static constexpr const char* const CLASS_NAME = "org/kiwix/libzim/Blob";
};

template<> struct WrappedType<zim::Searcher>{
  static constexpr const type_id ID = type_id::Searcher;
  static constexpr const char* const CLASS_NAME = "org/kiwix/libzim/Searcher";
};


template<> struct WrappedType<zim::Search>{
  static constexpr const type_id ID = type_id::Search;
  static constexpr const char* const CLASS_NAME = "org/kiwix/libzim/Search";
};

template<> struct WrappedType<zim::Query>{
  static constexpr const type_id ID = type_id::Query;
  static constexpr const char* const CLASS_NAME = "org/kiwix/libzim/Query";
};

template<> struct WrappedType<zim::SearchIterator>{
  static constexpr const type_id ID = type_id::SearchIterator;
  //static constexpr const char* const CLASS_NAME = "org/kiwix/libzim/Search";
};

template<> struct WrappedType<zim::SuggestionSearcher>{
  static constexpr const type_id ID = type_id::SuggestionSearcher;
  static constexpr const char* const CLASS_NAME = "org/kiwix/libzim/SuggestionSearcher";
};

template<> struct WrappedType<zim::SuggestionSearch>{
  static constexpr const type_id ID = type_id::SuggestionSearch;
  static constexpr const char* const CLASS_NAME = "org/kiwix/libzim/SuggestionSearch";
};

template<> struct WrappedType<zim::SuggestionIterator>{
  static constexpr const type_id ID = type_id::SuggestionIterator;
  //static constexpr const char* const CLASS_NAME = "org/kiwix/libzim/SuggestionIterator";
};

template<> struct WrappedType<zim::SuggestionItem>{
  static constexpr const type_id ID = type_id::SuggestionItem;
  static constexpr const char* const CLASS_NAME = "org/kiwix/libzim/SuggestionItem";
};

template<> struct WrappedType<zim::Entry>{
  static constexpr const type_id ID = type_id::Entry;
  static constexpr const char* const CLASS_NAME = "org/kiwix/libzim/Entry";
};

template<> struct WrappedType<zim::Item>{
  static constexpr const type_id ID = type_id::Item;
  static constexpr const char* const CLASS_NAME = "org/kiwix/libzim/Item";
};


template<> struct WrappedType<kiwix::Library>{
  static constexpr const type_id ID = type_id::Library;
  static constexpr const char* const CLASS_NAME = "org/kiwix/libkiwix/Library";
};

template<> struct WrappedType<kiwix::Bookmark>{
  static constexpr const type_id ID = type_id::Bookmark;
  static constexpr const char* const CLASS_NAME = "org/kiwix/libkiwix/Bookmark";
};


template<> struct WrappedType<kiwix::Filter>{
  static constexpr const type_id ID = type_id::Filter;
  static constexpr const char* const CLASS_NAME = "org/kiwix/libkiwix/Filter";
};

template<> struct WrappedType<kiwix::Manager>{
  static constexpr const type_id ID = type_id::Manager;
  static constexpr const char* const CLASS_NAME = "org/kiwix/libkiwix/Manager";
};

template<> struct WrappedType<kiwix::Server>{
  static constexpr const type_id ID = type_id::Server;
  static constexpr const char* const CLASS_NAME = "org/kiwix/libkiwix/Server";
};

template<> struct WrappedType<kiwix::Book>{
  static constexpr const type_id ID = type_id::Book;
  static constexpr const char* const CLASS_NAME = "org/kiwix/libkiwix/Book";
};

template<> struct WrappedType<const kiwix::Book>{
  static constexpr const type_id ID = type_id::ConstBook;
  static constexpr const char* const CLASS_NAME = "org/kiwix/libkiwix/Book";
};

template<> struct WrappedType<kiwix::Book::Illustration>{
  static constexpr const type_id ID = type_id::Illustration;
  static constexpr const char* const CLASS_NAME = "org/kiwix/libkiwix/Illustration";
};


template<> struct WrappedType<const kiwix::Book::Illustration>{
  static constexpr const type_id ID = type_id::ConstIllustration;
  static constexpr const char* const CLASS_NAME = "org/kiwix/libkiwix/Illustration";
};


inline jfieldID getHandleField(JNIEnv* env, jobject obj, const char* handleName)
{
  jclass c = env->GetObjectClass(obj);
  // J is the type signature for long:
  return env->GetFieldID(c, handleName, "J");
}


template<typename T>
inline jobject newResource(JNIEnv* env, T&& reference) {
  auto ptr = std::make_shared<typename std::remove_reference<T>::type>(std::move(reference));
  return newResource(env, std::move(ptr));
}

template<typename T>
inline jobject newResource(JNIEnv* env, shared_ptr<T>&& ptr) {
  jclass wrapperClass = env->FindClass("org/kiwix/Wrapper/Resource");
  jmethodID initMethod = env->GetMethodID(wrapperClass, "<init>", "(IL)V");
  // allocate a shared_ptr on the head
  shared_ptr<T>* handle = new shared_ptr<T>(ptr);
  jobject wrapper = env->NewObject(wrapperClass, initMethod, static_cast<int>(WrappedType<T>::ID), reinterpret_cast<jlong>(handle));
  return wrapper;
}
#define NEW_RESOURCE(SHARED_PTR) newResource(env, std::move(SHARED_PTR));


inline void deleteResource(JNIEnv* env, jobject resource) {
  jclass resourceClass = env->GetObjectClass(resource);

  jfieldID handleFieldId = env->GetFieldID(resourceClass, "nativeHandle", "J");
  auto handle_ptr = env->GetLongField(resource, handleFieldId);

  // We now need to know the type of the handle.
  jfieldID typeFieldId = env->GetFieldID(resourceClass, "classid", "I");
  auto type_id = static_cast<enum type_id>(env->GetIntField(resource, typeFieldId));

  switch (type_id) {
    case type_id::Archive:
      delete reinterpret_cast<shared_ptr<zim::Archive>*>(handle_ptr);
      break;
    case type_id::Iterator_path:
      delete reinterpret_cast<shared_ptr<zim::Archive::iterator<zim::EntryOrder::pathOrder>>*>(handle_ptr);
      break;
    case type_id::Iterator_title:
      delete reinterpret_cast<shared_ptr<zim::Archive::iterator<zim::EntryOrder::titleOrder>>*>(handle_ptr);
      break;
    case type_id::Iterator_efficient:
      delete reinterpret_cast<shared_ptr<zim::Archive::iterator<zim::EntryOrder::efficientOrder>>*>(handle_ptr);
      break;
    case type_id::Blob:
      delete reinterpret_cast<shared_ptr<zim::Blob>*>(handle_ptr);
      break;
    case type_id::Searcher:
      delete reinterpret_cast<shared_ptr<zim::Searcher>*>(handle_ptr);
      break;
    case type_id::Query:
      delete reinterpret_cast<shared_ptr<zim::Query>*>(handle_ptr);
      break;
    case type_id::Search:
      delete reinterpret_cast<shared_ptr<zim::Search>*>(handle_ptr);
      break;
    case type_id::SearchIterator:
      delete reinterpret_cast<shared_ptr<zim::SearchIterator>*>(handle_ptr);
      break;
    case type_id::SuggestionSearcher:
      delete reinterpret_cast<shared_ptr<zim::SuggestionSearcher>*>(handle_ptr);
      break;
    case type_id::SuggestionSearch:
      delete reinterpret_cast<shared_ptr<zim::SuggestionSearch>*>(handle_ptr);
      break;
    case type_id::SuggestionIterator:
      delete reinterpret_cast<shared_ptr<zim::SuggestionIterator>*>(handle_ptr);
      break;
    case type_id::SuggestionItem:
      delete reinterpret_cast<shared_ptr<zim::SuggestionItem>*>(handle_ptr);
      break;
    case type_id::Entry:
      delete reinterpret_cast<shared_ptr<zim::Entry>*>(handle_ptr);
      break;
    case type_id::Item:
      delete reinterpret_cast<shared_ptr<zim::Item>*>(handle_ptr);
      break;

    case type_id::Library:
      delete reinterpret_cast<shared_ptr<kiwix::Library>*>(handle_ptr);
      break;
    case type_id::Bookmark:
      delete reinterpret_cast<shared_ptr<kiwix::Bookmark>*>(handle_ptr);
      break;
    case type_id::Filter:
      delete reinterpret_cast<shared_ptr<kiwix::Filter>*>(handle_ptr);
      break;
    case type_id::Manager:
      delete reinterpret_cast<shared_ptr<kiwix::Manager>*>(handle_ptr);
      break;
    case type_id::Server:
      delete reinterpret_cast<shared_ptr<kiwix::Server>*>(handle_ptr);
      break;
    case type_id::Book:
      delete reinterpret_cast<shared_ptr<kiwix::Book>*>(handle_ptr);
      break;
    case type_id::ConstBook:
      delete reinterpret_cast<shared_ptr<const kiwix::Book>*>(handle_ptr);
      break;
    case type_id::Illustration:
      delete reinterpret_cast<shared_ptr<kiwix::Book::Illustration>*>(handle_ptr);
      break;
    case type_id::ConstIllustration:
      delete reinterpret_cast<shared_ptr<const kiwix::Book::Illustration>*>(handle_ptr);
      break;
  };
}

template<typename T>
shared_ptr<T> getPtr(JNIEnv* env, jobject thisObj, const char* resourceField = "nativeResource")
{
  jclass thisClass = env->GetObjectClass(thisObj);
  jfieldID resourceFieldId = env->GetFieldID(thisClass, resourceField, "org/kiwix/Wrapper/Resource");
  jobject resource = env->GetObjectField(thisObj, resourceFieldId);

  // This may be Wrapper.Resource or IterWrapper.Resource
  jclass resourceClass = env->GetObjectClass(resource);
  jfieldID handleFieldId = env->GetFieldID(resourceClass, "nativeHandle", "J");
  auto handle_ptr = env->GetLongField(resource, handleFieldId);

  // Let's check that asked type is same that the one registered in the resource.
  jfieldID typeFieldId = env->GetFieldID(resourceClass, "classid", "I");
  auto type_id = static_cast<enum type_id>(env->GetIntField(resource, typeFieldId));
  assert(type_id == WrappedType<T>::ID);

  auto handle = reinterpret_cast<shared_ptr<T>*>(handle_ptr);
  return *handle;
}


// Here is the wrapping structure.
// All java class wrapping a `Native` instance must contain a pointer (cast as a long (J)) called "nativeHandle".
// They also need a constructor taking no argument (or they can, but helper here cannot be used.)
// The "nativeHandle" pointer points to a  heap allocated `Handle<Native>`. The handle itself IS a shared_ptr.
// !!! This is a shared_ptr heap allocated instance which contains a `Native` heap allocated.
// So if the `Native` instance is own by a smart pointer (shared_ptr), the shared_ptr itself is "own" by a raw pointer.

// From the jobject and the pointer field ("nativeHandle"), we can access a shared_ptr (not a pointer to a shared_ptr).
// To avoid a memory leak, we must at java wrapper destruction (dispose), delete the heap shared_ptr.

// Create a java object using a default constructor. No field is set.
inline jobject newObject(const char* className, JNIEnv* env) {
  jclass objClass = env->FindClass(className);
  jmethodID initMethod = env->GetMethodID(objClass, "<init>", "()V");
  jobject wrapper = env->NewObject(objClass, initMethod);
  return wrapper;
}
#define NEW_OBJECT(CLASSNAME) newObject(CLASSNAME, env)

// Set the pointer to the wrapped object.
/*template<typename T>
inline void setPtr(JNIEnv* env, jobject thisObj, shared_ptr<T>&& ptr, const char* handleName = "nativeHandle")
{
  jclass thisClass = env->GetObjectClass(thisObj);
  jfieldID fieldId = env->GetFieldID(thisClass, handleName, "J");
  // if field id is not null, we are leaking the currently stored handle
  assert(env->GetLongField(thisObj, fieldId) == 0);
  // allocate a shared_ptr on the head
  shared_ptr<T>* handle = new shared_ptr<T>(ptr);
  env->SetLongField(thisObj, fieldId, reinterpret_cast<jlong>(handle));
}
#define SET_PTR(SHARED_PTR) setPtr(env, thisObj, std::move(SHARED_PTR))*/

// This create a object and set it in the wrapper
/*template<typename T, typename ...Args>
inline void setHandle(JNIEnv* env, jobject thisObj, Args && ...args)
{
  auto ptr = std::make_shared<T>(std::forward<Args>(args)...);
  setPtr(env, thisObj, std::move(ptr));
}
#define SET_HANDLE(NATIVE_TYPE, OBJ, VALUE) setHandle<NATIVE_TYPE>(env, OBJ, VALUE)*/


// Return a shared_ptr for the handle
/*
template<typename T>
shared_ptr<T> getPtr(JNIEnv* env, jobject thisObj, const char* handleName = "nativeHandle")
{
  jclass thisClass = env->GetObjectClass(thisObj);
  jfieldID fidNumber = env->GetFieldID(thisClass, handleName, "J");
  auto handle = reinterpret_cast<shared_ptr<T>*>(env->GetLongField(thisObj, fidNumber));
  return *handle;
}
#define GET_PTR(NATIVE_TYPE) getPtr<NATIVE_TYPE>(env, thisObj)*/

// Delete the heap allocated handle
template<typename T>
void dispose(JNIEnv* env, jobject thisObj, const char* handleName = "nativeHandle")
{
  jclass thisClass = env->GetObjectClass(thisObj);
  jfieldID fieldId = env->GetFieldID(thisClass, handleName, "J");
  auto handle = reinterpret_cast<shared_ptr<T>*>(env->GetLongField(thisObj, fieldId));
  if (handle != 0) {
    delete handle;
  }
  env->SetLongField(thisObj, fieldId, 0);
}


inline jobjectArray createArray(JNIEnv* env, size_t length, const std::string& type_sig)
{
  jclass c = env->FindClass(type_sig.c_str());
  return env->NewObjectArray(length, c, NULL);
}



template<typename T>
inline jobject buildWrapper(JNIEnv* env, std::shared_ptr<T>&& ptr) {
  auto resource = newResource(env, std::move(ptr));
  jclass wrapperClass = env->FindClass(WrappedType<T>::CLASS_NAME);
  jmethodID initMethod = env->GetMethodID(wrapperClass, "<init>", "(org/kiwix/Wrapper/Resource)V");
  return env->NewObject(wrapperClass, initMethod, resource);
}
template<typename T>
inline jobject buildWrapper(JNIEnv* env, T&& obj) {
  auto resource = newResource(env, std::move(obj));
  jclass wrapperClass = env->FindClass(WrappedType<T>::CLASS_NAME);
  jmethodID initMethod = env->GetMethodID(wrapperClass, "<init>", "(org/kiwix/Wrapper/Resource)V");
  return env->NewObject(wrapperClass, initMethod, resource);
}
#define BUILD_WRAPPER(OBJ) buildWrapper(env, std::move(OBJ))

#define CATCH(MESSAGE) catch (...) { \
  jclass exceptionClass = env->FindClass("java/lang/RuntimeException"); \
  env->ThrowNew(exceptionClass, MESSAGE); \
}


// ---------------------------------------------------------------------------
// Convert things to JAVA
// ---------------------------------------------------------------------------

template<typename T>
struct JType { };

template<> struct JType<bool>{ typedef jboolean type_t; };
template<> struct JType<int16_t>{ typedef jint type_t; };
template<> struct JType<int32_t>{ typedef jint type_t; };
template<> struct JType<int64_t>{ typedef jlong type_t; };
template<> struct JType<uint16_t>{ typedef jint type_t; };
template<> struct JType<uint64_t> { typedef jlong type_t; };
template<> struct JType<uint32_t> { typedef jlong type_t; };
template<> struct JType<std::string>{ typedef jstring type_t; };
template<> struct JType<float> { typedef jfloat type_t;};
template<> struct JType<double> { typedef jdouble type_t;};


template<typename T, typename U=T>
inline typename JType<T>::type_t c2jni(const T& val, JNIEnv* env) {
  return static_cast<typename JType<T>::type_t>(val);
}

template<>
inline jboolean c2jni(const bool& val, JNIEnv* env) { return val ? JNI_TRUE : JNI_FALSE; }

template<>
inline jstring c2jni(const std::string& val, JNIEnv* env)
{
  return env->NewStringUTF(val.c_str());
}


template<typename T>
struct JTypeArray {};
template<> struct JTypeArray<bool>{
  typedef jbooleanArray type_t;
  static jbooleanArray createArray(JNIEnv* env, size_t length) {
    return env->NewBooleanArray(length);
  }
  static void setArray(JNIEnv* env, jbooleanArray array, const bool* data, size_t length) {
    env->SetBooleanArrayRegion(array, 0, length, reinterpret_cast<const jboolean*>(data));
  }
};
template<> struct JTypeArray<int32_t>{
  typedef jintArray type_t;
  static jintArray createArray(JNIEnv* env, size_t length) {
    return env->NewIntArray(length);
  }
  static void setArray(JNIEnv* env, jintArray array, const int32_t* data, size_t length) {
    env->SetIntArrayRegion(array, 0, length, data);
  }
};
template<> struct JTypeArray<int64_t>{
  typedef jlongArray type_t;
  static jlongArray createArray(JNIEnv* env, size_t length) {
    return env->NewLongArray(length);
  }
  static void setArray(JNIEnv* env, jlongArray array, const int64_t* data, size_t length) {
    env->SetLongArrayRegion(array, 0, length, data);
  }
};
template<> struct JTypeArray<uint64_t> {
  typedef jlongArray type_t;
  static jlongArray createArray(JNIEnv* env, size_t length) {
    return env->NewLongArray(length);
  }
  static void setArray(JNIEnv* env, jlongArray array, const uint64_t* data, size_t length) {
    env->SetLongArrayRegion(array, 0, length, reinterpret_cast<const jlong*>(data));
  }
};
template<> struct JTypeArray<uint32_t> {
  typedef jlongArray type_t;
  static jlongArray createArray(JNIEnv* env, size_t length) {
    return env->NewLongArray(length);
  }
  static void setArray(JNIEnv* env, jlongArray array, const uint32_t* data, size_t length) {
    std::vector<jlong> temp(data, data+length);
    env->SetLongArrayRegion(array, 0, length, temp.data());
  }
};
template<> struct JTypeArray<std::string>{
  typedef jobjectArray type_t;
  static jobjectArray createArray(JNIEnv* env, size_t length) {
    return ::createArray(env, length, "java/lang/String");
  }
  static void setArray(JNIEnv* env, jobjectArray array, const std::string* data, size_t length) {
    size_t index = 0;
    for(size_t index=0; index<length; index++) {
      auto jElem = c2jni(data[index], env);
      env->SetObjectArrayElement(array, index, jElem);
    }
  }
};

/*
template<>
inline jobjectArray c2jni(const std::vector<std::string>& val, JNIEnv* env)
{
  auto array = createArray(env, val.size(), "java/lang/String");
  size_t index = 0;
  for (auto& elem: val) {
    auto jElem = c2jni(elem, env);
    env->SetObjectArrayElement(array, index++, jElem);
  }
  return array;
}*/

template<typename U>
inline typename JTypeArray<U>::type_t c2jni(const std::vector<U>& val, JNIEnv* env)
{
  auto array = JTypeArray<U>::createArray(env, val.size());
  JTypeArray<U>::setArray(env, array, val.data(), val.size());
  return array;
}

template<typename U>
inline typename JTypeArray<U>::type_t c2jni(const std::set<U>& val, JNIEnv* env)
{
  std::vector<U> temp(val.begin(), val.end());
  return c2jni(temp, env);
}

#define TO_JNI(VAL) c2jni(VAL, env)


// ---------------------------------------------------------------------------
// Convert things to C
// ---------------------------------------------------------------------------


template<typename T, typename U=T>
struct CType { };

template<> struct CType<jboolean>{ typedef bool type_t; };
template<> struct CType<jint>{ typedef int type_t; };
template<> struct CType<jlong>{ typedef long type_t; };
template<> struct CType<jstring>{ typedef std::string type_t; };
template<> struct CType<jfloat> { typedef float type_t; };
template<> struct CType<jdouble> { typedef double type_t; };

template<typename U>
struct CType<jobjectArray, U>{ typedef std::vector<typename CType<U>::type_t> type_t; };

/* jni2c type conversion functions */
template<typename T, typename U=T>
inline typename CType<T>::type_t jni2c(const T& val, JNIEnv* env) {
  return static_cast<typename CType<T>::type_t>(val);
}

template<>
inline bool jni2c(const jboolean& val, JNIEnv* env) { return val == JNI_TRUE; }

template<>
inline std::string jni2c(const jstring& val, JNIEnv* env)
{
  const char* chars = env->GetStringUTFChars(val, 0);
  std::string ret(chars);
  env->ReleaseStringUTFChars(val, chars);
  return ret;
}

template<typename U>
inline typename CType<jobjectArray, U>::type_t jni2c(const jobjectArray& val, JNIEnv* env)
{
  jsize length = env->GetArrayLength(val);
  typename CType<jobjectArray, U>::type_t v(length);

  int i;
  for (i = 0; i < length; i++) {
    U obj = (U) env->GetObjectArrayElement(val, i);
    auto cobj = jni2c<U>(obj, env);
    v.push_back(cobj);
  }
  return v;
}

#define TO_C(VAL) jni2c(VAL, env)

/* Method to deal with variable passed by reference */
inline std::string getStringObjValue(const jobject obj, JNIEnv* env)
{
  jclass objClass = env->GetObjectClass(obj);
  jfieldID objFid = env->GetFieldID(objClass, "value", "Ljava/lang/String;");
  jstring jstr = (jstring)env->GetObjectField(obj, objFid);
  return jni2c(jstr, env);
}
inline void setStringObjValue(const std::string& value,
                              const jobject obj,
                              JNIEnv* env)
{
  jclass objClass = env->GetObjectClass(obj);
  jfieldID objFid = env->GetFieldID(objClass, "value", "Ljava/lang/String;");
  env->SetObjectField(obj, objFid, c2jni(value, env));
}

inline void setIntObjValue(const int value, const jobject obj, JNIEnv* env)
{
  jclass objClass = env->GetObjectClass(obj);
  jfieldID objFid = env->GetFieldID(objClass, "value", "I");
  env->SetIntField(obj, objFid, value);
}

inline void setBoolObjValue(const bool value, const jobject obj, JNIEnv* env)
{
  jclass objClass = env->GetObjectClass(obj);
  jfieldID objFid = env->GetFieldID(objClass, "value", "Z");
  env->SetIntField(obj, objFid, c2jni(value, env));
}

inline void setDaiObjValue(const std::string& filename, const long offset,
                            const jobject obj, JNIEnv* env)
{
  jclass objClass = env->GetObjectClass(obj);
  jfieldID filenameFid = env->GetFieldID(objClass, "filename", "Ljava/lang/String;");
  env->SetObjectField(obj, filenameFid, c2jni(filename, env));
  jfieldID offsetFid = env->GetFieldID(objClass, "offset", "J");
  env->SetLongField(obj, offsetFid, offset);
}

#endif // _ANDROID_JNI_UTILS_H
