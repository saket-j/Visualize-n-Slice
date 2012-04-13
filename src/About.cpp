/***************************************************************************
** 
** About.cpp
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

#include "About.h"


//Constructor: Creates the About Dialog Box
AboutBox::AboutBox()
{
	QVBoxLayout *mainl = new QVBoxLayout;
	QWidget *mainwid = new QWidget(this);
	QWidget *butwid = new QWidget(this);

	mainl->addWidget(mainwid,100);
	mainl->addWidget(butwid,1);
	this->setLayout(mainl);
 
	QHBoxLayout *butl = new QHBoxLayout;
	QPushButton *okb = new QPushButton(tr("OK"),butwid);
	butl->addStretch();
	butl->addWidget(okb);
	butwid->setLayout(butl);
	connect(okb,SIGNAL(clicked()),this,SLOT(close()));

	QHBoxLayout *mainwidl = new QHBoxLayout;
	QLabel *image = new QLabel(mainwid);
	image->setPixmap(QPixmap(tr(":/ICONS/Head.jpg")));
	QWidget *contentw = new QWidget(this);
	mainwidl->addWidget(image,1);
	mainwidl->addWidget(contentw,10);
	mainwid->setLayout(mainwidl);

	QVBoxLayout *contentwidl = new QVBoxLayout;
	contentw->setLayout(contentwidl);

	QLabel *ver = new QLabel(tr("Product Version : 1.0"),contentw);
	QLabel *author = new QLabel(tr("Author : Saket Jalan"),contentw);
	QLabel *super = new QLabel(tr("Supervisor : Dr. Anupam Agrawal"),contentw);
	QTextEdit *info = new QTextEdit(contentw);
	
	info->setReadOnly(true);
	info->setText(tr("Visualize and Slice is an application for 3D medical image data Visualization and Slicing.")
		+tr("\nVisualization is performed by generating Isosurface using the contour filter.")
		+tr("This application can be used to slice the data slong any arbitrary axis.")
		+tr("\n\nVisualize and Slice is a free application distributed under GNU General Public License."));

	contentwidl->addWidget(ver,1);
	contentwidl->addWidget(author,1);
	contentwidl->addWidget(super,1);
	contentwidl->addWidget(info,10);
}
