#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dicore_dicore_date_string_invalid : public CConditionObject
	{
	public:
		CIFast_IFast_dicore_dicore_date_string_invalid() { }
		~CIFast_IFast_dicore_dicore_date_string_invalid() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DICORE_DATE_STRING_INVALID")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dicore")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The following bank information: %BANKINFO% is required for the systematic record.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("The following bank information: %BANKINFO% is required for the systematic record.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Die folgende Bankinformation: %BANKINFO% ist für den Systematischer Plan-Eintrag erforderlich.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La siguiente información de banco: %BANKINFO% es obligatoria para el registro de plan sistemático.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'information bancaire suivante : %BANKINFO% est requise pour l'enregistrement systématique.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("De volgende bankgegevens: %BANKINFO% zijn vereist voor het systeemplanrecord")); }

        // Actions
	};
}



