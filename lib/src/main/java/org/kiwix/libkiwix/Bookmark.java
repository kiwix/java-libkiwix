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

package org.kiwix.libkiwix;

import org.kiwix.Wrapper;

public class Bookmark extends Wrapper
{
  public Bookmark() {
    super(buildNativeBookmark());
  }

  public native void setBookId(String bookId);
  public native void setBookTitle(String bookTitle);
  public native void setUrl(String url);
  public native void setTitle(String title);
  public native void setLanguage(String language);
  public native void setDate(String Date);

  public native String getBookId();
  public native String getBookTitle();
  public native String getUrl();
  public native String getTitle();
  public native String getLanguage();
  public native String getDate();


  private native static Wrapper.Resource buildNativeBookmark();
}
