#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_bewareof_pendingtrade : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_bewareof_pendingtrade() { }
		~CIFast_IFast_ifastcbo_err_bewareof_pendingtrade() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_BEWAREOF_PENDINGTRADE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Pending trade(s) exist on or after the input stop date.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Beware of Pending trades.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Une/des transaction(s) en suspens existe(nt) à la date d'arrêt saisie ou après.")); }

        // Actions
	};
}



