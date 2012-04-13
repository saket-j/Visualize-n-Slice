/***************************************************************************
** 
** volinfo.cpp
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

#include "volinfo.h"
#include "vtkStructuredPoints.h"
#include "vtkStructuredPointsReader.h"

//Constructor: Creates Volume Information Dialog and displays information Slice Spacing and Dimension
volInfo::volInfo(QString filen)
{
	vtkStructuredPointsReader *reader = vtkStructuredPointsReader::New();
	reader->SetFileName(filen.toLatin1());
	reader->Update();

	QGroupBox *dimen = new QGroupBox(tr("Dimension"));
	QGroupBox *spac = new QGroupBox(tr("Spacing"));

	QVBoxLayout *mainl = new QVBoxLayout;
	mainl->addWidget(dimen);
	mainl->addWidget(spac);
	this->setLayout(mainl);

	int extent[6];
	QString xstr,ystr,zstr;
	reader->GetOutput()->GetWholeExtent(extent);
	xstr.sprintf("     x     =     %d",extent[1]-extent[0]+1);
	ystr.sprintf("     y     =     %d",extent[3]-extent[2]+1);
	zstr.sprintf("     z     =     %d",extent[5]-extent[4]+1);
	QVBoxLayout *dimenl = new QVBoxLayout;
	QLabel *xd = new QLabel(xstr,dimen);
	QLabel *yd = new QLabel(ystr,dimen);
	QLabel *zd = new QLabel(zstr,dimen);
	dimenl->addWidget(xd);
	dimenl->addWidget(yd);
	dimenl->addWidget(zd);
	dimen->setLayout(dimenl);

	QVBoxLayout *spacl = new QVBoxLayout;
	double spacing[3];
	reader->GetOutput()->GetSpacing(spacing);
	QString xst,yst,zst;
	xst.sprintf("     x     =     %f",spacing[0]);
	yst.sprintf("     y     =     %f",spacing[1]);
	zst.sprintf("     z     =     %f",spacing[2]);
	QLabel *xs = new QLabel(xst,spac);
	QLabel *ys = new QLabel(yst,spac);
	QLabel *zs = new QLabel(zst,spac);
	spacl->addWidget(xs);
	spacl->addWidget(ys);
	spacl->addWidget(zs);
	spac->setLayout(spacl);
}
