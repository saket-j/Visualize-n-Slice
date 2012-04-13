/***************************************************************************
** 
** CoInputDialog.h
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
	Class for Coordinate Input Dialog. Used in Arbitrary Axis Slicing module

*/

#ifndef COINPUTDIALOG_H
#define COINPUTDIALOG_H

#include <QtGui>

class CoInputDialog : public QDialog
{
	Q_OBJECT
public:
	CoInputDialog(double *x1,double *y1,double *z1,double *x2,double *y2,double *z2,bool *ok);

private:
	double *px1,*py1,*pz1,*px2,*py2,*pz2;
	bool *fok;
	QLineEdit *lex1,*ley1,*lez1,*lex2,*ley2,*lez2;

	private slots:
		void okbclicked();
};

#endif
