/*
 * uMPS - A general purpose computer system simulator
 *
 * Copyright (C) 2010 Tomislav Jonjic
 * Copyright (C) 2020 Mattia Biondi
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef QMPS_MACHINE_CONFIG_DIALOG_H
#define QMPS_MACHINE_CONFIG_DIALOG_H

#include <QDialog>

#include "umps/machine_config.h"

class QListWidget;
class QStackedLayout;
class QSpinBox;
class QComboBox;
class QLineEdit;
class QCheckBox;
class AsidLineEdit;

class MachineConfigDialog : public QDialog {
Q_OBJECT

public:
MachineConfigDialog(MachineConfig* config, QWidget* parent = 0);

private:
QWidget* createGeneralTab();
QWidget* createDeviceTab();
void registerDeviceClass(const QString& label,
                         const QString& icon,
                         unsigned int devClassIndex,
                         const QString& deviceClassName,
                         const QString& deviceName,
                         bool selected = false);

MachineConfig* const config;

QSpinBox* cpuSpinner;
QSpinBox* clockRateSpinner;
QComboBox* tlbSizeList;
QComboBox* tlbFloorAddressList;
QSpinBox* ramSizeSpinner;
QCheckBox* coreBootCheckBox;
AsidLineEdit* stabAsidEdit;

struct {
	const char* description;
	QLineEdit* lineEdit;
} romFileInfo[N_ROM_TYPES];

QListWidget* devClassView;
QStackedLayout* devFileChooserStack;

private Q_SLOTS:
void getROMFileName(int index);

void onDeviceClassChanged();

void saveConfigChanges();
};

#endif // QMPS_MACHINE_CONFIG_DIALOG_H
