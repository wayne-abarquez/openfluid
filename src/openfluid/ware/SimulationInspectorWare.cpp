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
  @file SimulationInspectorWare.cpp

  @author Jean-Christophe FABRE <jean-christophe.fabre@supagro.inra.fr>
 */


#include <openfluid/ware/SimulationInspectorWare.hpp>
#include <openfluid/tools/DataHelpers.hpp>

namespace openfluid { namespace ware {

// =====================================================================
// =====================================================================


bool SimulationInspectorWare::IsUnitIDInPtrList(const openfluid::core::UnitsPtrList_t* UnitsList,
                                                const openfluid::core::UnitID_t& ID)
{
  if (UnitsList == NULL) return false;

  bool Found = false;
  openfluid::core::UnitsPtrList_t::const_iterator UnitsIt = UnitsList->begin();

  while (!Found && UnitsIt != UnitsList->end())
  {
    if ((*UnitsIt)->getID() == ID) Found = true;
    UnitsIt++;
  }

  return Found;
}


// =====================================================================
// =====================================================================


void SimulationInspectorWare::OPENFLUID_GetAttribute(const openfluid::core::SpatialUnit *UnitPtr,
                            const openfluid::core::AttributeName_t& AttrName,
                            openfluid::core::StringValue& Val) const
{
  REQUIRE_SIMULATION_STAGE_GE(openfluid::base::SimulationStatus::PREPAREDATA,
                             "SimulationInspectorWare::OPENFLUID_GetAttribute","Attributes cannot be accessed during INITPARAMS stage")

  if (UnitPtr != NULL)
  {
    if (!UnitPtr->attributes()->getValue(AttrName,Val))
      throw openfluid::base::FrameworkException("SimulationInspectorWare::OPENFLUID_GetAttribute","StringValue for attribute "+ AttrName +" does not exist");
  }
  else throw openfluid::base::FrameworkException("SimulationInspectorWare::OPENFLUID_GetAttribute","Unit is NULL");
}


// =====================================================================
// =====================================================================


void SimulationInspectorWare::OPENFLUID_GetAttribute(const openfluid::core::SpatialUnit *UnitPtr,
                                    const openfluid::core::AttributeName_t& AttrName,
                                    openfluid::core::DoubleValue& Val) const
{
  double TmpVal;
  OPENFLUID_GetAttribute(UnitPtr,AttrName,TmpVal);
  Val.set(TmpVal);
}


// =====================================================================
// =====================================================================


void SimulationInspectorWare::OPENFLUID_GetAttribute(const openfluid::core::SpatialUnit *UnitPtr,
                                    const openfluid::core::AttributeName_t& AttrName,
                                    openfluid::core::VectorValue& Val) const
{
  openfluid::core::StringValue TmpVal;
  OPENFLUID_GetAttribute(UnitPtr,AttrName,TmpVal);
  TmpVal.toVectorValue(Val.getStreamSeparator(1),Val);
}


// =====================================================================
// =====================================================================


void SimulationInspectorWare::OPENFLUID_GetAttribute(const openfluid::core::SpatialUnit *UnitPtr,
                            const openfluid::core::AttributeName_t& AttrName,
                            openfluid::core::MatrixValue& Val) const
{
  openfluid::core::StringValue TmpVal;
  OPENFLUID_GetAttribute(UnitPtr,AttrName,TmpVal);
  TmpVal.toMatrixValue(Val.getStreamSeparator(1),Val.getStreamSeparator(2),Val);
}


// =====================================================================
// =====================================================================


void SimulationInspectorWare::OPENFLUID_GetAttribute(const openfluid::core::SpatialUnit *UnitPtr,
                                    const openfluid::core::AttributeName_t& AttrName,
                                    double& Val) const
{
  REQUIRE_SIMULATION_STAGE_GE(openfluid::base::SimulationStatus::PREPAREDATA,
                               "SimulationInspectorWare::OPENFLUID_GetAttribute","Attributes cannot be accessed during INITPARAMS stage")

  if (UnitPtr != NULL)
  {
    if (!UnitPtr->attributes()->getValueAsDouble(AttrName,Val))
      throw openfluid::base::FrameworkException("SimulationInspectorWare::OPENFLUID_GetAttribute","Double value for attribute "+ AttrName +" does not exist");
  }
  else throw openfluid::base::FrameworkException("SimulationInspectorWare::OPENFLUID_GetAttribute","Unit is NULL");
}


// =====================================================================
// =====================================================================


void SimulationInspectorWare::OPENFLUID_GetAttribute(const openfluid::core::SpatialUnit *UnitPtr,
                                    const openfluid::core::AttributeName_t& AttrName,
                                    long& Val) const
{
  REQUIRE_SIMULATION_STAGE_GE(openfluid::base::SimulationStatus::PREPAREDATA,
                                 "SimulationInspectorWare::OPENFLUID_GetAttribute","Attributes cannot be accessed during INITPARAMS stage")

  if (UnitPtr != NULL)
  {
    if (!UnitPtr->attributes()->getValueAsLong(AttrName,Val))
      throw openfluid::base::FrameworkException("SimulationInspectorWare::OPENFLUID_GetAttribute","Long integer for attribute "+ AttrName +" does not exist");
  }
  else throw openfluid::base::FrameworkException("SimulationInspectorWare::OPENFLUID_GetAttribute","Unit is NULL");
}


// =====================================================================
// =====================================================================


void SimulationInspectorWare::OPENFLUID_GetAttribute(const openfluid::core::SpatialUnit *UnitPtr,
                                    const openfluid::core::AttributeName_t& AttrName,
                                    std::string& Val) const
{
  REQUIRE_SIMULATION_STAGE_GE(openfluid::base::SimulationStatus::PREPAREDATA,
                              "SimulationInspectorWare::OPENFLUID_GetAttribute","Attributes cannot be accessed during INITPARAMS stage")

  if (UnitPtr != NULL)
  {
    if (!UnitPtr->attributes()->getValue(AttrName,Val))
      throw openfluid::base::FrameworkException("SimulationInspectorWare::OPENFLUID_GetAttribute","String value for attribute "+ AttrName +" does not exist");
  }
  else throw openfluid::base::FrameworkException("SimulationInspectorWare::OPENFLUID_GetAttribute","Unit is NULL");
}


// =====================================================================
// =====================================================================


bool SimulationInspectorWare::OPENFLUID_IsAttributeExist(const openfluid::core::SpatialUnit *UnitPtr,
                               const openfluid::core::AttributeName_t& AttrName) const
{
  REQUIRE_SIMULATION_STAGE_GE(openfluid::base::SimulationStatus::PREPAREDATA,
                              "SimulationInspectorWare::OPENFLUID_IsAttributeExist","Attributes cannot be accessed during INITPARAMS stage");

  if (UnitPtr != NULL)
    return UnitPtr->attributes()->isAttributeExist(AttrName);

  throw openfluid::base::FrameworkException("SimulationInspectorWare::OPENFLUID_IsAttributeExist","Unit is NULL");
  return false;
}


// =====================================================================
// =====================================================================


void SimulationInspectorWare::OPENFLUID_GetVariable(const openfluid::core::SpatialUnit *UnitPtr,
                                        const openfluid::core::VariableName_t& VarName,
                                        const openfluid::core::TimeIndex_t Index,
                                        openfluid::core::Value& Val) const
{
  REQUIRE_SIMULATION_STAGE_GE(openfluid::base::SimulationStatus::INITIALIZERUN,
                              "SimulationInspectorWare::OPENFLUID_GetVariable","Variables can be accessed using time index only during INITIALIERUN, RUNSTEP and FINALIZERUN stages")

  if (UnitPtr != NULL)
  {
    if (!UnitPtr->variables()->getValue(VarName,Index,&Val))
    {
      std::string TimeStr;
      openfluid::tools::convertValue(Index,&TimeStr);
      throw openfluid::base::FrameworkException("SimulationInspectorWare::OPENFLUID_GetVariable","Value for variable "+ VarName +" does not exist or is not right type at time index "+ TimeStr);
    }
  }
  else throw openfluid::base::FrameworkException("SimulationInspectorWare::OPENFLUID_GetVariable","Unit is NULL");
}


// =====================================================================
// =====================================================================


void SimulationInspectorWare::OPENFLUID_GetVariable(const openfluid::core::SpatialUnit* UnitPtr,
                                       const openfluid::core::VariableName_t& VarName,
                                       const openfluid::core::TimeIndex_t Index,
                                       double& Val) const
{
  openfluid::core::DoubleValue TmpVal(Val);
  OPENFLUID_GetVariable(UnitPtr,VarName,Index,TmpVal);
  Val = TmpVal.get();
}


// =====================================================================
// =====================================================================


void SimulationInspectorWare::OPENFLUID_GetVariable(const openfluid::core::SpatialUnit* UnitPtr,
                                       const openfluid::core::VariableName_t& VarName,
                                       const openfluid::core::TimeIndex_t Index,
                                       long& Val) const
{
  openfluid::core::IntegerValue TmpVal(Val);
  OPENFLUID_GetVariable(UnitPtr,VarName,Index,TmpVal);
  Val = TmpVal.get();
}


// =====================================================================
// =====================================================================


void SimulationInspectorWare::OPENFLUID_GetVariable(const openfluid::core::SpatialUnit* UnitPtr,
                                       const openfluid::core::VariableName_t& VarName,
                                       const openfluid::core::TimeIndex_t Index,
                                       bool& Val) const
{
  openfluid::core::BooleanValue TmpVal(Val);
  OPENFLUID_GetVariable(UnitPtr,VarName,Index,TmpVal);
  Val = TmpVal.get();
}


// =====================================================================
// =====================================================================


void SimulationInspectorWare::OPENFLUID_GetVariable(const openfluid::core::SpatialUnit* UnitPtr,
                                       const openfluid::core::VariableName_t& VarName,
                                       const openfluid::core::TimeIndex_t Index,
                                       std::string& Val) const
{
  openfluid::core::StringValue TmpVal(Val);
  OPENFLUID_GetVariable(UnitPtr,VarName,Index,TmpVal);
  Val = TmpVal.get();
}


// =====================================================================
// =====================================================================


void SimulationInspectorWare::OPENFLUID_GetVariable(const openfluid::core::SpatialUnit *UnitPtr,
                                        const openfluid::core::VariableName_t& VarName,
                                        openfluid::core::Value& Val) const
{
  REQUIRE_SIMULATION_STAGE_GE(openfluid::base::SimulationStatus::INITIALIZERUN,
                              "SimulationInspectorWare::OPENFLUID_GetVariable","Variables can be accessed only during INITIALIZERUN, RUNSTEP and FINALIZERUN stages")

  if (UnitPtr != NULL)
  {
    if (!UnitPtr->variables()->getValue(VarName,OPENFLUID_GetCurrentTimeIndex(),&Val))
    {
      std::string TimeStr;
      openfluid::tools::convertValue(OPENFLUID_GetCurrentTimeIndex(),&TimeStr);
      throw openfluid::base::FrameworkException("SimulationInspectorWare::OPENFLUID_GetVariable","Value for variable "+ VarName +" does not exist or is not right type at time index "+ TimeStr);
    }
  }
  else throw openfluid::base::FrameworkException("SimulationInspectorWare::OPENFLUID_GetVariable","Unit is NULL");
}


// =====================================================================
// =====================================================================


void SimulationInspectorWare::OPENFLUID_GetVariable(const openfluid::core::SpatialUnit* UnitPtr,
                                       const openfluid::core::VariableName_t& VarName,
                                       double& Val) const
{
  openfluid::core::DoubleValue TmpVal(Val);
  OPENFLUID_GetVariable(UnitPtr,VarName,TmpVal);
  Val = TmpVal.get();
}


// =====================================================================
// =====================================================================


void SimulationInspectorWare::OPENFLUID_GetVariable(const openfluid::core::SpatialUnit* UnitPtr,
                                       const openfluid::core::VariableName_t& VarName,
                                       long& Val) const
{
  openfluid::core::IntegerValue TmpVal(Val);
  OPENFLUID_GetVariable(UnitPtr,VarName,TmpVal);
  Val = TmpVal.get();
}


// =====================================================================
// =====================================================================


void SimulationInspectorWare::OPENFLUID_GetVariable(const openfluid::core::SpatialUnit* UnitPtr,
                                       const openfluid::core::VariableName_t& VarName,
                                       bool& Val) const
{
  openfluid::core::BooleanValue TmpVal(Val);
  OPENFLUID_GetVariable(UnitPtr,VarName,TmpVal);
  Val = TmpVal.get();
}


// =====================================================================
// =====================================================================


void SimulationInspectorWare::OPENFLUID_GetVariable(const openfluid::core::SpatialUnit* UnitPtr,
                                       const openfluid::core::VariableName_t& VarName,
                                       std::string& Val) const
{
  openfluid::core::StringValue TmpVal(Val);
  OPENFLUID_GetVariable(UnitPtr,VarName,TmpVal);
  Val = TmpVal.get();
}


// =====================================================================
// =====================================================================


void SimulationInspectorWare::OPENFLUID_GetLatestVariable(const openfluid::core::SpatialUnit* UnitPtr,
                                 const openfluid::core::VariableName_t& VarName,
                                 openfluid::core::IndexedValue& IndVal)
{
  REQUIRE_SIMULATION_STAGE_GE(openfluid::base::SimulationStatus::INITIALIZERUN,
                              "SimulationInspectorWare::OPENFLUID_GetLatestVariable","Variables can be accessed only during INITIALIZERUN, RUNSTEP and FINALIZERUN stages")

  if (UnitPtr != NULL)
   {
     if (!UnitPtr->variables()->getLatestIndexedValue(VarName,IndVal))
     {
       std::string TimeStr;
       openfluid::tools::convertValue(OPENFLUID_GetCurrentTimeIndex(),&TimeStr);
       throw openfluid::base::FrameworkException("SimulationInspectorWare::OPENFLUID_GetLatestVariable","Indexed value for variable "+ VarName +" does not exist or is empty at time index "+ TimeStr);
     }
   }
   else throw openfluid::base::FrameworkException("SimulationInspectorWare::OPENFLUID_GetLatestVariable","Unit is NULL");

}


// =====================================================================
// =====================================================================


void SimulationInspectorWare::OPENFLUID_GetLatestVariables(const openfluid::core::SpatialUnit* UnitPtr,
                                 const openfluid::core::VariableName_t& VarName,
                                 const openfluid::core::TimeIndex_t BeginIndex,
                                 openfluid::core::IndexedValueList& IndValList)
{
  REQUIRE_SIMULATION_STAGE_GE(openfluid::base::SimulationStatus::INITIALIZERUN,
                              "SimulationInspectorWare::OPENFLUID_GetLatestVariables","Variables lists can be accessed only during RUNSTEP and FINALIZERUN stages")

  if (UnitPtr != NULL)
   {
     if (!UnitPtr->variables()->getLatestIndexedValues(VarName,BeginIndex,IndValList))
     {
       std::string TimeStr;
       openfluid::tools::convertValue(OPENFLUID_GetCurrentTimeIndex(),&TimeStr);
       throw openfluid::base::FrameworkException("SimulationInspectorWare::OPENFLUID_GetLatestVariables","Indexed values for variable "+ VarName +" does not exist or is empty at time index "+ TimeStr);
     }
   }
   else throw openfluid::base::FrameworkException("SimulationInspectorWare::OPENFLUID_GetLatestVariables","Unit is NULL");
}


// =====================================================================
// =====================================================================


void SimulationInspectorWare::OPENFLUID_GetVariables(const openfluid::core::SpatialUnit* UnitPtr,
                            const openfluid::core::VariableName_t& VarName,
                            const openfluid::core::TimeIndex_t BeginIndex,
                            const openfluid::core::TimeIndex_t EndIndex,
                            openfluid::core::IndexedValueList& IndValList)
{
  REQUIRE_SIMULATION_STAGE_GE(openfluid::base::SimulationStatus::RUNSTEP,
                              "SimulationInspectorWare::OPENFLUID_GetVariables","Variables lists can be accessed only during RUNSTEP and FINALIZERUN stages")

  if (UnitPtr != NULL)
   {
     if (!UnitPtr->variables()->getIndexedValues(VarName,BeginIndex,EndIndex,IndValList))
     {
       std::string TimeStr;
       openfluid::tools::convertValue(OPENFLUID_GetCurrentTimeIndex(),&TimeStr);
       throw openfluid::base::FrameworkException("SimulationInspectorWare::OPENFLUID_GetVariables","Indexed values for variable "+ VarName +" does not exist or is empty at time index "+ TimeStr);
     }
   }
   else throw openfluid::base::FrameworkException("SimulationInspectorWare::OPENFLUID_GetVariables","Unit is NULL");
}


// =====================================================================
// =====================================================================


bool SimulationInspectorWare::OPENFLUID_IsVariableExist(const openfluid::core::SpatialUnit *UnitPtr,
                                        const openfluid::core::VariableName_t& VarName) const
{
  REQUIRE_SIMULATION_STAGE_GE(openfluid::base::SimulationStatus::INITIALIZERUN,
                              "SimulationInspectorWare::OPENFLUID_IsVariableExist","Variables can be accessed only during INITIALIZERUN, RUNSTEP and FINALIZERUN stages")

  return (UnitPtr != NULL && UnitPtr->variables()->isVariableExist(VarName));
}


// =====================================================================
// =====================================================================


bool SimulationInspectorWare::OPENFLUID_IsVariableExist(const openfluid::core::SpatialUnit *UnitPtr,
                                        const openfluid::core::VariableName_t& VarName,
                                        const openfluid::core::TimeIndex_t Index) const
{
  REQUIRE_SIMULATION_STAGE_GE(openfluid::base::SimulationStatus::INITIALIZERUN,
                              "SimulationInspectorWare::OPENFLUID_IsVariableExist","Variables can be accessed using time index only during INITIALIZERUN, RUNSTEP and FINALIZERUN stages")

   return (UnitPtr != NULL && UnitPtr->variables()->isVariableExist(VarName,Index));
}


// =====================================================================
// =====================================================================


bool SimulationInspectorWare::OPENFLUID_IsVariableExist(const openfluid::core::SpatialUnit *UnitPtr,
                               const openfluid::core::VariableName_t& VarName,
                               const openfluid::core::TimeIndex_t Index,
                               const openfluid::core::Value::Type ValueType) const
{
  REQUIRE_SIMULATION_STAGE_GE(openfluid::base::SimulationStatus::INITIALIZERUN,
                              "SimulationInspectorWare::OPENFLUID_IsVariableExist","Variables can be accessed using time index only during INITIALIZERUN, RUNSTEP and FINALIZERUN stages")

  return (UnitPtr != NULL && UnitPtr->variables()->isVariableExist(VarName,Index,ValueType));
}


// =====================================================================
// =====================================================================


bool SimulationInspectorWare::OPENFLUID_IsTypedVariableExist(const openfluid::core::SpatialUnit *UnitPtr,
                                        const openfluid::core::VariableName_t& VarName,
                                        const openfluid::core::Value::Type VarType) const
{
  REQUIRE_SIMULATION_STAGE_GE(openfluid::base::SimulationStatus::INITIALIZERUN,
                              "SimulationInspectorWare::OPENFLUID_IsTypedVariableExist","Variables can be accessed only during INITIALIZERUN, RUNSTEP and FINALIZERUN stages")

  return (UnitPtr != NULL && UnitPtr->variables()->isTypedVariableExist(VarName,VarType));
}


// =====================================================================
// =====================================================================


bool SimulationInspectorWare::OPENFLUID_IsTypedVariableExist(const openfluid::core::SpatialUnit *UnitPtr,
                                        const openfluid::core::VariableName_t& VarName,
                                        const openfluid::core::TimeIndex_t Index,
                                        const openfluid::core::Value::Type VarType) const
{
  REQUIRE_SIMULATION_STAGE_GE(openfluid::base::SimulationStatus::INITIALIZERUN,
                              "SimulationInspectorWare::OPENFLUID_IsTypedVariableExist","Variables can be accessed using time index only during INITIALIZERUN, RUNSTEP and FINALIZERUN stages")

  return (UnitPtr != NULL && UnitPtr->variables()->isTypedVariableExist(VarName,Index,VarType));
}


// =====================================================================
// =====================================================================


void SimulationInspectorWare::OPENFLUID_GetEvents(const openfluid::core::SpatialUnit *UnitPtr,
                                            const openfluid::core::DateTime BeginDate,
                                            const openfluid::core::DateTime EndDate,
                                            openfluid::core::EventsCollection& Events) const
{
  REQUIRE_SIMULATION_STAGE_GE(openfluid::base::SimulationStatus::PREPAREDATA,
                              "SimulationInspectorWare::OPENFLUID_GetEvents","Events cannot be accessed during INITPARAMS stage")


  if (UnitPtr != NULL)
    UnitPtr->events()->getEventsBetween(BeginDate,EndDate,Events);

  else throw openfluid::base::FrameworkException("SimulationInspectorWare::OPENFLUID_GetEvents","Unit is NULL");
}


// =====================================================================
// =====================================================================


bool SimulationInspectorWare::OPENFLUID_IsUnitExist(openfluid::core::UnitClass_t ClassName,
                                              openfluid::core::UnitID_t ID) const
{
  return (mp_SpatialData->spatialUnit(ClassName,ID) != NULL);
}


// =====================================================================
// =====================================================================


bool SimulationInspectorWare::OPENFLUID_IsUnitClassExist(openfluid::core::UnitClass_t ClassName) const
{
  return mp_SpatialData->isUnitsClassExist(ClassName);
}


// =====================================================================
// =====================================================================


bool SimulationInspectorWare::OPENFLUID_GetUnitsCount(const openfluid::core::UnitClass_t ClassName,
                                                unsigned int& UnitsCount) const
{
  UnitsCount = 0;
  if (mp_SpatialData->isUnitsClassExist(ClassName))
  {
    UnitsCount = mp_SpatialData->spatialUnits(ClassName)->list()->size();
    return true;
  }
  else return false;
}


// =====================================================================
// =====================================================================


void SimulationInspectorWare::OPENFLUID_GetUnitsCount(unsigned int& UnitsCount) const
{
  UnitsCount = 0;
  openfluid::core::UnitsListByClassMap_t::const_iterator UnitsIt;

  for (UnitsIt = mp_SpatialData->allSpatialUnitsByClass()->begin(); UnitsIt != mp_SpatialData->allSpatialUnitsByClass()->end();++UnitsIt )
  {
    UnitsCount = UnitsCount + (*UnitsIt).second.list()->size();
  }
}


// =====================================================================
// =====================================================================


bool SimulationInspectorWare::OPENFLUID_GetUnit(const openfluid::core::UnitClass_t& ClassName,
                                          const openfluid::core::UnitID_t& ID,
                                          openfluid::core::SpatialUnit* aUnit) const
{
  aUnit =  const_cast<openfluid::core::SpatialUnit*>(mp_SpatialData->spatialUnit(ClassName,ID));
  return (aUnit != NULL);
}


// =====================================================================
// =====================================================================


openfluid::core::SpatialUnit* SimulationInspectorWare::OPENFLUID_GetUnit(const openfluid::core::UnitClass_t& ClassName,
                                                            const openfluid::core::UnitID_t& ID) const
{
  return mp_SpatialData->spatialUnit(ClassName,ID);
}


// =====================================================================
// =====================================================================

bool SimulationInspectorWare::OPENFLUID_IsUnitConnectedTo(openfluid::core::SpatialUnit* aUnit,
                                                    const openfluid::core::UnitClass_t& ClassNameTo,
                                                    const openfluid::core::UnitID_t& IDTo) const
{
  if (aUnit == NULL || !mp_SpatialData->isUnitsClassExist(ClassNameTo)) return false;
  return IsUnitIDInPtrList(aUnit->toSpatialUnits(ClassNameTo),IDTo);
}


// =====================================================================
// =====================================================================


bool SimulationInspectorWare::OPENFLUID_IsUnitConnectedFrom(openfluid::core::SpatialUnit* aUnit,
                                                      const openfluid::core::UnitClass_t& ClassNameFrom,
                                                      const openfluid::core::UnitID_t& IDFrom) const
{
  if (aUnit == NULL || !mp_SpatialData->isUnitsClassExist(ClassNameFrom)) return false;
  return IsUnitIDInPtrList(aUnit->fromSpatialUnits(ClassNameFrom),IDFrom);
}


// =====================================================================
// =====================================================================


bool SimulationInspectorWare::OPENFLUID_IsUnitChildOf(openfluid::core::SpatialUnit* aUnit,
                                                const openfluid::core::UnitClass_t& ClassNameParent,
                                                const openfluid::core::UnitID_t& IDParent) const
{
  if (aUnit == NULL || !mp_SpatialData->isUnitsClassExist(ClassNameParent)) return false;
  return IsUnitIDInPtrList(aUnit->parentSpatialUnits(ClassNameParent),IDParent);
}


// =====================================================================
// =====================================================================


bool SimulationInspectorWare::OPENFLUID_IsUnitParentOf(openfluid::core::SpatialUnit* aUnit,
                                                 const openfluid::core::UnitClass_t& ClassNameChild,
                                                 const openfluid::core::UnitID_t& IDChild) const
{
  if (aUnit == NULL || !mp_SpatialData->isUnitsClassExist(ClassNameChild)) return false;
  return IsUnitIDInPtrList(aUnit->childSpatialUnits(ClassNameChild),IDChild);
}



} } // openfluid::ware

