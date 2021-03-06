/*

  This file is part of OpenFLUID software
  Copyright(c) 2007, INRA - Montpellier SupAgro


 == GNU General Public License Usage ==

  OpenFLUID is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  OpenFLUID is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with OpenFLUID. If not, see <http://www.gnu.org/licenses/>.


 == Other Usage ==

  Other Usage means a use of OpenFLUID that is inconsistent with the GPL
  license, and requires a written agreement between You and INRA.
  Licensees for Other Usage of OpenFLUID may use this file in accordance
  with the terms contained in the written agreement between You and INRA.
 
 */


/**
 @file DevStudioPreferencesManager.cpp
 @brief Implements ...

 @author Aline LIBRES <aline.libres@gmail.com>
 */


#include <QDir>

#include <openfluid/base/PreferencesManager.hpp>
#include <openfluid/base/Environment.hpp>

#include "DevStudioPreferencesManager.hpp"
#include "devstudioconfig.hpp"


OPENFLUID_SINGLETON_INITIALIZATION(DevStudioPreferencesManager)


// =====================================================================
// =====================================================================


DevStudioPreferencesManager::DevStudioPreferencesManager() :
    mp_Settings(nullptr)
{
  openfluid::base::Environment::init();

  switchWorkspace(openfluid::base::PreferencesManager::instance()->getBuilderWorkspacePath());
}


// =====================================================================
// =====================================================================


DevStudioPreferencesManager::~DevStudioPreferencesManager()
{
  delete mp_Settings;
}


// =====================================================================
// =====================================================================


void DevStudioPreferencesManager::switchWorkspace(const QString& NewAbsoluteWorkspacePath)
{
  QString WSConfFilename = QDir(NewAbsoluteWorkspacePath).filePath(WORKSPACE_CONF_FILE);

  if (mp_Settings)
  {
    delete mp_Settings;
  }

  mp_Settings = new QSettings(WSConfFilename, QSettings::IniFormat);
}


// =====================================================================
// =====================================================================


QStringList DevStudioPreferencesManager::getLastOpenWares()
{
  return mp_Settings->value("openfluid.workspace.waresdev/openwares", QStringList()).toStringList();
}


// =====================================================================
// =====================================================================


void DevStudioPreferencesManager::setLastOpenWares(const QStringList& OpenWaresAbsolutePath)
{
  mp_Settings->setValue("openfluid.workspace.waresdev/openwares",
                        OpenWaresAbsolutePath.isEmpty() ? QVariant("") : OpenWaresAbsolutePath);
  mp_Settings->sync();
}


// =====================================================================
// =====================================================================


QString DevStudioPreferencesManager::getLastActiveWare()
{
  return mp_Settings->value("openfluid.workspace.waresdev/activeware", "").toString();
}


// =====================================================================
// =====================================================================


void DevStudioPreferencesManager::setLastActiveWare(const QString& ActiveWareAbsolutePath)
{
  mp_Settings->setValue("openfluid.workspace.waresdev/activeware", ActiveWareAbsolutePath);
  mp_Settings->sync();
}


// =====================================================================
// =====================================================================


QString DevStudioPreferencesManager::getConfigBuildMode()
{
  return mp_Settings->value("openfluid.workspace.waresdev/buildmode", "").toString();
}


// =====================================================================
// =====================================================================


void DevStudioPreferencesManager::setConfigBuildMode(const QString& Mode)
{
  mp_Settings->setValue("openfluid.workspace.waresdev/buildmode", Mode);
}
