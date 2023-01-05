#pragma once

UENUM(BlueprintType)
enum class EGameModes : uint8
{   
    EGM_NoMode UMETA(DisplayName="No Mode"),
    EGM_Domination UMETA(DisplayName="Domination"),
    EGM_TDM UMETA(DisplayName="Team Deathmatch"),
    EGM_Control UMETA(DisplayName="Control"),

    EGM_Max UMETA(DisplayName = "DefaultMAX")
};