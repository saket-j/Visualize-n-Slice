/***************************************************************************
** 
** ArbAxisInterCall.cpp
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

#include "ArbAxisInterCall.h"

ArbAxisInterCall::ArbAxisInterCall() 
{
	this->Slicing = 0; 
    this->ImageReslice = 0;
    this->Interactor = 0; 
};

// This funnction changes the location of slice viewed based on the mouse button.
// when left button is clicked, slicing is on, and it effects the slice viewed 
// when left button is not clicked, slicing turns falls, and no effects on mouse movement
// During slicing, it takes the initial and final mouse positions, and based on the amunt of movement
// slice is varied
void ArbAxisInterCall::Execute(vtkObject *, unsigned long event, void *)
{
	vtkRenderWindowInteractor *interactor = this->GetInteractor();

    int lastPos[2];
    interactor->GetLastEventPosition(lastPos);
    int currPos[2];
    interactor->GetEventPosition(currPos);
    
    if (event == vtkCommand::LeftButtonPressEvent)
    {
      this->Slicing = 1;
    }
    else if (event == vtkCommand::LeftButtonReleaseEvent)
    {
      this->Slicing = 0;
    }
    else if (event == vtkCommand::MouseMoveEvent)
    {
      if (this->Slicing)
      {
        vtkImageReslice *reslice = this->ImageReslice;
        int deltaY = lastPos[1] - currPos[1];

        reslice->GetOutput()->UpdateInformation();
        double sliceSpacing = reslice->GetOutput()->GetSpacing()[2];
        vtkMatrix4x4 *matrix = reslice->GetResliceAxes();

        double point[4];
        double center[4];
        point[0] = 0.0;
        point[1] = 0.0;
        point[2] = sliceSpacing * deltaY;
        point[3] = 1.0;
        matrix->MultiplyPoint(point, center);
        matrix->SetElement(0, 3, center[0]);
        matrix->SetElement(1, 3, center[1]);
        matrix->SetElement(2, 3, center[2]);
        interactor->Render();
      }
      else
      {
        vtkInteractorStyle *style = vtkInteractorStyle::SafeDownCast(
          interactor->GetInteractorStyle());
        if (style)
        {
          style->OnMouseMove();
        }
      }
	}
}
    
