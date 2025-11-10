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

package org.kiwix.test.libkiwix;

import org.kiwix.libkiwix.SpellingsDB;
import org.kiwix.libzim.Archive;
import org.kiwix.test.libzim.TestArchive;

public class TestSpellingsDB {
    private SpellingsDB inner;

    public TestSpellingsDB(TestArchive archive, String cacheDirPath) {
        inner = new SpellingsDB(archive.inner(), cacheDirPath);
    }

    public String[] getSpellingCorrections(String word, int maxCount) {
        return inner.getSpellingCorrections(word, maxCount);
    }
}