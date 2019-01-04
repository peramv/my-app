#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_closed_country_resident_for_money_in : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_closed_country_resident_for_money_in() { }
		~CIFast_IFast_ifastcbo_err_closed_country_resident_for_money_in() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CLOSED_COUNTRY_RESIDENT_FOR_MONEY_IN")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No %TRADETYPE% allowed for closed country resident.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucun type de transaction %TRADETYPE% n'est autorisé pour les résidents de pays couvert.")); }

        // Actions
	};
}



