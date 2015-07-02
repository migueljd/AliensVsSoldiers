// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "AliensVsSoldiers.h"
#include "AliensVsSoldiersPlayerController.h"
#include "AI/Navigation/NavigationSystem.h"
#include "BaseCharacter.h"

AAliensVsSoldiersPlayerController::AAliensVsSoldiersPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void AAliensVsSoldiersPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// keep updating the destination every tick while desired
	if (bMoveToMouseCursor)
	{
		MoveToMouseCursor();
	}
}

void AAliensVsSoldiersPlayerController::SetupInputComponent()
{
    UE_LOG(LogAliensVsSoldiers, Warning, TEXT("Setting up input components"));

	// set up gameplay key bindings
	Super::SetupInputComponent();

//	InputComponent->BindAction("SetDestination", IE_Pressed, this, &AAliensVsSoldiersPlayerController::OnSetDestinationPressed);
//	InputComponent->BindAction("SetDestination", IE_Released, this, &AAliensVsSoldiersPlayerController::OnSetDestinationReleased);
//
//	// support touch devices 
//	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AAliensVsSoldiersPlayerController::MoveToTouchLocation);
//	InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &AAliensVsSoldiersPlayerController::MoveToTouchLocation);
}

void AAliensVsSoldiersPlayerController::MoveToMouseCursor()
{
	// Trace to see what is under the mouse cursor
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);
    


	if (Hit.bBlockingHit)
	{

        try{
       
            AActor* actorHit = Hit.GetActor();
        
            ABaseCharacter* tryCast ;
            tryCast=dynamic_cast<ABaseCharacter* >(actorHit);
        

            
            if( tryCast == 0){
            
                // We hit something, move there
                SetNewMoveDestination(Hit.ImpactPoint);

            }
            //if an exception is cast, it means that we didn't hit an enemy
        } catch(std::exception& e){


            // We hit something that isn't an enemy, move there
            SetNewMoveDestination(Hit.ImpactPoint);
        }
	}
}

void AAliensVsSoldiersPlayerController::MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	FVector2D ScreenSpaceLocation(Location);

	// Trace to see what is under the touch location
	FHitResult HitResult;
	GetHitResultAtScreenPosition(ScreenSpaceLocation, CurrentClickTraceChannel, true, HitResult);    
    
    if (HitResult.bBlockingHit)
    {
        
        try{
            
            AActor* actorHit = HitResult.GetActor();
            
            ABaseCharacter* tryCast ;
            tryCast=dynamic_cast<ABaseCharacter* >(actorHit);
            
            
            
            if( tryCast == 0){
                
                // We hit something, move there
                SetNewMoveDestination(HitResult.ImpactPoint);                
            }
            //if an exception is cast, it means that we didn't hit an enemy
        } catch(std::exception& e){
            
            if(GEngine)
                GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Exception launched");
            
            // We hit something that isn't an enemy, move there
            SetNewMoveDestination(HitResult.ImpactPoint);
        }
    }
}

void AAliensVsSoldiersPlayerController::SetNewMoveDestination(const FVector DestLocation)
{

	APawn* const Pawn = GetPawn();
	if (Pawn)
	{
		UNavigationSystem* const NavSys = GetWorld()->GetNavigationSystem();
		float const Distance = FVector::Dist(DestLocation, Pawn->GetActorLocation());

		// We need to issue move command only if far enough in order for walk animation to play correctly
		if (NavSys && (Distance > 120.0f))
		{
			NavSys->SimpleMoveToLocation(this, DestLocation);
		}
	}
}

void AAliensVsSoldiersPlayerController::OnSetDestinationPressed()
{
	// set flag to keep updating destination until released
	bMoveToMouseCursor = true;
}

void AAliensVsSoldiersPlayerController::OnSetDestinationReleased()
{
	// clear flag to indicate we should stop updating the destination
	bMoveToMouseCursor = false;
}
