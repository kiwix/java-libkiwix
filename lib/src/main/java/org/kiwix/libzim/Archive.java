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

import org.kiwix.libzim.ZimFileFormatException;
import org.kiwix.libzim.Entry;
import org.kiwix.libzim.Item;
import org.kiwix.libzim.EntryIterator;
import java.io.FileDescriptor;

public class Archive
{

  public Archive(String filename) throws ZimFileFormatException
  {
    setNativeArchive(filename);
  }

  public Archive(FileDescriptor fd) throws ZimFileFormatException
  {
    setNativeArchiveByFD(fd);
  }

  public Archive(FileDescriptor fd, long offset, long size)
          throws ZimFileFormatException
  {
    setNativeArchiveEmbedded(fd, offset, size);
  }

  public native String getFilename();
  public native long getFilesize();
  public native int getAllEntryCount();
  public native int getEntryCount();
  public native int getArticleCount();
  public native int getMediaCount();
  public native String getUuid();
  public native String getMetadata(String name) throws EntryNotFoundException;
  public native Item getMetadataItem(String name) throws EntryNotFoundException;
  public native String[] getMetadataKeys();

  public native Item getIllustrationItem(int size);
  public native boolean hasIllustration(int size);
  public native long[] getIllustrationSizes();

  public native Entry getEntryByPath(String path) throws EntryNotFoundException;
  public native Entry getEntryByPath(int index) throws EntryNotFoundException;
  public native boolean hasEntryByPath(String path);

  public native Entry getEntryByTitle(String title) throws EntryNotFoundException;
  public native Entry getEntryByTitle(int index) throws EntryNotFoundException;
  public native boolean hasEntryByTitle(String title);

  public native Entry getEntryByClusterOrder(int index) throws EntryNotFoundException;

  public native Entry getMainEntry() throws EntryNotFoundException;
  public native boolean hasMainEntry();

  public native Entry getRandomEntry();

  public native boolean hasFulltextIndex();
  public native boolean hasTitleIndex();

  public native boolean hasChecksum();
  public native String getChecksum();
  public native boolean check();

  public native boolean isMultiPart();
  public native boolean hasNewNamespaceScheme();

  public native EntryIterator iterByPath();
  public native EntryIterator iterByTitle();
  public native EntryIterator iterEfficient();
  public native EntryIterator findByPath(String path);
  public native EntryIterator findByTitle(String path);


  private native void setNativeArchive(String filename);
  private native void setNativeArchiveByFD(FileDescriptor fd);
  private native void setNativeArchiveEmbedded(FileDescriptor fd, long offset, long size);

  @Override
  protected void finalize() { dispose(); }


///--------- The wrapper thing
  // To delete our native wrapper
  public native void dispose();

  // A pointer (as a long) to a native Handle
  private long nativeHandle;
}
