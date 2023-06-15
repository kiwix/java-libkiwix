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

package org.kiwix.test.libkiwix;

import org.kiwix.libkiwix.Manager;

public class TestManager
{
  private Manager inner;

  public TestManager(Manager _inner) { inner = _inner; }

  public boolean readFile(String path) { return inner.readFile(path); }
  public boolean readXml(String content, String libraryPath) { return inner.readXml(content, libraryPath); }
  public boolean readOpds(String content, String urlHost) { return inner.readOpds(content, urlHost); }
  public boolean readBookmarkFile(String path) { return inner.readBookmarkFile(path); }
  public String addBookFromPath(String pathToOpen,
                                String pathToSave,
                                String url,
                                boolean checkMetaData)
  { return inner.addBookFromPath(pathToOpen, pathToSave, url, checkMetaData); }

  public TestManager(TestLibrary library) {
    inner = new Manager(library.inner());
  }
}
