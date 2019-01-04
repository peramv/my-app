#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastbp_bp_err_invalid_date_format : public CConditionObject
	{
	public:
		CIFast_IFast_ifastbp_bp_err_invalid_date_format() { }
		~CIFast_IFast_ifastbp_bp_err_invalid_date_format() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("BP_ERR_INVALID_DATE_FORMAT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastbp")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid Date Format.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültiges Datumsformat")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Formato de fecha no válido")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Format de date invalide")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldige datumindeling")); }

        // Actions
	};
}



