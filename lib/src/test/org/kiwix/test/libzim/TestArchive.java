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

import org.kiwix.libzim.ZimFileFormatException;
import org.kiwix.libzim.EntryIterator;
import org.kiwix.libzim.Archive;
import java.io.FileDescriptor;
import org.kiwix.libzim.*;

public class TestArchive
{
  private Archive inner;
  public Archive inner() { return inner; }

  public TestArchive(Archive _inner) { inner = _inner; }
  public TestArchive(String filename) throws ZimFileFormatException
  {
    inner = new Archive(filename);
  }

  public TestArchive(FileDescriptor fd) throws ZimFileFormatException
  {
    inner = new Archive(fd);
  }

  public TestArchive(FileDescriptor fd, long offset, long size)
          throws ZimFileFormatException
  {
    inner = new Archive(fd, offset, size);
  }

  public TestArchive(FdInput fd)
          throws ZimFileFormatException
  {
    inner = new Archive(fd);
  }

  public TestArchive(FdInput[] fds)
          throws ZimFileFormatException
  {
    inner = new Archive(fds);
  }

  public String getFilename() { return inner.getFilename(); }
  public long getFilesize() { return inner.getFilesize(); }
  public int getAllEntryCount() { return inner.getAllEntryCount(); }
  public int getEntryCount() { return inner.getEntryCount(); }
  public int getArticleCount() { return inner.getArticleCount(); }
  public int getMediaCount() { return inner.getMediaCount(); }
  public String getUuid() { return inner.getUuid(); }
  public String getMetadata(String name) throws EntryNotFoundException { return inner.getMetadata(name); }
  public TestItem getMetadataItem(String name) throws EntryNotFoundException { return new TestItem(inner.getMetadataItem(name)); }
  public String[] getMetadataKeys() { return inner.getMetadataKeys(); }

  public TestItem getIllustrationItem(int size) { return new TestItem(inner.getIllustrationItem(size)); }
  public boolean hasIllustration(int size) { return inner.hasIllustration(size); }
  public long[] getIllustrationSizes() { return inner.getIllustrationSizes(); }

  public TestEntry getEntryByPath(String path) throws EntryNotFoundException { return new TestEntry(inner.getEntryByPath(path)); }
  public TestEntry getEntryByPath(int index) throws EntryNotFoundException { return new TestEntry(inner.getEntryByPath(index)); }
  public boolean hasEntryByPath(String path) { return inner.hasEntryByPath(path); }

  public TestEntry getEntryByTitle(String title) throws EntryNotFoundException { return new TestEntry(inner.getEntryByTitle(title)); }
  public TestEntry getEntryByTitle(int index) throws EntryNotFoundException { return new TestEntry(inner.getEntryByTitle(index)); }
  public boolean hasEntryByTitle(String title) { return inner.hasEntryByTitle(title); }

  public TestEntry getEntryByClusterOrder(int index) throws EntryNotFoundException { return new TestEntry(inner.getEntryByClusterOrder(index)); }

  public TestEntry getMainEntry() throws EntryNotFoundException { return new TestEntry(inner.getMainEntry()); }
  public boolean hasMainEntry() { return inner.hasMainEntry(); }

  public TestEntry getRandomEntry() { return new TestEntry(inner.getRandomEntry()); }

  public boolean hasFulltextIndex() { return inner.hasFulltextIndex(); }
  public boolean hasTitleIndex() { return inner.hasTitleIndex(); }

  public boolean hasChecksum() { return inner.hasChecksum(); }
  public String getChecksum() { return inner.getChecksum(); }
  public boolean check() { return inner.check(); }

  public boolean isMultiPart() { return inner.isMultiPart(); }
  public boolean hasNewNamespaceScheme() { return inner.hasNewNamespaceScheme(); }

  public TestEntryIterator iterByPath() { return new TestEntryIterator(inner.iterByPath()); }
  public TestEntryIterator iterByTitle() { return new TestEntryIterator(inner.iterByTitle()); }
  public TestEntryIterator iterEfficient() { return new TestEntryIterator(inner.iterEfficient()); }
  public TestEntryIterator findByPath(String path) { return new TestEntryIterator(inner.findByPath(path)); }
  public TestEntryIterator findByTitle(String path) { return new TestEntryIterator(inner.findByTitle(path)); }

  public void dispose() { inner.dispose(); }
}
