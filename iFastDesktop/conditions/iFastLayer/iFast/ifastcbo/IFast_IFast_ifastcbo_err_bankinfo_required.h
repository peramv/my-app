#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_bankinfo_required : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_bankinfo_required() { }
		~CIFast_IFast_ifastcbo_err_bankinfo_required() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_BANKINFO_REQUIRED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

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



