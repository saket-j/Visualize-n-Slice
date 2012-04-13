/***************************************************************************
** 
** project_config.h
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
	This file helps in link process for VTK

*/

#ifndef PROJECT_CONFIG_H
#define PROJECT_CONFIG_H

#ifdef _DEBUG
	#pragma comment(lib,"vtkCommon.lib")
	#pragma comment(lib,"vtkDICOMParser.lib")
	#pragma comment(lib,"vtkFiltering.lib")
	#pragma comment(lib,"vtkGenericFiltering.lib")
	#pragma comment(lib,"vtkGraphics.lib")
	#pragma comment(lib,"vtkHybrid.lib")
	#pragma comment(lib,"vtkIO.lib")
	#pragma comment(lib,"vtkImaging.lib")	
	#pragma comment(lib,"vtkNetCDF.lib")
	#pragma comment(lib,"vtkRendering.lib")
	#pragma comment(lib,"vtkVolumeRendering.lib")
	#pragma comment(lib,"vtkWidgets.lib")
	#pragma comment(lib,"vtkexoIIc.lib")
	#pragma comment(lib,"vtkexpat.lib")
	#pragma comment(lib,"vtkfreetype.lib")
	#pragma comment(lib,"vtkftgl.lib")
	#pragma comment(lib,"vtkjpeg.lib")
	#pragma comment(lib,"vtkpng.lib")
	#pragma comment(lib,"vtksys.lib")
	#pragma comment(lib,"vtktiff.lib")
	#pragma comment(lib,"vtkzlib.lib")
	#pragma comment(lib,"opengl32.lib")
	#pragma comment(lib,"glu32.lib")
    #pragma comment(lib,"QVTK.lib")

#else // _RELEASE
	#pragma comment(lib,"vtkCommon.lib")
	#pragma comment(lib,"vtkDICOMParser.lib")
	#pragma comment(lib,"vtkFiltering.lib")
	#pragma comment(lib,"vtkGenericFiltering.lib")
	#pragma comment(lib,"vtkGraphics.lib")
	#pragma comment(lib,"vtkHybrid.lib")
	#pragma comment(lib,"vtkIO.lib")
	#pragma comment(lib,"vtkImaging.lib")	
	#pragma comment(lib,"vtkNetCDF.lib")
	#pragma comment(lib,"vtkRendering.lib")
	#pragma comment(lib,"vtkVolumeRendering.lib")
	#pragma comment(lib,"vtkWidgets.lib")
	#pragma comment(lib,"vtkexoIIc.lib")
	#pragma comment(lib,"vtkexpat.lib")
	#pragma comment(lib,"vtkfreetype.lib")
	#pragma comment(lib,"vtkftgl.lib")
	#pragma comment(lib,"vtkjpeg.lib")
	#pragma comment(lib,"vtkpng.lib")
	#pragma comment(lib,"vtksys.lib")
	#pragma comment(lib,"vtktiff.lib")
	#pragma comment(lib,"vtkzlib.lib")
	#pragma comment(lib,"opengl32.lib")
	#pragma comment(lib,"glu32.lib")
    #pragma comment(lib,"QVTK.lib")
#endif


#endif // PROJECT_CONFIG_H
