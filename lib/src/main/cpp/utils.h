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
#include <memory>
#include <cassert>
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

using std::shared_ptr;

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

// Create a java object using a constructor setting handle.
template<typename T>
inline jobject newObject2(const char* className, JNIEnv* env, shared_ptr<T>&& ptr) {
  jclass objClass = env->FindClass(className);
  jmethodID initMethod = env->GetMethodID(objClass, "<init>", "(J)V");
  // allocate a shared_ptr on the head
  shared_ptr<T>* handle = new shared_ptr<T>(ptr);
  jobject wrapper = env->NewObject(objClass, initMethod, reinterpret_cast<jlong>(handle));
  return wrapper;
}
#define NEW_OBJECT2(CLASSNAME, ptr) newObject2(CLASSNAME, env, ptr)


// Set the pointer to the wrapped object.
template<typename T>
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
#define SET_PTR(SHARED_PTR) setPtr(env, thisObj, std::move(SHARED_PTR))

// This create a object and set it in the wrapper
template<typename T, typename ...Args>
inline void setHandle(JNIEnv* env, jobject thisObj, Args && ...args)
{
  auto ptr = std::make_shared<T>(std::forward<Args>(args)...);
  setPtr(env, thisObj, std::move(ptr));
}
#define SET_HANDLE(NATIVE_TYPE, OBJ, VALUE) setHandle<NATIVE_TYPE>(env, OBJ, VALUE)


// Return a shared_ptr for the handle
template<typename T>
shared_ptr<T> getPtr(JNIEnv* env, jobject thisObj, const char* handleName = "nativeHandle")
{
  jclass thisClass = env->GetObjectClass(thisObj);
  jfieldID fidNumber = env->GetFieldID(thisClass, handleName, "J");
  auto handle = reinterpret_cast<shared_ptr<T>*>(env->GetLongField(thisObj, fidNumber));
  return *handle;
}
#define GET_PTR(NATIVE_TYPE) getPtr<NATIVE_TYPE>(env, thisObj)

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

inline jfieldID getHandleField(JNIEnv* env, jobject obj, const char* handleName)
{
  jclass c = env->GetObjectClass(obj);
  // J is the type signature for long:
  return env->GetFieldID(c, handleName, "J");
}

inline jobjectArray createArray(JNIEnv* env, size_t length, const std::string& type_sig)
{
  jclass c = env->FindClass(type_sig.c_str());
  return env->NewObjectArray(length, c, NULL);
}

template<typename T>
inline jobject buildWrapper(JNIEnv* env, const char* class_name, T&& obj, const char* handleName = "nativeHandle") {
  auto wrapper = newObject(class_name, env);
  auto ptr = std::make_shared<T>(std::move(obj));
  setPtr(env, wrapper, std::move(ptr));
  return wrapper;
}

template<typename T>
inline jobject buildWrapper(JNIEnv* env, const char* class_name, std::shared_ptr<T>&& ptr, const char* handleName = "nativeHandle") {
  auto wrapper = newObject(class_name, env);
  setPtr(env, wrapper, std::move(ptr));
  return wrapper;
}

#define BUILD_WRAPPER(CLASSNAME, OBJ) buildWrapper(env, CLASSNAME, std::move(OBJ))

template<typename T>
inline jobject buildWrapper2(JNIEnv* env, const char* class_name, T&& obj, const char* handleName = "nativeHandle") {
  auto ptr = std::make_shared<T>(std::move(obj));
  auto wrapper = newObject2(class_name, env, std::move(ptr));
  return wrapper;
}
#define BUILD_WRAPPER2(CLASSNAME, OBJ) buildWrapper2(env, CLASSNAME, std::move(OBJ))




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
template<> struct JTypeArray<char>{
  typedef jbyteArray type_t;
  static jbyteArray createArray(JNIEnv* env, size_t length) {
    return env->NewByteArray(length);
  }
  static void setArray(JNIEnv* env, jbyteArray array, const char* data, size_t length) {
    env->SetByteArrayRegion(array, 0, length, reinterpret_cast<const signed char*>(data));
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

template<typename U>
inline typename JTypeArray<U>::type_t cArray2jni(const U* data, size_t length, JNIEnv* env)
{
  auto array = JTypeArray<U>::createArray(env, length);
  JTypeArray<U>::setArray(env, array, data, length);
  return array;
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
