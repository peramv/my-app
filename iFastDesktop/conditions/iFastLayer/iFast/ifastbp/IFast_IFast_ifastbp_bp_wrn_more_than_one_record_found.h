#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastbp_bp_wrn_more_than_one_record_found : public CConditionObject
	{
	public:
		CIFast_IFast_ifastbp_bp_wrn_more_than_one_record_found() { }
		~CIFast_IFast_ifastbp_bp_wrn_more_than_one_record_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("BP_WRN_MORE_THAN_ONE_RECORD_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastbp")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Multiple accounts exist with the same Other Reference/Alternate Account Number.  Trade was processed for iFAST account %AccountNum%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Multiple accounts exist with the same Other Reference/Alternate Account Number.  Trade was processed for iFAST account %AccountNum%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("De multiples comptes existent avec le même autre numéro de référence/de compte. La transaction a été traitée pour le compte iFAST %AccountNum%.")); }

        // Actions
	};
}



