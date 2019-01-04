#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_additional_acctnum_must_be_setup_in_identification : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_additional_acctnum_must_be_setup_in_identification() { }
		~CIFast_IFast_ifastcbo_warn_additional_acctnum_must_be_setup_in_identification() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_ADDITIONAL_ACCTNUM_MUST_BE_SETUP_IN_IDENTIFICATION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Additional Account Number must be setup in Identification section for Fund Sponsor entity.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le numéro de compte supplémentaire doit être réglé dans la section de l'identification pour l'entité promotrice de fonds.")); }

        // Actions
	};
}



