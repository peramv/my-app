#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastcbo_err_refnumber_not_exist : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastcbo_err_refnumber_not_exist() { }
		~CIFast_Infrastructure_ifastcbo_err_refnumber_not_exist() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_REFNUMBER_NOT_EXIST")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

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



