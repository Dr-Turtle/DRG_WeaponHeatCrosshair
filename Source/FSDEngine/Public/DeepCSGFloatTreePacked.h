#pragma once
#include "CoreMinimal.h"
#include "DeepCSGNode.h"
#include "DeepCSGFloatTreePacked.generated.h"

USTRUCT(BlueprintType)
struct FDeepCSGFloatTreePacked {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess=true))
    FDeepCSGNode Root;
    
    UPROPERTY(BlueprintReadWrite, meta=(AllowPrivateAccess=true))
    TArray<int32> encplanes;
    
    FSDENGINE_API FDeepCSGFloatTreePacked();
};

