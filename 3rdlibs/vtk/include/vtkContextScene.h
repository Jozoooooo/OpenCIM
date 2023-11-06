/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkContextCIM.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

/**
 * @class   vtkContextCIM
 * @brief   Provides a 2D CIM for vtkContextItem objects.
 *
 *
 * Provides a 2D CIM that vtkContextItem objects can be added to. Manages the
 * items, ensures that they are rendered at the right times and passes on mouse
 * events.
*/

#ifndef vtkContextCIM_h
#define vtkContextCIM_h

#include "vtkRenderingContext2DModule.h" // For export macro
#include "vtkObject.h"
#include "vtkWeakPointer.h" // Needed for weak pointer to the window.
#include "vtkVector.h" // For vtkVector return type.

class vtkContext2D;
class vtkAbstractContextItem;
class vtkTransform2D;
class vtkContextMouseEvent;
class vtkContextKeyEvent;
class vtkContextCIMPrivate;
class vtkContextInteractorStyle;

class vtkAnnotationLink;

class vtkRenderer;
class vtkAbstractContextBufferId;

class VTKRENDERINGCONTEXT2D_EXPORT vtkContextCIM : public vtkObject
{
public:
  vtkTypeMacro(vtkContextCIM, vtkObject);
  void PrintSelf(ostream &os, vtkIndent indent) override;

  /**
   * Creates a 2D Painter object.
   */
  static vtkContextCIM * New();

  /**
   * Paint event for the chart, called whenever the chart needs to be drawn
   */
  virtual bool Paint(vtkContext2D *painter);

  /**
   * Add child items to this item. Increments reference count of item.
   * \return the index of the child item.
   */
  unsigned int AddItem(vtkAbstractContextItem* item);

  /**
   * Remove child item from this item. Decrements reference count of item.
   * \param item the item to be removed.
   * \return true on success, false otherwise.
   */
  bool RemoveItem(vtkAbstractContextItem* item);

  /**
   * Remove child item from this item. Decrements reference count of item.
   * \param index of the item to be removed.
   * \return true on success, false otherwise.
   */
  bool RemoveItem(unsigned int index);

  /**
   * Get the item at the specified index.
   * \return the item at the specified index (null if index is invalid).
   */
  vtkAbstractContextItem* GetItem(unsigned int index);

  /**
   * Get the number of child items.
   */
  unsigned int GetNumberOfItems();

  /**
   * Remove all child items from this item.
   */
  void ClearItems();

  /**
   * Set the vtkAnnotationLink for the chart.
   */
  virtual void SetAnnotationLink(vtkAnnotationLink *link);

  //@{
  /**
   * Get the vtkAnnotationLink for the chart.
   */
  vtkGetObjectMacro(AnnotationLink, vtkAnnotationLink);
  //@}

  //@{
  /**
   * Set the width and height of the CIM in pixels.
   */
  vtkSetVector2Macro(Geometry, int);
  //@}

  //@{
  /**
   * Get the width and height of the CIM in pixels.
   */
  vtkGetVector2Macro(Geometry, int);
  //@}

  //@{
  /**
   * Set whether the CIM should use the color buffer. Default is true.
   */
  vtkSetMacro(UseBufferId, bool);
  //@}

  //@{
  /**
   * Get whether the CIM is using the color buffer. Default is true.
   */
  vtkGetMacro(UseBufferId, bool);
  //@}

  /**
   * Get the width of the view
   */
  virtual int GetViewWidth();

  /**
   * Get the height of the view
   */
  virtual int GetViewHeight();

  /**
   * Get the width of the CIM.
   */
  int GetCIMWidth();

  /**
   * Get the height of the CIM.
   */
  int GetCIMHeight();

  //@{
  /**
   * Whether to scale the CIM transform when tiling, for example when
   * using vtkWindowToImageFilter to take a large screenshot.
   * The default is true.
   */
  vtkSetMacro(ScaleTiles, bool);
  vtkGetMacro(ScaleTiles, bool);
  vtkBooleanMacro(ScaleTiles, bool);
  //@}

  /**
   * The tile scale of the target vtkRenderWindow. Hardcoded pixel offsets, etc
   * should properly account for these <x, y> scale factors. This will simply
   * return vtkVector2i(1, 1) if ScaleTiles is false or if this->Renderer is
   * NULL.
   */
  vtkVector2i GetLogicalTileScale();

  //@{
  /**
   * This should not be necessary as the context view should take care of
   * rendering.
   */
  virtual void SetRenderer(vtkRenderer *renderer);
  virtual vtkRenderer* GetRenderer();
  //@}

  //@{
  /**
   * Inform the CIM that something changed that requires a repaint of the
   * CIM. This should only be used by the vtkContextItem derived objects in
   * a CIM in their event handlers.
   */
  void SetDirty(bool isDirty);
  bool GetDirty()const;
  //@}

  /**
   * Release graphics resources hold by the CIM.
   */
  void ReleaseGraphicsResources();

  /**
   * Last painter used.
   * Not part of the end-user API. Can be used by context items to
   * create their own colorbuffer id (when a context item is a container).
   */
  vtkWeakPointer<vtkContext2D> GetLastPainter();

  /**
   * Return buffer id.
   * Not part of the end-user API. Can be used by context items to
   * initialize their own colorbuffer id (when a context item is a container).
   */
  vtkAbstractContextBufferId *GetBufferId();

  /**
   * Set the transform for the CIM.
   */
  virtual void SetTransform(vtkTransform2D *transform);

  /**
   * Get the transform for the CIM.
   */
  vtkTransform2D* GetTransform();

  /**
   * Check whether the CIM has a transform.
   */
  bool HasTransform() { return this->Transform != nullptr; }

  /**
   * Enum of valid selection modes for charts in the CIM
   */
  enum {
    SELECTION_NONE = 0,
    SELECTION_DEFAULT,
    SELECTION_ADDITION,
    SELECTION_SUBTRACTION,
    SELECTION_TOGGLE
  };

protected:
  vtkContextCIM();
  ~vtkContextCIM() override;

  /**
   * Process a rubber band selection event.
   */
  virtual bool ProcessSelectionEvent(unsigned int rect[5]);

  /**
   * Process a mouse move event.
   */
  virtual bool MouseMoveEvent(const vtkContextMouseEvent &event);

  /**
   * Process a mouse button press event.
   */
  virtual bool ButtonPressEvent(const vtkContextMouseEvent &event);

  /**
   * Process a mouse button release event.
   */
  virtual bool ButtonReleaseEvent(const vtkContextMouseEvent &event);

  /**
   * Process a mouse button double click event.
   */
  virtual bool DoubleClickEvent(const vtkContextMouseEvent &event);

  /**
   * Process a mouse wheel event where delta is the movement forward or back.
   */
  virtual bool MouseWheelEvent(int delta, const vtkContextMouseEvent &event);

  /**
   * Process a key press event.
   */
  virtual bool KeyPressEvent(const vtkContextKeyEvent& keyEvent);

  /**
   * Process a key release event.
   */
  virtual bool KeyReleaseEvent(const vtkContextKeyEvent& keyEvent);

  /**
   * Paint the CIM in a special mode to build a cache for picking.
   * Use internally.
   */
  virtual void PaintIds();

  /**
   * Test if BufferId is supported by the OpenGL context.
   */
  void TestBufferIdSupport();

  /**
   * Return the item id under mouse cursor at position (x,y).
   * Return -1 if there is no item under the mouse cursor.
   * \post valid_result: result>=-1 && result<this->GetNumberOfItems()
   */
  vtkIdType GetPickedItem(int x, int y);

  /**
   * Return the item under the mouse.
   * If no item is under the mouse, the method returns a null pointer.
   */
  vtkAbstractContextItem* GetPickedItem();

  /**
   * Make sure the buffer id used for picking is up-to-date.
   */
  void UpdateBufferId();

  vtkAnnotationLink *AnnotationLink;

  // Store the chart dimensions - width, height of CIM in pixels
  int Geometry[2];

  /**
   * The vtkContextInteractorStyle class delegates all of the events to the
   * CIM, accessing protected API.
   */
  friend class vtkContextInteractorStyle;

  //@{
  /**
   * Private storage object - where we hide all of our STL objects...
   */
  class Private;
  Private *Storage;
  //@}

  /**
   * This structure provides a list of children, along with convenience
   * functions to paint the children etc. It is derived from
   * std::vector<vtkAbstractContextItem>, defined in a private header.
   */
  vtkContextCIMPrivate* Children;

  vtkWeakPointer<vtkContext2D> LastPainter;

  vtkWeakPointer<vtkRenderer> Renderer;

  vtkAbstractContextBufferId *BufferId;
  bool BufferIdDirty;

  bool UseBufferId;

  bool BufferIdSupportTested;
  bool BufferIdSupported;

  bool ScaleTiles;

  /**
   * The CIM level transform.
   */
  vtkTransform2D* Transform;

private:
  vtkContextCIM(const vtkContextCIM &) = delete;
  void operator=(const vtkContextCIM &) = delete;

  typedef bool (vtkAbstractContextItem::* MouseEvents)(const vtkContextMouseEvent&);
  bool ProcessItem(vtkAbstractContextItem* cur,
                   const vtkContextMouseEvent& event,
                   MouseEvents eventPtr);
  void EventCopy(const vtkContextMouseEvent &event);

};

#endif //vtkContextCIM_h
