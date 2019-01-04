#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_management_company_not_found : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_management_company_not_found() { }
		~CIFast_IFast_ifastdbrkr_err_management_company_not_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_MANAGEMENT_COMPANY_NOT_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Management Company %MGMT% not found.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Management Company %MGMT% not found.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Management-Unternehmen %MGMT% nicht gefunden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se encontró la compañía administradora %MGMT%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Environnement %MGMT% introuvable")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Beheerbedrijf %MGMT% is niet gevonden")); }

        // Actions
	};
}



