#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_deposit_id_closed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_deposit_id_closed() { }
		~CIFast_IFast_ifastcbo_err_deposit_id_closed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DEPOSIT_ID_CLOSED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Deposit ID closed.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Depot-ID geschlossen")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La identificación de depósito está cerrada")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Code de dépôt fermé")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Deposito-ID is gesloten")); }

        // Actions
	};
}



