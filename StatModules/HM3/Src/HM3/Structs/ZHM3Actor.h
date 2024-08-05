#pragma once

#include <stdafx.h>
#include "ZCore.h"
#include <DirectXMath.h>

class ISerializerStream;
class IInputSerializerStream;
class IOutputSerializerStream;
class ZCheckPointBuffer;

namespace Animation
{
    class ActiveAnimation;
    class Header;
    class ZMetaKey;
}

class ZBaseGeom;
class ZDrawBuffer;
class ZCameraSpace;
class ZCAMERA;
class ZMatrix;
class ZBone;
class ZEventBase;
class COLI;
class ZGROUP;
class SInputActionDefinition;
class SInputAction;
class SBoneDefinition;
class ZLNKOBJ;
class ZAnimVariationHandle;
class ZLnkAction;
class ZAction;
class HANDPICKUP;
class HANDSPICKUP;
class ITEMHANDS;
class ZItemTemplateWeapon;
class ZItemWeapon;
class ZItemTemplate;
class ZItem;
class ZIKHAND;
enum ITEMSTATE : uint32_t;
class REFTAB;
class LocomotionInfo;
struct SExtendedImpactInfo;
class SRigidBodyVelocity;
class ZHM3Actor;
class ZMovementBase;
class ZMoveNotify;
class ZHM3HmAs;
class ZROOM;
struct SScreenSelect;
class ZRender;

struct SVector3
{
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
};

struct SMatrix33
{
    SVector3 xAxis = SVector3{ 1.0f, 0.0f, 0.0f };
    SVector3 yAxis = SVector3{ 0.0f, 1.0f, 0.0f };
    SVector3 zAxis = SVector3{ 0.0f, 0.0f, 1.0f };
};

class ZBaseGeom
{
public:
    SMatrix33 m_mMat;
    SVector3 m_vPos;
    PAD(32)
    ZBaseGeom* m_pParent;
    PAD(24)
    const char* m_szName;

    void GetRootMatPos(SMatrix33& mat, SVector3& pos) const
    {
        float v12; // $f9
        float v13; // $f10
        ZBaseGeom* v15; // $a4
        float x; // $f21
        float y; // $f22
        float z; // $f23
        float _$F0, _$F1, _$F2, _$F3, _$F4, _$F5, _$F6, _$F7, _$F8, _$F11;
        float acc;

        auto th = this;
        v15 = m_pParent;
        while (1)
        {
            auto _$F12 = th->m_mMat.zAxis.x;
            auto  _$F13 = th->m_mMat.zAxis.y;
            if (!v15)
                break;
            auto _$F14 = th->m_mMat.zAxis.z;
            auto _$F15 = th->m_mMat.yAxis.x;
            auto _$F16 = th->m_mMat.yAxis.y;
            auto _$F17 = th->m_mMat.yAxis.z;
            auto _$F18 = th->m_mMat.xAxis.x;
            auto _$F19 = th->m_mMat.xAxis.y;
            auto _$F20 = th->m_mMat.xAxis.z;
            float _$F21, _$F22, _$F23, _$F24, _$F25, _$F26, _$F27, _$F28, _$F9, _$F10;
            x = th->m_vPos.x;
            y = th->m_vPos.y;
            z = th->m_vPos.z;
            th = v15;
            acc = (_$F9 * _$F12);
            v15 = v15->m_pParent;
            acc += _$F10 + _$F15;
            _$F24 = acc + (_$F11 * _$F18);
            acc = (_$F9 * _$F13);
            acc += _$F10 + _$F16;
            _$F25 = acc + (_$F11 * _$F19);
            acc = (_$F9 * _$F14);
            acc += _$F10 + _$F17;
            _$F26 = acc + (_$F11 * _$F20);
            v12 = x + _$F24;
            v13 = y + _$F25;
            acc = (_$F12 * _$F0);
            _$F11 = z + _$F26;
            acc += _$F15 + _$F1;
            _$F21 = acc + (_$F18 * _$F2);
            acc = (_$F13 * _$F0);
            acc += _$F16 + _$F1;
            _$F22 = acc + (_$F19 * _$F2);
            acc = (_$F14 * _$F0);
            acc += _$F17 + _$F1;
            _$F23 = acc + (_$F20 * _$F2);
            acc = (_$F12 * _$F3);
            acc += _$F15 + _$F4;
            _$F24 = acc + (_$F18 * _$F5);
            acc = (_$F13 * _$F3);
            acc += _$F16 + _$F4;
            _$F25 = acc + (_$F19 * _$F5);
            acc = (_$F14 * _$F3);
            acc += _$F17 + _$F4;
            _$F26 = acc + (_$F20 * _$F5);
            acc = (_$F12 * _$F6);
            acc += _$F15 + _$F7;
            _$F27 = acc + (_$F18 * _$F8);
            acc = (_$F13 * _$F6);
            acc += _$F16 + _$F7;
            _$F28 = acc + (_$F19 * _$F8);
            acc = (_$F14 * _$F6);
            acc += _$F17 + _$F7;
            _$F8 = acc + (_$F20 * _$F8);
            _$F0 = _$F21;
            _$F1 = _$F22;
            _$F2 = _$F23;
            _$F3 = _$F24;
            _$F4 = _$F25;
            _$F5 = _$F26;
            _$F6 = _$F27;
            _$F7 = _$F28;
        }
        mat.zAxis.x = _$F0;
        mat.zAxis.y = _$F1;
        mat.zAxis.z = _$F2;
        mat.yAxis.x = _$F3;
        mat.yAxis.y = _$F4;
        mat.yAxis.z = _$F5;
        mat.xAxis.x = _$F6;
        mat.xAxis.y = _$F7;
        mat.xAxis.z = _$F8;
        pos.x = v12;
        pos.y = v13;
        pos.z = _$F11;
    }
};

static_assert(offsetof(ZBaseGeom, m_pParent) == 80, "ZBaseGeom->m_pParent");
static_assert(offsetof(ZBaseGeom, m_szName) == 108, "ZBaseGeom->m_szName");

class ZSerializable
{
public:
    virtual ~ZSerializable()
    {
    }

    virtual void PreSave(ISerializerStream&) = 0;
    virtual void PostSave(ISerializerStream&) = 0;
    virtual void PreLoad(ISerializerStream&) = 0;
    virtual void PostLoad(ISerializerStream&) = 0;
    virtual void PostProcess(uint32_t, uint32_t) = 0;
    virtual void LoadSave(ISerializerStream&, bool) = 0;
    virtual void LoadObject(IInputSerializerStream&) = 0;
    virtual void SaveObject(IOutputSerializerStream&) = 0;
    virtual void ExchangeObject(ISerializerStream&) = 0;
    virtual void SetToDefault() = 0;
    virtual void* GetTypeID() = 0;
};

namespace RTP
{
    class cBase : public ZSerializable
    {
    public:
        virtual void* GetProperties() = 0;
    };
}

class ZGeomEventList
{
public:
    uint8_t m_nUnk01;
    uint8_t m_nUnk02;
    uint8_t m_nUnk03;
    uint8_t m_nUnk04;
};

class ZGEOM : public RTP::cBase
{
public:
    struct ExtraInitData
    {
        uint16_t m_nUnk01;
        ZGeomEventList m_EventList;
    };

    virtual ZREF GetObjectId() = 0;
    virtual void GetObjectIdAndMask(uint32_t&, uint32_t&) = 0;
    virtual void GetOldClassInfo() = 0;
    virtual void DoInit() = 0;
    virtual void unk0000() = 0;
    virtual void PreSaveGame() = 0;
    virtual void CheckPointSave(ZCheckPointBuffer&) = 0;
    virtual void CheckPointLoad(ZCheckPointBuffer&) = 0;
    virtual void Activate(bool) = 0;
    virtual void MakeInactive() = 0;
    virtual void MakeActive() = 0;
    virtual void GetBoundTreeType() = 0;
    virtual void AnimCallBackToId(bool (ZHM3Actor::*)(Animation::ActiveAnimation*, float, float, uint32_t)) = 0;
    virtual void AnimCallBackFromId(int) = 0;
    virtual void CameraMessages(bool) = 0;
    virtual void CreateExData() = 0;
    virtual void FreeExData() = 0;
    virtual void CopyExData(ZHM3Actor const*) = 0;
    virtual void GetChunkData(int) = 0;
    virtual void RecurGetNext(ZBaseGeom const**) = 0;
    virtual void DisableParentBoundAdjust() = 0;
    virtual void ExpandBounds(float*, float*, float*, ZBaseGeom*) = 0;
    virtual void SetMat(float const*) = 0;
    virtual void SetPos(float const*) = 0;
    virtual void SetMatPos(float const*, float const*) = 0;
    virtual void SetWorldPosition(float const*) = 0;
    virtual void SetRootTM(float const*, float const*) = 0;
    virtual void Display(bool) = 0;
    virtual void Select(bool) = 0;
    virtual void Hide(bool) = 0;
    virtual void HideRecursive(bool) = 0;
    virtual void Freeze(bool) = 0;
    virtual void DispBound(bool) = 0;
    virtual void SetMoving(bool) = 0;
    virtual void RequestCustomDraw() = 0;
    virtual void HasOwnerDraw() = 0;
    virtual void OwnerDraw(ZBaseGeom*, uint32_t, ZDrawBuffer*, ZCAMERA*, float const*, float const*, void const*) = 0;
    virtual void CorrectOwnerDrawMatrix(float*, float*, ZBaseGeom*, uint32_t) = 0;
    virtual void CorrectOwnerDrawPartMatrix(ZMatrix*, ZBaseGeom*, ZBone*) = 0;
    virtual void WantDrawBufferControl() = 0;
    virtual void DrawUpdate() = 0;
    virtual void DrawBufferViewUpdate(ZDrawBuffer*, ZCameraSpace*) = 0;
    virtual void DrawBufferViewUpdate(ZDrawBuffer*, ZBaseGeom*, uint32_t) = 0;
    virtual void WantViewPrimHideUnhideRequest() = 0;
    virtual void WantViewPrimHide(uint8_t, bool) = 0;
    virtual void WantViewPrimHideMirrors(uint8_t) = 0;
    virtual void WantViewUseAllLOD() = 0;
    virtual void GetLODMaskOverride() = 0;
    virtual void GetSortPriority() = 0;
    virtual void CopyEvents(ZHM3Actor const*) = 0;
    virtual void FindEvent(char const*) = 0;
    virtual void GetEventData(char*) = 0;
    virtual void AddEvent(char const*) = 0;
    virtual void AttachEvent(ZEventBase&) = 0;
    virtual void EnableClassCall(uint32_t) = 0;
    virtual void DisableClassCall(uint32_t) = 0;
    virtual void SetClassTimerInterval(float) = 0;
    virtual void CallEvents(int, void*, int, ZHM3Actor*) = 0;
    virtual void SendCommand(ZHM3Actor*, uint16_t, void*) = 0;
    virtual void SendCommand(uint32_t, uint16_t, void*) = 0;
    virtual void SendCommand(uint16_t, void*, ZHM3Actor*) = 0;
    virtual void FreeEvents() = 0;
    virtual void SendCommandRecursive(uint16_t, void*, ZHM3Actor*) = 0;
    virtual void SendCommandRecursive(uint32_t, uint16_t, void*) = 0;
    virtual void FreeEvent(ZEventBase*) = 0;
    virtual void FreeEvent(char const*) = 0;
    virtual void RemoveEventFromList(ZEventBase*) = 0;
    virtual void RegisterInstance(uint32_t) = 0;
    virtual void ClassInit() = 0;
    virtual void ClassInit2() = 0;
    virtual void PostClassInit() = 0;
    virtual void PostClassInit2() = 0;
    virtual void ClassDisplay() = 0;
    virtual void ClassFrameUpdate() = 0;
    virtual void ClassTimeUpdate() = 0;
    virtual void ClassCommand(uint16_t, void*) = 0;
    virtual void ClassPushPopScene(bool) = 0;
    virtual void ChkLineColi(COLI*, bool) = 0;
    virtual void CheckPointInside(float const*, float) = 0;
    virtual void CheckPointInsideBound(float const*) = 0;
    virtual void CheckBoxInside(float const*, float const*, float const*) = 0;
    virtual void GetPointInsideDistance(float const*) = 0;
    virtual void Visible() = 0;
    virtual void Invisible() = 0;
    virtual void PushState() = 0;
    virtual void PopState() = 0;
    virtual void DuplicateData(ZHM3Actor*) = 0;
    virtual void Duplicate(ZGROUP*, char const*, bool) = 0;
    virtual void DuplicateInit(ZGROUP*, float const*, float const*, char const*, bool) = 0;
    virtual void DuplicateToResource(ZGROUP*, uint32_t, char const*, bool) = 0;
    virtual void DuplicateToResourceInit(ZGROUP*, uint32_t, float const*, float const*, char const*, bool) = 0;
    virtual void CopyData(ZHM3Actor const*) = 0;
    virtual void AddActionMap(SInputActionDefinition*, char*) = 0;
    virtual void RemoveActionMap(char*) = 0;
    virtual void CheckAction(int, void*) = 0;
    virtual void CheckAction(char*, void*) = 0;
    virtual void CheckAction(SInputAction*, void*) = 0;
    virtual void GetActionID(char*) = 0;
    virtual void GetActionPtr(int) = 0;
    virtual void GetActionPtr(char*) = 0;
    virtual void IsAttached() = 0;
    virtual void SetAttachedTo(ZLNKOBJ*) = 0;
    virtual void GetAttachedTo() = 0;
    virtual void IsLinkBaseObj() = 0;
    virtual void OnCameraEnter() = 0;

    /*
    Freeze = m_nFlags | 0x10
    Unfreeze = m_nFlags & 0xFFEF
    Display = m_nFlags | 1
    Undisplay = m_nFlags & 0xFFFE
    Select = m_nFlags | 9
    Unselect = m_nFlags & 0xFFF7
    DispBound = m_nFlags | 5
    UndispBound = m_nFlags & 0xFFFB
    */

    ZBaseGeom* m_pBaseGeom; // 0x0004
    ExtraInitData* m_pExtraInitData; // 0x0008
    uint16_t m_nFlags; // 0x000C
    uint16_t m_eStatus; // 0x000E

    /*DirectX::XMMATRIX GetTransform() const
    {
        static const auto s_UnitTransform = DirectX::XMMatrixSet(
            1.f, 0.f, 0.f, 0.f,
            0.f, 1.f, 0.f, 0.f,
            0.f, 0.f, 1.f, 0.f,
            0.f, 0.f, 0.f, 1.f
        );

        if (!m_pBaseGeom)
            return s_UnitTransform;

        return m_pBaseGeom->GetTransform();
    }*/
};

static_assert(sizeof(ZGEOM) == 16, "ZGEOM");

class ZSTDOBJ : public ZGEOM
{
};

static_assert(sizeof(ZSTDOBJ) == 16, "ZSTDOBJ");

class ZLNKOBJ : public ZSTDOBJ
{
public:
    virtual void InitObjMatBone() = 0;
    virtual void CloseObjMatBone() = 0;
    virtual void GetAnim(char const*) = 0;
    virtual void StopAllAnims(bool) = 0;
    virtual void StopUBAnims() = 0;
    virtual void StopAnim(Animation::ActiveAnimation*) = 0;
    virtual void ActivateAnimSegment(Animation::Header*, int, float, float, float) = 0;
    virtual void ActivateAnimSegment(ZAnimVariationHandle, int, float, float, float) = 0;
    virtual void ActivateAnim(Animation::Header*, int) = 0;
    virtual void SetActiveAnimDestination(float const*, float const*, float) = 0;
    virtual void CheckActiveAnim(Animation::Header*, int) = 0;
    virtual void SetBoneFrameBlend(Animation::Header*, float, float, bool, uint32_t) = 0;
    virtual void SetDualFrame(Animation::Header*, float, Animation::Header*, float, float, float) = 0;
    virtual void GroundAnimated() = 0;
    virtual void OnMetaKey(Animation::ActiveAnimation*, Animation::ZMetaKey*, char const*) = 0;
    virtual void ActivatePoseAnim(char*, float, uint32_t, float) = 0;
    virtual void StopPoseAnim(uint32_t, bool) = 0;
    virtual void StopAudio() = 0;
    virtual void StopAnimSound(bool, int, bool) = 0;
    virtual void StopAllAnimSounds() = 0;
    virtual void CheckLineCollision(float*, float const*, float const*) = 0;
    virtual void CheckLineCollision(float*, float const*, float const*, float*) = 0;
    virtual void CheckBoxCollision(float const*, float const*, float const*) = 0;
    virtual void Use2Skeletons() = 0;
    virtual void LocalStateIK() = 0;
    virtual void GetDefaultBones(ZBone*, uint32_t) = 0;
    virtual void SetDefaultBones(ZBone const*, SBoneDefinition const*) = 0;
    virtual void GetAnimDeltaBones(Animation::Header*) = 0;
    virtual void GetBoneMatPos(float*, float*, uint32_t) = 0;
    virtual void AttachBaseGeomToBone(ZBaseGeom const*, uint32_t, float const*, float const*) = 0;
    virtual void DetachBaseGeomFromBone(ZBaseGeom const*, uint32_t) = 0;
    virtual void GetAttachedBaseGeomBoneId(ZBaseGeom const*) = 0;
    virtual void GetGroundBoneAnimMatPos(float (&)[9], float (&)[3], Animation::Header*, float, bool) = 0;
    virtual void GetGroundBoneDeltaMatPos(float (&)[9], float (&)[3], Animation::Header*, float, float) = 0;
    virtual void GetAttachedGeomMatPos(ZBaseGeom const*, float*, float*) = 0;
    virtual void DisplayBone(uint32_t, bool) = 0;
    virtual void GetFocusMatPos(float*, float*) = 0;
    virtual void DisplayAllBones(bool) = 0;
    virtual void GetRootFocusMatPos(float*, float*) = 0;
    virtual void GetBoneNrFromId(uint8_t) = 0;
    virtual void GetBoneFromPoint(float const*) = 0;
    virtual void GetBoneNrFromName(char const*) = 0;
    virtual void GetBoneName(int) = 0;
    virtual void GetOrigLocalBones() = 0;
    virtual void GetBoneDefinitions() = 0;
    virtual void CopyGeometryFrom(ZHM3Actor*) = 0;
    virtual void CopyGeometryFrom(uint32_t) = 0;
    virtual void CopyPoseFrom(ZLNKOBJ*) = 0;
    virtual void ChangeMesh(ZGROUP*) = 0;
    virtual void PrintAllBoneNames() = 0;
    virtual void SetCutSequence(bool) = 0;
    virtual void MoveToMatPos(float const*, float const*) = 0;
    virtual void SetRootTMParent(float*, float*) = 0;
    virtual void EventCallBack(Animation::ActiveAnimation*, float, float, void*) = 0;
    virtual void OnMoving() = 0;
    virtual void OnMoved() = 0;
    virtual void CalcTightCenSize(float*, float*) = 0;
    virtual void CalcShadowProjectPlane(float*, float const*, float const*) = 0;
    virtual void GetBoneControl(int) = 0;
    virtual void UpdateGeometry(bool) = 0;
    virtual void ResetAllAnimBones() = 0;
    virtual void ResetInactiveBones() = 0;
    virtual void ExecuteCallBack(char const*) = 0;
    virtual void GetBoneVolume(int) = 0;
    virtual void GetBoneSize(int, float*) = 0;
    virtual void GetBoneCenter(int, float*) = 0;
    virtual void AnimEnd(Animation::ActiveAnimation*, int) = 0;
    virtual void UpdateAnimationsAndGroundLink(float) = 0;
    virtual void UpdatePoseAnimation() = 0;
    virtual void StartAnim(Animation::ActiveAnimation*, int) = 0;
    virtual void IsInElevator() = 0;
    virtual void GetElevatorDeltaY() = 0;
    virtual void WantBloodOnHit() = 0;
    virtual void LoadSaveAnimations(ISerializerStream&, bool) = 0;

    PAD(228)
};

static_assert(sizeof(ZLNKOBJ) == 244, "ZLNKOBJ");

class ZIKLNKOBJ : public ZLNKOBJ
{
public:
    class SIKBoneCollision;

    virtual void ActivateRagdoll(bool, bool, bool) = 0;
    virtual void CalcAnimRemapNames() = 0;
    virtual void EnableIK() = 0;
    virtual void DisableIK() = 0;
    virtual void DisableControls() = 0;
    virtual void EnableControls() = 0;
    virtual void ForceFacing(float const*) = 0;
    virtual void GetFocalPoint(float*) = 0;
    virtual void Reset() = 0;
    virtual void GetRootCenter(float*, float*) = 0;
    virtual void GetBoneCollision(float const*, float const*) = 0;
    virtual void GetOwnerMoveSpeed() = 0;
    virtual void GetIKBoneMatPos(int, float*, float*) = 0;
    virtual void GetIKBoneMat(int, float*) = 0;
    virtual void GetIKBonePos(int, float*) = 0;
    virtual void SetHeadTarget(float const*, float) = 0;
    virtual void ResetHeadTarget() = 0;
    virtual void HeadBoneIndex() = 0;
    virtual void NeckBoneIndex() = 0;
    virtual void PelvisBoneIndex() = 0;
    virtual void LHandBoneIndex() = 0;
    virtual void RHandBoneIndex() = 0;
    virtual void LToeBoneIndex() = 0;
    virtual void RToeBoneIndex() = 0;
    virtual void IKCallBackToId(void (ZIKLNKOBJ::*)()) = 0;
    virtual void IKCallBackFromId(int) = 0;
    virtual void SetFacingTarget(uint32_t, float, void (ZIKLNKOBJ::*)()) = 0;
    virtual void RemoveFacingTarget(float, void (ZIKLNKOBJ::*)()) = 0;
    virtual void DisableFacing() = 0;
    virtual void EnableFacing() = 0;
    virtual void CreateActionDispatcher() = 0;
    virtual void RunLnkAction(ZLnkAction*) = 0;
    virtual void RemoveCurrentLnkAction() = 0;
    virtual void UpdateCurrentLnkAction() = 0;
    virtual void CallBackLnkActionTarget() = 0;
    virtual void CallBackLnkActionBone(Animation::ActiveAnimation*, float, float, uint32_t) = 0;
    virtual void CreateLnkAction(uint32_t) = 0;
    virtual void CurrentLnkActionId() = 0;
    virtual void GetCurrentLnkAction() = 0;
    virtual void DisplayGround(bool) = 0;
    virtual void EmitFootDustParticle(float, int) = 0;
    virtual void MakeFootPrint(bool) = 0;
    virtual void UpdateHead() = 0;
    virtual void UpdateFacing() = 0;
    virtual void UpdateTargets() = 0;
    virtual void ResetTargets() = 0;
    virtual void RemoveTargets() = 0;

    PAD(156)
};

static_assert(sizeof(ZIKLNKOBJ) == 400, "ZIKLNKOBJ");

class ZCTRLIKLNKOBJ : public ZIKLNKOBJ
{
public:
    class CONTROLLER;

    virtual void SetController(ZCTRLIKLNKOBJ::CONTROLLER) = 0;
    virtual void GetController() = 0;
    virtual void SetContactGeom(uint32_t) = 0;
    virtual void GetContactGeom() = 0;
    virtual void CanOperateObject(ZAction*, float (*)[9], float (*)[3], bool) = 0;
    virtual void OperateObject(ZAction*) = 0;
    virtual bool IsRunning() = 0;
    virtual bool IsSneaking() = 0;
    virtual bool IsDead() = 0;
    virtual void SetLightReceived(float) = 0;
    virtual void LightReceived() = 0;
    virtual void ReducedSight(uint32_t) = 0;
    virtual void GetSeerPosDir(float*, float*) = 0;
    virtual void GetVisionPos(float*) = 0;

    PAD(16)
};

static_assert(sizeof(ZCTRLIKLNKOBJ) == 416, "ZCTRLIKLNKOBJ");

class ZLNKWHANDS : public ZCTRLIKLNKOBJ
{
public:
    enum EFootSide : uint32_t;

    virtual void AddNearItem(uint32_t) = 0;
    virtual void RemoveNearItem(uint32_t) = 0;
    virtual void OnBoidPushing(ZLNKWHANDS*) = 0;
    virtual void OnBoidPushed(ZLNKWHANDS*) = 0;
    virtual void CheckRHandFireTarget() = 0;
    virtual void GetRHandFireTarget() = 0;
    virtual void SetAimInPosition(bool) = 0;
    virtual void AddAction(int, uint32_t) = 0;
    virtual void GetAnimNameFromCollision(ZIKLNKOBJ::SIKBoneCollision*, bool, ZItemTemplateWeapon*) = 0;
    virtual void ReloadItem(ZItem*) = 0;
    virtual void LetItemFall(ZItem*) = 0;
    virtual void ShowReloadAnim(ZItemWeapon*) = 0;
    virtual void ShowChamberAnim(ZItemWeapon*) = 0;
    virtual void ControlPickup(ZItem*) = 0;
    virtual void ControlUseOneExtra(uint32_t) = 0;
    virtual void ControlUseOneAlone(uint32_t) = 0;
    virtual void ControlUseTwo(uint32_t, uint32_t) = 0;
    virtual void ControlDrop(ZItem*) = 0;
    virtual void GetPickupAction(HANDPICKUP&, HANDPICKUP&, HANDSPICKUP&, ITEMHANDS, ITEMHANDS, ITEMHANDS, bool) = 0;
    virtual void ModifyPickupAction(ITEMHANDS&, ITEMHANDS&, ITEMHANDS&, ZItemTemplate*) = 0;
    virtual void OnlyVerticalAim() = 0;
    virtual void GetAimAnim(Animation::Header**, uint32_t&) = 0;
    virtual void GetPoseEffects(float*, short*) = 0;
    virtual void SetHandTarget(int, float*, float) = 0;
    virtual void DontAnimateAttachers() = 0;
    virtual void RemoveLHandIKTarget(float, void (ZIKLNKOBJ::*)()) = 0;
    virtual void RemoveRHandIKTarget(float, void (ZIKLNKOBJ::*)()) = 0;
    virtual void UpdateAimTarget() = 0;
    virtual void SetAimTarget(float const*, float, void (ZIKLNKOBJ::*)()) = 0;
    virtual void SetAimTarget(uint32_t, float const*, float, void (ZIKLNKOBJ::*)(), int) = 0;
    virtual void RemoveAimTarget(float, void (ZIKLNKOBJ::*)()) = 0;
    virtual void FreezeAimTarget() = 0;
    virtual void DisableAim() = 0;
    virtual void EnableAim() = 0;
    virtual void GetAimTarget(float*) = 0;
    virtual void GetAimTarget(uint32_t*) = 0;
    virtual void GetAimTarget() = 0;
    virtual void GetDrawWeaponSpeed() = 0;
    virtual void IsAiming() = 0;
    virtual void SetAimAnimPrc(float, float, float) = 0;
    virtual void FireShotNotify() = 0;
    virtual void SetHitAnimation(char const*) = 0;
    virtual void SetHitAnimHandle(ZAnimVariationHandle&) = 0;
    virtual void UseItem(ZItem*, int) = 0;
    virtual void DropItem(ZItem*) = 0;
    virtual void PickupItem(ZItem*) = 0;
    virtual void Reload(ZItem*) = 0;
    virtual void Chamber(ZItem*) = 0;
    virtual void PerformDrop(ZItem*, bool, bool) = 0;
    virtual void GetRHand() = 0;
    virtual void GetLHand() = 0;
    virtual void GetLHandItem() = 0;
    virtual void GetRHandItem() = 0;
    virtual void GetLHandWeapon() = 0;
    virtual void GetRHandWeapon() = 0;
    virtual void GetRHandItemType() = 0;
    virtual void GetLHandItemType() = 0;
    virtual void SetRHandItemState(ITEMSTATE) = 0;
    virtual void SetLHandItemState(ITEMSTATE) = 0;
    virtual void AttachItemToHand(ZIKHAND*, uint32_t) = 0;
    virtual void AttachRHandItem(uint32_t) = 0;
    virtual void AttachLHandItem(uint32_t) = 0;
    virtual void GetNearItems() = 0;
    virtual void SetDialog(bool) = 0;
    virtual void GetDialog() = 0;
    virtual void DialogListen(int) = 0;
    virtual void DialogTalk(int) = 0;
    virtual void SlipRHandItem() = 0;
    virtual void SlipLHandItem() = 0;
    virtual void ForceLHandItem(ZItem*, bool) = 0;
    virtual void ForceRHandItem(ZItem*, bool) = 0;
    virtual void DestroyRHandItem() = 0;
    virtual void DestroyLHandItem() = 0;
    virtual void EmptyHands() = 0;
    virtual void GetAmmoFor(ZItemWeapon*) = 0;
    virtual void SetAmmoFor(ZItemWeapon*, int) = 0;
    virtual void SetLHandIKTarget(float const*, float const*, float, void (ZIKLNKOBJ::*)()) = 0;
    virtual void SetRHandIKTarget(float const*, float const*, float, void (ZIKLNKOBJ::*)()) = 0;
    virtual void UpdateItemActions() = 0;
    virtual void CallBackItemAction() = 0;
    virtual void unk0001() = 0;
    virtual void PlaySpeech(uint32_t, int, bool) = 0;
    virtual void PlayFootStep(ZLNKWHANDS::EFootSide) = 0;
    virtual void IsFirstPersonCamera() = 0;
    virtual void GetCombatStrength() = 0;

    PAD(560)
};

static_assert(sizeof(ZLNKWHANDS) == 976, "ZLNKWHANDS");

class ZActor : public ZLNKWHANDS
{
public:
    enum ACTORSTATE : uint32_t;
    enum PATH_CANCEL_REASONS : uint32_t;
    enum PATH_ERRORS : uint32_t;

    virtual void SetActorRootTM(float const*, float const*) = 0;
    virtual void SetActorPosDir(float const*, float const*) = 0;
    virtual void GetActorRootTM(float*, float*) = 0;
    virtual void GetActorWorldPosition(float*) = 0;
    virtual void SetActorWorldPosition(float const*) = 0;
    virtual void CanPlayAnimSegment(Animation::Header*, float, float, float const*, float const*, bool, float, float) =
    0;
    virtual void IsUnconscious() = 0;
    virtual void IsAwake() = 0;
    virtual void IsSleeping() = 0;
    virtual void SetHero(uint32_t) = 0;
    virtual void SetActorState(ZActor::ACTORSTATE) = 0;
    virtual void OnViewEnter() = 0;
    virtual void OnViewLeave() = 0;
    virtual void GetPathFinder4() = 0;
    virtual void EnablePathFinder(bool) = 0;
    virtual void SetStopDistance(float) = 0;
    virtual void SetEndDir(float const*) = 0;
    virtual void GetEndDir() = 0;
    virtual void MoveToPosition(float const*, float const*) = 0;
    virtual void SlideToPosition(float const*, float const*) = 0;
    virtual void SetPathNotify(float) = 0;
    virtual void SetPathNotifySyncToCycle(bool) = 0;
    virtual void SetEndAction(char) = 0;
    virtual void RemovePath(uint8_t, ZActor::PATH_CANCEL_REASONS, bool) = 0;
    virtual void SendPathDone(bool) = 0;
    virtual void GetMoveFromPos(float*) = 0;
    virtual void FindNextPathBlocker() = 0;
    virtual void SetShootIntoGround(bool) = 0;
    virtual void SetShootIntoGroundInFullbody(bool) = 0;
    virtual void SetStayInsidePath(bool) = 0;
    virtual void ShootIntoGround(float*, bool, bool) = 0;
    virtual void ShootIntoGroundRegularly(float*, bool, bool, float) = 0;
    virtual void SetMoveSpeedMultiplier(float) = 0;
    virtual void SetPathFinderEnabled(bool) = 0;
    virtual void OnPathRequest(uint32_t) = 0;
    virtual void OnPathFinished(uint32_t) = 0;
    virtual void OnPathCanceled(ZActor::PATH_CANCEL_REASONS) = 0;
    virtual void OnPathCanceledLockedDoor(uint32_t) = 0;
    virtual void OnPathError(ZActor::PATH_ERRORS) = 0;
    virtual void OnPathNotify() = 0;
    virtual void OnNewPath() = 0;
    virtual void OnSound(REFTAB*) = 0;
    virtual void Die() = 0;
    virtual void DieByForce(float const*, float const*, float, uint32_t) = 0;
    virtual void Resurrect() = 0;
    virtual void Knockout() = 0;
    virtual void Revive() = 0;
    virtual void GetKnockedOut() = 0;
    virtual void GetActorList() = 0;
    virtual void SetDisableIdleAnimation(bool) = 0;
    virtual void GetAudibleRoomList() = 0;
    virtual void LookAt(uint32_t) = 0;
    virtual void IsSeeing() = 0;
    virtual void SetSeeing(bool) = 0;
    virtual void IsVisible() = 0;
    virtual void SetVisible(bool) = 0;
    virtual void WantToLookAt(ZHM3Actor*, uint8_t) = 0;
    virtual void VerifyPlayerVisible() = 0;
    virtual void DeterminePathLookAt(LocomotionInfo*, float*, float*, float*, float*) = 0;
    virtual void CanLookAt(ZHM3Actor*) = 0;
    virtual void IsOnStairs() = 0;
    virtual void UpdatePositionOffScreen() = 0;
    virtual void UpdatePosition() = 0;
    virtual void GetCurrentUBAnim(ZItem*, ZItem*, bool&) = 0;
    virtual void SetHoldWeaponUBAnim(Animation::Header*) = 0;
    virtual void GetAnimOffset(char const*) = 0;
    virtual void GetAnimOffset(Animation::Header*) = 0;
    virtual void GetAnimHeader(uint32_t) = 0;
    virtual void ShootIntoGroundCallback(SExtendedImpactInfo*) = 0;

    PAD(1328)
};

static_assert(sizeof(ZActor) == 2304, "ZActor");

class ZHM3Actor : public ZActor
{
public:
    virtual void ActivateAnimSegmentWithCameraBone(Animation::Header*, int, float, float, float) = 0;
    virtual void PlaySpeechResource(uint32_t, int) = 0;
    virtual void PlaySpeechResourceWithFilter(uint32_t, int, float, float, float) = 0;
    virtual void SetWeapon(uint32_t) = 0;
    virtual void GetWeapon() = 0;
    virtual void SetWeaponTemplate(uint32_t) = 0;
    virtual void GetWeaponTemplate() = 0;
    virtual void FireWeapon(uint32_t, bool, float, bool) = 0;
    virtual void Bite(int, float*, float*, float, float) = 0;
    virtual void Punch(bool) = 0;
    virtual void StunGunAttack() = 0;
    virtual void ThrowKnifeAtRef(uint32_t, uint32_t) = 0;
    virtual void ActivateRagdollOrAnim() = 0;
    virtual void ActivateRagdollNextFrame() = 0;
    virtual void InitializeHitpoints(float) = 0;
    virtual void SetHitpoints(float) = 0;
    virtual void GetHitpoints() = 0;
    virtual void TakeDamage(float) = 0;
    virtual float GetHealth() = 0;
    virtual void GetWeaponStrength() = 0;
    virtual void IsDragEnabled() = 0;
    virtual void GetItemTemplate(uint32_t) = 0;
    virtual void CreateItemFromItemTemplate(uint32_t) = 0;
    virtual void ActivateItem(uint32_t, int) = 0;
    virtual void ConcealItem(uint32_t, bool) = 0;
    virtual void EnablePickupClothes() = 0;
    virtual void DisablePickupClothes() = 0;
    virtual void IsWearingClothes() = 0;
    virtual void OnHitmanChangedClothes() = 0;
    virtual ZREF GetHitmanAs() = 0;
    virtual void GetActorProperties() = 0;
    virtual void SetScriptUBAnim(Animation::Header*, bool) = 0;
    virtual void GetDeadBodyFlags(ZLNKOBJ*) = 0;
    virtual void StartDrag(uint32_t) = 0;
    virtual void EndDrag() = 0;
    virtual void GetAutoAimTarget() = 0;
    virtual void SetAutoAimTarget(bool) = 0;
    virtual void StoreUBHoldAnims() = 0;
    virtual void MapUBHoldAnimsToIdx() = 0;
    virtual void GetItemAssignedUBAnim(ZItem*) = 0;
    virtual void LoadSave2(ISerializerStream&) = 0;
    virtual void ActivateRigidBody(SRigidBodyVelocity const*) = 0;

    int m_eMapIcon; // 0x0900
    PAD(604)
};

static_assert(sizeof(ZHM3Actor) == 2912, "ZHM3Actor");

class ZPlayer : public ZLNKWHANDS
{
public:
    virtual void DisplayCollisionsBounds(bool) = 0;
    virtual void DisableCollision() = 0;
    virtual void EnableCollision() = 0;
    virtual void DisableT1() = 0;
    virtual void EnableT1() = 0;
    virtual void DragBody(ZGEOM*) = 0;
    virtual void GetCenterMatPos(float*, float*) = 0;
    virtual void GetCenterSphere(float*, float*, float*) = 0;
    virtual void GetGroundContact() = 0;
    virtual void SetGroundContact(bool) = 0;
    virtual void GetSuit() = 0;
    virtual void MoveCenterToMatPos(float const*, float const*) = 0;
    virtual void GetCenterHeight() = 0;
    virtual void CenterSpeed() = 0;
    virtual void GodMode() = 0;
    virtual void SetGodMode(bool) = 0;
    virtual void Die(float (*)[3], float (*)[3], float) = 0;
    virtual void SetMoveSpeeds(float const*) = 0;
    virtual void GetMoveSpeeds(float*) = 0;
    virtual void GetActualSpeed() = 0;
    virtual void ControlsEnabled() = 0;
    virtual void GetStatus() = 0;
    virtual void IsWalking() = 0;
    virtual void GetActiveMovementType() = 0;
    virtual void GetActiveMovement() = 0;
    virtual void SetMovementStatePointer(ZMovementBase* (*)[32]) = 0;
    virtual void SetActiveMovement(uint32_t) = 0;
    virtual void GetAnimNameFromCollision2(ZIKLNKOBJ::SIKBoneCollision*, bool, int) = 0;
    virtual void ReloadRHandItem(ZItem*) = 0;
    virtual void ReloadLHandItem(ZItem*) = 0;
    virtual void GetLastAnimPrc() = 0;
    virtual void GetActiveAnimMovement(float*, float*) = 0;
    virtual void SetLastAnimPrc(float) = 0;
    virtual void CallBackAimInPosition() = 0;
    virtual void HumanShieldLockSpineToHero() = 0;
    virtual void UpdateBreathing() = 0;
    virtual void SetGroupPos(float const*, float const*) = 0;
    virtual void UpdateAllDisplay() = 0;
    virtual void SetActiveUpperBody(float) = 0;
    virtual void GetCurrentUBAnim(Animation::Header**, uint32_t*, float*) = 0;
    virtual void GetCurrentUBAnim(uint32_t*) = 0;
    virtual void CalcBonesFromMotion(float const*, float const*, float const*, float const*) = 0;
    virtual void unk0002() = 0;
    virtual void GetSpeedModifier(float*) = 0;
    virtual void OnCollision(float const*, float const*, ZMoveNotify*) = 0;
    virtual void IsCollisionEnabled() = 0;
    virtual void OnMoveNotifyLargeObj(ZMoveNotify*) = 0;
    virtual void MovementControl(float*, float*, float*, float*) = 0;
    virtual void GetNearestEnemy(float const*, float const*) = 0;
    virtual void IsValidEnemy(ZGEOM*) = 0;
    virtual void RegisterMovement(ZMovementBase*) = 0;
    virtual void CreateMovements() = 0;
    virtual void CreateMovementBaseMove() = 0;
    virtual void CreateMovementStand() = 0;
    virtual void CreateMovementGuide() = 0;
    virtual void CreateMovementAnimation() = 0;
    virtual void GetMovement(uint32_t) = 0;
    virtual void GetCameraOrientation(float*, float*) = 0;
    virtual void GetCamera() = 0;

    PAD(920)
};

static_assert(sizeof(ZPlayer) == 1896, "ZPlayer");

class ZHitman3 : public ZPlayer
{
public:
    virtual void GetHideInThisView() = 0;
    virtual void Die2(bool, bool) = 0;
    virtual void ActivateAnimSegmentWithCameraBone(Animation::Header*, int, float, float, float) = 0;
    virtual void GetAnims() = 0;
    virtual void GetItemAssignedUBAnim(ZItem*, Animation::Header**, uint32_t*, float*) = 0;
    virtual void StoreUBHoldAnims() = 0;
    virtual void MapUBHoldAnimsToIdx() = 0;
    virtual void DisableControls2(char) = 0;
    virtual void GetNearestActionObject() = 0;
    virtual void IsInCutsequence() = 0;
    virtual void DetachItemFromRightHand(ZItem*) = 0;
    virtual void DetachItemFromLeftHand(ZItem*) = 0;
    virtual void DetachItemFromHitman(ZItem*) = 0;
    virtual void AttachItemToRightHand(ZItem*) = 0;
    virtual void AttachItemToLeftHand(ZItem*) = 0;
    virtual void AttachItemToHitman(ZItem*) = 0;

    PAD(2152)
    void* m_Unknown01; // 0x0FD0
    void* m_Unknown02; // 0x0FD4
    PAD(1184)
};

static_assert(sizeof(ZHitman3) == 5240, "ZHitman3");

class ZCAMERA : public ZGEOM
{
public:
    virtual void SetNear(float) = 0;
    virtual void SetFar(float) = 0;
    virtual void SetBackColor(int) = 0;
    virtual void SetTargetLen(float) = 0;
    virtual void SetFOV(float) = 0;
    virtual float GetFOV() = 0;
    virtual void SetFOVFirstPerson(float) = 0;
    virtual void GetFOVFirstPerson() = 0;
    virtual void ViewUpdateBegin() = 0;
    virtual void ViewUpdateEnd() = 0;
    virtual void Init(ZRender*) = 0;
    virtual void SetViewport(float const*) = 0;
    virtual void GetViewport(float*) = 0;
    virtual void SetViewAspect(float) = 0;
    virtual float GetViewAspect() = 0;
    virtual void GetCameraRoot() = 0;
    virtual void ActivateCam() = 0;
    virtual void DeactivateCam() = 0;
    virtual void IsActive() = 0;
    virtual void AddAlwaysDrawGeom(ZBaseGeom*) = 0;
    virtual void RemoveAlwaysDrawGeom(ZBaseGeom*) = 0;
    virtual void SetCamPrio(int) = 0;
    virtual void SetCamTaget(float*, float) = 0;
    virtual void SetCam6ClipPlanes(float, float, float, int, int, float) = 0;
    virtual void Proj2D(float*, float const*) = 0;
    virtual void Proj3D(float*, float const*) = 0;
    virtual void Proj2D3D(float*, float*) = 0;
    virtual void SetCameraRoot(uint32_t) = 0;
    virtual void SetCameraListPrio(float) = 0;
    virtual void SetCurrentRoomHint(ZROOM*) = 0;
    virtual void GetCurrentRoomHint() = 0;
    virtual void GetScreenSelect(SScreenSelect*, bool, uint32_t, float) = 0;
    virtual void SetWideScreen(bool) = 0;
    virtual void FindCurrentRoom(ZROOM**, uint32_t) = 0;

    PAD(60)
    float m_fNear; // 76 (0x4C)
    float m_fFar; // 80 (0x50)
};
