#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_escrowfund_class : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_escrowfund_class() { }
		~CIFast_IFast_ifastcbo_err_escrowfund_class() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ESCROWFUND_CLASS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Escrow/Assigned Fund and Class must be held by the account.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Escrow Fund and Escrow Class must be held by the account.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Escrow-Fonds und Escrow-Klasse müssen über das Konto geführt werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("EscrowFund y EscrowClass deben ser mantenidos por la cuenta.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le fonds et la classe mis en garantie doivent être compris dans le compte.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Fonds en categorie in pandaccount moeten door het account worden gehouden")); }

        // Actions
	};
}



