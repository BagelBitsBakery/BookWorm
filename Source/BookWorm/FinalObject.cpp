// Fill out your copyright notice in the Description page of Project Settings.


#include "FinalObject.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"

void AFinalObject::EatEffect()
{
	UUserWidget* NewWidget = CreateWidget<UUserWidget>(GetWorld(), WidgetClass);
	NewWidget->AddToViewport();

	UGameplayStatics::SetGamePaused(GetWorld(), true);
}
