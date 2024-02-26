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

package org.kiwix.test.libkiwix;

import org.kiwix.libkiwix.Library;
import org.kiwix.test.libzim.TestArchive;
import org.kiwix.test.libkiwix.TestBookmark;
import org.kiwix.libzim.Searcher;
import org.kiwix.libkiwix.Filter;
import org.kiwix.libkiwix.JNIKiwixException;
import org.kiwix.libkiwix.BookmarkMigrationResult;
import java.util.stream.Stream;

public class TestLibrary
{
  private Library inner;
  public Library inner() { return inner; }
  public TestLibrary() { inner = new  Library(); }
  public TestLibrary(Library _inner) { inner = _inner; }
  public boolean addBook(TestBook book) throws JNIKiwixException { return inner.addBook(book.inner());  }

  public TestBook getBookById(String id) { return new TestBook(inner.getBookById(id)); }

  public TestArchive getArchiveById(String id) { return new TestArchive(inner.getArchiveById(id)); }
  //public native Searcher getSearcherById(String id);
  //public native Searcher getSearcherByIds(String ids[]);

  public boolean removeBookById(String id) { return inner.removeBookById(id); }

  public boolean writeToFile(String path) { return inner.writeToFile(path); }
  public boolean writeBookmarksToFile(String path) { return inner.writeBookmarksToFile(path); }

  public int getBookCount(boolean localBooks, boolean remoteBooks) { return inner.getBookCount(localBooks, remoteBooks); }

  public String[] getBooksIds() { return inner.getBooksIds(); }
  public String[] filter(Filter filter) { return inner.filter(filter); }

  public String[] getBooksLanguages() { return inner.getBooksLanguages(); }
  public String[] getBooksCategories() { return inner.getBooksCategories(); }
  public String[] getBooksCreators() { return inner.getBooksCreators(); }
  public String[] getBooksPublishers() { return inner.getBooksPublishers(); }

  public void addBookmark(TestBookmark bookmark) { inner.addBookmark(bookmark.inner()); }
  public boolean removeBookmark(String zimId, String url) { return inner.removeBookmark(zimId, url); }
  public BookmarkMigrationResult migrateBookmarks(boolean allowDowngrade) { return inner.migrateBookmarks(allowDowngrade); }
  public int migrateBookmarks(String sourceBookId, boolean allowDowngrade) { return inner.migrateBookmarks(sourceBookId, allowDowngrade); }
  public int migrateBookmarks(String sourceBookId, String targetBookId) { return inner.migrateBookmarks(sourceBookId, targetBookId); }
  public TestBookmark[] getBookmarks(boolean onlyValidBookmarks) { return Stream.of(inner.getBookmarks(onlyValidBookmarks)).map(b -> new TestBookmark(b)).toArray(TestBookmark[]::new); }

  public String getBestTargetBookId(TestBookmark bookmark, boolean allowDowngrade) { return inner.getBestTargetBookId(bookmark.inner(), allowDowngrade); }
  public String getBestTargetBookId(String bookname) { return inner.getBestTargetBookId(bookname); }
  public String getBestTargetBookId(String bookname, String preferedFlavour) { return inner.getBestTargetBookId(bookname, preferedFlavour); }
  public String getBestTargetBookId(String bookname, String preferedFlavour, String minDate) { return inner.getBestTargetBookId(bookname, preferedFlavour, minDate); }
}
