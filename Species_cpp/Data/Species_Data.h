// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <string>
#include <vector>
#include <iostream>
#include "GameFramework/Character.h"

using namespace std;

class AAI_Character_0;

enum Species_Type
{
	type_0 = 0,
	type_1,
	typeCount,
	undefined
};


enum MetabolicState
{
	standard,
	resting,
	count
};

class SPECIES_CPP_API SelfAwareData
{
public:
	FName data_name;
	FString data_type;
	void* data_ptr;

	SelfAwareData(FName _dataname, const char* _data_type, void* _ptr)
	{
		data_name = _dataname;
		data_type = FString(_data_type);
		data_ptr = _ptr;
	}

	SelfAwareData()
	{
		data_name = "none";
		data_type = "null";
		data_ptr = nullptr;
	}
};

class SPECIES_CPP_API Species_Data
{
private:

	//Constant for Changing state
	int m_iMaxValueBeforeTooHigh_Hunger;
	int m_iMinValueBeforeTooLow_Energy;

	//RecoveryDelimiter
	int m_iValueOptimalEnergyRecovery;
	int m_iValueOptimalHungerReduction;


	//MaxValue
	int m_iMaxLife;
	int m_iMaxHunger;
	int m_iMaxEnergy;

	//Consntant before loosing life
	int m_iMinEnergyBeforeDamage;
	int m_iMaxHungerBeforeDamage;

	//string keys

	Species_Data();
	~Species_Data();

	Species_Data GetPrefabSpeciesData(Species_Type _type);
protected:
	vector<SelfAwareData> m_cSAData;

	struct metabolicSignature
	{
		float m_fTickTimer_Hunger;
		float m_fTickTimer_Energy;
		float m_fTickTimer_DOT;
	};

	metabolicSignature* metabolicSignatures;
public:

	Species_Data(Species_Type _type, AAI_Character_0* _owner);
	
	//Increase hunger and energy each tick defined by tickTimer
	float m_fTimer_Hunger;
	float m_fTimer_Energy;
	float m_fTimer_DOT;

	MetabolicState currentState;

	inline float GetTickTimerHunger() { return metabolicSignatures[currentState].m_fTickTimer_Hunger; }
	inline float GetTickTimerEnergy() { return metabolicSignatures[currentState].m_fTickTimer_Energy; }
	inline float GetTickTimerDOT() { return metabolicSignatures[currentState].m_fTickTimer_DOT; }

	inline int GetMaxHungerBeforeNeedingToEat() const { return m_iMaxValueBeforeTooHigh_Hunger; }
	inline int GetMinEnergyBeforeNeedingToRest() const { return m_iMinValueBeforeTooLow_Energy; }

	inline int GetMaxLifePossible() const { return m_iMaxLife; }
	inline int GetMaxHungerPossible() const { return m_iMaxHunger; }
	inline int GetMaxEnergyPossible() const { return m_iMaxEnergy; }

	inline int GetOptimalEnergyRecovery() const { return m_iValueOptimalEnergyRecovery; }
	inline int GetOptimalHungerReduction() const { return m_iValueOptimalHungerReduction; }
	
	inline int GetMaxHungerBeforeDamage() const { return m_iMaxHungerBeforeDamage; }
	inline int GetMinEnergyBeforeDamage() const { return m_iMinEnergyBeforeDamage; }

	inline void ResetTimers() { m_fTimer_DOT = m_fTimer_Energy = m_fTimer_Hunger = 0.0f; }

	SelfAwareData GetDataFromName(FName _name);

	SelfAwareData GetDataFromAddress(void* _address);

	bool CanReproduce();

	inline bool IsAvailableForReproduction() { return m_iReproduction_ID == -1 && CanReproduce(); }

	inline vector<SelfAwareData> GetSelfAwareDataList() const { return m_cSAData; }

	//Return status
	bool m_bisHungry;

	//No used for now
	bool m_bIsSelected;

	int m_iReproduction_ID;
	AActor* m_pPartnerRef;

	AAI_Character_0* m_pOwner;

	//Pure Data
	int* m_piHunger;
	int* m_piEnergy;
	int* m_piLife;


	FVector* m_pvTargetLocation;
};