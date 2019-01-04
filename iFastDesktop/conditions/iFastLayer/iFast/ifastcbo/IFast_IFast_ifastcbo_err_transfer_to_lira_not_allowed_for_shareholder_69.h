#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_transfer_to_lira_not_allowed_for_shareholder_69 : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_transfer_to_lira_not_allowed_for_shareholder_69() { }
		~CIFast_IFast_ifastcbo_err_transfer_to_lira_not_allowed_for_shareholder_69() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TRANSFER_TO_LIRA_NOT_ALLOWED_FOR_SHAREHOLDER_69")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("PRIF Transfer to LIRA is not allowed for shareholder over 71 years old.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("PRIF-Transfer zu LIRA ist nicht erlaubt für einen Aktionär, der über 71 Jahre alt ist.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se permiten transferencias de PRIF a LIRA para accionistas de más de 71 años.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le transfert d'un FRRP vers un CRI n'est pas autorisé pour un actionnaire âgé de plus de 71 ans.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("PRIF-overdracht naar LIRA is niet toegestaan voor aandeelhouder die ouder is dan 71")); }

        // Actions
	};
}



