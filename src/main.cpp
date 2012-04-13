/***************************************************************************
** 
** main.cpp
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

#include "Application.h"
#include "project_config.h"
#include "qrc_Project.cpp"

int main(int argc, char* argv[])
{
	QApplication app(argc,argv);
	Q_INIT_RESOURCE(Project);		//initialising the qt resource file containing icons

	Application mainWindow;
	mainWindow.setMinimumSize(800,600);
	mainWindow.setWindowTitle("Visualize and Slice");
	mainWindow.setWindowIcon(QIcon(":/ICONS/Head.jpg"));
	mainWindow.showMaximized();

	return app.exec();
}
