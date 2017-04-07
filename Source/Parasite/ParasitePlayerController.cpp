// Copyright Adam Joyce 2017.  All rights reserved.

#include "Parasite.h"
#include "ParasitePlayerController.h"


AParasitePlayerController::AParasitePlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
	bEnableMouseOverEvents = true;
}