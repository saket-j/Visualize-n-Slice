/***************************************************************************
** 
** GUI.cpp
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

#include <QApplication>

#include "GUI.h"
#include "About.h"

// Constructor: This call all other functions, to create the complete GUI. All the QVTKWidgets are inside a QGroupBox
// This also adds dummy rendering window to the QVTKWidgets, so that GUI is not distorted.
GUI::GUI()
{
	Setstyle();

	createactions();
	createmenu();

	centralWid = new QWidget(this);
	this->setCentralWidget(centralWid);
	
	mainLayout = new QHBoxLayout;
	createVtoolbar();
	acttoolwid = new QWidget(centralWid);
	mainLayout->addWidget(acttoolwid);
	mainLayout->setSpacing(0);
	mainLayout->setContentsMargins(0,0,0,0);
	centralWid->setContentsMargins(0,0,0,0);
	centralWid->setLayout(mainLayout);

	vLayout = new QVBoxLayout;
	createHtoolbar();
	vLayout->setSpacing(0);
	vLayout->setContentsMargins(0,0,0,0);
	acttoolwid->setContentsMargins(0,0,0,0);
	QWidget *upper = new QWidget(acttoolwid);
	QWidget *lower = new QWidget(acttoolwid);
	vLayout->addWidget(upper);
	vLayout->addWidget(lower);
	acttoolwid->setLayout(vLayout);

	QHBoxLayout *upperwidlayout = new QHBoxLayout;
	QHBoxLayout *lowerwidlayout = new QHBoxLayout;
	QGroupBox *isosurface = new QGroupBox(tr("IsoSurface"));
	QGroupBox *pathviewer = new QGroupBox(tr("Arbitrary Axis Slice Viewer"));
	QGroupBox *axialslice = new QGroupBox(tr("Axial Slice"));
	QGroupBox *coroslice = new QGroupBox(tr("Coronal Slice"));
	QGroupBox *sagislice = new QGroupBox(tr("Sagittal Slice"));
	upperwidlayout->addWidget(isosurface);		//Adding QGroupBoxes for differnt viewers
	upperwidlayout->addWidget(pathviewer);
	lowerwidlayout->addWidget(axialslice);
	lowerwidlayout->addWidget(coroslice);
	lowerwidlayout->addWidget(sagislice);
	
	upper->setLayout(upperwidlayout);
	lower->setLayout(lowerwidlayout);

	QHBoxLayout *corola = new QHBoxLayout;
	QHBoxLayout *axialla = new QHBoxLayout;
	QHBoxLayout *sagila = new QHBoxLayout;
	QHBoxLayout *araxl = new QHBoxLayout;

	corowid = new QVTKWidget(coroslice);	//Widgets that will contains diff rendering windows
	sagiwid = new QVTKWidget(sagislice);
	axiawid = new QVTKWidget(axialslice);
	isoshow = new QVTKWidget(isosurface);
	defaxwid = new QVTKWidget(pathviewer);
	
	vtkRenderer *duma = vtkRenderer::New();		//Dummy renderers
	vtkRenderer *dums = vtkRenderer::New();
	vtkRenderer *dumc = vtkRenderer::New();
	vtkRenderer *dumx = vtkRenderer::New();
	vtkRenderWindow *winda = vtkRenderWindow::New();
	vtkRenderWindow *winds = vtkRenderWindow::New();
	vtkRenderWindow *windc = vtkRenderWindow::New();
	vtkRenderWindow *windx = vtkRenderWindow::New();
	winda->AddRenderer(duma);
	windc->AddRenderer(dumc);
	winds->AddRenderer(dums);
	windx->AddRenderer(dumx);
	corowid->SetRenderWindow(dumc->GetRenderWindow());	//Adding dummy rendering windows
	sagiwid->SetRenderWindow(dums->GetRenderWindow());
	axiawid->SetRenderWindow(duma->GetRenderWindow());
	defaxwid->SetRenderWindow(dumx->GetRenderWindow());

	coroslice->setLayout(corola);
	sagislice->setLayout(sagila);
	axialslice->setLayout(axialla);
	pathviewer->setLayout(araxl);

	QWidget *corosl = new QWidget(coroslice);
	QWidget *sagisl = new QWidget(sagislice);
	QWidget *axiasl = new QWidget(axialslice);

	corola->addWidget(corowid);
	corola->addWidget(corosl);
	sagila->addWidget(sagiwid);
	sagila->addWidget(sagisl);
	axialla->addWidget(axiawid);
	axialla->addWidget(axiasl);
	araxl->addWidget(defaxwid);

	//Add slider and label
	labc = new QLabel(corosl);
	labs = new QLabel(sagisl);
	laba = new QLabel(axiasl);

	slc = new QSlider(Qt::Vertical,corosl);
	sls = new QSlider(Qt::Vertical,sagisl);
	sla = new QSlider(Qt::Vertical,axiasl);

	QVBoxLayout *sal = new QVBoxLayout;
	QVBoxLayout *axl = new QVBoxLayout;
	QVBoxLayout *col = new QVBoxLayout;
	QVBoxLayout *iso = new QVBoxLayout;

	sal->addWidget(labs);
	sal->addWidget(sls);
	axl->addWidget(laba);
	axl->addWidget(sla);
	col->addWidget(labc);
	col->addWidget(slc);
	iso->addWidget(isoshow);

	corosl->setLayout(col);
	axiasl->setLayout(axl);
	sagisl->setLayout(sal);
	isosurface->setLayout(iso);

	Disableall();
	createstatusbar();
}

//This sets style of the interface
void GUI::Setstyle()
{
	QApplication::setStyle(QStyleFactory::create("Plastique"));
	QApplication::setPalette(QApplication::style()->standardPalette());
}

//	creates actions for menus
void GUI::createactions()
{
	openVtk = new QAction(QIcon(":/ICONS/logo-vtk.gif"),tr("&Open VTK"), this);
    openVtk->setStatusTip(tr("Open VTK File"));

	saveAxial = new QAction(tr("&Save Axial"), this);
    saveAxial->setStatusTip(tr("Save Slice on Axial View"));

	saveCoro = new QAction(tr("&Save Coronal"), this);
    saveCoro->setStatusTip(tr("Save Slice on Coronal View"));

	saveSagi = new QAction(tr("&Save Sagital"), this);
    saveSagi->setStatusTip(tr("Save Slice on Sagital View"));

	savePathview = new QAction(tr("&Save Arbitrary Axis View"), this);
    savePathview->setStatusTip(tr("Save Slice on Arbitrary Axis Viewer"));
	
	exitAct = new QAction(QIcon(":/ICONS/exit.png"),tr("&Exit"), this);
    exitAct->setShortcut(tr("Alt+X"));
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, SIGNAL(triggered()), qApp, SLOT(quit()));

	volinfo = new QAction(QIcon(":/ICONS/info.png"),tr("&Volume Information"), this);
	volinfo->setShortcut(tr("Ctrl+I"));
    volinfo->setStatusTip(tr("View Information of Volume"));

	definep = new QAction(tr("&Define Axis"), this);
	definep->setStatusTip(tr("Used to Define New Axis"));

	aboutapp = new QAction(QIcon(":/ICONS/aboutapp.png"),tr("&About Application"), this);
    aboutapp->setStatusTip(tr("About Application"));
	aboutapp->setShortcut(tr("F1"));
	connect(aboutapp,SIGNAL(triggered()),this,SLOT(aboutapptr()));
}

// Creates MenuBar and the menus, and adds actions to them
void GUI::createmenu()
{
	menuBar()->setStyle(QStyleFactory::create("Cleanlooks"));
	filemenu = menuBar()->addMenu(tr("&File"));
	filemenu->setStatusTip("File Menu");
	openmenu = filemenu->addMenu(QIcon(":/ICONS/open3.png"),"&Open");
	savemenu = filemenu->addMenu(QIcon(":/ICONS/save.png"),"&Save Slices");
	filemenu->addSeparator();
	filemenu->addAction(exitAct);
	openmenu->addAction(openVtk);
	savemenu->addAction(saveAxial);
	savemenu->addAction(saveCoro);
	savemenu->addAction(saveSagi);
	savemenu->addAction(savePathview);

	toolmenu = menuBar()->addMenu(tr("&Tools"));
	toolmenu->setStatusTip("Tools Menu");
	PathView = toolmenu->addMenu(QIcon(":/ICONS/path.png"),"&Arbitrary Axis Viewer");
	PathView->addAction(definep);
	toolmenu->addSeparator();
	toolmenu->addAction(volinfo);

	aboutmenu = menuBar()->addMenu(tr("&Help"));
	aboutmenu->setStatusTip("Help Menu");
	aboutmenu->addAction(aboutapp);
}

// Function to create Horizontal Toolbar
void GUI::createHtoolbar()
{
	htoolbar = new QToolBar;
	htoolbar->setFixedHeight(30);
	vLayout->addWidget(htoolbar);
	QPalette pal;
	pal.setColor(QPalette::Background, QColor("lightGray"));
	htoolbar->setAutoFillBackground(true); 
	htoolbar->setPalette(pal);
}

// Function to create Vertical Toolbar
void GUI::createVtoolbar()
{
	vtoolbar = new QToolBar;
	vtoolbar->setFixedWidth(60);
	vtoolbar->setOrientation(Qt::Vertical);

	QWidget *dummy = new QWidget(vtoolbar);
	dummy->setFixedHeight(30);
	dummy->setFixedWidth(60);
	vtoolbar->addWidget(dummy);

	open = new QToolButton(vtoolbar);
	open->setStatusTip("Open Volume Files");
	open->setFixedHeight(50);
	open->setFixedWidth(50);
	open->setCheckable(true);
	open->setIcon(QIcon(":/ICONS/open3.png"));
	vtoolbar->addWidget(open);

	save = new QToolButton(vtoolbar);
	save->setStatusTip("Save Slices");
	save->setFixedHeight(50);
	save->setFixedWidth(50);
	save->setCheckable(true);
	save->setIcon(QIcon(":/ICONS/save.png"));
	vtoolbar->addWidget(save);

	showiso = new QToolButton(vtoolbar);
	showiso->setStatusTip("Toggle Visibility of ISOsurface");
	showiso->setFixedHeight(50);
	showiso->setFixedWidth(50);
	showiso->setCheckable(true);
	showiso->setIcon(QIcon(":/ICONS/iso.png"));
	vtoolbar->addWidget(showiso);

	pathview = new QToolButton(vtoolbar);
	pathview->setStatusTip("Define or Show Slices on an Arbitrary Axis");
	pathview->setFixedHeight(50);
	pathview->setFixedWidth(50);
	pathview->setCheckable(true);
	pathview->setIcon(QIcon(":/ICONS/path.png"));
	vtoolbar->addWidget(pathview);

	Exittool = new QToolButton(vtoolbar);
	Exittool->setStatusTip("Exit Application");
	Exittool->setFixedHeight(50);
	Exittool->setFixedWidth(50);
	Exittool->setIcon(QIcon(":/ICONS/exit.png"));
	vtoolbar->addWidget(Exittool);
	connect(Exittool,SIGNAL(clicked()),qApp,SLOT(quit()));

	QPalette pal;
	pal.setColor(QPalette::Background, QColor("Gray"));
	vtoolbar->setAutoFillBackground(true);
	vtoolbar->setPalette(pal);
	mainLayout->addWidget(vtoolbar);
}

// Creates Status Bar
void GUI::createstatusbar()
{
	statusBar()->setStyle(QStyleFactory::create("WindowsXP"));
	QPalette pal;
	pal.setColor(QPalette::Background, QColor("lightGray"));
	statusBar()->setAutoFillBackground(true);
	statusBar()->setPalette(pal);
	statusBar()->showMessage(tr("Ready"));
}

// A slot that adds Open buttons to Horizontal toolbar as Open button on Vertical is Clicked
void GUI::openClicked()
{
	htoolbar->clear();
	save->setChecked(false);
	pathview->setChecked(false);

	openVtkbutton = new QPushButton(htoolbar);
	openVtkbutton->setText("Vtk Data");
	openVtkbutton->setStatusTip("Open a VTK Volume data file");
	htoolbar->addWidget(openVtkbutton);
}

// A slot that adds Save buttons to Horizontal toolbar as Save button on Vertical is Clicked
void GUI::saveClicked()
{
	htoolbar->clear();
	open->setChecked(false);
	pathview->setChecked(false);

	saveaxbutton = new QPushButton(htoolbar);
	saveaxbutton->setText("Axial Slice");
	saveaxbutton->setStatusTip("Saves current slice on axial view");
	htoolbar->addWidget(saveaxbutton);

	savecobutton = new QPushButton(htoolbar);
	savecobutton->setText("Coronal Slice");
	savecobutton->setStatusTip("Saves current slice on Coronal view");
	htoolbar->addWidget(savecobutton);

	savesabutton = new QPushButton(htoolbar);
	savesabutton->setText("Sagittal Slice");
	savesabutton->setStatusTip("Saves current slice on Sagittal view");
	htoolbar->addWidget(savesabutton);

	savepabutton = new QPushButton(htoolbar);
	savepabutton->setText("Arbitary View Slice");
	savepabutton->setStatusTip("Saves current slice on Arbitrary Slice view");
	htoolbar->addWidget(savepabutton);
}

// A slot that adds Define Axis button to Horizointal toolbar as Arbitrary Axis button on Vertical is Clicked
void GUI::pathviewClicked()
{

	htoolbar->clear();
	save->setChecked(false);
	open->setChecked(false);

	definepbutton = new QPushButton(htoolbar);
	definepbutton->setText("Define Axis");
	definepbutton->setStatusTip("Define a new Axis for Arbitrary Axis Slicer");
	htoolbar->addWidget(definepbutton);
}

// This function disables all toolbuttons of no use at the beginning
void GUI::Disableall()
{
	save->setDisabled(true);
	pathview->setDisabled(true);
	showiso->setDisabled(true);
	savemenu->setDisabled(true);
	PathView->setDisabled(true);
	volinfo->setDisabled(true);
}

//This function enables buttons disabled at the beginning as a file is sucessfully opened
void GUI::Enableall()
{
	save->setEnabled(true);
	pathview->setEnabled(true);
	showiso->setEnabled(true);
	savemenu->setEnabled(true);
	PathView->setEnabled(true);
	volinfo->setEnabled(true);
}

// Shows the About Application Dialog
void GUI::aboutapptr()
{
	AboutBox *aboutdialog = new AboutBox();
	aboutdialog->setStyle(QStyleFactory::create("Plastique"));
	aboutdialog->setWindowIcon(QIcon(":/ICONS/aboutapp.png"));
	aboutdialog->setWindowTitle(tr("About Visualize and Slice"));
	aboutdialog->setFixedSize(550,350);
	aboutdialog->exec();
}

#include "moc_GUI.cpp"
