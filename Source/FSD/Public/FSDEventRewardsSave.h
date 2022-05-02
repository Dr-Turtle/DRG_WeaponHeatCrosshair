#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FSDEventRewardsSave.generated.h"

USTRUCT(BlueprintType)
struct FFSDEventRewardsSave {
    GENERATED_BODY()
public:
protected:
    UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess=true))
    TSet<FGuid> EventsSeen;
    
public:
    FSD_API FFSDEventRewardsSave();
};

