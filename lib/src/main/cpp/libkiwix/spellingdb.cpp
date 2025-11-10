/*
 * Copyright (C) 2025 Matthieu Gautier <mgautier@kymeria.fr>
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
#include "org_kiwix_libkiwix_SpellingsDB.h"
#include "spelling_correction.h"
#include <zim/archive.h>
#include "utils.h"

#define NATIVE_TYPE kiwix::SpellingsDB
#define TYPENAME libkiwix_SpellingsDB

#include <macros.h>

METHOD(void, setNativeSpellingsDB, jobject archive, jstring cacheDirPath) {
    auto archive1 = getPtr<zim::Archive>(env, archive);
    std::string cPath = TO_C(cacheDirPath);

    auto spellingsDB = std::make_shared<kiwix::SpellingsDB>(*archive1, cPath);
    SET_PTR(spellingsDB);
} CATCH_EXCEPTION()

DISPOSE

METHOD(jobjectArray, getSpellingCorrections, jstring jWord, jint maxCount) {
    auto results = THIS->getSpellingCorrections(TO_C(jWord), TO_C(maxCount));
    jclass stringClass = env->FindClass("java/lang/String");
    jobjectArray jArray = env->NewObjectArray(results.size(), stringClass, nullptr);

    for (size_t i = 0; i < results.size(); ++i) {
        env->SetObjectArrayElement(jArray, i, TO_JNI(results[i]));
    }

    return jArray;
} CATCH_EXCEPTION(nullptr)