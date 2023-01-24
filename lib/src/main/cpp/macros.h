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


// You must define NATIVE_TYPE("zim::Archive") and TYPENAME("zim__Archive")


#define BUILD_METHOD_NX(TYPE, NAME) Java_org_kiwix_ ## TYPE ## _ ## NAME
#define BUILD_METHOD(TYPE, NAME) BUILD_METHOD_NX(TYPE, NAME)

#define THIS getPtr<NATIVE_TYPE>(env, thisObj)

#define METHOD0(retType, name) \
JNIEXPORT retType JNICALL BUILD_METHOD(TYPENAME, name) ( \
  JNIEnv* env, jobject thisObj)

#define METHOD(retType, name, ...) \
JNIEXPORT retType JNICALL BUILD_METHOD(TYPENAME ,name) ( \
  JNIEnv* env, jobject thisObj, __VA_ARGS__)

#define GETTER(retType, name) METHOD0(retType, name) { \
  return TO_JNI(THIS->name()); \
}

#define DISPOSE  METHOD0(void, dispose)  { dispose<NATIVE_TYPE>(env, thisObj); }
