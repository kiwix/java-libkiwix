/*
 * Copyright (C) 2022 Matthieu Gautier <mgautier@kymeria.fr>
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

package org.kiwix.test.libzim;

import org.kiwix.libzim.SearchIterator;
import java.util.Iterator;

public class TestSearchIterator implements Iterator<TestEntry>
{
  private SearchIterator inner;
  public TestSearchIterator(SearchIterator _inner) { inner = _inner; }
  public String getPath() { return inner.getPath(); }
  public String getTitle() { return inner.getTitle(); }
  public int getScore() { return inner.getScore(); }
  public String getSnippet() { return inner.getSnippet(); }
  public int getWordCount() { return inner.getWordCount(); }
  public int getFileIndex() { return inner.getFileIndex(); }
  public int getSize() { return inner.getSize(); }
  public String getZimId() { return inner.getZimId(); }

  public boolean hasNext() { return inner.hasNext(); }
  public TestEntry next() { return new TestEntry(inner.next()); }
}
