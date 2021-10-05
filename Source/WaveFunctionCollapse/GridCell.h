// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tile.h"

/**
 * 
 */
class WAVEFUNCTIONCOLLAPSE_API GridCell
{
public:
	GridCell();
	~GridCell();

	ATile* Tile;
};
