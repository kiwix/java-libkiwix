/*
 * Copyright (C) 2019-2020 Matthieu Gautier <mgautier@kymeria.fr>
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

import org.kiwix.libzim.Archive;
import org.kiwix.libzim.Searcher;
import org.kiwix.libkiwix.Book;
import org.kiwix.libkiwix.JNIKiwixException;
import org.kiwix.libkiwix.Bookmark;
import org.kiwix.libkiwix.BookmarkMigrationResult;

public class Library
{
  public Library()
  {
    setNativeHandler();
  }
  public native boolean addBook(Book book) throws JNIKiwixException;

  public native Book getBookById(String id);

  public native Archive getArchiveById(String id);
  //public native Searcher getSearcherById(String id);
  //public native Searcher getSearcherByIds(String ids[]);

  public native boolean removeBookById(String id);

  public native boolean writeToFile(String path);
  public native boolean writeBookmarksToFile(String path);

  public native int getBookCount(boolean localBooks, boolean remoteBooks);

  public native String[] getBooksIds();
  public native String[] filter(Filter filter);

  public native String[] getBooksLanguages();
  public native String[] getBooksCategories();
  public native String[] getBooksCreators();
  public native String[] getBooksPublishers();

  public native void addBookmark(Bookmark bookmark);
  public native boolean removeBookmark(String zimId, String url);
  public native BookmarkMigrationResult migrateBookmarks(boolean allowDowngrade);
  public native int migrateBookmarks(String sourceBookId, boolean allowDowngrade);
  public native int migrateBookmarks(String sourceBookId, String targetBookId);
  public native Bookmark[] getBookmarks(boolean onlyValidBookmarks);

  public native String getBestTargetBookId(Bookmark bookmark, boolean allowDowngrade);
  public String getBestTargetBookId(String bookName) {
    return getBestTargetBookId(bookName, "", "");
  }
  public String getBestTargetBookId(String bookName, String preferedFlavour) {
    return getBestTargetBookId(bookName, preferedFlavour, "");
  }
  public native String getBestTargetBookId(String bookName, String preferedFlavour, String minDate);

  @Override
  protected void finalize() { dispose(); }
  private native void setNativeHandler();
  private native void dispose();
  private long nativeHandle;
}
