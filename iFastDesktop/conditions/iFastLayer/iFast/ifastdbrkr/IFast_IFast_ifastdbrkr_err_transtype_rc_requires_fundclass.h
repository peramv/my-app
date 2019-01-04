#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_transtype_rc_requires_fundclass : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_transtype_rc_requires_fundclass() { }
		~CIFast_IFast_ifastdbrkr_err_transtype_rc_requires_fundclass() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TRANSTYPE_RC_REQUIRES_FUNDCLASS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund and class cannot be blank for TransType RC")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fund and class cannot be blank for TransType RC")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le fonds et la classe sont requis pour le type de transaction RC.")); }

        // Actions
	};
}



