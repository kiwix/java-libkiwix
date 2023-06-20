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

import org.kiwix.libzim.Search;
import org.kiwix.libzim.SearchIterator;

public class TestSearch
{
  private Search inner;
  public TestSearch(Search _inner) { inner = _inner; }
  public TestSearchIterator getResults(int start, int maxResults) { return new TestSearchIterator(inner.getResults(start, maxResults)); }
  public long getEstimatedMatches() { return inner.getEstimatedMatches(); }
}
