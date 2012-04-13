/***************************************************************************
** 
** GUI.h
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
	Class for GUI of application. This class creates the complete GUI.

*/

#ifndef GUI_H
#define GUI_H

#include <QtGui>
#include "QVTKWidget.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"

class GUI : public QMainWindow
{
	Q_OBJECT

public:
	GUI();

protected:
	//menu actions
	QAction *openVtk;
	QAction *saveAxial;
	QAction *saveSagi;
	QAction *saveCoro;
	QAction *savePathview;
	QAction *volinfo;
	QAction *definep;

	//Toolbar buttons
	QPushButton *openVtkbutton;
	QPushButton *saveaxbutton;
	QPushButton *savecobutton;
	QPushButton *savesabutton;
	QPushButton *savepabutton;
	QPushButton *definepbutton;

	//vertical toolbar buttons
	QToolButton *open;
	QToolButton *save;
	QToolButton *showiso;
	QToolButton *pathview;

	//widgets that would contain rendering window
	QVTKWidget *corowid;
	QVTKWidget *sagiwid;
	QVTKWidget *axiawid;
	QVTKWidget *isoshow;
	QVTKWidget *defaxwid;

	QLabel *labc;
	QLabel *labs;
	QLabel *laba;

	QSlider *slc;
	QSlider *sls;
	QSlider *sla;

	void Enableall();
	void openClicked();
	void saveClicked();
	void pathviewClicked();

private:
	//Menu
	QMenu *filemenu;
	QMenu *toolmenu;
	QMenu *aboutmenu;
	QMenu *openmenu;
	QMenu *savemenu;
	QMenu *PathView;

	QWidget *centralWid;
	QWidget *acttoolwid;
	QWidget *mainwid;

	QHBoxLayout *mainLayout;
	QVBoxLayout *vLayout;

	QToolBar *vtoolbar;
	QToolBar *htoolbar;

	QToolButton *Exittool;

	QAction *aboutapp;
	QAction *exitAct;
	
	void Setstyle();
	void createmenu();
	void createactions();
	void createstatusbar();
	void createVtoolbar();
	void createHtoolbar();
	void Disableall();

	private slots:
		void aboutapptr();
};

#endif
