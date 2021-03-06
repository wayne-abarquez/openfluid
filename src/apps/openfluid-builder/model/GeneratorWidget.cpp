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
  @file GeneratorWidget.cpp

  @author Jean-Christophe FABRE <jean-christophe.fabre@inra.fr>
*/


#include <openfluid/machine/SimulatorSignatureRegistry.hpp>
#include "builderconfig.hpp"

#include "ui_WareWidget.h"
#include "GeneratorWidget.hpp"
#include "ParameterWidget.hpp"


GeneratorWidget::GeneratorWidget(QWidget* Parent,
                                 openfluid::fluidx::ModelItemDescriptor* Desc,
                                 const openfluid::ware::WareID_t& ID,
                                 int Index,
                                 const openfluid::machine::ModelItemSignatureInstance* SignInstance):
  ModelItemWidget(Parent,Desc,ID,tr("Generator"),BUILDER_GENERATOR_BGCOLOR, Index),
  mp_SignInstance(SignInstance)
{  
  refresh();
  ui->AddParamButton->setVisible(false);
  ui->ParameterizationSwitchLabel->setVisible(false);
}


// =====================================================================
// =====================================================================


GeneratorWidget::~GeneratorWidget()
{

}


// =====================================================================
// =====================================================================


void GeneratorWidget::updateParametersList()
{
  createParamWidgetsFromSignature(mp_SignInstance);
}


// =====================================================================
// =====================================================================


void GeneratorWidget::refresh()
{

  if (mp_SignInstance != nullptr)
  {
    setAvailableWare(true);

    QString DimStr = tr("scalar");
    if (static_cast<const openfluid::fluidx::GeneratorDescriptor*>(mp_Desc)->getVariableSize() > 1)
    {
      DimStr = tr("vector");
    }

    ui->NameLabel->setText(
        tr("Produces %1 variable %2 on %3 (%4)")
        .arg(DimStr)
        .arg(QString::fromStdString(static_cast<const openfluid::fluidx::GeneratorDescriptor*>(mp_Desc)
                                    ->getVariableName()))
        .arg(QString::fromStdString(static_cast<const openfluid::fluidx::GeneratorDescriptor*>(mp_Desc)
                                    ->getUnitsClass()))
        .arg(QString::fromStdString(mp_SignInstance->Signature->Name)));

    // TODO add produced variable in signature
    ui->InfosSideWidget->update(mp_SignInstance);

    updateParametersList();
  }
  else
  {
    setAvailableWare(false);
    ui->NameLabel->setText("");
  }
}
