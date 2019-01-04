#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_backdatedreason_for_backdate_trade : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_backdatedreason_for_backdate_trade() { }
		~CIFast_IFast_ifastcbo_err_backdatedreason_for_backdate_trade() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_BACKDATEDREASON_FOR_BACKDATE_TRADE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Backdated reason code must be entered for Backdated Trade.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Zurückdatierter Begründungscode muss für einen Zurückdatierten Handel eingegeben werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Debe introducirse un código de motivo antedatado para una operación antedatada.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code de raison d'antidatage doit être saisi pour une transaction antidatée.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Redencode antedateren moet worden ingevoerd voor geantedateerde handel")); }

        // Actions
	};
}



