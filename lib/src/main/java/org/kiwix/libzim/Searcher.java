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
import org.kiwix.libzim.Archive;
import org.kiwix.libzim.Search;
import org.kiwix.libzim.Query;
import java.io.FileDescriptor;
import org.kiwix.Wrapper;

public class Searcher extends Wrapper
{

  public Searcher(Archive archive) throws Exception
  {
    super(buildNativeSearcher(archive));
  }

  public Searcher(Archive[] archives) throws Exception
  {
    super(buildNativeSearcherMulti(archives));
  }

  public native Searcher addArchive(Archive archive);
  public native Search search(Query query);
  public native void setVerbose(boolean verbose);

  private native static Wrapper.Resource buildNativeSearcher(Archive archive);
  private native static Wrapper.Resource buildNativeSearcherMulti(Archive[] archives);
}
