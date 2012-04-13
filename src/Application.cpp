/***************************************************************************
** 
** Application.cpp
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
#include "ArbAxisInterCall.h"
#include "CoInputDialog.h"
#include "vtkImageReslice.h"
#include "vtkImageActor.h"
#include "vtkPolyDataMapper.h"
#include "vtkContourFilter.h"
#include "vtkLookupTable.h"
#include "vtkWindowToImageFilter.h"
#include "vtkPNGWriter.h"
#include "volinfo.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkInteractorStyleImage.h"

// Contructor
Application::Application()
{
	GUI();
	setConnections();
	showisotog();
}

// Sets connection to slots for vertical toolbar buttons, and menu items (actions)
void Application::setConnections()
{
	connect(open,SIGNAL(clicked()),this,SLOT(OpenClicked()));
	connect(save,SIGNAL(clicked()),this,SLOT(SaveClicked()));
	connect(pathview,SIGNAL(clicked()),this,SLOT(PathviewClicked()));
	connect(openVtk,SIGNAL(triggered()),this,SLOT(openvtkclicked()));
	connect(showiso,SIGNAL(toggled(bool)),this,SLOT(showisotog()));
	connect(saveAxial,SIGNAL(triggered()),this,SLOT(saveAxialcl()));
	connect(saveCoro,SIGNAL(triggered()),this,SLOT(savecorocl()));
	connect(saveSagi,SIGNAL(triggered()),this,SLOT(savesagicl()));
	connect(savePathview,SIGNAL(triggered()),this,SLOT(savepathcl()));
	connect(volinfo,SIGNAL(triggered()),this,SLOT(volinfotr()));
	connect(definep,SIGNAL(triggered()),this,SLOT(defineptr()));
}

// This slot is called when Open button on VToolBar is clicked
void Application::OpenClicked()
{
	openClicked();
	connect(openVtkbutton,SIGNAL(clicked()),this,SLOT(openvtkclicked()));
}

//This function generates or closes isosurfacing based on toggling of isosurface button
void Application::showisotog()
{
	if(showiso->isChecked() == true)		//if isosurfacing is turned on
	{
		vtkContourFilter *contour= vtkContourFilter::New();			//Applying Contour filtering
		contour->SetInput((vtkDataObject *)reader->GetOutput());
		contour->SetNumberOfContours(0);
		bool ok;
		double value = QInputDialog::getDouble(this,tr("Contour Value"),tr("Enter the Contour Value"),
			100.0,-2147483647,2147483647,1,&ok);	//gets value of contour from user
		if(!ok)
		{
			showiso->setChecked(false);	//if user clicks cancel, isosurafcing is turned false
			return;
		}
		contour->SetValue(0,value);	//setiing the contour value to the value specified by user

		QApplication::setOverrideCursor(Qt::BusyCursor);
		
		vtkLookupTable* bwLut = vtkLookupTable::New();		//black and white lookup table
		bwLut->SetTableRange (0, 1);
		bwLut->SetSaturationRange (0, 0);
		bwLut->SetHueRange (0, 0);
		bwLut->SetValueRange (0, 1);
		bwLut->SetAlphaRange (0, 1);
		bwLut->Build();

		vtkPolyDataMapper *mapper = vtkPolyDataMapper::New();	//mapping data (contour filtered) using lookup table
		mapper->SetInput((vtkPolyData *)contour->GetOutput());	
        mapper->SetColorModeToMapScalars();
		mapper->SetLookupTable(bwLut);

		vtkActor *actor = vtkActor::New();
		actor->SetMapper(mapper);

		vtkRenderer *renderer = vtkRenderer::New();
		renderer->AddActor(actor);

		vtkRenderWindow *window = vtkRenderWindow::New();
		window->AddRenderer(renderer);
		isoshow->SetRenderWindow(renderer->GetRenderWindow());	//finally rendering is QVTKWidget

		QApplication::restoreOverrideCursor();
	}
	else
	{
		vtkRenderer *dum = vtkRenderer::New();			//in case isosurfacing is turned off,
		vtkRenderWindow *wind = vtkRenderWindow::New(); //this adds dummy rendering window
		wind->AddRenderer(dum);							//in it's place
		isoshow->SetRenderWindow(dum->GetRenderWindow());
	}
}

//Function (slot) to read vtk image data
void Application::openvtkclicked()
{
	QString temp = QFileDialog::getOpenFileName(this, tr("Open VTK Data File"),"",tr("VTK Data (*.vtk)"));
	QFile data(temp);
	QString line;
	QTextStream in(&data);
	in.setCodec("UTF-8");
	if (data.open(QFile::ReadOnly)) 
	{
		line = in.readLine();
		if(line.contains("vtk") == true)
		{
			do 
			{
				line = in.readLine();
				if(line.contains("DATASET") == true)
				{
					//call for slicers
					if(line.contains("STRUCTURED_POINTS") == true)//if dataset is compatible
					{
						dataset = line;
						currentfile = temp;
						viewstructuredpointslices();		//calls this function to display slices along axes
						showisotog();						//generates isosurface in case, isosurfacing is true
						Enableall();
					}
					else
					{
						setStatusTip("Unsupported or Invalid Dataset!!");
						QErrorMessage errmsg;
						errmsg.showMessage(tr("Unsupported or Invalid Dataset!!"));
						errmsg.setWindowIcon(QIcon(":/ICONS/Head.jpg"));
						errmsg.exec();
					}
					break;
				}
			} while (!line.isNull());
		}
		else
		{
			this->setStatusTip("Invalid VTK file or file corrupt!!");
			QErrorMessage errmsg;
			errmsg.showMessage(tr("Invalid VTK file or file corrupt!!"));
			errmsg.setWindowIcon(QIcon(":/ICONS/Head.jpg"));
			errmsg.exec();
		}
		data.close();
	}
	else
		this->setStatusTip("File Opening Failed!!");
}

// this function displays slices along the three coordinate axes
void Application::viewstructuredpointslices()
{
	reader = vtkStructuredPointsReader::New();
	reader->SetFileName(currentfile.toLatin1());
	reader->Update();

	reader->GetOutput()->GetWholeExtent(extent);		//gets extent, spacing and origin of data
	reader->GetOutput()->GetSpacing(spacing);			
	reader->GetOutput()->GetOrigin(origin);

	center[0] = origin[0] + spacing[0] * 0.5 * (extent[0] + extent[1]); //calculate center coordinates
	center[1] = origin[1] + spacing[1] * 0.5 * (extent[2] + extent[3]); 
	center[2] = origin[2] + spacing[2] * 0.5 * (extent[4] + extent[5]); 

	double axialElements[16] = {			//matrix for slices along Axial View
           1, 0, 0, 0,
           0, 1, 0, 0,
           0, 0, 1, 0,
           0, 0, 0, 1 };

	double coronalElements[16] = {			//matrix for slices along Coronal View
           1, 0, 0, 0,
           0, 0, 1, 0,
           0,-1, 0, 0,
           0, 0, 0, 1 };

	double sagittalElements[16] = {			//matrix for slices along Sagittal View
           0, 0,-1, 0,
           1, 0, 0, 0,
           0,-1, 0, 0,
           0, 0, 0, 1 };

	axialmat = vtkMatrix4x4::New();
	axialmat->DeepCopy(axialElements);	
	sagimat = vtkMatrix4x4::New();
	sagimat->DeepCopy(sagittalElements);
	coromat = vtkMatrix4x4::New();
	coromat->DeepCopy(coronalElements);

	axialmat->SetElement(0, 3, center[0]);		//setting initial position to center of the axis in all three directions
	axialmat->SetElement(1, 3, center[1]);
	axialmat->SetElement(2, 3, center[2]);
	sagimat->SetElement(0, 3, center[0]);
	sagimat->SetElement(1, 3, center[1]);
	sagimat->SetElement(2, 3, center[2]);
	coromat->SetElement(0, 3, center[0]);
	coromat->SetElement(1, 3, center[1]);
	coromat->SetElement(2, 3, center[2]);

	vtkImageReslice *sliceax = vtkImageReslice::New();		//setting up the new slicing axis
	sliceax->SetInputConnection(reader->GetOutputPort());
	sliceax->SetOutputDimensionality(2);
	sliceax->SetResliceAxes(axialmat);
	sliceax->SetInterpolationModeToLinear();

	vtkImageReslice *sliceco = vtkImageReslice::New();
	sliceco->SetInputConnection(reader->GetOutputPort());
	sliceco->SetOutputDimensionality(2);
	sliceco->SetResliceAxes(coromat);
	sliceco->SetInterpolationModeToLinear();

	vtkImageReslice *slicesa = vtkImageReslice::New();
	slicesa->SetInputConnection(reader->GetOutputPort());
	slicesa->SetOutputDimensionality(2);
	slicesa->SetResliceAxes(sagimat);
	slicesa->SetInterpolationModeToLinear();

	vtkImageActor *actors = vtkImageActor::New();			//making actors
	actors->SetInput(slicesa->GetOutput());
	vtkRenderer *renderersa = vtkRenderer::New();
	renderersa->AddActor(actors);

	vtkImageActor *actora = vtkImageActor::New();
	actora->SetInput(sliceax->GetOutput());
	vtkRenderer *rendererax = vtkRenderer::New();
	rendererax->AddActor(actora);

	vtkImageActor *actorc = vtkImageActor::New();
	actorc->SetInput(sliceco->GetOutput());
	vtkRenderer *rendererco = vtkRenderer::New();
	rendererco->AddActor(actorc);

	vtkRenderWindow *winda = vtkRenderWindow::New();
	vtkRenderWindow *winds = vtkRenderWindow::New();
	vtkRenderWindow *windc = vtkRenderWindow::New();
	winda->AddRenderer(rendererax);
	windc->AddRenderer(rendererco);
	winds->AddRenderer(renderersa);

	corowid->SetRenderWindow(rendererco->GetRenderWindow());		//Render in QVTKWidgets
	sagiwid->SetRenderWindow(renderersa->GetRenderWindow());
	axiawid->SetRenderWindow(rendererax->GetRenderWindow());

	sla->setRange(extent[4],extent[5]);				//slider range is the data range along respective direction
	sla->setValue((extent[4]+extent[5])/2);
	slc->setRange(extent[2],extent[3]);		
	slc->setValue((extent[2]+extent[3])/2);
	sls->setRange(extent[0],extent[1]);
	sls->setValue((extent[0]+extent[1])/2);

	labc->setNum(slc->value());
	labs->setNum(sls->value());
	laba->setNum(sla->value());

	connect(slc,SIGNAL(valueChanged(int)),this,SLOT(slcvalc()));
	connect(sla,SIGNAL(valueChanged(int)),this,SLOT(slavalc()));
	connect(sls,SIGNAL(valueChanged(int)),this,SLOT(slsvalc()));

	vtkRenderer *dumm = vtkRenderer::New();
	vtkRenderWindow *windx = vtkRenderWindow::New();
	windx->AddRenderer(dumm);
	defaxwid->SetRenderWindow(dumm->GetRenderWindow());
}

//this slot takes the two points as input, for defining a new axis 
//for slicing, the new axis being the line joining these two points.
//This axis is considered as z-axis, whose direction cosines are easily obtained 
//by using simple maths formula. Now, for for other two axis, idea is that they must 
//lie on the plane perpendicular to the axis. So by defining this plane, an arbitrary axis is 
//chosen from this plane as x-axis and direction cosines for y-axis is obtained by using
//cross product rule. For arbitrarily chosing x-axis, concept used is that it must cut atleast 
//one of three coordinate planes.
void Application::defineptr()
{
	double x1=0,y1=0,z1=0,x2=0,y2=0,z2=0,tx,ty,tz;
	double lx,ly,lz,mx,my,mz,nx,ny,nz;	
	bool ok=0;
	CoInputDialog *dialog = new CoInputDialog(&x1,&y1,&z1,&x2,&y2,&z2,&ok);	//taking input of coordinates
	dialog->setStyle(QStyleFactory::create("Plastique"));
	dialog->exec();

	if(!ok)
	{
		return;
	}

	if(x1 == x2 && y1 == y2 && z1 == z2)
	{
		QErrorMessage errmsg;
		errmsg.showMessage(tr("Invalid Input!!"));
		errmsg.setWindowIcon(QIcon(":/ICONS/Head.jpg"));
		errmsg.exec();
		return;
	}

	lz = (x2-x1)/sqrt(pow(x2-x1,2)+pow(y2-y1,2)+pow(z2-z1,2));	//direction cosines of new z-axis
	mz = (y2-y1)/sqrt(pow(x2-x1,2)+pow(y2-y1,2)+pow(z2-z1,2));
	nz = (z2-z1)/sqrt(pow(x2-x1,2)+pow(y2-y1,2)+pow(z2-z1,2));

	if(lz!=0 )							//choosing a coordinate on perpendicular plane
	{
	  tz = 0;
	  ty = 1/sqrt(1+((mz*mz)/(lz*lz)));
	  tx = sqrt(1-(ty*ty));
	}
	else if (mz!=0)
	{
	  tx = 0;
	  tz = 1/sqrt(1+((nz*nz)/(mz*mz)));
	  ty = sqrt(1-(tz*tz));
	}
	else if (nz!=0)
	{
	  ty = 0;
	  tx = 1/sqrt(1+((lz*lz)/(nz*nz)));
	  tz = sqrt(1-(tx*tx));
	}

	lx = tx/sqrt((tx*tx)+(ty*ty)+(tz*tz));		//direction cosines of new x-axis, based on the point choosen
	mx = ty/sqrt((tx*tx)+(ty*ty)+(tz*tz));
	nx = tz/sqrt((tx*tx)+(ty*ty)+(tz*tz));

	ly = (mz*nx) - (mx*nz);		//using cross product, direction cosines of new y-axis
	my = (lx*nz) - (lz*nx);
	ny = (lz*mx) - (lx*mz);

	double arbaxisElements[16] = {			//matrix for reslicing
           lx, mx, nx, 0,
           ly, my, ny, 0,
           lz, mz, nz, 0,
            0,  0,  0, 1 };

	pathmat = vtkMatrix4x4::New();
	pathmat->DeepCopy(arbaxisElements);

	pathmat->SetElement(0, 3, center[0]);
	pathmat->SetElement(1, 3, center[1]);
	pathmat->SetElement(2, 3, center[2]);

	vtkImageReslice *reslice = vtkImageReslice::New();		//setting the new axis
	reslice->SetInputConnection(reader->GetOutputPort());
	reslice->SetOutputDimensionality(2);
	reslice->SetResliceAxes(pathmat);
	reslice->SetInterpolationModeToLinear();

	vtkImageActor *actorx = vtkImageActor::New();
	actorx->SetInput(reslice->GetOutput());
	vtkRenderer *rendererx = vtkRenderer::New();
	rendererx->AddActor(actorx);

	vtkRenderWindow *windx = vtkRenderWindow::New();
	windx->AddRenderer(rendererx);
	
	vtkInteractorStyleImage *imageStyle = vtkInteractorStyleImage::New();
	vtkRenderWindowInteractor *interactor = vtkRenderWindowInteractor::New();
	interactor->SetInteractorStyle(imageStyle);			//setting up interactor style to image style
	windx->SetInteractor(interactor);

	ArbAxisInterCall *Intercall = new ArbAxisInterCall();
	Intercall->SetImageReslice(reslice);
	Intercall->SetInteractor(interactor);

	imageStyle->AddObserver(vtkCommand::MouseMoveEvent, Intercall);		//Adding observer for renedring based on mouse activies
	imageStyle->AddObserver(vtkCommand::LeftButtonPressEvent, Intercall);
    imageStyle->AddObserver(vtkCommand::LeftButtonReleaseEvent, Intercall);

	defaxwid->SetRenderWindow(windx);
	defaxwid->GetRenderWindow()->Render();		//rendering
}

//functions for checking the slider values, and setting the new image in axial slice viewers
void Application::slcvalc()
{
	labc->setNum(slc->value());
	coromat->SetElement(1, 3, origin[1] + spacing[1] *slc->value());
	corowid->update();
}

void Application::slsvalc()
{
	labs->setNum(sls->value());
	sagimat->SetElement(0, 3, origin[0] + spacing[0] *sls->value());
	sagiwid->update();
}

void Application::slavalc()
{
	laba->setNum(sla->value());
	axialmat->SetElement(2, 3, origin[2] + spacing[2] *sla->value());
	axiawid->update();
}

//Connections for Other Tool Buttons
void Application::SaveClicked()
{
	saveClicked();
	connect(saveaxbutton,SIGNAL(clicked()),this,SLOT(saveAxialcl()));
	connect(savecobutton,SIGNAL(clicked()),this,SLOT(savecorocl()));
	connect(savesabutton,SIGNAL(clicked()),this,SLOT(savesagicl()));
	connect(savepabutton,SIGNAL(clicked()),this,SLOT(savepathcl()));
}
	
void Application::PathviewClicked()
{
	pathviewClicked();
	connect(definepbutton,SIGNAL(clicked()),this,SLOT(defineptr()));
}

//Saving images in viewers as PNG image using PNG writer
void Application::saveAxialcl()
{
	QString filen = QFileDialog::getSaveFileName(this, tr("Save Axial Image"),"",tr("*.png"));
	if(filen.isEmpty() == true)
		return;
	vtkWindowToImageFilter *filter = vtkWindowToImageFilter::New();
	filter->SetInput(axiawid->GetRenderWindow());
	vtkPNGWriter *wr = vtkPNGWriter::New();
	wr->SetInput(filter->GetOutput());
	wr->SetFileName(filen.toLatin1());
	wr->Write();
	wr->Delete();
	filter->Delete();
}

void Application::savecorocl()
{
	QString filen = QFileDialog::getSaveFileName(this, tr("Save Coronal Image"),"",tr("*.png"));
	if(filen.isEmpty() == true)
		return;
	vtkWindowToImageFilter *filter = vtkWindowToImageFilter::New();
	filter->SetInput(corowid->GetRenderWindow());
	vtkPNGWriter *wr = vtkPNGWriter::New();
	wr->SetInput(filter->GetOutput());
	wr->SetFileName(filen.toLatin1());
	wr->Write();
	wr->Delete();
	filter->Delete();
}

void Application::savesagicl()
{
	QString filen = QFileDialog::getSaveFileName(this, tr("Save Sagittal Image"),"",tr("*.png"));
	if(filen.isEmpty() == true)
		return;
	vtkWindowToImageFilter *filter = vtkWindowToImageFilter::New();
	filter->SetInput(sagiwid->GetRenderWindow());
	vtkPNGWriter *wr = vtkPNGWriter::New();
	wr->SetInput(filter->GetOutput());
	wr->SetFileName(filen.toLatin1());
	wr->Write();
	wr->Delete();
	filter->Delete();
}

void Application::savepathcl()
{
	QString filen = QFileDialog::getSaveFileName(this, tr("Save Arbitrary Axis Image View"),"",tr("*.png"));
	if(filen.isEmpty() == true)
		return;
	vtkWindowToImageFilter *filter = vtkWindowToImageFilter::New();
	filter->SetInput(defaxwid->GetRenderWindow());
	vtkPNGWriter *wr = vtkPNGWriter::New();
	wr->SetInput(filter->GetOutput());
	wr->SetFileName(filen.toLatin1());
	wr->Write();
	wr->Delete();
	filter->Delete();
}

//calls volume information dialog
void Application::volinfotr()
{
	volInfo *infopane = new volInfo(currentfile);
	infopane->setWindowTitle("Volume Information");
	infopane->setWindowIcon(QIcon(":/ICONS/info.png"));
	infopane->setFixedSize(350,250);
	infopane->setStyle(QStyleFactory::create("Plastique"));
	infopane->exec();
}

#include "moc_Application.cpp"
