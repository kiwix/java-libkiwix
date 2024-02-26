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

package org.kiwix.test.libkiwix;

import org.kiwix.libkiwix.Bookmark;

public class TestBookmark
{
  private Bookmark inner;
  public Bookmark inner() { return inner; }
  public TestBookmark() { inner = new Bookmark(); }
  public TestBookmark(Bookmark _inner) { inner = _inner; }

  public void setBookId(String bookId) { inner.setBookId(bookId); }
  public void setBookTitle(String bookTitle) { inner.setBookTitle(bookTitle); }
  public void setBookName(String bookName) { inner.setBookName(bookName); }
  public void setBookFlavour(String bookFlavour) { inner.setBookFlavour(bookFlavour); }
  public void setUrl(String url) { inner.setUrl(url); }
  public void setTitle(String title) { inner.setTitle(title); }
  public void setLanguage(String language) { inner.setLanguage(language); }
  public void setDate(String date) { inner.setDate(date); }

  public String getBookId() { return inner.getBookId(); }
  public String getBookTitle() { return inner.getBookTitle(); }
  public String getBookName() { return inner.getBookName(); }
  public String getBookFlavour() { return inner.getBookFlavour(); }
  public String getUrl() { return inner.getUrl(); }
  public String getTitle() { return inner.getTitle(); }
  public String getLanguage() { return inner.getLanguage(); }
  public String getDate() { return inner.getDate(); }
}
