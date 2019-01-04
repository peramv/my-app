#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dicore_dicore_hostmasks_not_defined_in_registry : public CConditionObject
	{
	public:
		CIFast_IFast_dicore_dicore_hostmasks_not_defined_in_registry() { }
		~CIFast_IFast_dicore_dicore_hostmasks_not_defined_in_registry() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DICORE_HOSTMASKS_NOT_DEFINED_IN_REGISTRY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dicore")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The reference number does not exist.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("The reference number does not exist.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Die Referenznummer existiert nicht.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El número de referencia no existe.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Numéro de référence inexistant")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Het referentienummer bestaat niet")); }

        // Actions
	};
}



