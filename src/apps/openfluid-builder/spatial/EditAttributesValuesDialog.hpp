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
  @file EditAttributesValuesDialog.hpp

  @author Jean-Christophe FABRE <jean-christophe.fabre@inra.fr>
 */


#ifndef __OPENFLUID_BUILDERAPP_EDITATTRIBUTESVALUESDIALOG_HPP__
#define __OPENFLUID_BUILDERAPP_EDITATTRIBUTESVALUESDIALOG_HPP__


namespace Ui
{
  class EditAttributesValuesDialog;
}


#include <openfluid/ui/common/MessageDialog.hpp>


class EditAttributesValuesDialog : public openfluid::ui::common::MessageDialog
{
  Q_OBJECT;

  private slots:

    void checkGlobal();

    void adaptSelection();


  private:

    Ui::EditAttributesValuesDialog* ui;


  public:

    enum EditMode { EDIT_REPLACE, EDIT_MULTIPLY, EDIT_ADD, EDIT_UNKNOWN };

    EditAttributesValuesDialog(QWidget* Parent = nullptr);

    ~EditAttributesValuesDialog();

    EditMode getEditMode() const;

    QString getReplaceValue() const;

    double getMultiplyValue() const;

    double getAddValue() const;
};


#endif /* __OPENFLUID_BUILDERAPP_EDITATTRIBUTESVALUESDIALOG_HPP__ */
