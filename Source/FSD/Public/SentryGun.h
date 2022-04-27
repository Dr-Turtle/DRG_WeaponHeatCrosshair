#pragma once
#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "Upgradable.h"
#include "GameFramework/Actor.h"
#include "WeaponFireOwner.h"
#include "SentryGunMuzzleSetup.h"
#include "AmmoCountChangedEventDelegate.h"
#include "TracerData.h"
#include "Engine/EngineTypes.h"
#include "UObject/NoExportTypes.h"
#include "GameplayTagContainer.h"
#include "UObject/NoExportTypes.h"
#include "LaserPointerTarget.h"
#include "UObject/NoExportTypes.h"
#include "UObject/NoExportTypes.h"
#include "SentryGun.generated.h"

class USkeletalMeshComponent;
class USoundBase;
class APlayerCharacter;
class AProjectile;
class UAudioComponent;
class USoundCue;
class UParticleSystem;
class UWeaponFireComponent;
class UHealthComponentBase;

UCLASS(Abstract)
class FSD_API ASentryGun : public AActor, public IWeaponFireOwner, public IUpgradable {
    GENERATED_BODY()
public:
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEnabledChanged, bool, IsEnabled);
    
    UPROPERTY(BlueprintAssignable, BlueprintReadWrite, meta=(AllowPrivateAccess=true))
    FEnabledChanged OnEnabledChanged;
    
    UPROPERTY(BlueprintAssignable, BlueprintReadWrite, meta=(AllowPrivateAccess=true))
    FAmmoCountChangedEvent OnAmmoCountChanged;
    
    UPROPERTY(BlueprintAssignable, BlueprintReadWrite, meta=(AllowPrivateAccess=true))
    FAmmoCountChangedEvent OnMaxAmmoCountChanged;
    
protected:
    UPROPERTY(BlueprintReadWrite, Export, VisibleAnywhere, meta=(AllowPrivateAccess=true))
    USkeletalMeshComponent* SentryGunMesh;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FSentryGunMuzzleSetup> SentryGunMuzzels;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TSubclassOf<AProjectile> ProjectileClass;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    USoundCue* ShootingSound;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    UParticleSystem* MuzzleFlash;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FTracerData TracerData;
    
    UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta=(AllowPrivateAccess=true))
    UParticleSystem* Tracer;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float MinTracerDistance;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float AngleRestriction;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Replicated, meta=(AllowPrivateAccess=true))
    bool Enabled;
    
    UPROPERTY(meta=(AllowPrivateAccess=true))
    TArray<FOverlapResult> OverlapCache;
    
    UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess=true))
    FRotator MinRotation;
    
    UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess=true))
    FRotator MaxRotation;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float AquisitionRange;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float RotationSpeed;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float ShotCoolDown;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float TargetLeading;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    int32 BurstCount;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float BurstShotCoolDown;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float IdleScanAngle;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float IdleScanSpeed;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    float FinalShotFadeOut;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    USoundBase* AudioOnTurn;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FGameplayTagContainer DissallowedTargetTags;
    
    UPROPERTY(BlueprintReadWrite, Transient, ReplicatedUsing=OnRep_AmmoCount, meta=(AllowPrivateAccess=true))
    int32 AmmoCount;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, ReplicatedUsing=OnRep_MaxAmmoCount, meta=(AllowPrivateAccess=true))
    int32 MaxAmmoCount;
    
    UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess=true))
    float Damage;
    
    UPROPERTY(BlueprintReadWrite, Replicated, Transient, meta=(AllowPrivateAccess=true))
    float TargetYaw;
    
    UPROPERTY(BlueprintReadWrite, Replicated, Transient, meta=(AllowPrivateAccess=true))
    float TargetPitch;
    
    UPROPERTY(BlueprintReadWrite, Export, Transient, ReplicatedUsing=OnRep_LastTarget, meta=(AllowPrivateAccess=true))
    TWeakObjectPtr<UHealthComponentBase> LastTarget;
    
    UPROPERTY(BlueprintReadWrite, Export, Replicated, Transient, meta=(AllowPrivateAccess=true))
    TWeakObjectPtr<UHealthComponentBase> PrioritizedTarget;
    
    UPROPERTY(BlueprintReadWrite, Export, Transient, meta=(AllowPrivateAccess=true))
    UWeaponFireComponent* WeaponFire;
    
private:
    UPROPERTY(BlueprintReadWrite, Export, Transient, meta=(AllowPrivateAccess=true))
    UAudioComponent* ShootingAudioComponent;
    
public:
    ASentryGun();
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
    
    UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable)
    void UseAmmo(int32 Amount);
    
protected:
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void ReceiveAmmoChanged(int32 Delta, int32 currentAmount);
    
    UFUNCTION(BlueprintCallable)
    void OnRep_MaxAmmoCount(int32 OldCount);
    
    UFUNCTION(BlueprintCallable)
    void OnRep_LastTarget();
    
    UFUNCTION(BlueprintCallable)
    void OnRep_AmmoCount(int32 OldCount);
    
    UFUNCTION(BlueprintCallable)
    void OnProjectileFired(const FVector& Location);
    
    UFUNCTION(BlueprintCallable)
    void OnNewTargetRequested(const FLaserPointerTarget& HitInfo);
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    FTransform GetMuzzleTransform() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    FName GetMuzzleName() const;
    
public:
    UFUNCTION(BlueprintCallable, BlueprintPure)
    int32 GetMaxAmmoCount() const;
    
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, BlueprintPure)
    float GetDeployProgress() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    float GetAmmoLeftPct() const;
    
    UFUNCTION(BlueprintCallable, BlueprintPure)
    int32 GetAmmoLeft() const;
    
    UFUNCTION(BlueprintCallable, Reliable, Server)
    void Force_Fire(AActor* Target);
    
protected:
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void AmmoSpent();
    
    
    // Fix for true pure virtual functions not being implemented
public:
    UFUNCTION(BlueprintCallable)
    APlayerCharacter* GetPlayerCharacter() const override PURE_VIRTUAL(GetPlayerCharacter, return NULL;);
    
    UFUNCTION(BlueprintCallable)
    FQuat GetMuzzleQuat() const override PURE_VIRTUAL(GetMuzzleQuat, return FQuat{};);
    
    UFUNCTION(BlueprintCallable)
    FVector GetMuzzleLocation() const override PURE_VIRTUAL(GetMuzzleLocation, return FVector{};);
    
    UFUNCTION(BlueprintCallable)
    bool GetIsLocallyControlled() const override PURE_VIRTUAL(GetIsLocallyControlled, return false;);
    
    UFUNCTION(BlueprintCallable)
    bool GetIsFirstPerson() const override PURE_VIRTUAL(GetIsFirstPerson, return false;);
    
};

