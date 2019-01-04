#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_bankmst_unavailable : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_bankmst_unavailable() { }
		~CIFast_IFast_ifastdbrkr_err_bankmst_unavailable() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_BANKMST_UNAVAILABLE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Bank-Mstr record is not available.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Bank-Mstr record is not available.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Bank-Mstr-Eintrag ist nicht verfügbar")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El registro Bank-Mstr no está disponible")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'enregistrement de l'original bancaire n'est pas disponible.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Record Bank-Mstr is niet beschikbaar")); }

        // Actions
	};
}



