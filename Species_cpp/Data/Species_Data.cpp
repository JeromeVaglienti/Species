// Fill out your copyright notice in the Description page of Project Settings.


#include "Species_Data.h"
#include <typeinfo>

Species_Data::Species_Data()
{
	
}

Species_Data::~Species_Data()
{
}

Species_Data::Species_Data(Species_Type _type, AAI_Character_0* _owner)
{
	*this = Species_Data::GetPrefabSpeciesData(_type);
	m_pOwner = _owner;
}

SelfAwareData Species_Data::GetDataFromName(FName _name)
{
	vector<SelfAwareData>::iterator it;

	for (it = m_cSAData.begin(); it != m_cSAData.end(); it++)
	{
		if (it->data_name == _name)
		{
			return *it;
		}
	}
	return SelfAwareData();
}

SelfAwareData Species_Data::GetDataFromAddress(void* _address)
{
	vector<SelfAwareData>::iterator it;

	for (it = m_cSAData.begin(); it != m_cSAData.end(); it++)
	{
		if (it->data_ptr == _address)
		{
			return *it;
		}
	}
	return SelfAwareData();
}

bool Species_Data::CanReproduce()
{
	if (currentState == MetabolicState::resting)
	{
		return false;
	}

	return  (*m_piEnergy > GetMinEnergyBeforeNeedingToRest()) && (*m_piHunger < GetMaxHungerBeforeNeedingToEat());
}

Species_Data Species_Data::GetPrefabSpeciesData(Species_Type _type)
{
	Species_Data toReturn;

	toReturn.m_bIsSelected = false;

	toReturn.ResetTimers();

	toReturn.m_iReproduction_ID = -1;

	toReturn.currentState = MetabolicState::standard;

	toReturn.m_pPartnerRef = nullptr;

	toReturn.metabolicSignatures = new metabolicSignature[MetabolicState::count];

	switch (_type)
	{
	case Species_Type::type_0:
		toReturn.metabolicSignatures[MetabolicState::standard].m_fTickTimer_DOT = .33f;
		toReturn.metabolicSignatures[MetabolicState::standard].m_fTickTimer_Energy = 1.5f;
		toReturn.metabolicSignatures[MetabolicState::standard].m_fTickTimer_Hunger = 1.8f;

		toReturn.metabolicSignatures[MetabolicState::resting].m_fTickTimer_DOT = .5f;
		toReturn.metabolicSignatures[MetabolicState::resting].m_fTickTimer_Energy = .15f;
		toReturn.metabolicSignatures[MetabolicState::resting].m_fTickTimer_Hunger = 9.0f;

		toReturn.m_iMaxLife = 100;
		toReturn.m_iMaxEnergy = 200;
		toReturn.m_iMaxHunger = 150;

		toReturn.m_piEnergy = new int(140);
		toReturn.m_piHunger = new int(0);
		toReturn.m_piLife = new int(toReturn.m_iMaxLife);
		toReturn.m_pvTargetLocation = new FVector(0.0f);

		toReturn.m_iMinValueBeforeTooLow_Energy = 80;
		toReturn.m_iMaxValueBeforeTooHigh_Hunger = 45;

		toReturn.m_iValueOptimalEnergyRecovery = 185;
		toReturn.m_iValueOptimalHungerReduction = 20;

		toReturn.m_iMinEnergyBeforeDamage = 50;
		toReturn.m_iMaxHungerBeforeDamage = 80;

		break;
	case Species_Type::type_1:
		break;
	case Species_Type::typeCount:
		break;
	case Species_Type::undefined:
		break;
	default:
		break;
	}

	toReturn.m_cSAData.push_back(SelfAwareData(FName("TargetLocation"), typeid(*toReturn.m_pvTargetLocation).name(), toReturn.m_pvTargetLocation));
	toReturn.m_cSAData.push_back(SelfAwareData(FName("Life"), typeid(*toReturn.m_piLife).name(), toReturn.m_piLife));
	toReturn.m_cSAData.push_back(SelfAwareData(FName("Energy"), typeid(*toReturn.m_piEnergy).name(), toReturn.m_piEnergy));
	toReturn.m_cSAData.push_back(SelfAwareData(FName("Hunger"), typeid(*toReturn.m_piHunger).name(), toReturn.m_piHunger));

	return toReturn;
}
