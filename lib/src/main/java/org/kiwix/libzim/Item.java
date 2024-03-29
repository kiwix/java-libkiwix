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

import org.kiwix.libzim.Blob;
import org.kiwix.libzim.DirectAccessInfo;

public class Item
{
  public native String getTitle();
  public native String getPath();
  public native String getMimetype();

  public native Blob getData();
  public native long getSize();

  public native DirectAccessInfo getDirectAccessInformation();

  @Override
  protected void finalize() { dispose(); }

///--------- The wrapper thing
  // To delete our native wrapper
  private native void dispose();

  // A pointer (as a long) to a native Handle
  private long nativeHandle;
}
