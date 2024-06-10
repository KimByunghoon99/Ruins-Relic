// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInstance.h"


UPlayerInstance::UPlayerInstance()
{
    // 초기 값 설정

    PlayerMaxHealth = 100.0f;  
    PlayerHealth = 100.0f;    
    PlayerAttackDamage = 10.0f; 
    PlayerAttackSpeed = 1.0f;
}