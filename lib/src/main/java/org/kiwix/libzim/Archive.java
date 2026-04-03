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

import java.io.FileDescriptor;
import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

public class Archive
{

  public Archive(String filename) throws ZimFileFormatException
  {
    setNativeArchive(filename);
  }

  public Archive(@NonNull String filename, @NonNull OpenConfig config) throws ZimFileFormatException {
    setNativeArchiveWithConfig(filename, config);
  }

  public Archive(@NonNull FileDescriptor fd) throws ZimFileFormatException
  {
    setNativeArchiveByFD(fd);
  }

  public Archive(@NonNull FileDescriptor fd, @NonNull OpenConfig openConfig) throws ZimFileFormatException
  {
    setNativeArchiveByFDWithConfig(fd, openConfig);
  }

  public Archive(FileDescriptor fd, long offset, long size)
          throws ZimFileFormatException
  {
    setNativeArchiveEmbedded(fd, offset, size);
  }

  public Archive(FileDescriptor fd, long offset, long size, OpenConfig openConfig)
          throws ZimFileFormatException
  {
    setNativeArchiveEmbeddedWithConfig(fd, offset, size, openConfig);
  }

  public Archive(FdInput fd)
  throws ZimFileFormatException
  {
    setNativeArchiveEmbeddedFd(fd);
  }

  public Archive(FdInput fd, OpenConfig openConfig)
          throws ZimFileFormatException
  {
    setNativeArchiveEmbeddedFdWithConfig(fd, openConfig);
  }

  public Archive(FdInput[] fds)
  throws ZimFileFormatException
  {
    setNativeArchiveEmbeddedFds(fds);
  }

  public Archive(FdInput[] fds, OpenConfig openConfig)
          throws ZimFileFormatException
  {
    setNativeArchiveEmbeddedFdsWithConfig(fds, openConfig);
  }

  @NonNull public native String getFilename();
  public native long getFilesize();
  public native int getAllEntryCount();
  public native int getEntryCount();
  public native int getArticleCount();
  public native int getMediaCount();
  @NonNull public native String getUuid();
  @NonNull public native String getMetadata(@NonNull String name) throws EntryNotFoundException;
  @NonNull public native Item getMetadataItem(@NonNull String name) throws EntryNotFoundException;
  @NonNull public native String[] getMetadataKeys();
  @Nullable public native Item getIllustrationItem(@NonNull IllustrationInfo info);
  @Nullable public native Item getIllustrationItem(int size);
  public native boolean hasIllustration(int size);
  @Deprecated
  @NonNull public native long[] getIllustrationSizes();

  @NonNull public native Entry getEntryByPath(@NonNull String path) throws EntryNotFoundException;
  @NonNull public native Entry getEntryByPath(int index) throws EntryNotFoundException;
  public native boolean hasEntryByPath(@NonNull String path);

  @NonNull public native Entry getEntryByTitle(@NonNull String title) throws EntryNotFoundException;
  @NonNull public native Entry getEntryByTitle(int index) throws EntryNotFoundException;
  public native boolean hasEntryByTitle(@NonNull String title);

  @NonNull public native Entry getEntryByClusterOrder(int index) throws EntryNotFoundException;

  @NonNull public native Entry getMainEntry() throws EntryNotFoundException;
  public native boolean hasMainEntry();

  @Nullable public native Entry getRandomEntry();

  public native boolean hasFulltextIndex();
  public native boolean hasTitleIndex();

  public native boolean hasChecksum();
  @NonNull public native String getChecksum();
  public native boolean check();

  public native boolean isMultiPart();
  public native boolean hasNewNamespaceScheme();

  @NonNull public native EntryIterator iterByPath();
  @NonNull public native EntryIterator iterByTitle();
  @NonNull public native EntryIterator iterEfficient();
  @NonNull public native EntryIterator findByPath(@NonNull String path);
  @NonNull public native EntryIterator findByTitle(@NonNull String path);
  public native long getDirentCacheMaxSize();
  public native long getDirentCacheCurrentSize();
  public native void setDirentCacheMaxSize(long nbDirents);
  public native long getClusterCacheMaxSize();
  public native long getClusterCacheCurrentSize();
  public native void setClusterCacheMaxSize(long sizeInBytes);


  private native void setNativeArchive(String filename);
  private native void setNativeArchiveWithConfig(String filename, OpenConfig openConfig);
  private native void setNativeArchiveByFD(FileDescriptor fd);
  private native void setNativeArchiveByFDWithConfig(FileDescriptor fd, OpenConfig openConfig);
  private native void setNativeArchiveEmbedded(FileDescriptor fd, long offset, long size);
  private native void setNativeArchiveEmbeddedWithConfig(FileDescriptor fd, long offset, long size, OpenConfig openConfig);
  private native void setNativeArchiveEmbeddedFd(FdInput fd);
  private native void setNativeArchiveEmbeddedFdWithConfig(FdInput fd, OpenConfig openConfig);
  private native void setNativeArchiveEmbeddedFds(FdInput[] fds);
  private native void setNativeArchiveEmbeddedFdsWithConfig(FdInput[] fds, OpenConfig openConfig);

  @Override
  protected void finalize() { dispose(); }


///--------- The wrapper thing
  // To delete our native wrapper
  public native void dispose();

  // A pointer (as a long) to a native Handle
  private long nativeHandle;
}
