#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_traded_unit_position : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_traded_unit_position() { }
		~CIFast_IFast_ifastcbo_err_traded_unit_position() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TRADED_UNIT_POSITION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The estimated transaction level traded unit position of the account fund class is %tupunits% units.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La position estimée de l'unité échangée au niveau de la transaction de la classe de fonds du compte est %tupunits% unités.")); }

        // Actions
	};
}



