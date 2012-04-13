/***************************************************************************
** 
** Application.h
** This file is part of Visualize and Slice
**
** This program is free software; you can redistribute it and/or
** modify it under the terms of the GNU General Public License
** as published by the Free Software Foundation; either
** version 2 of the License, or (at your option) any later version.
** 
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
** 
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
** 
***************************************************************************/

/*
	Class for handling of all operations of the application. This is the main class

*/

#ifndef APPLICATION_H
#define APPLICATION_H

#include "GUI.h"
#include "string.h"
#include "vtkMatrix4x4.h"
#include "vtkStructuredPoints.h"
#include "vtkStructuredPointsReader.h"

class Application : public GUI
{
	Q_OBJECT

public:
	Application();

private:
	QString dataset;		//this holds the dataset type of VTK file opened
	QString currentfile;	//this holds the path of current file in process

	//matrices for defining slicing axis
	vtkMatrix4x4 *axialmat;
	vtkMatrix4x4 *coromat;
	vtkMatrix4x4 *sagimat;
	vtkMatrix4x4 *pathmat;

	vtkStructuredPointsReader *reader;

	double spacing[3];
	double origin[3];
	int extent[6];
	double center[3];

	void setConnections();
	void viewstructuredpointslices();

private slots:
	void openvtkclicked();
	void OpenClicked();
	void SaveClicked();
	void PathviewClicked();
	void slcvalc();
	void slsvalc();
	void slavalc();
	void showisotog();
	void saveAxialcl();
	void savecorocl();
	void savesagicl();
	void savepathcl();
	void volinfotr();
	void defineptr();
};

#endif
