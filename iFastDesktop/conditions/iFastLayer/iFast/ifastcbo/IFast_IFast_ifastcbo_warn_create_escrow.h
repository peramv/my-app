#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_create_escrow : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_create_escrow() { }
		~CIFast_IFast_ifastcbo_warn_create_escrow() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_CREATE_ESCROW")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("If grant is not cancelled, the grant amount will be put under clawback.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Si la subvention n'est pas annulée, le montant de la subvention sera récupéré.")); }

        // Actions
	};
}



