/*
 * Copyright (C) 2019 Matthieu Gautier <mgautier@kymeria.fr>
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
import org.kiwix.libkiwix.Server;

public class TestServer
{
  private Server inner;

  public void setRoot(String root) { inner.setRoot(root); }
  public void setAddress(String address) { inner.setAddress(address); }

  public String[] getServerAccessUrls() { return inner.getServerAccessUrls(); }
  public void setPort(int port) { inner.setPort(port); }
  public void setNbThreads(int nbTreads) { inner.setNbThreads(nbTreads); }
  public void setTaskbar(boolean withTaskBar, boolean witLibraryButton) { inner.setTaskbar(withTaskBar, witLibraryButton); }
  public void setBlockExternalLinks(boolean blockExternalLinks) { inner.setBlockExternalLinks(blockExternalLinks); }
  public boolean start() { return inner.start(); }
  public void stop() { inner.stop(); }
  public TestServer(TestLibrary library)
  {
    inner = new Server(library.inner());
  }
}
