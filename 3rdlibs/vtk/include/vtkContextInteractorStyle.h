/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkContextInteractorStyle.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
/**
 * @class   vtkContextInteractorStyle
 * @brief   An interactor for chart views.
 *
 *
 * It observes the user events (mouse events) and propagates them
 * to the CIM. If the CIM doesn't eat the event, it is propagated
 * to the interactor style superclass.
*/

#ifndef vtkContextInteractorStyle_h
#define vtkContextInteractorStyle_h

#include "vtkViewsContext2DModule.h" // For export macro
#include "vtkInteractorStyle.h"
#include "vtkNew.h" // For ivars
#include "vtkWeakPointer.h" // For ivars

class vtkContextMouseEvent;
class vtkContextCIM;

class VTKVIEWSCONTEXT2D_EXPORT vtkContextInteractorStyle : public vtkInteractorStyle
{
public:
  static vtkContextInteractorStyle *New();
  vtkTypeMacro(vtkContextInteractorStyle, vtkInteractorStyle);
  void PrintSelf(ostream& os, vtkIndent indent) override;

  /**
   * Set the CIM to forward user events to.
   * Refresh the view when the CIM is dirty and no event is being processed.
   * The CIM is observed (vtkCommand::ModifiedEvent) and a refresh on the
   * view is called appropriately: CIM is dirty and no event is being
   * processed.
   */
  void SetCIM(vtkContextCIM* CIM);

  /**
   * Return the observed CIM.
   */
  vtkContextCIM* GetCIM();

  /**
   * Called when the CIM is modified. Refresh the CIM if needed.
   */
  virtual void OnCIMModified();

  /**
   * Called when the user moves the mouse
   * Default behavior forwards the event to the observed CIM.
   */
  void OnMouseMove() override;

  /**
   * Called when the user clicks the mouse left button.
   * Default behavior forwards the event to the observed CIM.
   */
  void OnLeftButtonDown() override;

  /**
   * Called when the user releases the mouse left button.
   * Default behavior forwards the event to the observed CIM.
   */
  void OnLeftButtonUp() override;

  /**
   * Called when the user clicks the mouse middle button.
   * Default behavior forwards the event to the observed CIM.
   */
  void OnMiddleButtonDown() override;

  /**
   * Called when the user releases the mouse middle button.
   * Default behavior forwards the event to the observed CIM.
   */
  void OnMiddleButtonUp() override;

  /**
   * Called when the user clicks the mouse right button.
   * Default behavior forwards the event to the observed CIM.
   */
  void OnRightButtonDown() override;

  /**
   * Called when the user releases the mouse right button.
   * Default behavior forwards the event to the observed CIM.
   */
  void OnRightButtonUp() override;

  /**
   * Called when the user moves the mouse wheel forward.
   * Default behavior forwards the event to the observed CIM.
   */
  void OnMouseWheelForward() override;

  /**
   * Called when the user moves the mouse wheel backward.
   * Default behavior forwards the event to the observed CIM.
   */
  void OnMouseWheelBackward() override;

  /**
   * Place holder for future implementation.
   * Default behavior forwards the event to the observed CIM.
   */
  virtual void OnSelection(unsigned int rect[5]);

  /**
   * Handle key presses.
   */
  void OnChar() override;

  /**
   * Called when the user presses a key.
   */
  void OnKeyPress() override;

  /**
   * Called when the user releases a key.
   */
  void OnKeyRelease() override;

protected:
  vtkContextInteractorStyle();
  ~vtkContextInteractorStyle() override;

  static void ProcessCIMEvents(vtkObject* object, unsigned long event,
                                 void* clientdata, void* calldata);

  static void ProcessInteractorEvents(vtkObject* object, unsigned long event,
                                      void* clientdata, void* calldata);

  virtual void RenderNow();

  /**
   * Inform the interactor style that an event is being processed.
   * That way is knows to not refresh the view (the view will eventually be
   * refreshed at the end.
   */
  void BeginProcessingEvent();

  /**
   * Inform the interactor style that an event is finished to be processed.
   * If no other event is being processed it check if the CIM needs to be
   * rendered (CIM is dirty)
   */
  void EndProcessingEvent();

  vtkWeakPointer<vtkContextCIM> CIM;
  vtkNew<vtkCallbackCommand> CIMCallbackCommand;
  vtkNew<vtkCallbackCommand> InteractorCallbackCommand;
  int                 ProcessingEvents;
  vtkMTimeType        LastCIMRepaintMTime;

  int                 CIMTimerId;
  bool                TimerCallbackInitialized;

private:
  vtkContextInteractorStyle(const vtkContextInteractorStyle&) = delete;
  void operator=(const vtkContextInteractorStyle&) = delete;

  void ConstructMouseEvent(vtkContextMouseEvent &event, int button);
  bool ProcessMousePress(const vtkContextMouseEvent &event);
};

#endif
