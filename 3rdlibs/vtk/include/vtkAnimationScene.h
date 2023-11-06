/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkAnimationCIM.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
/**
 * @class   vtkAnimationCIM
 * @brief   the animation CIM manager.
 *
 * vtkAnimationCue and vtkAnimationCIM provide the framework to support
 * animations in VTK. vtkAnimationCue represents an entity that changes/
 * animates with time, while vtkAnimationCIM represents CIM or setup
 * for the animation, which consists of individual cues or other CIMs.
 *
 * A CIM can be played in real time mode, or as a sequence of frames
 * 1/frame rate apart in time.
 * @sa
 * vtkAnimationCue
*/

#ifndef vtkAnimationCIM_h
#define vtkAnimationCIM_h

#include "vtkCommonDataModelModule.h" // For export macro
#include "vtkAnimationCue.h"

class vtkAnimationCue;
class vtkCollection;
class vtkCollectionIterator;
class vtkTimerLog;

class VTKCOMMONDATAMODEL_EXPORT vtkAnimationCIM: public vtkAnimationCue
{
public:
  vtkTypeMacro(vtkAnimationCIM, vtkAnimationCue);
  void PrintSelf(ostream& os, vtkIndent indent) override;
  static vtkAnimationCIM* New();

  //@{
  /**
   * Get/Set the PlayMode for running/playing the animation CIM.
   * In the Sequence mode, all the frames are generated one after the other.
   * The time reported to each Tick of the constituent cues (during Play) is
   * incremented by 1/frame rate, irrespective of the current time.
   * In the RealTime mode, time indicates the instance in time.
   */
  vtkSetMacro(PlayMode, int);
  void SetModeToSequence() { this->SetPlayMode(PLAYMODE_SEQUENCE); }
  void SetModeToRealTime() { this->SetPlayMode(PLAYMODE_REALTIME); }
  vtkGetMacro(PlayMode, int);
  //@}

  //@{
  /**
   * Get/Set the frame rate (in frames per second).
   * This parameter affects only in the Sequence mode. The time interval
   * indicated to each cue on every tick is progressed by 1/frame-rate seconds.
   */
  vtkSetMacro(FrameRate, double);
  vtkGetMacro(FrameRate, double);
  //@}

  //@{
  /**
   * Add/Remove an AnimationCue to/from the CIM.
   * It's an error to add a cue twice to the CIM.
   */
  void AddCue(vtkAnimationCue* cue);
  void RemoveCue(vtkAnimationCue* cue);
  void RemoveAllCues();
  int  GetNumberOfCues();
  //@}

  /**
   * Starts playing the animation CIM. Fires a vtkCommand::StartEvent
   * before play beings and vtkCommand::EndEvent after play ends.
   */
  virtual void Play();

  /**
   * Stops the animation CIM that is running.
   */
  void Stop();

  //@{
  /**
   * Enable/Disable animation loop.
   */
  vtkSetMacro(Loop, int);
  vtkGetMacro(Loop, int);
  //@}

  /**
   * Makes the state of the CIM same as the given time.
   */
  void SetAnimationTime(double time);

  /**
   * Overridden to allow change to Normalized mode only
   * if none of the constituent cues is in Relative time mode.
   */
  void SetTimeMode(int mode) override;

  /**
   * Returns if the animation is being played.
   */
  int IsInPlay() { return this->InPlay; }

  enum PlayModes
  {
    PLAYMODE_SEQUENCE=0,
    PLAYMODE_REALTIME=1
  };

protected:
  vtkAnimationCIM();
  ~vtkAnimationCIM() override;

  //@{
  /**
   * Called on every valid tick.
   * Calls ticks on all the contained cues.
   */
  void TickInternal(double currenttime, double deltatime, double clocktime) override;
  void StartCueInternal() override;
  void EndCueInternal() override;
  //@}

  void InitializeChildren();
  void FinalizeChildren();

  int PlayMode;
  double FrameRate;
  int Loop;
  int InPlay;
  int StopPlay;

  vtkCollection* AnimationCues;
  vtkCollectionIterator* AnimationCuesIterator;
  vtkTimerLog* AnimationTimer;

private:
  vtkAnimationCIM(const vtkAnimationCIM&) = delete;
  void operator=(const vtkAnimationCIM&) = delete;
};

#endif
