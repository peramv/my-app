#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_rif_invalid_gross_net_method_after_netoffees_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_rif_invalid_gross_net_method_after_netoffees_date() { }
		~CIFast_IFast_ifastcbo_err_rif_invalid_gross_net_method_after_netoffees_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RIF_INVALID_GROSS_NET_METHOD_AFTER_NETOFFEES_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Gross/Net pretax must be 'Net of Fees'  for Pay option \"Minimum\" and \"Maximum\".")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'avant impôts brut/net doit être Net de frais pour l'option de paiement Minimum et Maximum.")); }

        // Actions
	};
}



