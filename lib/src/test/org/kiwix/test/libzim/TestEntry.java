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

import org.kiwix.libzim.Entry;

public class TestEntry
{
  private Entry inner;
  public TestEntry(Entry _inner) { inner = _inner; }
  public boolean isRedirect() { return inner.isRedirect(); }
  public String getTitle() { return inner.getTitle(); }
  public String getPath() { return inner.getPath(); }

  public TestItem getItem(boolean follow) { return new TestItem(inner.getItem(follow)); }
  public TestItem getRedirect() { return new TestItem(inner.getRedirect()); }
  public TestEntry getRedirectEntry() { return new TestEntry(inner.getRedirectEntry()); }
}
