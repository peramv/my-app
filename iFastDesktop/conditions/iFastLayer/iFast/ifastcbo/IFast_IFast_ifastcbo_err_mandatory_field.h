#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_mandatory_field : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_mandatory_field() { }
		~CIFast_IFast_ifastcbo_err_mandatory_field() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_MANDATORY_FIELD")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Additional Account Number must be setup in Identification section for Fund Sponsor entity.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le numéro de compte supplémentaire doit être réglé dans la section de l'identification pour l'entité promotrice de fonds.")); }

        // Actions
	};
}



