# @note: for some reason Rubat/Garry made CallWithArgs use index of string stored inside Lua Registry
#        so this script is just finding all references and reads index that is being called

import idaapi
import idautils
import idc

# debug.getregistry()[3]
HOOKS={1:'AcceptInput',2:'AdjustMouseSensitivity',3:'AllowPlayerPickup',4:'CalcMainActivity',5:'CalcView',6:'CalcViewModelView',7:'CanExitVehicle',8:'CanPlayerEnterVehicle',9:'CanPlayerSuicide',10:'ChatText',11:'ChatTextChanged',12:'CheckPassword',13:'ClientSignOnStateChanged',14:'CreateClientsideRagdoll',15:'CreateEntityRagdoll',16:'CreateMove',17:'DoAnimationEvent',18:'DoPlayerDeath',19:'DrawMonitors',20:'DrawPhysgunBeam',21:'EndEntityDriving',22:'EntityEmitSound',23:'EntityFireBullets',24:'PostEntityFireBullets',25:'EntityKeyValue',26:'EntityNetworkedVarChanged',27:'EntityRemoved',28:'EntityTakeDamage',29:'PostEntityTakeDamage',30:'FindUseEntity',31:'FinishChat',32:'FinishMove',33:'GUIMouseDoublePressed',34:'GUIMousePressed',35:'GUIMouseReleased',36:'GetFallDamage',37:'GetGameDescription',38:'GetMotionBlurValues',39:'GetPreferredCarryAngles',40:'GetTeamColor',41:'GravGunOnDropped',42:'GravGunOnPickedUp',43:'GravGunPickupAllowed',44:'GravGunPunt',45:'HUDAmmoPickedUp',46:'HUDDrawScoreBoard',47:'HUDItemPickedUp',48:'HUDPaint',49:'HUDPaintBackground',50:'HUDShouldDraw',51:'HUDWeaponPickedUp',52:'InitPostEntity',53:'InputMouseApply',54:'KeyPress',55:'KeyRelease',56:'Move',57:'NeedsDepthPass',58:'NetworkEntityCreated',59:'NetworkIDValidated',60:'NotifyShouldTransmit',61:'OnAchievementAchieved',62:'OnChatTab',63:'OnCrazyPhysics',64:'OnDamagedByExplosion',65:'OnEntityCreated',66:'OnEntityWaterLevelChanged',67:'OnNPCKilled',68:'OnNPCDropItem',69:'OnPhysgunFreeze',70:'OnPhysgunReload',71:'OnPlayerChat',72:'OnPlayerHitGround',73:'PlayerChangedTeam',74:'OnViewModelChanged',75:'PhysgunDrop',76:'PhysgunPickup',77:'OnPhysgunPickup',78:'PlayerAuthed',79:'PlayerBindPress',80:'PlayerButtonDown',81:'PlayerButtonUp',82:'PlayerCanHearPlayersVoice',83:'PlayerCanPickupItem',84:'PlayerCanPickupWeapon',85:'PlayerCanSeePlayersChat',86:'PlayerConnect',87:'PlayerDeath',88:'PlayerDeathSound',89:'PlayerDeathThink',90:'PlayerDroppedWeapon',91:'PlayerDisconnected',92:'PlayerDriveAnimate',93:'PlayerEndVoice',94:'PlayerEnteredVehicle',95:'PlayerFootstep',96:'PlayerHurt',97:'PlayerInitialSpawn',98:'PlayerLeaveVehicle',99:'PlayerNoClip',100:'PlayerPostThink',101:'PlayerSay',102:'PlayerSelectSpawn',103:'PlayerShouldTakeDamage',104:'PlayerShouldTaunt',105:'PlayerSilentDeath',106:'PlayerSpawn',107:'PlayerSpray',108:'PlayerStartTaunt',109:'PlayerStartVoice',110:'PlayerStepSoundTime',111:'PlayerSwitchFlashlight',112:'PlayerSwitchWeapon',113:'PlayerTick',114:'PlayerTraceAttack',115:'PlayerUse',116:'PostCleanupMap',117:'PostDraw2DSkyBox',118:'PostDrawEffects',119:'PostDrawHUD',120:'PostDrawOpaqueRenderables',121:'PostDrawSkyBox',122:'PostDrawTranslucentRenderables',123:'PostDrawViewModel',124:'PostPlayerDeath',125:'PostPlayerDraw',126:'PostRender',127:'PostRenderVGUI',128:'PreCleanupMap',129:'PreDrawEffects',130:'PreDrawHUD',131:'PreDrawOpaqueRenderables',132:'PreDrawSkyBox',133:'PreDrawTranslucentRenderables',134:'PreDrawViewModel',135:'PreDrawViewModels',136:'PrePlayerDraw',137:'PreRender',138:'PreventScreenClicks',139:'PropBreak',140:'RenderScene',141:'RenderScreenspaceEffects',142:'Restored',143:'Saved',144:'ScaleNPCDamage',145:'ScalePlayerDamage',146:'ScoreboardHide',147:'ScoreboardShow',148:'SetupMove',149:'SetupPlayerVisibility',150:'SetupSkyboxFog',151:'SetupWorldFog',152:'ShouldCollide',153:'ShouldDrawLocalPlayer',154:'ShouldDrawParticles',155:'ShowHelp',156:'ShowSpare1',157:'ShowSpare2',158:'ShowTeam',159:'ShutDown',160:'SpawniconGenerated',161:'StartChat',162:'StartCommand',163:'StartEntityDriving',164:'Think',165:'Tick',166:'TranslateActivity',167:'UpdateAnimation',168:'VGUIMousePressAllowed',169:'VGUIMousePressed',170:'VehicleMove',171:'ViewPunch',172:'WeaponEquip',173:'PlayerAmmoChanged',174:'PlayerClassChanged',175:'PlayerHandleAnimEvent',176:'PlayerFireAnimationEvent',177:'OnPlayerPhysicsPickup',178:'OnPlayerPhysicsDrop',179:'OnPlayerJump',180:'OnCloseCaptionEmit',181:'HandlePlayerArmorReduction',182:'OnPauseMenuShow',183:'OnClientLuaError',184:'OnChangeActivity',185:'BehaveUpdate',186:'Blocked',187:'BodyUpdate',188:'Deploy',189:'DoImpactEffect',190:'Draw',191:'DrawTranslucent',192:'EndTouch',193:'Equip',194:'EquipAmmo',195:'ExpressionFinished',196:'FireAnimationEvent',197:'FreezeMovement',198:'GetAttackSpread',199:'GetCapabilities',200:'GetRelationship',201:'GetRenderMesh',202:'HandleAnimEvent',203:'Holster',204:'ImpactTrace',205:'KeyValue',206:'OnCondition',207:'OnContact',208:'OnIgnite',209:'OnInjured',210:'OnKilled',211:'OnTraceAttack',212:'OnLandOnGround',213:'OnLeaveGround',214:'OnNavAreaChanged',215:'OnOtherKilled',216:'OnStuck',217:'OnTakeDamage',218:'OnUnStuck',219:'PassesDamageFilter',220:'PassesFilter',221:'PassesTriggerFilters',222:'PhysicsCollide',223:'PhysicsSimulate',224:'PhysicsUpdate',225:'RunEngineTask',226:'StartEngineSchedule',227:'StartEngineTask',228:'StartTouch',229:'TestCollision',230:'Touch',231:'UpdateTransmitState',232:'Use',233:'IsJumpLegal',234:'CalcWeaponProficiency',235:'GetShadowCastDirection',236:'OnEntitySight',237:'OnEntitySightLost',238:'OnMovementFailed',239:'OnMovementComplete',240:'OnActiveWeaponChanged',241:'RunAI',242:'OnTaskFailed',243:'OverrideMove',244:'OverrideMoveFacing',245:'TranslateSchedule',246:'TranslateNavGoal',247:'OnStateChange',248:'CustomAmmoDisplay',249:'DrawHUD',250:'DrawHUDBackground',251:'DrawWorldModel',252:'DrawWorldModelTranslucent',253:'DrawWeaponSelection',254:'DoDrawCrosshair',255:'ShouldDrawViewModel',256:'GetTracerOrigin',257:'OnDrop',258:'OnRemove',259:'PrimaryAttack',260:'SecondaryAttack',261:'Reload',262:'RenderScreen',263:'ViewModelDrawn',264:'TranslateFOV',265:'SetWeaponHoldType',266:'CanBePickedUpByNPCs',267:'NPCShoot_Primary',268:'NPCShoot_Secondary',269:'GetNPCRestTimes',270:'GetNPCBurstSettings',271:'GetNPCBulletSpread',272:'ShouldDropOnDie',273:'ActionSignal',274:'AllowInput',275:'ApplySchemeSettings',276:'ConsoleMessage',277:'DoClick',278:'OnActivate',279:'OnBeginLoadingDocument',280:'OnCallback',281:'OnChangeAddressBar',282:'OnChangeTargetURL',283:'OnChangeTitle',284:'OnChildViewCreated',285:'OnCursorEntered',286:'OnCursorExited',287:'OnCursorMoved',288:'OnDeactivate',289:'OnDeletion',290:'OnDocumentReady',291:'OnFinishLoadingDocument',292:'OnFocusChanged',293:'OnGetFocus',294:'OnKeyCodePressed',295:'OnKeyCodeReleased',296:'OnKeyCodeTyped',297:'OnLoseFocus',298:'OnMousePressed',299:'OnMouseReleased',300:'OnMouseWheeled',301:'OnScreenSizeChanged',302:'OnSizeChanged',303:'OnTextChanged',304:'OnTextClicked',305:'PerformLayout',306:'ResourceLoaded',307:'TestHover',308:'DTVar_ReceiveProxyGL',309:'Float',310:'Int',311:'Bool',312:'Vector',313:'Angle',314:'String',315:'Entity'}

def get_second_arg(call_ea):
    ea = idc.prev_head(call_ea)

    for _ in range(20):
        if ea == idc.BADADDR:
            break

        mnem = idc.print_insn_mnem(ea).lower()
        if mnem == "mov":
            dst = idc.print_operand(ea, 0).lower()
            if dst in ("edx", "rdx") and idc.get_operand_type(ea, 1) == idc.o_imm:
                return idc.get_operand_value(ea, 1)

        ea = idc.prev_head(ea)

    return None

def get_refs(name):
    func = idc.get_name_ea_simple(name)
    if func == idc.BADADDR:
        return
    
    print(f"[ * ] {name} @ ({hex(func)})\n")

    return idautils.CodeRefsTo(func, 0)

def get_hook_name(ref):
    func = idaapi.get_func(ref)
    if not func:
        return "", ""

    func_name = idc.get_func_name(func.start_ea)
    arg_val = get_second_arg(ref)

    if arg_val is None:
        return "", ""

    hook_name = HOOKS.get(arg_val, "UNKNOWN")
    return func_name, hook_name

def main():
    print('\n'.join(f"{idc.get_func_name(idaapi.get_func(ref).start_ea) if idaapi.get_func(ref) else '<no func>'} -> {HOOKS.get(get_second_arg(ref), '?')} ({get_second_arg(ref)})" for ref in get_refs("CLuaGamemode::Call") if idaapi.get_func(ref)))
    print('\n'.join(f"{idc.get_func_name(idaapi.get_func(ref).start_ea) if idaapi.get_func(ref) else '<no func>'} -> {HOOKS.get(get_second_arg(ref), '?')} ({get_second_arg(ref)})" for ref in get_refs("CLuaGamemode::CallWithArgs") if idaapi.get_func(ref)))

if __name__ == "__main__":
    main()
