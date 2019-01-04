#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_incomplete_from_fund_information : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_incomplete_from_fund_information() { }
		~CIFast_IFast_ifastcbo_err_incomplete_from_fund_information() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INCOMPLETE_FROM_FUND_INFORMATION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Incomplete distribution entry - from fund information.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Unvollständiger Verteilungs-Eintrag – Von-Fund-Information.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Entrada de distribución incompleta - información de fondo de origen.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Saisie de distribution incomplète – information sur le fonds source")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Onvolledige distributie-invoer - van-fondsgegevens")); }

        // Actions
	};
}



