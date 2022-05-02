#pragma once
#include "CoreMinimal.h"
#include "CharacterOptions.generated.h"

USTRUCT(BlueprintType)
struct FCharacterOptions {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess=true))
    bool GrapplingHookAutoSwitch;
    
    UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess=true))
    bool ZiplineGunAutoSwitch;
    
    FSD_API FCharacterOptions();
};

