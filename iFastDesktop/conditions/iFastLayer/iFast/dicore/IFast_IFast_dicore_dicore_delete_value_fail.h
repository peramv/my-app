#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dicore_dicore_delete_value_fail : public CConditionObject
	{
	public:
		CIFast_IFast_dicore_dicore_delete_value_fail() { }
		~CIFast_IFast_dicore_dicore_delete_value_fail() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DICORE_DELETE_VALUE_FAIL")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dicore")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Identification record does not exist.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Identification record does not exist.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Identifizierungseintrag existiert nicht.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El registro de identificación no existe")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Enregistrement d'identification inexistant")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Identificatierecord bestaat niet")); }

        // Actions
	};
}



