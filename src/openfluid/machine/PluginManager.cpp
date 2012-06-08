/*
  This file is part of OpenFLUID software
  Copyright (c) 2007-2010 INRA-Montpellier SupAgro


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
  along with OpenFLUID.  If not, see <http://www.gnu.org/licenses/>.

  In addition, as a special exception, INRA gives You the additional right
  to dynamically link the code of OpenFLUID with code not covered
  under the GNU General Public License ("Non-GPL Code") and to distribute
  linked combinations including the two, subject to the limitations in this
  paragraph. Non-GPL Code permitted under this exception must only link to
  the code of OpenFLUID dynamically through the OpenFLUID libraries
  interfaces, and only for building OpenFLUID plugins. The files of
  Non-GPL Code may be link to the OpenFLUID libraries without causing the
  resulting work to be covered by the GNU General Public License. You must
  obey the GNU General Public License in all respects for all of the
  OpenFLUID code and other code used in conjunction with OpenFLUID
  except the Non-GPL Code covered by this exception. If you modify
  this OpenFLUID, you may extend this exception to your version of the file,
  but you are not obligated to do so. If you do not wish to provide this
  exception without modification, you must delete this exception statement
  from your version and license this OpenFLUID solely under the GPL without
  exception.


 == Other Usage ==

  Other Usage means a use of OpenFLUID that is inconsistent with the GPL
  license, and requires a written agreement between You and INRA.
  Licensees for Other Usage of OpenFLUID may use this file in accordance
  with the terms contained in the written agreement between You and INRA.
*/


/**
  @file
  @brief implements the plugins management class

  @author Jean-Christophe FABRE <fabrejc@supagro.inra.fr>
*/

#include <openfluid/machine/PluginManager.hpp>

#include <openfluid/base/RuntimeEnv.hpp>
#include <openfluid/base/PlugFunction.hpp>
#include <openfluid/machine/ModelItemInstance.hpp>

namespace openfluid { namespace machine {


PluginManager* PluginManager::mp_Singleton = NULL;


// =====================================================================
// =====================================================================


PluginManager::PluginManager()
{

}

// =====================================================================
// =====================================================================

PluginManager::~PluginManager()
{

}


// =====================================================================
// =====================================================================


PluginManager* PluginManager::getInstance()
{
  if (mp_Singleton == NULL) mp_Singleton = new PluginManager();
  return mp_Singleton;
}


// =====================================================================
// =====================================================================

openfluid::base::PluggableFunction* PluginManager::completePluginWithFunction(ModelItemInstance* Item)
{
  std::string PluginFilename = Item->Filename;

  if (m_LoadedPlugins.find(PluginFilename) == m_LoadedPlugins.end())
  {
    m_LoadedPlugins[PluginFilename] = new Glib::Module(PluginFilename,Glib::MODULE_BIND_LOCAL);
  }

  Glib::Module* PlugLib = m_LoadedPlugins[PluginFilename];


  // library loading
  if(*PlugLib)
  {
    void* FunctionSymbol;

    // checks if the handle proc exists
    if(PlugLib->get_symbol(PLUGFUNCTION_PROC_NAME,FunctionSymbol))
    {

      // hooks the handle proc
      openfluid::base::GetPluggableFunctionProc PlugProc = (openfluid::base::GetPluggableFunctionProc)FunctionSymbol;

      if (PlugProc != NULL)
      {
        Item->Function = PlugProc();

        if (Item->Function == NULL)
          throw openfluid::base::OFException("OpenFLUID framework","PluginManager::loadPluginFunction","Function from plugin file " + PluginFilename + " cannot be instanciated");

      }
      else throw openfluid::base::OFException("OpenFLUID framework","PluginManager::loadPluginFunction","Unable to find function in plugin file " + PluginFilename);
    }
    else throw openfluid::base::OFException("OpenFLUID framework","PluginManager::loadPluginFunction","Format error in plugin file " + PluginFilename);
  }
  else throw openfluid::base::OFException("OpenFLUID framework","PluginManager::loadPluginFunction","Unable to find plugin file " + PluginFilename);

  return Item->Function;
}


// =====================================================================
// =====================================================================


ModelItemInstance* PluginManager::buildUncompletedPluginContainer(std::string PluginFilename)
{
  std::string PluginFile = openfluid::base::RuntimeEnvironment::getInstance()->getPluginFullPath(PluginFilename);
  ModelItemInstance* Plug = NULL;

  if (m_LoadedPlugins.find(PluginFilename) == m_LoadedPlugins.end())
  {
    m_LoadedPlugins[PluginFilename] = new Glib::Module(PluginFile,Glib::MODULE_BIND_LOCAL);
  }

  Glib::Module* PlugLib = m_LoadedPlugins[PluginFilename];


  // library loading
  if(*PlugLib)
  {
    Plug = new ModelItemInstance();
    Plug->Filename = PluginFile;

    void* SDKVersionSymbol;

    if(PlugLib->get_symbol(PLUGSDKVERSION_PROC_NAME,SDKVersionSymbol))
    {
      openfluid::base::GetSDKVersionProc SDKProc;

      SDKProc = (openfluid::base::GetSDKVersionProc)SDKVersionSymbol;
      Plug->SDKCompatible = (openfluid::tools::CompareVersions(openfluid::config::FULL_VERSION,SDKProc(),false) == 0);
    }
    else Plug->SDKCompatible = false;


    if (Plug->SDKCompatible)
    {
      void* FunctionSymbol;
      void* SignatureSymbol;

      // checks if the handle proc exists
      if(PlugLib->get_symbol(PLUGFUNCTION_PROC_NAME,FunctionSymbol)
          && PlugLib->get_symbol(PLUGSIGNATURE_PROC_NAME,SignatureSymbol))
      {

        // hooks the handle proc
        openfluid::base::GetSignatureProc SignProc = (openfluid::base::GetSignatureProc)SignatureSymbol;


        if (SignProc != NULL)
        {
          Plug->Signature = SignProc();

          if (Plug->Signature == NULL)
            throw openfluid::base::OFException("OpenFLUID framework","PluginManager::buildUnloadedPluginContainer","Signature from plugin file " + PluginFilename + " cannot be instanciated");

            Plug->Function = 0;
        }
        else throw openfluid::base::OFException("OpenFLUID framework","PluginManager::buildUnloadedPluginContainer","Unable to find signature in plugin file " + PluginFilename);

      }
      else throw openfluid::base::OFException("OpenFLUID framework","PluginManager::buildUnloadedPluginContainer","Format error in plugin file " + PluginFilename);
    }
    else throw openfluid::base::OFException("OpenFLUID framework","PluginManager::buildUnloadedPluginContainer","Compatibility version mismatch for plugin file " + PluginFilename);
  }
  else throw openfluid::base::OFException("OpenFLUID framework","PluginManager::buildUnloadedPluginContainer","Unable to find plugin file " + PluginFilename);

  return Plug;
}


// =====================================================================
// =====================================================================


SignatureItemInstance* PluginManager::getSignatureFromPlugin(std::string PluginFilename)
{
  std::string PluginFile = openfluid::base::RuntimeEnvironment::getInstance()->getPluginFullPath(PluginFilename);
  SignatureItemInstance* Plug = NULL;

  if (m_LoadedPlugins.find(PluginFilename) == m_LoadedPlugins.end())
  {
    m_LoadedPlugins[PluginFilename] = new Glib::Module(PluginFile,Glib::MODULE_BIND_LOCAL);
  }


  Glib::Module* PlugLib = m_LoadedPlugins[PluginFilename];

  // library loading
  if(*PlugLib)
  {
    Plug = new ModelItemInstance();
    Plug->Filename = PluginFile;

    void* SDKVersionSymbol = 0;

      if(PlugLib->get_symbol(PLUGSDKVERSION_PROC_NAME,SDKVersionSymbol))
    {
      openfluid::base::GetSDKVersionProc SDKProc;

      SDKProc = (openfluid::base::GetSDKVersionProc)SDKVersionSymbol;

      Plug->SDKCompatible = (openfluid::tools::CompareVersions(openfluid::config::FULL_VERSION,SDKProc(),false) == 0);
    }
    else Plug->SDKCompatible = false;


    if (Plug->SDKCompatible)
    {
      void* FunctionSymbol = 0;
      void* SignatureSymbol = 0;

      // checks if the handle proc exists
      if(PlugLib->get_symbol(PLUGFUNCTION_PROC_NAME,FunctionSymbol)
          && PlugLib->get_symbol(PLUGSIGNATURE_PROC_NAME,SignatureSymbol))
      {

        // hooks the handle proc
        openfluid::base::GetSignatureProc SignProc = (openfluid::base::GetSignatureProc)SignatureSymbol;


        if (SignProc != NULL)
        {
          Plug->Signature = SignProc();

          if (Plug->Signature == NULL)
            throw openfluid::base::OFException("OpenFLUID framework","PluginManager::getSignatureFromPlugin","Signature from plugin file " + PluginFilename + " cannot be instanciated");

        }
        else throw openfluid::base::OFException("OpenFLUID framework","PluginManager::getSignatureFromPlugin","Unable to find signature in plugin file " + PluginFilename);
      }
      else throw openfluid::base::OFException("OpenFLUID framework","PluginManager::getSignatureFromPlugin","Format error in plugin file " + PluginFilename);
    }
  }
  else throw openfluid::base::OFException("OpenFLUID framework","PluginManager::getSignatureFromPlugin","Unable to find plugin file " + PluginFilename);

  return Plug;
}

// =====================================================================
// =====================================================================


ArrayOfSignatureItemInstance PluginManager::getAvailableFunctions(const std::string Pattern)
{
  ArrayOfSignatureItemInstance PluginsContainers;
  std::vector<std::string> PluginsPaths = openfluid::base::RuntimeEnvironment::getInstance()->getPluginsPaths();
  std::vector<std::string> PluginFiles;
  std::vector<std::string> TmpFiles;
  unsigned int i,j;


  for (i=0;i<PluginsPaths.size();i++)
  {
    TmpFiles = openfluid::tools::GetFilesByExt(PluginsPaths[i],openfluid::config::PLUGINS_EXT,false,true);
    for (j=0;j<TmpFiles.size();j++) PluginFiles.push_back(TmpFiles[j]);
  }


  SignatureItemInstance* CurrentPlug;

  for (i=0;i<PluginFiles.size();i++)
  {
    CurrentPlug = getSignatureFromPlugin(PluginFiles[i]);

    if (CurrentPlug != NULL && CurrentPlug->SDKCompatible)
    {
      if (Pattern != "")
      {
        if (openfluid::tools::WildcardMatching(Pattern,CurrentPlug->Signature->ID))
          PluginsContainers.push_back(CurrentPlug);
      }
      else PluginsContainers.push_back(CurrentPlug);
    }
  }

  return PluginsContainers;
}


// =====================================================================
// =====================================================================


ModelItemInstance* PluginManager::getUncompletedPlugin(std::string PluginName)
{
  ModelItemInstance* Plug = buildUncompletedPluginContainer(PluginName+openfluid::config::PLUGINS_EXT);

  if (Plug != NULL && Plug->SDKCompatible) return Plug;

  return NULL;
}


// =====================================================================
// =====================================================================


void PluginManager::unloadAllPlugins()
{
  std::map<std::string,Glib::Module*>::iterator it;

  for (it=m_LoadedPlugins.begin();it != m_LoadedPlugins.end(); ++it)
  {
    delete (it->second);
  }

  m_LoadedPlugins.clear();
}

// =====================================================================
// =====================================================================


} } //namespaces


