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

package org.kiwix.libzim;

import java.util.Iterator;

public class EntryIterator implements Iterator<Entry>
{
  private EntryIterator(int order) {
    this.order = order;
  }
  public native boolean hasNext();
  public native Entry next();

  @Override
  protected void finalize() { dispose(); }


///--------- The wrapper thing
  // To delete our native wrapper
  public native void dispose();

  // A marker of the order used for this iterator
  private int order;

  // A pointer (as a long) to a native Handle
  private long nativeHandle;

  // A pointer (as a long) to the native end
  private long nativeHandleEnd;
}
