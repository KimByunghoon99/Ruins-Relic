// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInstance.h"


UPlayerInstance::UPlayerInstance()
{
    PlayerMaxHealth = 100.0f;  
    PlayerHealth = 100.0f;    
    PlayerAttackDamage = 20.0f; 
    PlayerAttackSpeed = 1.0f; 
    PlayerDodgeCool = 4.0f;
    PlayerWhirlwindCool = 20.0f;
    PlayerTornadoCool = 30.0f;
}