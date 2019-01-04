#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_warn_in_kind_trans_acb : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_warn_in_kind_trans_acb() { }
		~CIFast_IFast_ifastcbo_err_warn_in_kind_trans_acb() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_WARN_IN_KIND_TRANS_ACB")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("This is an In-Kind Transfer which will retain the source fund's adjusted cost base.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Dies ist ein Kauf-Transfer, bei dem die angepasste Kostenbasis des Quellen-Fonds beibehalten wird")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Ésta es una transferencia en especie que retendrá la base de costo ajustada del fondo de origen")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Ceci est un transfert en biens qui conservera le prix de base rajusté du fonds source.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Dit is een overdracht in natura die de aangepaste kostenbasis voor het bronfonds behoudt")); }

        // Actions
	};
}



