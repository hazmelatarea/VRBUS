// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"

AGameManager::AGameManager()
{
    CurrentState = EGameState::Start;
}

void AGameManager::BeginPlay()
{
    Super::BeginPlay();

    CurrentStateEvent();
}

void AGameManager::CurrentStateEvent()
{
    switch (CurrentState)
    {
    case EGameState::Start:
        StartState();
        break;

    case EGameState::Preparation:
        PreparationState();
        break;

    case EGameState::Drive:
        DriveState();
        break;

    case EGameState::BusStop:
        BusStopState();
        break;

    case EGameState::Sleep:
        SleepState();
        break;

    default:
        break;
    }
}

void AGameManager::NextState()
{
    switch (CurrentState)
    {
    case EGameState::Start:
        CurrentState = EGameState::Preparation;
        break;

    case EGameState::Preparation:
        CurrentState = EGameState::Drive;
        break;

    case EGameState::Drive:
        CurrentState = EGameState::BusStop;
        break;

    case EGameState::BusStop:
        CurrentState = EGameState::Drive;
        break;

    case EGameState::Sleep:
        CurrentState = EGameState::Start;
        break;
    }

    CurrentStateEvent();
}


void AGameManager::StartState()
{
}

void AGameManager::PreparationState()
{
}

void AGameManager::DriveState()
{
}

void AGameManager::BusStopState()
{
}

void AGameManager::SleepState()
{
}
