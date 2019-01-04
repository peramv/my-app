#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_order_header_already_exists : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_order_header_already_exists() { }
		~CIFast_IFast_ifastdbrkr_err_order_header_already_exists() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ORDER_HEADER_ALREADY_EXISTS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 1; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("OrderHeader record already exists")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("OrderHeader record already exists")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'enregistrement d'en-tête de l'ordre existe déjà.")); }

        // Actions
	};
}



