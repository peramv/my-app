#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_no_dofdeath_for_shareholder : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_no_dofdeath_for_shareholder() { }
		~CIFast_IFast_ifastcbo_err_no_dofdeath_for_shareholder() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_DOFDEATH_FOR_SHAREHOLDER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There is no date of death for this shareholder.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es gibt kein Todesdatum für diesen Aktionär.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No hay fecha de fallecimiento para este accionista.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il n'y a aucune date de décès pour cet actionnaire.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is geen overlijdensdatum voor deze aandeelhouder")); }

        // Actions
	};
}



