#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_dicore_dicore_hostmasks_not_defined_in_registry : public CConditionObject
	{
	public:
		CBase_Infrastructure_dicore_dicore_hostmasks_not_defined_in_registry() { }
		~CBase_Infrastructure_dicore_dicore_hostmasks_not_defined_in_registry() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DICORE_HOSTMASKS_NOT_DEFINED_IN_REGISTRY")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dicore")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Cannot find the definition of HostMasks in the registry")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Cannot find the definition of HostMasks in the registry")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Definition der HostMasks kann in der Registrierung nicht gefunden werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se puede encontrar la definición de HostMasks en el registro")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible de trouver la définition des masques de l'hôte dans le registre.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Definitie van HostMasks kon niet worden gevonden in het register")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("HostMasks should be defined in the registry under DICORE")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("HostMasks should be defined in the registry under DICORE")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("HostMasks sollte in der Registrierung unter DICORE definiert sein")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("HostMasks should be defined in the registry under DICORE")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Les masques de l'hôte devraient être définis dans le registre avec DICORE.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("HostMasks moet zijn gedefinieerd in het register onder DICORE")); }
	};
}



