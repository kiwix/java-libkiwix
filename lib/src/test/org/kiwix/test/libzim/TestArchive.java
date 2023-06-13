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
import org.kiwix.libzim.Entry;
import org.kiwix.libzim.Item;
import org.kiwix.libzim.EntryIterator;
import org.kiwix.libzim.Archive;
import java.io.FileDescriptor;
import org.kiwix.libzim.*;

public class TestArchive
{
  private Archive inner;

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

  public String getFilename() { return inner.getFilename(); }
  public long getFilesize() { return inner.getFilesize(); }
  public int getAllEntryCount() { return inner.getAllEntryCount(); }
  public int getEntryCount() { return inner.getEntryCount(); }
  public int getArticleCount() { return inner.getArticleCount(); }
  public int getMediaCount() { return inner.getMediaCount(); }
  public String getUuid() { return inner.getUuid(); }
  public String getMetadata(String name) { return inner.getMetadata(name); }
  public Item getMetadataItem(String name) { return inner.getMetadataItem(name); }
  public String[] getMetadataKeys() { return inner.getMetadataKeys(); }

  public Item getIllustrationItem(int size) { return inner.getIllustrationItem(size); }
  public boolean hasIllustration(int size) { return inner.hasIllustration(size); }
  public long[] getIllustrationSizes() { return inner.getIllustrationSizes(); }

  public Entry getEntryByPath(String path) { return inner.getEntryByPath(path); }
  public Entry getEntryByPath(int index) { return inner.getEntryByPath(index); }
  public boolean hasEntryByPath(String path) { return inner.hasEntryByPath(path); }

  public Entry getEntryByTitle(String title) { return inner.getEntryByTitle(title); }
  public Entry getEntryByTitle(int index) { return inner.getEntryByTitle(index); }
  public boolean hasEntryByTitle(String title) { return inner.hasEntryByTitle(title); }

  public Entry getEntryByClusterOrder(int index) { return inner.getEntryByClusterOrder(index); }

  public Entry getMainEntry() { return inner.getMainEntry(); }
  public boolean hasMainEntry() { return inner.hasMainEntry(); }

  public Entry getRandomEntry() { return inner.getRandomEntry(); }

  public boolean hasFulltextIndex() { return inner.hasFulltextIndex(); }
  public boolean hasTitleIndex() { return inner.hasTitleIndex(); }

  public boolean hasChecksum() { return inner.hasChecksum(); }
  public String getChecksum() { return inner.getChecksum(); }
  public boolean check() { return inner.check(); }

  public boolean isMultiPart() { return inner.isMultiPart(); }
  public boolean hasNewNamespaceScheme() { return inner.hasNewNamespaceScheme(); }

  public EntryIterator iterByPath() { return inner.iterByPath(); }
  public EntryIterator iterByTitle() { return inner.iterByTitle(); }
  public EntryIterator iterEfficient() { return inner.iterEfficient(); }
  public EntryIterator findByPath(String path) { return inner.findByPath(path); }
  public EntryIterator findByTitle(String path) { return inner.findByTitle(path); }

  public void dispose() { inner.dispose(); }
}
