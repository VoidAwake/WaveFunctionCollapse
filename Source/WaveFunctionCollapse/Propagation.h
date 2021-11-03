#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Tile.h"
#include "GridCell.h"
#include "Propagation.generated.h"

UCLASS()
class WAVEFUNCTIONCOLLAPSE_API UPropagation : public UObject
{
	GENERATED_BODY()

public:
	//void Initialise(AGridCell* GridCellArg);

	//AGridCell* GridCell;

	TArray<TSubclassOf<ATile>> OldWave;
};
