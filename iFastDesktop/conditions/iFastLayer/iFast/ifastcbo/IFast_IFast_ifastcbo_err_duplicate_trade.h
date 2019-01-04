#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_duplicate_trade : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_duplicate_trade() { }
		~CIFast_IFast_ifastcbo_err_duplicate_trade() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DUPLICATE_TRADE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Duplicate trade already exists.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Cette transaction existe déja.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Entsprechender Handel existiert bereits")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La operación repetida ya existe.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Une copie de la transaction existe déjà.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Dubbele handel bestaat al")); }

        // Actions
	};
}



