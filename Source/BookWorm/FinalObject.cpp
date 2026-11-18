// Fill out your copyright notice in the Description page of Project Settings.


#include "FinalObject.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"

void AFinalObject::EatEffect()
{
	//Creating widget and adding it to the screen
	UUserWidget* NewWidget = CreateWidget<UUserWidget>(GetWorld(), WidgetClass);
	NewWidget->AddToViewport();

	UGameplayStatics::SetGamePaused(GetWorld(), true);
}
