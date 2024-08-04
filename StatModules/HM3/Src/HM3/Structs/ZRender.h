#pragma once

#include <cstdint>

#include "ZCore.h"

class REFTAB;
class ZCAMERA;
class ZBoneModifyBase;
struct SPrims;
class IView;

class ZDrawSurface
{
public:
    enum TARGET : uint32_t;
};

class ZLNKOBJ;
class ZBaseGeom;

class ZRender
{
public:
    virtual ~ZRender() {}
    virtual void Close() = 0;
    virtual void CrashClose() = 0;
    virtual void SetWideScreen(bool) = 0;
    virtual void SetLetterBox(bool) = 0;
    virtual void SetSurroundGaming(bool) = 0;
    virtual void ShadowMode() = 0;
    virtual void SetCopyToFrontAlpha(uint32_t) = 0;
    virtual void GetDrawBase() = 0;
    virtual void unk0001() = 0;
    virtual void BeginScene() = 0;
    virtual void EndScene() = 0;
    virtual void ForceAllLeave() = 0;
    virtual void SetLOD(uint8_t *,uint32_t,uint32_t) = 0;
    virtual void AllocateDrawBuffers() = 0;
    virtual void FreeDrawBuffers() = 0;
    virtual void InvalidateDraw() = 0;
    virtual void FadeScreen(float,uint32_t) = 0;
    virtual void LockDrawBaseGeomsBuffer(void **) = 0;
    virtual void UnlockDrawBaseGeomsBuffer() = 0;
    virtual void unk0002() = 0;
    virtual void CopyFrontToBack() = 0;
    virtual void GetClippedPrimTriangles(REFTAB *,uint32_t,float *,uint32_t,float const*,float const*,ZCAMERA *,ZBoneModifyBase *) = 0;
    virtual void DrawMemory(uint32_t const*,uint32_t) = 0;
    virtual void DrawMemory(uint32_t) = 0;
    virtual void DrawDebugObjectPrim(SPrims const*,float *,float *,uint32_t,uint32_t) = 0;
    virtual void ToggleMode(int) = 0;
    virtual void ResetFadeingLights(ZLNKOBJ *) = 0;
    virtual void SetKeepInside(bool) = 0;
    virtual void GetKeepInside() = 0;
    virtual void Dump(char const*) = 0;
    virtual void GetCameraList() = 0;
    virtual void CreateView(uint32_t,ZDrawSurface::TARGET) = 0;
    virtual void FindView(uint32_t) = 0;
    virtual void GetViewByIndex(int) = 0;
    virtual void RemoveView(IView *) = 0;
    virtual void AddCamera(ZCAMERA *,uint32_t,float) = 0;
    virtual void InitCamera(ZCAMERA *) = 0;
    virtual ZREF GetCamera(int) = 0;
    virtual void RemoveCamera(ZCAMERA *,uint32_t) = 0;
    virtual void RemoveCameras() = 0;
    virtual void ChkCamera(ZCAMERA *) = 0;
    virtual void SetCameraPrio(ZCAMERA *,float) = 0;
    virtual void Update() = 0;
    virtual void UpdateCameras() = 0;
    virtual void HandleShadows() = 0;
    virtual void GetSizeX() = 0;
    virtual void GetSizeY() = 0;
    virtual void SetSize(int,int) = 0;
    virtual void ScreenAspectXY() = 0;
    virtual void PixelAspectXY() = 0;
    virtual void GetTextSizeX() = 0;
    virtual void GetTextSizeY() = 0;
    virtual void GetLetterSizeX() = 0;
    virtual void GetLetterSizeY() = 0;
    virtual void SetFontSize(float const*) = 0;
    virtual void GetFontSize(float *) = 0;
    virtual void SetEnvironment(float,int) = 0;
    virtual void PlotStatCounters(int) = 0;
    virtual void GetMouse(float *) = 0;
    virtual void GetMouse3D(float *) = 0;
    virtual void GetMouseButtons(bool &,bool &,bool &) = 0;
    virtual void unk0003() = 0;
    virtual void UPlotF(int,int,char const*) = 0;
    virtual void UPlotFNxt(char const*) = 0;
    virtual void SetViewport(float,float,float,float) = 0;
    virtual void ClearViewport(uint32_t,uint32_t) = 0;
    virtual void SetState() = 0;
    virtual void ResetState() = 0;
    virtual void PushState() = 0;
    virtual void PopState() = 0;
    virtual void SetProjection(float,float,float,float,float,float,bool) = 0;
    virtual void SetModelView(float const*,float const*,float,float) = 0;
    virtual void SetFog(float,float,uint32_t) = 0;
    virtual void GetRenderName() = 0;
    virtual void ProgressBar(float,uint32_t,uint32_t) = 0;
    virtual void RemoveBaseGeom(ZBaseGeom *) = 0;
    virtual void UpdateBaseGeom(ZBaseGeom *) = 0;
    virtual void ChangePrim(ZBaseGeom *,uint32_t) = 0;
    virtual void BeginShadows() = 0;
    virtual void AddShadow(ZBaseGeom *,ZBaseGeom *,ZBaseGeom *,ZBaseGeom **,uint32_t) = 0;
    virtual void EndShadows() = 0;
    virtual void SetEditCursor(int) = 0;
    virtual void GetEditCursor() = 0;
    virtual void SetMaxFrameInterval(uint32_t) = 0;
    virtual void UpdateShortCuts() = 0;
};