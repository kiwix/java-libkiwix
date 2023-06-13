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

import org.kiwix.libzim.Item;
import org.kiwix.libzim.Blob;
import org.kiwix.libzim.DirectAccessInfo;

public class TestItem
{
  private Item inner;
  public TestItem(Item _inner) { inner = _inner; }
  public String getTitle() { return inner.getTitle(); }
  public String getPath() { return inner.getPath(); }
  public String getMimetype() { return inner.getMimetype(); }

  public Blob getData() { return inner.getData(); }
  public long getSize() { return inner.getSize(); }

  public DirectAccessInfo getDirectAccessInformation() { return inner.getDirectAccessInformation(); }
}
