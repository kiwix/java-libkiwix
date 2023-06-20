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

import org.kiwix.libzim.Archive;
import org.kiwix.libzim.Searcher;
import org.kiwix.libzim.Search;
import java.util.stream.Stream;

public class TestSearcher
{
  private Searcher inner;
  public TestSearcher(TestArchive archive) throws Exception
  {
    inner = new Searcher(archive.inner());
  }

  public TestSearcher(TestArchive[] archives) throws Exception
  {
    inner = new Searcher(
      Stream.of(archives).map(a -> a.inner()).toArray(Archive[]::new)
    );
  }

  public TestSearcher addArchive(TestArchive archive) { inner.addArchive(archive.inner()); return this; }
  public TestSearch search(TestQuery query) { return new TestSearch(inner.search(query.inner())); }
  public void setVerbose(boolean verbose) { inner.setVerbose(verbose); }

  public void dispose() { inner.dispose(); }
}
