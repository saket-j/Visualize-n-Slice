/***************************************************************************
** 
** CoInputDialog.cpp
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

#include "CoInputDialog.h"

/*
	Constructor: Creates the Dialog Box to input coordinates of two points to be used for defining new axis 
				 for arbitrary slice viewer
*/
CoInputDialog::CoInputDialog(double *x1, double *y1, double *z1, double *x2, double *y2, double *z2, bool *ok)
{
	this->setWindowTitle("Enter Coordinates!!");
	this->setWindowIcon(QIcon(":/ICONS/Head.jpg"));
	this->setFixedSize(350,420);

	px1 = x1;
	px2 = x2;
	py1 = y1;
	py2 = y2;
	pz1 = z1;
	pz2 = z2;
	fok = ok;
	*fok = 0;

	QVBoxLayout *mainl = new QVBoxLayout;
	QGroupBox *Pt1 = new QGroupBox(tr("Point 1"),this);
	QGroupBox *Pt2 = new QGroupBox(tr("Point 2"),this);
	QWidget *butwid = new QWidget(this);
	mainl->addWidget(Pt1);
	mainl->addWidget(Pt2);
	mainl->addWidget(butwid);
	this->setLayout(mainl);

	QVBoxLayout *pt1 = new QVBoxLayout;
	QVBoxLayout *pt2 = new QVBoxLayout;

	QLabel *lx1 = new QLabel("x1 =",Pt1);
	QLabel *ly1 = new QLabel("y1 =",Pt1);
	QLabel *lz1 = new QLabel("z1 =",Pt1);
	QLabel *lx2 = new QLabel("x2 =",Pt1);
	QLabel *ly2 = new QLabel("y2 =",Pt1);
	QLabel *lz2 = new QLabel("z2 =",Pt1);

	lex1 = new QLineEdit("0.0",Pt1);
	ley1 = new QLineEdit("0.0",Pt1);
	lez1 = new QLineEdit("0.0",Pt1);
	lex2 = new QLineEdit("0.0",Pt2);
	ley2 = new QLineEdit("0.0",Pt2);
	lez2 = new QLineEdit("0.0",Pt2);

	pt1->addWidget(lx1);
	pt1->addWidget(lex1);
	pt1->addWidget(ly1);
	pt1->addWidget(ley1);
	pt1->addWidget(lz1);
	pt1->addWidget(lez1);
	pt2->addWidget(lx2);
	pt2->addWidget(lex2);
	pt2->addWidget(ly2);
	pt2->addWidget(ley2);
	pt2->addWidget(lz2);
	pt2->addWidget(lez2);

	Pt1->setLayout(pt1);
	Pt2->setLayout(pt2);

	QPushButton *okb = new QPushButton(tr("OK"),butwid);
	QPushButton *cab = new QPushButton(tr("Cancel"),butwid);
	QHBoxLayout *butl = new QHBoxLayout;
	butl->addStretch(0);
	butl->addWidget(okb);
	butl->addWidget(cab);
	butwid->setLayout(butl);

	connect(okb,SIGNAL(clicked()),this,SLOT(okbclicked()));
	connect(cab,SIGNAL(clicked()),this,SLOT(close()));
}

//IN case ok button is clicked, after inputting the value, this function initialises variables with new values
void CoInputDialog::okbclicked()
{
	*fok = 1;
	*px1 = lex1->text().toDouble();
	*px2 = lex2->text().toDouble();
	*py1 = ley1->text().toDouble();
	*py2 = ley2->text().toDouble();
	*pz1 = lez1->text().toDouble();
	*pz2 = lez2->text().toDouble();
	done(1);		//functions exits the dialog
}

#include "moc_CoInputDialog.cpp"
